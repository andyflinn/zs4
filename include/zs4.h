#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

#include <zs4error.h>

typedef class zs4
{
public:
	class driver;
#define device char
#define intclass byte
#define symbolclass byteEvent
#define objectclass byteObject
	typedef char byte_t;
#include <zs4device.h>

#define device short
#define intclass word
#define symbolclass wordEvent
#define objectclass wordObject
	typedef short word_t;
#include <zs4device.h>

#define device long
#define intclass quad
#define symbolclass quadEvent
#define objectclass quadObject
	typedef long quad_t;
#include <zs4device.h>

#define device long long
#define intclass oct
#define symbolclass octEvent
#define objectclass octObject
	typedef long long oct_t;
#include <zs4device.h>

	class driver : public zs4::byte::object
	{
		byte_t _buf_[byte::MAX];
	protected:
#define DRIVER_TYPE(t) inline virtual const char * type(void){static const char * t = #t; return t;}
		DRIVER_TYPE(zs4)

	public:

		inline driver(zs4::byte::stream * in, zs4::byte::stream * out){
			zs4::byte::object::construct(NULL,(unsigned char*)_buf_, byte::MAX, in, out);
		}
	};

}zs4;

#endif
