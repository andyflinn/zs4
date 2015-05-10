#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

//#include <zs4config.h>
#include <zs4error.h>

typedef class zs4
{
public:

#define device char
#define intclass byte
#define eventclass byteEvent
#define objectclass byteObject
#define type_t byte_t
#include <zs4device.h>

#define device short
#define intclass word
#define eventclass wordEvent
#define objectclass wordObject
#define type_t word_t
#include <zs4device.h>

#define device long
#define intclass quad
#define eventclass quadEvent
#define objectclass quadObject
#define type_t quad_t
#include <zs4device.h>

#define device long long
#define intclass oct
#define eventclass octEvent
#define objectclass octObject
#define type_t oct_t
#include <zs4device.h>

}zs4;

#endif
