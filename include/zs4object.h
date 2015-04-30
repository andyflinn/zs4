#ifndef ZS4_OBJECT_H
#define ZS4_OBJECT_H

#include "zs4config.h"
#include "zs4types.h"

typedef int (qsort_compare_foo)(const void *, const void *);

class zs4object {
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


#endif
