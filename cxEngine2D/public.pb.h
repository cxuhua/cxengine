/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.8-dev at Fri Nov 25 21:22:27 2016. */

#ifndef PB_PUBLIC_PB_H_INCLUDED
#define PB_PUBLIC_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _IndexType {
    int32_t tid;
    pb_callback_t code;
    pb_callback_t name;
    pb_callback_t icon_m;
    pb_callback_t icon_s;
    pb_callback_t as;
/* @@protoc_insertion_point(struct:IndexType) */
} IndexType;

/* Default values for struct fields */

/* Initializer values for message structs */
#define IndexType_init_default                   {0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define IndexType_init_zero                      {0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define IndexType_tid_tag                        1
#define IndexType_code_tag                       2
#define IndexType_name_tag                       3
#define IndexType_icon_m_tag                     4
#define IndexType_icon_s_tag                     5
#define IndexType_as_tag                         6

/* Struct field encoding specification for nanopb */
extern const pb_field_t IndexType_fields[7];

/* Maximum encoded size of messages (where known) */
/* IndexType_size depends on runtime parameters */

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define PUBLIC_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif