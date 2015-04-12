#ifndef TAB_ZS4_CRYPT_H
#define TAB_ZS4_CRYPT_H

#include "../include/zs4jsonparser.h"

class tab_zs4_crypt : public zs4StringBuffer
{
public:
	tab_zs4_crypt();
	virtual ~tab_zs4_crypt();

	static zs4error StringToMD5(const char * str, zs4StringBuffer * hash);
	static zs4error StringToSha256(const char * str, zs4StringBuffer * hash);
	static const char * RandomBytes(int len, zs4StringBuffer * buffer = NULL);
};

#endif