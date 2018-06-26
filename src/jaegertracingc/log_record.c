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

#include "jaegertracingc/log_record.h"

void jaeger_log_record_destroy(jaeger_log_record* log_record)
{
    if (log_record == NULL) {
        return;
    }
    JAEGERTRACINGC_VECTOR_FOR_EACH(
        &log_record->fields, jaeger_tag_destroy, jaeger_tag);
    jaeger_vector_destroy(&log_record->fields);
}

bool jaeger_log_record_init(jaeger_log_record* log_record)
{
    assert(log_record != NULL);
    jaeger_timestamp_now(&log_record->timestamp);
    return jaeger_vector_init(&log_record->fields, sizeof(jaeger_tag));
}

bool jaeger_log_record_copy(jaeger_log_record* restrict dst,
                            const jaeger_log_record* restrict src)
{
    assert(dst != NULL);
    assert(src != NULL);
    if (!jaeger_log_record_init(dst) ||
        !jaeger_vector_copy(
            &dst->fields, &src->fields, &jaeger_tag_copy_wrapper, NULL)) {
        jaeger_log_record_destroy(dst);
        return false;
    }
    dst->timestamp = src->timestamp;
    return true;
}

bool jaeger_log_record_from_opentracing(
    jaeger_log_record* restrict dst, const opentracing_log_record* restrict src)
{
    if (!jaeger_log_record_init(dst) ||
        !jaeger_vector_reserve(&dst->fields, src->num_fields)) {
        goto cleanup;
    }
    for (int i = 0; i < src->num_fields; i++) {
        jaeger_tag* tag = jaeger_vector_append(&dst->fields);
        assert(tag != NULL);
        if (!jaeger_tag_from_key_value(
                tag, src->fields[i].key, &src->fields[i].value)) {
            dst->fields.len--;
        }
    }
    dst->timestamp = src->timestamp;
    return true;

cleanup:
    jaeger_log_record_destroy(dst);
    return false;
}

void jaeger_log_record_protobuf_destroy(
    Jaegertracing__Protobuf__Log* log_record)
{
    if (log_record == NULL || log_record->fields == NULL) {
        return;
    }

    for (int i = 0; i < (int) log_record->n_fields; i++) {
        if (log_record->fields[i] != NULL) {
            jaeger_tag_destroy(log_record->fields[i]);
            jaeger_free(log_record->fields[i]);
        }
    }
    jaeger_free(log_record->fields);
    *log_record =
        (Jaegertracing__Protobuf__Log) JAEGERTRACING__PROTOBUF__LOG__INIT;
}

bool jaeger_log_record_to_protobuf(Jaegertracing__Protobuf__Log* restrict dst,
                                   const jaeger_log_record* restrict src)
{
    assert(dst != NULL);
    assert(src != NULL);
    *dst = (Jaegertracing__Protobuf__Log) JAEGERTRACING__PROTOBUF__LOG__INIT;
#ifdef JAEGERTRACINGC_HAVE_PROTOBUF_OPTIONAL_FIELDS
    dst->has_timestamp = true;
#endif /* JAEGERTRACINGC_HAVE_PROTOBUF_OPTIONAL_FIELDS */
    dst->timestamp = jaeger_timestamp_microseconds(&src->timestamp);
    if (!jaeger_vector_protobuf_copy((void***) &dst->fields,
                                     &dst->n_fields,
                                     &src->fields,
                                     sizeof(jaeger_tag),
                                     &jaeger_tag_copy_wrapper,
                                     &jaeger_tag_destroy_wrapper,
                                     NULL)) {
        jaeger_log_record_protobuf_destroy(dst);
        *dst =
            (Jaegertracing__Protobuf__Log) JAEGERTRACING__PROTOBUF__LOG__INIT;
        return false;
    }
    return true;
}
