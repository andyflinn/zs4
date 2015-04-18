#ifndef TAB_ZS4_CRYPT_H
#define TAB_ZS4_CRYPT_H

#include <zs4string.h>

class tab_zs4_crypt
{
public:
	tab_zs4_crypt();
	virtual ~tab_zs4_crypt();

	static zs4error StringToMD5(const char * str, zs4StringBuffer * hash);

	static zs4error StringToSha1(const char * str, zs4StringBuffer * hash);
	static zs4error StringToSha224(const char * str, zs4StringBuffer * hash);
	static zs4error StringToSha256(const char * str, zs4StringBuffer * hash);
	static zs4error StringToSha384(const char * str, zs4StringBuffer * hash);
	static zs4error StringToSha512(const char * str, zs4StringBuffer * hash);

	static const char * RandomBytes(int len, zs4StringBuffer * buffer = nullptr);
};

#endif