/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: baggage.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "baggage.pb-c.h"
void   jaegertracing__protobuf__baggage__baggage_restriction__init
                     (Jaegertracing__Protobuf__Baggage__BaggageRestriction         *message)
{
  static const Jaegertracing__Protobuf__Baggage__BaggageRestriction init_value = JAEGERTRACING__PROTOBUF__BAGGAGE__BAGGAGE_RESTRICTION__INIT;
  *message = init_value;
}
size_t jaegertracing__protobuf__baggage__baggage_restriction__get_packed_size
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestriction *message)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t jaegertracing__protobuf__baggage__baggage_restriction__pack
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestriction *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t jaegertracing__protobuf__baggage__baggage_restriction__pack_to_buffer
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestriction *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Jaegertracing__Protobuf__Baggage__BaggageRestriction *
       jaegertracing__protobuf__baggage__baggage_restriction__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Jaegertracing__Protobuf__Baggage__BaggageRestriction *)
     protobuf_c_message_unpack (&jaegertracing__protobuf__baggage__baggage_restriction__descriptor,
                                allocator, len, data);
}
void   jaegertracing__protobuf__baggage__baggage_restriction__free_unpacked
                     (Jaegertracing__Protobuf__Baggage__BaggageRestriction *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   jaegertracing__protobuf__baggage__baggage_restriction_request__init
                     (Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest         *message)
{
  static const Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest init_value = JAEGERTRACING__PROTOBUF__BAGGAGE__BAGGAGE_RESTRICTION_REQUEST__INIT;
  *message = init_value;
}
size_t jaegertracing__protobuf__baggage__baggage_restriction_request__get_packed_size
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest *message)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_request__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t jaegertracing__protobuf__baggage__baggage_restriction_request__pack
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_request__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t jaegertracing__protobuf__baggage__baggage_restriction_request__pack_to_buffer
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_request__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest *
       jaegertracing__protobuf__baggage__baggage_restriction_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest *)
     protobuf_c_message_unpack (&jaegertracing__protobuf__baggage__baggage_restriction_request__descriptor,
                                allocator, len, data);
}
void   jaegertracing__protobuf__baggage__baggage_restriction_request__free_unpacked
                     (Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_request__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   jaegertracing__protobuf__baggage__baggage_restriction_response__init
                     (Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse         *message)
{
  static const Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse init_value = JAEGERTRACING__PROTOBUF__BAGGAGE__BAGGAGE_RESTRICTION_RESPONSE__INIT;
  *message = init_value;
}
size_t jaegertracing__protobuf__baggage__baggage_restriction_response__get_packed_size
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse *message)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_response__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t jaegertracing__protobuf__baggage__baggage_restriction_response__pack
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_response__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t jaegertracing__protobuf__baggage__baggage_restriction_response__pack_to_buffer
                     (const Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_response__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse *
       jaegertracing__protobuf__baggage__baggage_restriction_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse *)
     protobuf_c_message_unpack (&jaegertracing__protobuf__baggage__baggage_restriction_response__descriptor,
                                allocator, len, data);
}
void   jaegertracing__protobuf__baggage__baggage_restriction_response__free_unpacked
                     (Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_response__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor jaegertracing__protobuf__baggage__baggage_restriction__field_descriptors[2] =
{
  {
    "baggage_key",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Jaegertracing__Protobuf__Baggage__BaggageRestriction, baggage_key),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "max_value_length",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Jaegertracing__Protobuf__Baggage__BaggageRestriction, max_value_length),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned jaegertracing__protobuf__baggage__baggage_restriction__field_indices_by_name[] = {
  0,   /* field[0] = baggage_key */
  1,   /* field[1] = max_value_length */
};
static const ProtobufCIntRange jaegertracing__protobuf__baggage__baggage_restriction__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor jaegertracing__protobuf__baggage__baggage_restriction__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "jaegertracing.protobuf.baggage.BaggageRestriction",
  "BaggageRestriction",
  "Jaegertracing__Protobuf__Baggage__BaggageRestriction",
  "jaegertracing.protobuf.baggage",
  sizeof(Jaegertracing__Protobuf__Baggage__BaggageRestriction),
  2,
  jaegertracing__protobuf__baggage__baggage_restriction__field_descriptors,
  jaegertracing__protobuf__baggage__baggage_restriction__field_indices_by_name,
  1,  jaegertracing__protobuf__baggage__baggage_restriction__number_ranges,
  (ProtobufCMessageInit) jaegertracing__protobuf__baggage__baggage_restriction__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor jaegertracing__protobuf__baggage__baggage_restriction_request__field_descriptors[1] =
{
  {
    "service_name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest, service_name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned jaegertracing__protobuf__baggage__baggage_restriction_request__field_indices_by_name[] = {
  0,   /* field[0] = service_name */
};
static const ProtobufCIntRange jaegertracing__protobuf__baggage__baggage_restriction_request__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor jaegertracing__protobuf__baggage__baggage_restriction_request__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "jaegertracing.protobuf.baggage.BaggageRestrictionRequest",
  "BaggageRestrictionRequest",
  "Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest",
  "jaegertracing.protobuf.baggage",
  sizeof(Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest),
  1,
  jaegertracing__protobuf__baggage__baggage_restriction_request__field_descriptors,
  jaegertracing__protobuf__baggage__baggage_restriction_request__field_indices_by_name,
  1,  jaegertracing__protobuf__baggage__baggage_restriction_request__number_ranges,
  (ProtobufCMessageInit) jaegertracing__protobuf__baggage__baggage_restriction_request__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor jaegertracing__protobuf__baggage__baggage_restriction_response__field_descriptors[1] =
{
  {
    "restrictions",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse, n_restrictions),
    offsetof(Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse, restrictions),
    &jaegertracing__protobuf__baggage__baggage_restriction__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned jaegertracing__protobuf__baggage__baggage_restriction_response__field_indices_by_name[] = {
  0,   /* field[0] = restrictions */
};
static const ProtobufCIntRange jaegertracing__protobuf__baggage__baggage_restriction_response__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor jaegertracing__protobuf__baggage__baggage_restriction_response__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "jaegertracing.protobuf.baggage.BaggageRestrictionResponse",
  "BaggageRestrictionResponse",
  "Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse",
  "jaegertracing.protobuf.baggage",
  sizeof(Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse),
  1,
  jaegertracing__protobuf__baggage__baggage_restriction_response__field_descriptors,
  jaegertracing__protobuf__baggage__baggage_restriction_response__field_indices_by_name,
  1,  jaegertracing__protobuf__baggage__baggage_restriction_response__number_ranges,
  (ProtobufCMessageInit) jaegertracing__protobuf__baggage__baggage_restriction_response__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCMethodDescriptor jaegertracing__protobuf__baggage__baggage_restriction_manager__method_descriptors[1] =
{
  { "GetBaggageRestrictions", &jaegertracing__protobuf__baggage__baggage_restriction_request__descriptor, &jaegertracing__protobuf__baggage__baggage_restriction_response__descriptor },
};
const unsigned jaegertracing__protobuf__baggage__baggage_restriction_manager__method_indices_by_name[] = {
  0         /* GetBaggageRestrictions */
};
const ProtobufCServiceDescriptor jaegertracing__protobuf__baggage__baggage_restriction_manager__descriptor =
{
  PROTOBUF_C__SERVICE_DESCRIPTOR_MAGIC,
  "jaegertracing.protobuf.baggage.BaggageRestrictionManager",
  "BaggageRestrictionManager",
  "Jaegertracing__Protobuf__Baggage__BaggageRestrictionManager",
  "jaegertracing.protobuf.baggage",
  1,
  jaegertracing__protobuf__baggage__baggage_restriction_manager__method_descriptors,
  jaegertracing__protobuf__baggage__baggage_restriction_manager__method_indices_by_name
};
void jaegertracing__protobuf__baggage__baggage_restriction_manager__get_baggage_restrictions(ProtobufCService *service,
                                                                                             const Jaegertracing__Protobuf__Baggage__BaggageRestrictionRequest *input,
                                                                                             Jaegertracing__Protobuf__Baggage__BaggageRestrictionResponse_Closure closure,
                                                                                             void *closure_data)
{
  assert(service->descriptor == &jaegertracing__protobuf__baggage__baggage_restriction_manager__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void jaegertracing__protobuf__baggage__baggage_restriction_manager__init (Jaegertracing__Protobuf__Baggage__BaggageRestrictionManager_Service *service,
                                                                          Jaegertracing__Protobuf__Baggage__BaggageRestrictionManager_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &jaegertracing__protobuf__baggage__baggage_restriction_manager__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}