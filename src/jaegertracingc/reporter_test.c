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

#include "jaegertracingc/reporter.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "jaegertracingc/span.h"
#include "jaegertracingc/threading.h"
#include "jaegertracingc/tracer.h"
#include "unity.h"

#define MAX_PORT_LEN 5

static inline int start_udp_server()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    const int fd = socket(AF_INET, SOCK_DGRAM, 0);
    TEST_ASSERT_GREATER_OR_EQUAL(0, fd);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    TEST_ASSERT_EQUAL(0, bind(fd, (struct sockaddr*) &addr, sizeof(addr)));
    return fd;
}

static void* flush_reporter(void* arg)
{
    TEST_ASSERT_NOT_NULL(arg);
    jaeger_reporter* r = (jaeger_reporter*) arg;
    bool success = r->flush(r);
    bool* return_value = jaeger_malloc(sizeof(bool));
    TEST_ASSERT_NOT_NULL(return_value);
    *return_value = success;
    return return_value;
}

void test_reporter()
{
    jaeger_const_sampler const_sampler;
    jaeger_const_sampler_init(&const_sampler, true);

    jaeger_tracer tracer = JAEGERTRACINGC_TRACER_INIT;
    TEST_ASSERT_TRUE(jaeger_tracer_init(&tracer,
                                        "test-service",
                                        (jaeger_sampler*) &const_sampler,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL));
    TEST_ASSERT_NOT_NULL(tracer.service_name);

    jaeger_span span = JAEGERTRACINGC_SPAN_INIT;
    TEST_ASSERT_TRUE(jaeger_span_init(&span));
    span.context.flags = jaeger_sampling_flag_sampled;
    span.tracer = &tracer;

    TEST_ASSERT_NULL(span.operation_name);
    jaeger_span_set_operation_name((opentracing_span*) &span, "test-operation");
    TEST_ASSERT_NOT_NULL(span.operation_name);

    opentracing_log_field fields[2] = {
        {
            .key = "key1",
            .value = {.type = opentracing_value_string,
                      .value = {.string_value = "value"}},
        },
        {
            .key = "key2",
            .value = {.type = opentracing_value_bool,
                      .value = {.bool_value = true}},
        }};
    opentracing_log_record log = {
        .fields = fields, .num_fields = sizeof(fields[0]) / sizeof(fields)};
    jaeger_timestamp_now(&log.timestamp);
    jaeger_span_log((opentracing_span*) &span, log.fields, log.num_fields);

    jaeger_span_ref* span_ref_ptr = jaeger_vector_append(&span.refs);
    TEST_ASSERT_NOT_NULL(span_ref_ptr);
    span_ref_ptr->context =
        (jaeger_span_context){.trace_id = {.high = 0xDEAD, .low = 0xBEEF},
                              .span_id = 0xCAFE,
                              .parent_id = 0,
                              .flags = 0};
    span_ref_ptr->type = opentracing_span_reference_child_of;

    TEST_ASSERT_TRUE(
        jaeger_hashtable_put(&span.context.baggage, "key", "value"));
    jaeger_reporter* r = jaeger_null_reporter();
    r->report(r, &span);
    TEST_ASSERT_TRUE(r->flush(r));
    ((jaeger_destructible*) r)->destroy((jaeger_destructible*) r);

    jaeger_reporter reporter;
    jaeger_logging_reporter_init(&reporter);
    r = &reporter;
    r->report(r, &span);
    ((jaeger_destructible*) r)->destroy((jaeger_destructible*) r);

    jaeger_in_memory_reporter in_memory_reporter;
    TEST_ASSERT_TRUE(jaeger_in_memory_reporter_init(&in_memory_reporter));
    r = (jaeger_reporter*) &in_memory_reporter;
    r->report(r, &span);
    r->report(r, NULL);
    ((jaeger_destructible*) r)->destroy((jaeger_destructible*) r);

    /* Test allocation failure for in memory reporter. */
    TEST_ASSERT_TRUE(jaeger_in_memory_reporter_init(&in_memory_reporter));
    jaeger_set_allocator(jaeger_null_allocator());
    jaeger_in_memory_reporter fail_in_memory_reporter;
    TEST_ASSERT_FALSE(jaeger_in_memory_reporter_init(&fail_in_memory_reporter));
    for (int i = 0; i < JAEGERTRACINGC_VECTOR_INIT_CAPACITY; i++) {
        r->report(r, &span);
    }
    r->report(r, &span);
    jaeger_set_allocator(jaeger_built_in_allocator());
    ((jaeger_destructible*) r)->destroy((jaeger_destructible*) r);

    jaeger_composite_reporter composite_reporter;
    TEST_ASSERT_TRUE(jaeger_composite_reporter_init(&composite_reporter));
    r = (jaeger_reporter*) &composite_reporter;
    r->report(r, &span);
    r->report(r, NULL);
    TEST_ASSERT_TRUE(r->flush(r));
    ((jaeger_destructible*) r)->destroy((jaeger_destructible*) r);

    /* Test allocation failure for composite reporter. */
    jaeger_set_allocator(jaeger_null_allocator());
    TEST_ASSERT_FALSE(jaeger_composite_reporter_init(&composite_reporter));
    jaeger_set_allocator(jaeger_built_in_allocator());

    const int server_fd = start_udp_server();
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t addr_len = sizeof(addr);
    TEST_ASSERT_EQUAL(
        0, getsockname(server_fd, (struct sockaddr*) &addr, &addr_len));
    TEST_ASSERT_EQUAL(sizeof(addr), addr_len);
    char host_port[INET_ADDRSTRLEN + 1 + MAX_PORT_LEN];
    TEST_ASSERT_NOT_NULL(
        inet_ntop(AF_INET, &addr.sin_addr, host_port, sizeof(host_port)));
    const int host_end = strlen(host_port);
    TEST_ASSERT_LESS_THAN(sizeof(host_port) - host_end,
                          snprintf(&host_port[host_end],
                                   sizeof(host_port) - host_end,
                                   ":%d",
                                   ntohs(addr.sin_port)));

    jaeger_remote_reporter remote_reporter;
    char buffer[1024];
    jaeger_metrics* metrics = jaeger_null_metrics();
    r = (jaeger_reporter*) &remote_reporter;
    TEST_ASSERT_TRUE(jaeger_remote_reporter_init(
        &remote_reporter, host_port, sizeof(buffer), metrics));
    r = (jaeger_reporter*) &remote_reporter;
    for (int i = 0; i < 100; i++) {
        r->report(r, &span);
    }
    jaeger_thread thread;
    TEST_ASSERT_EQUAL(
        0, jaeger_thread_init(&thread, &flush_reporter, &remote_reporter));
    const int num_read = recv(server_fd, buffer, sizeof(buffer), 0);
    Jaeger__Model__Batch* batch =
        jaeger__model__batch__unpack(NULL, num_read, (const uint8_t*) buffer);
    TEST_ASSERT_NOT_NULL(batch);
    void* success = NULL;
    jaeger_thread_join(thread, &success);
    TEST_ASSERT_NOT_NULL(success);
    TEST_ASSERT_EQUAL(true, *(bool*) success);
    jaeger__model__batch__free_unpacked(batch, NULL);
    ((jaeger_destructible*) r)->destroy((jaeger_destructible*) r);
    jaeger_free(success);

    const int small_packet_size = 1;
    TEST_ASSERT_TRUE(jaeger_remote_reporter_init(
        &remote_reporter, host_port, small_packet_size, metrics));
    r->report(r, &span);
    TEST_ASSERT_EQUAL(
        0, jaeger_thread_init(&thread, &flush_reporter, &remote_reporter));
    success = NULL;
    jaeger_thread_join(thread, &success);
    TEST_ASSERT_NOT_NULL(success);
    TEST_ASSERT_EQUAL(false, *(bool*) success);
    jaeger_free(success);
    ((jaeger_destructible*) r)->destroy((jaeger_destructible*) r);

    close(server_fd);
    jaeger_span_destroy((jaeger_destructible*) &span);

    jaeger_tracer_destroy((jaeger_destructible*) &tracer);

    ((jaeger_destructible*) &const_sampler)
        ->destroy((jaeger_destructible*) &const_sampler);
}
