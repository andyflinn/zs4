#ifndef ZS4_H
#define ZS4_H

#include <zs4types.h>
#include <zs4config.h>

class zs4
{
public:
	typedef enum {
		SUCCESS = 0,
		FAILURE,
		BUFFEROVERFLOW,
		NODATA,
		FILEINFOERROR,
		FILEOPENERROR,
		ERRORCOUNT
	}e;

	template <class type>
	class i
	{
	public:
		class {
		public:
			const size_t BITDEPTH(){ return (sizeof(type) * 8); }
			const size_t SIZEOF(){ return (1 << BITDEPTH()); }
			const size_t BITINDEX(){ size_t w = 1; while (((size_t)1 << w)<BITDEPTH())w++; return w; }
		} CONST;

		inline i(void){}
		inline virtual ~i(){}

		inline type getAll(void)const{
			return dta;
		}
		inline void setAll(void){
			dta |= (~0);
		}
		inline void setMask(type v){
			dta |= v;
		}
		inline void put(type idx, bool true_or_false){
			if (idx >= (int)bits() || idx < 0)
				return;

			if (true_or_false)
				set(idx);
			else
				clr(idx);
		}
		inline bool get(type idx) const {
			if (idx >= (int)bits() || idx < 0)
				return false;

			if (dta & mask(idx))
				return true;

			return false;
		}
		inline void set(type idx){
			if (idx >= (int)bits() || idx < 0)
				return;

			dta |= mask(idx);
		}
		inline void clr(type idx){
			if (idx >= (int)bits() || idx < 0)
				return;

			dta &= (~mask(idx));
		}
	};

	class c
	{
	public:
		inline static bool charUpperable(char c)	{
			if (c >= 'a' && c <= 'z')
				return true;

			return false;
		}
		inline static bool charLowerable(char c){
			if (c >= 'A' && c <= 'Z')
				return true;

			return false;
		}
		inline static char charMakeUpper(char c){
			if (charUpperable(c))
				return (c - 0x020);

			return c;
		}
		inline static char charMakeLower(char c){
			if (charLowerable(c))
				return (c + 0x020);

			return c;
		}
		inline static int charCompare(char c1, char c2){
			return c1 - c2;
		}

		inline static size_t strlen(const char * str){
			size_t ret = 0;
			while (str != nullptr && (*str != 0)){ 
				ret++;
			}
			return ret;
		}
		inline static int strcmp(const char * str1, const char * str2){
			for (;;)
			{
				if (*str1 == 0 && *str2 == 0)
					return 0;

				if (*str1 != *str2)
					return *str1 - *str2;

				str1++; str2++;
			}
		}
		inline static int stricmp(const char * str1, const char * str2){
			for (;;)
			{
				register char c1 = *str1++;
				register char c2 = *str2++;

				if (c1 == 0 && c2 == 0)
					return 0;

				c1 = charMakeLower(c1);
				c2 = charMakeLower(c2);

				if (c1 != c2)
					return c1 - c2;
			}
		}
		inline static int strncmp(const char * str1, const char * str2, size_t n){
			char c1, c2, *s1 = (char *)str1, *s2 = (char *)str2;
			for (size_t i = 0; i < n; i++)
			{
				c1 = *s1++;
				c2 = *s2++;
				if (c1 == 0 && c2 == 0) return 0;
				if (c1 != c2) return c1 - c2;
			}

			return 0;
		}

		inline static int strnicmp(const char * str1, const char * str2, size_t n){
			char c1, c2, *s1 = (char *)str1, *s2 = (char *)str2;
			for (size_t i = 0; i < n; i++)
			{
				c1 = *s1++;
				c2 = *s2++;
				if (c1 == 0 && c2 == 0) return 0;
				c1 = charMakeLower(c1);
				c2 = charMakeLower(c2);
				if (c1 != c2) return c1 - c2;
			}

			return 0;
		}
		inline static int strcharcount(const char * str, char c){
			if (str == 0)
				return 0;

			int ret = 0;

			while (*str != 0)
			{
				if (c == *str)
					ret++;
				str++;
			}

			return ret;
		}
		inline static int strcharcount(const char * s, const char * chrs){
			int ret = 0;
			for (const char * cp = s; cp && *cp; cp++)
			{
				for (const char * p = chrs; p && *p; p++)
				{
					if (*cp == *p)
						ret++;
				}
			}

			return ret;
		}
		inline static int strcharswap(char org, char * str, char nu){
			int ret = 0;
			while (*str != 0) { if (*str == org) { *str = nu; ret++; } str++; }
			return ret;
		}
		inline static int striend(const char * str, const char * end){
			size_t len_str = strlen(str);
			size_t len_end = strlen(end);

			if (len_end > len_str)
				return 1;


			return stricmp(&str[len_str - len_end], end);
		}
		inline static int strend(const char * str, const char * end){
			size_t len_str = strlen(str);
			size_t len_end = strlen(end);

			if (len_end > len_str)
				return 1;


			return strcmp(&str[len_str - len_end], end);
		}
	};

	class stream{

		inline static const char * HEX_CHARS(void){
			static const char * hc = "0123456789abcdef"; return hc;
		}
		inline virtual size_t readBlock(void * block, size_t size){
			size_t ret = 0;

			char * cp = (char*)block;

			for (size_t i = 0; i < size; i++)
			{
				if (0 == readChar(&cp[i]))
					return ret;

				ret++;
			}

			return ret;
		}
		inline virtual size_t readChar(char * c){
			if (0 == readBlock(c, 1))
				return 0;

			return 1;
		}
		inline virtual size_t writeBlock(const void * block, size_t size){
			size_t ret = 0;

			char * cp = (char*)block;

			for (size_t i = 0; i < size; i++)
			{
				if (0 == writeChar(cp[i]))
					return ret;

				ret++;
			}

			return ret;
		}
		inline virtual size_t writeChar(char c){
			if (0 == writeBlock(&c, 1))
				return 0;

			return 1;
		}
		inline virtual size_t readable(void){
			return 0;
		}
		inline virtual size_t writeable(void){
			return 0;
		}
		inline virtual e flush(void){
			return FAILURE;
		}
		inline virtual e close(void){
			return FAILURE;
		}
		inline virtual e rewind(void){
			return seek(0, SEEK_SET);
		}
		inline virtual e seekEnd(void){
			return seek(0, SEEK_END);
		}
		inline virtual e seek(size_t offset, int origin){
			return FAILURE;
		}
		inline virtual e tell(size_t * pPos){
			return FAILURE;
		}
		inline virtual e size(size_t * s){
			e err;
			size_t pos = 0;
			size_t size = 0;

			if ((err = tell(&pos)) != SUCCESS)
				return err;

			if ((err = seek(0, SEEK_END)) != SUCCESS)
				return err;

			if ((err = tell(&size)) != SUCCESS)
				return err;

			if ((err = seek(pos, SEEK_SET)) != SUCCESS)
				return err;

			*s = size;

			return SUCCESS;
		}
		inline virtual e write(const char * s){
			size_t l = c::strlen(s);
			if (l == writeBlock(s, l))
				return SUCCESS;
			return FAILURE;
		}
		inline virtual e write(char c){
			if (writeChar(c))
				return SUCCESS;
			return FAILURE;
		}
		inline virtual e write(int i, const char * fmt = "%d"){
			char buf[128];
			snprintf(buf, sizeof(buf), fmt, i);
			return write(buf);
		}
		inline virtual e writeInt64(long long i, const char * fmt = "%lld"){
			char buf[128];
			snprintf(buf, sizeof(buf), fmt, i);
			return write(buf);
		}
		inline virtual e write(double d, const char * fmt = "%g"){
			char buf[128];
			snprintf(buf, sizeof(buf), fmt, d);
			return write(buf);
		}
		inline virtual e write(stream * from){
			if (from == 0)
				return FAILURE;

			e err = SUCCESS;

			size_t size = 0;
			if ((err = from->size(&size)) != SUCCESS)
				return err;

			if ((err = from->seek(0, SEEK_SET)) != SUCCESS)
				return err;

			if (size == 0)
				return SUCCESS;

			return write(from, size);
		}
		inline virtual e write(stream * from, size_t length)	{
			char buf[4096];

			while (length > sizeof(buf))
			{
				if (from->readBlock(buf, sizeof(buf)) != sizeof(buf)
					|| writeBlock(buf, sizeof(buf)) != sizeof(buf)
					)
					return FAILURE;

				length -= sizeof(buf);
			}

			if (length > 0)
			{
				if (from->readBlock(buf, length) != length
					|| writeBlock(buf, length) != length
					)
					return FAILURE;
			}

			return SUCCESS;
		}
		inline static e copy(stream * from, stream * to){
			e err = FAILURE;

			size_t size = 0;
			if ((err = from->size(&size)) != SUCCESS)
				return err;

			if ((err = from->seek(0, SEEK_SET)) != SUCCESS)
				return err;

			return to->write(from, size);
		}
		inline e writeJson(const char * out)
		{
			for (const char * str = out; str && *str; str++)
			{
				switch (*str)
				{
				case '\\': write("\\\\"); break;
				case '"': write("\\\""); break;
					//case '\'': Write("\\\'"); break;
				case '/': write("\\/"); break;
				case '\b': write("\\b"); break;
				case '\f': write("\\f"); break;
				case '\n': write("\\n"); break;
				case '\r': write("\\r"); break;
				case '\t': write("\\t"); break;
				default: write(*str); break;
				}
			}
			return SUCCESS;
		}
		inline e writeHex(const char * str, int len)
		{
			if (len < 1)
				return FAILURE;

			e err = SUCCESS;

			for (int i = 0; i < len; i++)
			{
				err = writeHex(str[i]);
				if (err != SUCCESS)
					return err;
			}

			return SUCCESS;
		}
		inline e writeHex(const char * str)
		{
			if (str == 0 || str[0] == 0)
				return SUCCESS;

			while (str && *str)
				if (SUCCESS != writeHex(*str))
					return FAILURE;

			return SUCCESS;
		}
		inline e writeHex(char c)
		{
			int hi = c >> 4;
			hi &= 0x0f;
			if (SUCCESS != write(HEX_CHARS()[hi]))
				return FAILURE;

			return write(HEX_CHARS()[c & 0x0f]);
		}
	};

	class function{

	};

	class m
	{
	public:
		inline m(void){}
		inline virtual ~m(void){}
	};

/*	
	inline zs4(void){}
	inline zs4(char * memory, size_t size, int argc = 0, char **argv = nullptr){
		
	}
	inline virtual ~zs4(void){}
*/

protected:

};

#endif

