
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

typedef struct jaeger_allocator {
    void* (*malloc)(struct jaeger_allocator*, size_t);
    void* (*realloc)(struct jaeger_allocator*, void*, size_t);
    void (*free)(struct jaeger_allocator*, void*);
} jaeger_allocator;

jaeger_allocator jaeger_default_alloc;

void* jaeger_default_alloc_malloc(size_t sz);

void* jaeger_default_alloc_realloc(void* ptr, size_t sz);

void jaeger_default_alloc_free(void* ptr);

#endif  // JAEGERTRACINGC_ALLOC_H