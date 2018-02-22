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

#ifndef JAEGERTRACINGC_ALLOC_H
#define JAEGERTRACINGC_ALLOC_H

#include "jaegertracingc/common.h"
#include "jaegertracingc/logging.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct jaeger_allocator {
    void* (*malloc)(struct jaeger_allocator*, size_t);
    void* (*realloc)(struct jaeger_allocator*, void*, size_t);
    void (*free)(struct jaeger_allocator*, void*);
} jaeger_allocator;

jaeger_allocator* jaeger_built_in_allocator();

jaeger_allocator* jaeger_null_allocator();

extern jaeger_allocator* jaeger_alloc;

static inline void* jaeger_malloc(size_t sz)
{
    return jaeger_alloc->malloc(jaeger_alloc, sz);
}

static inline void* jaeger_realloc(void* ptr, size_t sz)
{
    return jaeger_alloc->realloc(jaeger_alloc, ptr, sz);
}

static inline void jaeger_free(void* ptr)
{
    jaeger_alloc->free(jaeger_alloc, ptr);
}

static inline char* jaeger_strdup_alloc(const char* str,
                                        jaeger_allocator* alloc,
                                        jaeger_logger* logger)
{
    if (alloc == NULL) {
        alloc = jaeger_built_in_allocator();
    }
    const int size = strlen(str) + 1;
    char* copy = alloc->malloc(alloc, size);
    if (copy == NULL) {
        logger->error(logger, "Cannot allocate string copy, size = %d", size);
        return NULL;
    }
    memcpy(copy, str, size);
    return copy;
}

static inline char* jaeger_strdup(const char* str, jaeger_logger* logger)
{
    return jaeger_strdup_alloc(str, NULL, logger);
}

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* JAEGERTRACINGC_ALLOC_H */
