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

#include "jaegertracingc/hashtable.h"

#include "jaegertracingc/internal/random.h"
#include "jaegertracingc/siphash.h"

static uint8_t seed[16];

static inline void fill_seed()
{
    RANDOM_SEED(seed);
}

static uint8_t* hash_seed()
{
    static jaeger_once once;
    jaeger_do_once(&once, &fill_seed);
    return seed;
}

size_t jaeger_hashtable_hash(const char* key)
{
    return jaeger_siphash((const uint8_t*) key, strlen(key), hash_seed());
}

size_t jaeger_hashtable_minimal_order(size_t size)
{
#ifdef HAVE_BUILTIN
    return 1 << (sizeof(size_t) * CHAR_BIT - __builtin_clz(size));
#else
    size_t order = 0;
    for (; ((size_t) 1 << order) < size; order++)
        ;
    return order;
#endif /* HAVE_BUILTIN */
}
