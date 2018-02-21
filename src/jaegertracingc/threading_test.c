/*
 * Copyright (c) 2018 Uber Technologies, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "jaegertracingc/threading.h"
#include "jaegertracingc/clock.h"
#include "jaegertracingc/logging.h"
#include "unity.h"

#define NUM_PHILOSOPHERS 5
#define NUM_ATTEMPTS 10
#define MAX_EAT_TIME 50
#define MAX_THINK_TIME (MAX_EAT_TIME / 2)
#define MAX_JITTER MAX_THINK_TIME
#define NS_PER_MS 1000000

static inline double random_value(int max)
{
    return (((double) rand()) / RAND_MAX) * max;
}

static inline int random_int(int max)
{
    return random_value(max);
}

typedef struct philosopher {
    jaeger_thread thread;
    int id;
    jaeger_mutex* left_fork;
    jaeger_mutex* right_fork;
    jaeger_duration* start_time;
    jaeger_logger* logger;
} philosopher;

static void* philosopher_func(void* arg)
{
    TEST_ASSERT_NOT_NULL(arg);
    philosopher* p = arg;

    jaeger_duration duration = {.tv_sec = 0,
                                .tv_nsec = random_int(MAX_JITTER) * NS_PER_MS};
    nanosleep(&duration, NULL);

    for (int i = 0; i < NUM_ATTEMPTS; i++) {
        jaeger_duration current_time;
        jaeger_duration elapsed_time;

        jaeger_duration_now(&current_time);
        TEST_ASSERT_TRUE(jaeger_duration_subtract(
            &current_time, p->start_time, &elapsed_time));
        p->logger->info(p->logger,
                        "%0.4f: Philosopher %d thinking\n",
                        elapsed_time.tv_sec +
                            ((double) elapsed_time.tv_nsec) /
                                JAEGERTRACINGC_NANOSECONDS_PER_SECOND,
                        p->id);
        duration.tv_nsec = random_int(MAX_THINK_TIME) * NS_PER_MS;
        nanosleep(&duration, NULL);

        jaeger_lock(p->left_fork, p->right_fork);
        jaeger_duration_now(&current_time);
        TEST_ASSERT_TRUE(jaeger_duration_subtract(
            &current_time, p->start_time, &elapsed_time));
        p->logger->info(p->logger,
                        "%0.4f: Philosopher %d eating\n",
                        elapsed_time.tv_sec +
                            ((double) elapsed_time.tv_nsec) /
                                JAEGERTRACINGC_NANOSECONDS_PER_SECOND,
                        p->id);
        duration.tv_nsec = random_int(MAX_EAT_TIME) * NS_PER_MS;
        jaeger_mutex_unlock(p->left_fork);
        jaeger_mutex_unlock(p->right_fork);
    }

    return NULL;
}

void test_threading()
{
    srand(time(NULL));

    jaeger_duration start_time;
    jaeger_duration_now(&start_time);

    jaeger_mutex forks[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        forks[i] = (jaeger_mutex) JAEGERTRACINGC_MUTEX_INIT;
    }

    jaeger_logger* logger = jaeger_null_logger();
    philosopher philosophers[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher* p = &philosophers[i];
        memset(p, 0, sizeof(*p));
        p->id = i;
        p->logger = logger;
        p->left_fork = &forks[i];
        p->right_fork = &forks[(i + 1) % NUM_PHILOSOPHERS];
        p->start_time = &start_time;
        jaeger_thread_init(&p->thread, &philosopher_func, p);
        logger->info(logger,
                     "Philosopher %lu assigned forks %d and %d\n",
                     p->thread,
                     i,
                     (i + 1) % NUM_PHILOSOPHERS);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        jaeger_thread_join(philosophers[i].thread, NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        jaeger_mutex_destroy(&forks[i]);
    }
}