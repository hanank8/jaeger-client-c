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

/**
 * @file
 * Key value pair representation.
 */

#ifndef JAEGERTRACINGC_KEY_VALUE_H
#define JAEGERTRACINGC_KEY_VALUE_H

#include "jaegertracingc/alloc.h"
#include "jaegertracingc/common.h"
#include "jaegertracingc/logging.h"
#include "jaegertracingc/vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct jaeger_key_value {
    char* key;
    char* value;
} jaeger_key_value;

#define JAEGERTRACINGC_KEY_VALUE_INIT \
    {                                 \
        .key = NULL, .value = NULL    \
    }

void jaeger_key_value_destroy(jaeger_key_value* kv);

bool jaeger_key_value_init(jaeger_key_value* kv,
                           const char* key,
                           const char* value);

bool jaeger_key_value_copy(jaeger_key_value* restrict dst,
                           const jaeger_key_value* restrict src);

JAEGERTRACINGC_WRAP_COPY(jaeger_key_value_copy,
                         jaeger_key_value,
                         jaeger_key_value)

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* JAEGERTRACINGC_KEY_VALUE_H */
