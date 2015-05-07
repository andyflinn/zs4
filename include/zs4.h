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
			inline virtual const ZS4CHAR count(void) = 0;
			inline virtual const ZS4CHAR * data(void) = 0;
		public:
			inline ZS4CHAR lookup(ZS4CHAR event, ZS4CHAR range = 10){

				for (ZS4LARGE i = 0; (i < range) && (i < count()); i++){
					if ((ZS4CHAR)data()[i] == (ZS4CHAR)event)
						return (ZS4CHAR)i;
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
				equal, or, and, plus, minus,
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


	}event;


	typedef class storage
	{
	public:
		inline virtual char * memory(void)const = 0;
		#define	INLINE_MEMORY_FUNCTION() inline virtual char * memory(void)const

		inline virtual ZS4LARGE bits(void)const{ return (sizeof(*this) << 3); }
		#define	INLINE_BITS_FUNCTION() inline virtual ZS4LARGE bits(void)const

		inline virtual void reset(void){};
		#define	INLINE_RESET_FUNCTION() inline virtual void reset(void)
		
		#define INLINE_INSTANCE(type) inline type(char * m, ZS4LARGE s)

		inline virtual e connect(stream * in, stream * out){ return FAILURE; }
		#define INLINE_CONNECT_FUNCTION() inline virtual e connect(stream * in, stream * out)

		inline virtual e tickle(void){ return SUCCESS; }
		#define INLINE_TICKLE_FUNCTION() inline virtual e tickle(void)

		inline virtual e onChar(char & c){ return FAILURE; }
		#define INLINE_ONCHAR_FUNCTION() inline virtual e onChar(char & c)

		inline virtual ZS4LARGE p8(void)const{ if (ZS4LARGE r = (bits() >> 3))return r; return 1; }
		inline virtual ZS4LARGE p16(void)const{ if (ZS4LARGE r = (bits() >> 4))return r; return 1; }
		inline virtual ZS4LARGE p32(void)const{ if (ZS4LARGE r = (bits() >> 5))return r; return 1; }
		inline virtual ZS4LARGE p64(void)const{ if (ZS4LARGE r = (bits() >> 6))return r; return 1; }

		inline virtual ZS4LARGE addressBits(void)const{ ZS4LARGE w = 1; while (((ZS4LARGE)1 << w)<bits())w++; return w; }
		inline virtual ZS4LARGE messageBits(void)const{ return (bits() - addressBits()); }

	}storage;

	#define device char 
	#define devicename "p8" 
	#define bussclass p8 
	#define readfunction(t,f) t f ## _ ## p8(void)
	#define writefunction(t,f,a) t f ## _ ## p8(p8 a)
	#include <zs4device.h>
	#undef writefunction 
	#undef readfunction 
	#undef bussclass 
	#undef devicename 
	#undef device 

	#define device short 
	#define devicename "p16" 
	#define bussclass p16 
	#define readfunction(t,f) t f ## _ ## p16(void)
	#define writefunction(t,f,a) t f ## _ ## p16(p16 a)
	#include <zs4device.h>
	#undef writefunction 
	#undef readfunction 
	#undef bussclass 
	#undef devicename 
	#undef device 

	#define device long 
	#define bussclass p32 
	#define devicename "p32" 
	#define readfunction(t,f) t f ## _ ## p32(void)
	#define writefunction(t,f,a) t f ## _ ## p32(p32 a)
	#include <zs4device.h>
	#undef writefunction 
	#undef readfunction 
	#undef bussclass 
	#undef devicename 
	#undef device 

	#define device long long
	#define bussclass p64 
	#define devicename "p64" 
	#define readfunction(t,f) t f ## _ ## p64(void)
	#define writefunction(t,f,a) t f ## _ ## p64(p64 a)
	#include <zs4device.h>
	#undef writefunction 
	#undef readfunction 
	#undef bussclass 
	#undef devicename 
	#undef device 

#	include <zs4util.h>

	typedef class machine : public stream
	{
		char * store;
		ZS4LARGE storesize;
		inline bool valid(void)const{
			if (storesize < (2 * sizeof(info)))
				return false;
			return true;
		}
	protected:
		INLINE_MEMORY_FUNCTION(){ return store; }
		INLINE_BITS_FUNCTION(){ return (storesize << 3); }
		INLINE_RESET_FUNCTION(){ memset(store, 0, storesize); }

		typedef struct info {
			stream * in;
			stream * out;
			char * str;
			unsigned long len, pos, siz;
		}info;
		inline struct info * getInfo(void){
			if (!valid())
				return nullptr;

			struct info * info = (struct info*)store;
			info->str = (char*)&info[1];
			info->siz = storesize - sizeof(struct info);

			return info;
		}

		inline virtual e jStart(const char * n = nullptr){ if (n != nullptr) { write('"'); writeString(n); write('"'); write(':'); }; return write('{'); }
		inline virtual e jEnd(){ return write('}'); }
		inline virtual e onj(void){
			
			jStart();
			{
				jStart("zs4");
				{
					jStart("c"); //constants
					{
						jStart("m"); // memory
						{
							jStart("s"); // size
							{
								writeString("\"a\":"); // available
								writeInteger(storesize - sizeof(struct info));
								write(',');

								writeString("\"t\":"); // total
								writeInteger(storesize);
								write(',');

								writeString("\"u\":"); // used
								writeInteger(sizeof(struct info));
								write(',');

								jStart("p"); // persistent
								{
									jStart("s"); // size
									{
										writeString("\"a\":"); // available
										writeInteger(0);
										write(',');

										writeString("\"t\":"); // total
										writeInteger(0);
										write(',');

										writeString("\"u\":"); // used
										writeInteger(0);
									}
									jEnd(); //p
								}
								jEnd(); //persistent
							}
							jEnd(); // size
						}
						jEnd(); // memory
					}
					jEnd(); //constant
				}
				jEnd();
			}
			jEnd();

			write('\n');

			return rewind();
		}

		INLINE_ONCHAR_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr || info->in == nullptr || info->out == nullptr) return FAILURE;

			if (info->len < 1)
				return FAILURE;

			if (info->str[info->len - 1] == '\n')
			{
				rewind();
				if (!strcmp(info->str, "?\n")){ onj(); }
				if (!strcmp(info->str, "j\n")){ onj(); }

				return SUCCESS;
			}

			return WAITING;
		}
	public:
		INLINE_INSTANCE(machine){ store = m; storesize = s; reset(); }
		INLINE_CONNECT_FUNCTION(){
			info * info = getInfo();
			if (info == nullptr) return FAILURE;
			info->in = in;
			info->out = out;
			return SUCCESS;
		}
		INLINE_TICKLE_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr || info->in == nullptr || info->out == nullptr) return FAILURE;

			char c = 0;
			e error = SUCCESS;

			for (;;){
				if (error = info->in->read(c))
					return error;

				if (error = write(c))
					return error;

				error = onChar(c);
				if (error == WAITING)
					continue;

				if (error)
					return error;

				break;
			}

			info->out->writeString((const char *)info->str);

			rewind();

			return SUCCESS;
		}

		INLINE_READABLE_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr) return 0;
			return (info->len - info->pos);
		}
		INLINE_WRITEABLE_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr) return 0;
			return (info->siz - info->pos);
		}

		INLINE_READ_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr) return FAILURE;
			if (info->len == 0 || info->pos >= info->len || info->pos >= (info->siz - 1))
				return FAILURE;

			c = info->str[info->pos]; info->pos++;

			return SUCCESS;
		}
		INLINE_WRITE_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr) return FAILURE;
			if (info->pos >= (info->siz - 1))
				return FAILURE;

			info->str[info->pos++] = c;
			info->str[info->pos] = 0;
			info->len = info->pos;

			return SUCCESS;
		}
		INLINE_SEEK_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr) return FAILURE;

			ZS4LARGE adj = info->len;
			if (origin == SEEK_SET) { adj = 0; }
			else if (origin == SEEK_CUR) { adj = info->pos; }

			offset += adj;

			if (offset < 0)
			{
				info->pos = 0; return FAILURE;
			}
			if (offset > info->len)
			{
				info->pos = info->len; return FAILURE;
			}
			info->pos = offset; return SUCCESS;
		}
		INLINE_TELL_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr) return FAILURE;
			pPos = info->pos;
			return SUCCESS;
		}
		INLINE_SIZE_FUNCTION(){
			struct info * info = getInfo();
			if (info == nullptr) return FAILURE;
			s = info->len;
			return SUCCESS;
		}

		inline bool check(void){
			if (!valid())return false;

			struct info * info = getInfo();

			if (info->str && info->str[0] && info->len)
				return true;

			return false;
		}
		inline e trim(void){
			struct info * info = getInfo();
			if (info == nullptr) return FAILURE;

			char * s = info->str; unsigned char lead = 0;

			if (s == nullptr)
				return FAILURE;

			while (s && *s && isspace(*s)) { lead++; s++; }

			if (lead>0)
				strcpy(info->str, s);

			info->len = (unsigned char)strlen(info->str);
			while (info->len > 0)
			{
				if (!isspace(info->str[info->len - 1]))
					break;

				info->len--;
				info->str[info->len] = 0;
			}

			info->pos = info->len;

			return SUCCESS;
		}
		inline const char ** tokenize(const char * s, const char * sep){
			struct info * info = getInfo();
			if (info == nullptr) return nullptr;

			unsigned char count = 0;
			if ((s == nullptr)
				|| (*s == 0)
				|| (sep == nullptr)
				|| (*sep == 0)
				|| (info->str == 0)
				|| (info->siz == 0)
				)
				return nullptr;

			info->pos = info->len = 0;

			// count separators
			int sep_count = c::strcharcount(s, sep) + 1;

			if (info->siz <= (sep_count*sizeof(const char *)))
				return nullptr;

			const char ** cpp = (const char**)info->str;
			for (int i = 0; i <= sep_count; i++)
			{
				cpp[i] = nullptr;
				info->len += sizeof(const char *);
			}

			// skip leading spaces and separators;
			while ((*s) && (isspace(*s) || c::strcharcount(sep, *s))) s++;
			if (*s == 0)
				return nullptr;

			while (*s)
			{
				while (*s != 0 && 0 == c::strcharcount(sep, *s))s++;
				if (*s == 0)
					return nullptr;

				*cpp++ = &info->str[info->len];
				while (*s != 0 && 0 != c::strcharcount(sep, *s)) {
					if (SUCCESS != write(*s))
						return nullptr;
					s++;
				}
				if (SUCCESS != write((char)0))
					return nullptr;
			}
			return (const char**)info->str;
		}

	} machine;

}zs4;

#endif
