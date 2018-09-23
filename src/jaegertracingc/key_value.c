/*
 * Copyright (c) 2018 The Jaeger Authors.
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

#include "jaegertracingc/key_value.h"

void jaeger_key_value_destroy(jaeger_key_value* kv)
{
    if (kv == NULL) {
        return;
    }
    if (kv->key != NULL) {
        jaeger_free(kv->key);
        kv->key = NULL;
    }
    if (kv->value != NULL) {
        jaeger_free(kv->value);
        kv->value = NULL;
    }
}

bool jaeger_key_value_init(jaeger_key_value* kv,
                           const char* key,
                           const char* value)
{
    assert(kv != NULL);
    assert(key != NULL);
    assert(value != NULL);
    *kv = (jaeger_key_value) JAEGERTRACINGC_KEY_VALUE_INIT;
    kv->key = jaeger_strdup(key);
    if (kv->key == NULL) {
        goto cleanup;
    }
    kv->value = jaeger_strdup(value);
    if (kv->value == NULL) {
        goto cleanup;
    }
    return true;

cleanup:
    jaeger_key_value_destroy(kv);
    return false;
}

bool jaeger_key_value_copy(jaeger_key_value* restrict dst,
                           const jaeger_key_value* restrict src)
{
    assert(dst != NULL);
    assert(src != NULL);
    return jaeger_key_value_init(dst, src->key, src->value);
}
