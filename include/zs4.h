#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

#include <zs4config.h>

#define ZS4_PARSER_SIZE ((ZS4LARGE)((ZS4LARGE)256*(ZS4LARGE)256))

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
	typedef class symbol {
	public:
		typedef class type
		{
		protected:
			inline virtual ZS4CHAR count(void) = 0;
			inline virtual ZS4CHAR * data(void) = 0;
		public:
			inline ZS4CHAR lookup(ZS4CHAR symbol, ZS4CHAR range = 10){

				for (ZS4LARGE i = 0; (i < range) && (i < count()); i++){
					if ((ZS4CHAR)data()[i] == (ZS4CHAR)symbol)
						return (ZS4CHAR)i;
				}
				return (ZS4CHAR)(~0);
			}
		}type;

		typedef class name : public type
		{
		public:
			typedef enum {
				a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
				SIZE
			} index;
			inline virtual ZS4CHAR count(void){ return (ZS4CHAR)SIZE; }

			inline virtual ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = {
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
				return data;
			}

		}name;

		typedef class numeric : public type
		{
		public:
			typedef enum {
				n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
				SIZE
			} index;
			inline virtual ZS4CHAR count(void){ return (ZS4CHAR)SIZE; }

			inline virtual ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
				return data;
			}
		}numeric;

		typedef class opcode : public type
		{
		public:
			typedef enum {
				equal, or, and, plus, minus,
				SIZE
			} index;
			inline virtual ZS4CHAR count(void){ return (ZS4CHAR)SIZE; }

			inline virtual ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = {
					'=', '|', '&', '+', '-' };
				return data;
			}

		}opcode;

		typedef class container : public type
		{
		public:
			typedef enum {
				parenthesis, curly, square,less,
				SIZE
			} index;
			inline virtual ZS4CHAR count(void){ return (ZS4CHAR)SIZE; }

			inline virtual ZS4CHAR * data(void){
				static ZS4CHAR data[SIZE] = {
					'(', '{', '[', '<' };
				return data;
			}

			inline virtual ZS4CHAR * end(void){
				static ZS4CHAR data[SIZE] = {
					')', '}', ']', '>' };
				return data;
			}

		}container;


	}symbol;


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

	typedef class object : public stream
	{
		char * store;
		ZS4LARGE storesize;
	protected:
		INLINE_MEMORY_FUNCTION(){ return store; }
		INLINE_BITS_FUNCTION(){ return (storesize << 3); }
		INLINE_RESET_FUNCTION(){ memset(store, 0, storesize); }

		typedef struct info {
			stream * in;
			stream * out;
			char * str;
			unsigned long len, pos, siz, stk, lim;
		}info;

		inline virtual e jStart(const char * n = nullptr){ if (n != nullptr) { write('"'); writeString(n); write('"'); write(':'); }; return write('{'); }

		inline virtual e jEnd(){ return write('}'); }

		inline bool valid(void)const{
			if (storesize < (2 * sizeof(info)))
				return false;
			return true;
		}
		inline struct info * getInfo(void){
			if (!valid())
				return nullptr;

			struct info * info = (struct info*)store;
			info->str = (char*)&info[1];
			info->siz = storesize - sizeof(struct info);

			return info;
		}

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
									writeString("\"t\":"); // total
									writeInteger(0);
									write(',');

									writeString("\"u\":"); // used
									writeInteger(0);
									write(',');

									writeString("\"a\":"); // available
									writeInteger(0);
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

#define	on(what) inline virtual e on ## what(void)

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
		INLINE_INSTANCE(object){ store = m; storesize = s; reset(); }
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

	};



	/*
	typedef class filter : public storage
	{
	public:
		inline ZS4CHAR WRITE_INDEX(){return data[(zs4::p8::PROBABILITY - 1)].data;}
		inline ZS4CHAR WRITE_INDEX_INC(){
			(data[(zs4::p8::PROBABILITY - 1)].data)++;
			data[(zs4::p8::PROBABILITY - 1)].data %= (BUFFER_SIZE());
			return data[(zs4::p8::PROBABILITY - 1)].data;
		}

		inline ZS4CHAR READ_INDEX(){return data[(zs4::p8::PROBABILITY - 2)].data;}
		inline ZS4CHAR READ_INDEX_INC(){
			(data[(zs4::p8::PROBABILITY - 2)].data)++;
			data[(zs4::p8::PROBABILITY - 2)].data %= (BUFFER_SIZE());
			return data[(zs4::p8::PROBABILITY - 2)].data;
		}

		inline ZS4CHAR BUFFER_SIZE(){ return (ZS4CHAR)(sizeof(data) - 2); }

		inline virtual ZS4CHAR read(ZS4CHAR & c){
			if (!readable())
				return 0;

			c = data[READ_INDEX()].data;

			READ_INDEX_INC();

			return 1;
		}
		inline virtual ZS4CHAR write(ZS4CHAR c){
			if (!writeable())
				return 0;

			data[WRITE_INDEX()].data = c;

			WRITE_INDEX_INC();

			return 1;
		}
		inline virtual ZS4CHAR readable(void){
			if ((ZS4CHAR)WRITE_INDEX() == (ZS4CHAR)READ_INDEX())
				return 0;

			if ((ZS4CHAR)WRITE_INDEX() > (ZS4CHAR)READ_INDEX())
				return ((ZS4CHAR)WRITE_INDEX() - (ZS4CHAR)READ_INDEX());

			return (ZS4CHAR)(ZS4LARGE)((ZS4LARGE)(ZS4CHAR)WRITE_INDEX() + (ZS4LARGE)BUFFER_SIZE()) - (ZS4LARGE)(ZS4CHAR)READ_INDEX();
		}
		inline virtual ZS4CHAR writeable(void){
			return ((BUFFER_SIZE() - 1) - readable());
		}

		inline unsigned char * shell(unsigned char * line, ZS4LARGE size)
		{
			for (unsigned char u = 0; (u < size) && (line[u] != 0); u++){
				if (!writeable())
					return nullptr;
				else
					write(line[u]);
			}

			line[0] = 0;
			for (unsigned char u = 0; (u < size - 1) && (readable()); u++){
				read(line[u]); line[u + 1] = 0;
			}

			return line;
		}

	}filter;
*/
}zs4;

#endif
