#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

#include <zs4error.h>

typedef class zs4
{
public:

#define device char
#define intclass byte
#define symbolclass byteEvent
#define objectclass byteObject
#define type_t byte_t
#include <zs4device.h>

#define device short
#define intclass word
#define symbolclass wordEvent
#define objectclass wordObject
#define type_t word_t
#include <zs4device.h>

#define device long
#define intclass quad
#define symbolclass quadEvent
#define objectclass quadObject
#define type_t quad_t
#include <zs4device.h>

#define device long long
#define intclass oct
#define symbolclass octEvent
#define objectclass octObject
#define type_t oct_t
#include <zs4device.h>

}zs4;

#endif
