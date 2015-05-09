#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

#include <zs4config.h>

typedef class zs4
{
public:
	class stream;
	typedef enum {
		SUCCESS = 0,
		FAILURE,
		WAITING,
		BUFFEROVERFLOW,
		NODATA,
		NOMEMORY,
		NOTFOUND,
		ALREADYEXISTS,
		BADNAME,
		FILEINFOERROR,
		FILEOPENERROR,
		ERRORCOUNT
	}e;
	typedef class event {
	public:
		typedef class set
		{
		protected:
			inline static const ZS4CHAR * ASCII(void){
				static const ZS4CHAR ASCII[128] = {
					0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
					0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
					0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
					0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
					0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
					0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
					0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
					0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
				};
				return ASCII;
			}
			inline bool valueReverse(){ return false; }
		public:
			inline virtual const ZS4CHAR count(void) = 0;
			inline virtual const ZS4CHAR * data(void) = 0;
			inline ZS4CHAR lookup(ZS4CHAR event){

				for (ZS4LARGE i = 0; i < count(); i++){
					if ((ZS4CHAR)data()[i] == (ZS4CHAR)event)
					{
						if (valueReverse()) { return (ZS4CHAR)(count() - i); }
						return (ZS4CHAR)i;
					}
				}
				return (ZS4CHAR)(~0);
			}
			inline ZS4CHAR bits(void){
				ZS4CHAR m = 0x7f;
				ZS4CHAR r = 7;
				while (((m >> 1)&((ZS4CHAR)count())) >= count()){
					m >>= 1; r--;
				}
				return r;
			}
		}set;

		typedef class name : public set
		{
		public:
			inline virtual const ZS4CHAR count(void){ return 26; }
			inline virtual const ZS4CHAR * data(void){
				return &(ASCII())['a'];
			}

		}name;

		typedef class space : public set
		{
		public:
			typedef enum {
				s, a, b, f, n, r, t, v,
				SIZE
			} index;
			inline virtual const ZS4CHAR count(void){ return SIZE; }
			inline virtual const ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = { ' ', '\a', '\b', '\f', '\n', '\r', '\t', '\v' };
				return data;
			}

		}space;

		typedef class numeric : public set
		{
		public:
			typedef enum {
				n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
				SIZE
			} index;
			inline virtual const ZS4CHAR count(void){ return (ZS4CHAR)SIZE; }
			inline virtual const ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
				return data;
			}
		}numeric;
		typedef class binary : public numeric
		{
		public:
			inline virtual const ZS4CHAR count(void){ return 2; }
		}binary;
		typedef class octal : public numeric
		{
		public:
			inline virtual const ZS4CHAR count(void){ return 8; }
		}octal;
		typedef class decimal : public numeric
		{
		public:
			inline virtual const ZS4CHAR count(void){ return 10; }
		}decimal;
		typedef class hexadecimal : public numeric
		{
		public:
			inline virtual const ZS4CHAR count(void){ return 16; }
		}hexadecimal;

		typedef class opcode : public set
		{
		public:
			typedef enum {
				_equal_, _or_, _and_, _plus_, _minus_,
				SIZE
			} index;
			inline virtual const ZS4CHAR count(void){ return (ZS4CHAR)SIZE; }
			inline virtual const ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = {
					'=', '|', '&', '+', '-' };
				return data;
			}

		}opcode;
		typedef class container : public set
		{
		public:
			typedef enum {
				parenthesis, curly, square,less,
				SIZE
			} index;
			inline virtual const ZS4CHAR count(void){ return (ZS4CHAR)SIZE; }

			inline virtual const ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = {
					'(', '{', '[', '<' };
				return data;
			}

			inline virtual const ZS4CHAR * end(void){
				static ZS4CHAR data[SIZE] = {
					')', '}', ']', '>' };
				return data;
			}

		}container;

		template <class eventset>
		bool is(ZS4CHAR c){
			eventset set;
			if ((ZS4CHAR)(~0) == set.lookup(c))
				return false;
			return true;
		}
	}event;

	typedef class storage
	{
	public:

		inline virtual ZS4LARGE bits(void)const{ return (sizeof(*this) << 3); }
		#define	INLINE_BITS_FUNCTION() inline virtual ZS4LARGE bits(void)const

		inline virtual void reset(void){};
		#define	INLINE_RESET_FUNCTION() inline virtual void reset(void)

		#define INLINE_CONNECT_FUNCTION() inline virtual e connect(stream * in, stream * out)
		#define INLINE_ONCHAR_FUNCTION() inline virtual e onChar(char & c)
		#define INLINE_ONLINE_FUNCTION() inline virtual e onLine(char * str)

		inline virtual ZS4LARGE p8(void)const{ if (ZS4LARGE r = (bits() >> 3))return r; return 1; }
		inline virtual ZS4LARGE p16(void)const{ if (ZS4LARGE r = (bits() >> 4))return r; return 1; }
		inline virtual ZS4LARGE p32(void)const{ if (ZS4LARGE r = (bits() >> 5))return r; return 1; }
		inline virtual ZS4LARGE p64(void)const{ if (ZS4LARGE r = (bits() >> 6))return r; return 1; }

		inline virtual ZS4LARGE addressBits(void)const{ ZS4LARGE w = 1; while (((ZS4LARGE)1 << w)<bits())w++; return w; }
		inline virtual ZS4LARGE messageBits(void)const{ return (bits() - addressBits()); }

	}storage;

	typedef class stream : public storage{
	public:
		inline stream(){}
		inline virtual e read(char & c){
			return FAILURE;
		}
		#define	INLINE_READ_FUNCTION() inline virtual e read(char & c)
		inline virtual e write(char c){
			return FAILURE;
		}
		#define	INLINE_WRITE_FUNCTION() inline virtual e write(char c)
		inline virtual ZS4LARGE readable(void){
			return 0;
		}
		#define	INLINE_READABLE_FUNCTION() inline virtual ZS4LARGE readable(void)
		inline virtual ZS4LARGE writeable(void){
			return 0;
		}
		#define	INLINE_WRITEABLE_FUNCTION() inline virtual ZS4LARGE writeable(void)
		inline virtual e flush(void){
			return FAILURE;
		}
		#define	INLINE_FLUSH_FUNCTION() inline virtual e flush(void)
		inline virtual e close(void){
			return FAILURE;
		}
		#define	INLINE_CLOSE_FUNCTION() inline virtual e close(void)
		inline virtual e rewind(void){
			return seek(0, SEEK_SET);
		}
		#define	INLINE_REWIND_FUNCTION() inline virtual e rewind(void)
		inline virtual e seekEnd(void){
			return seek(0, SEEK_END);
		}
		#define	INLINE_SEEKEND_FUNCTION() inline virtual e seekEnd(void)
		inline virtual e seek(ZS4LARGE offset, int origin){
			return FAILURE;
		}
		#define	INLINE_SEEK_FUNCTION() inline virtual e seek(ZS4LARGE offset, int origin)
		inline virtual e tell(ZS4LARGE & pPos){
			return FAILURE;
		}
		#define	INLINE_TELL_FUNCTION() inline virtual e tell(ZS4LARGE & pPos)
		inline virtual e size(ZS4LARGE & s){
			e err;
			ZS4LARGE pos = 0;
			ZS4LARGE size = 0;

			if ((err = tell(pos)) != SUCCESS)
				return err;

			if ((err = seek(0, SEEK_END)) != SUCCESS)
				return err;

			if ((err = tell(size)) != SUCCESS)
				return err;

			if ((err = seek(pos, SEEK_SET)) != SUCCESS)
				return err;

			s = size;

			return SUCCESS;
		}
		#define	INLINE_SIZE_FUNCTION() inline virtual e size(ZS4LARGE & s)

		inline virtual e writeString(const char * str){
			if (str == nullptr || (*str) == 0)
				return NODATA;

			unsigned char len = (unsigned char)strlen(str);
			for (unsigned char i = 0; i < len; i++){
				if (SUCCESS != write(str[i]))
					return FAILURE;
			}
			return SUCCESS;
		}
		#define	INLINE_WRITESTRING_FUNCTION() inline virtual e write(const char * str)

		inline e writeInteger(unsigned long long data, unsigned char base = 10){

			if (data & (1 << 63))
			{
				if (SUCCESS != write('-'))
					return FAILURE;

				data = (~data);
			}


			ZS4LARGE remainder = data;
			bool NOT_ZERO = false;

			ZS4LARGE MAX = (~0);
			ZS4LARGE count = 1;
			ZS4LARGE large = 1;
			while (large < (MAX / base)){
				large *= base; count++;
			}

			zs4::event::numeric numeric;
			ZS4LARGE accumulator;
			while (count)
			{
				if (0 != (accumulator = remainder / large))
				{
					remainder -= (accumulator*large);
					NOT_ZERO = true;
				}

				if (NOT_ZERO){
					if (SUCCESS != write((char)(numeric.data()[accumulator])))
						return BUFFEROVERFLOW;
				}

				large /= base;
				count--;
			}

			if (!NOT_ZERO)
			{
				if (SUCCESS != write((char)(numeric.data()[0])))
					return BUFFEROVERFLOW;
			}
			return SUCCESS;
		}
		inline e writeJsonString(const char * out)
		{
			for (const char * str = out; str && *str; str++)
			{
				switch (*str)
				{
				case '\\': if (SUCCESS != writeString("\\\\"))return FAILURE; break;
				case '"': if (SUCCESS != writeString("\\\""))return FAILURE; break;
				case '/': if (SUCCESS != writeString("\\/"))return FAILURE; break;
				case '\b': if (SUCCESS != writeString("\\b"))return FAILURE; break;
				case '\f': if (SUCCESS != writeString("\\f"))return FAILURE; break;
				case '\n': if (SUCCESS != writeString("\\n"))return FAILURE; break;
				case '\r': if (SUCCESS != writeString("\\r"))return FAILURE; break;
				case '\t': if (SUCCESS != writeString("\\t"))return FAILURE; break;
				default: if (SUCCESS != write(*str))return FAILURE; break;
				}
			}
			return SUCCESS;
		}
	}stream;

#	include <zs4util.h>

	#define device char
	#define devicename "p8"
	#define bussclass p8
	#define objectclass o8
	#define readfunction(t,f) t f ## _ ## p8(void)
	#define writefunction(t,f,a) t f ## _ ## p8(p8 a)
	#include <zs4device.h>
	#undef writefunction
	#undef readfunction
	#undef objectclass
	#undef bussclass
	#undef devicename
	#undef device

	#define device short
	#define devicename "p16"
	#define bussclass p16
	#define objectclass o16
	#define readfunction(t,f) t f ## _ ## p16(void)
	#define writefunction(t,f,a) t f ## _ ## p16(p16 a)
	#include <zs4device.h>
	#undef writefunction
	#undef readfunction
	#undef objectclass
	#undef bussclass
	#undef devicename
	#undef device

	#define device long
	#define bussclass p32
	#define objectclass o32
	#define devicename "p32"
	#define readfunction(t,f) t f ## _ ## p32(void)
	#define writefunction(t,f,a) t f ## _ ## p32(p32 a)
	#include <zs4device.h>
	#undef writefunction
	#undef readfunction
	#undef objectclass
	#undef bussclass
	#undef devicename
	#undef device

	#define device long long
	#define bussclass p64
	#define objectclass o64
	#define devicename "p64"
	#define readfunction(t,f) t f ## _ ## p64(void)
	#define writefunction(t,f,a) t f ## _ ## p64(p64 a)
	#include <zs4device.h>
	#undef writefunction
	#undef readfunction
	#undef objectclass
	#undef bussclass
	#undef devicename
	#undef device

}zs4;

#endif
