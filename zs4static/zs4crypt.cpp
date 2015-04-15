#include "zs4crypt.h"

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

tab_zs4_crypt::tab_zs4_crypt()
{
}

tab_zs4_crypt::~tab_zs4_crypt()
{
}

zs4error tab_zs4_crypt::StringToMD5(const char * str, zs4StringBuffer * hash)
{
	if (!str || !str[0] || !hash)
		return zs4FAILURE;

	char buffer[MD5_DIGEST_LENGTH + 1]; memset(buffer, 0, sizeof(buffer));
	MD5((unsigned char*)str, strlen(str), (unsigned char*)buffer);

	hash->clear();
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		hash->writeHex(buffer[i]);
	}

	return zs4SUCCESS;
}

zs4error tab_zs4_crypt::StringToSha1(const char * str, zs4StringBuffer * hash)
{
	if (!str || !str[0] || !hash)
		return zs4FAILURE;

	char buffer[SHA_DIGEST_LENGTH + 1]; memset(buffer, 0, sizeof(buffer));
	SHA1((unsigned char*)str, strlen(str), (unsigned char*)buffer);

	hash->clear();
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		hash->writeHex(buffer[i]);
	}

	return zs4SUCCESS;
}

zs4error tab_zs4_crypt::StringToSha224(const char * str, zs4StringBuffer * hash)
{
	if (!str || !str[0] || !hash)
		return zs4FAILURE;

	char buffer[SHA224_DIGEST_LENGTH + 1]; memset(buffer, 0, sizeof(buffer));
	SHA224((unsigned char*)str, strlen(str), (unsigned char*)buffer);

	hash->clear();
	for (int i = 0; i < SHA224_DIGEST_LENGTH; i++)
	{
		hash->writeHex(buffer[i]);
	}

	return zs4SUCCESS;
}

zs4error tab_zs4_crypt::StringToSha256(const char * str, zs4StringBuffer * hash)
{
	if (!str || !str[0] || !hash)
		return zs4FAILURE;

	char buffer[SHA256_DIGEST_LENGTH + 1]; memset(buffer, 0, sizeof(buffer));
	SHA256((unsigned char*)str, strlen(str), (unsigned char*)buffer);

	hash->clear();
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		hash->writeHex(buffer[i]);
	}

	return zs4SUCCESS;
}

zs4error tab_zs4_crypt::StringToSha384(const char * str, zs4StringBuffer * hash)
{
	if (!str || !str[0] || !hash)
		return zs4FAILURE;

	char buffer[SHA384_DIGEST_LENGTH + 1]; memset(buffer, 0, sizeof(buffer));
	SHA384((unsigned char*)str, strlen(str), (unsigned char*)buffer);

	hash->clear();
	for (int i = 0; i < SHA384_DIGEST_LENGTH; i++)
	{
		hash->writeHex(buffer[i]);
	}

	return zs4SUCCESS;
}

zs4error tab_zs4_crypt::StringToSha512(const char * str, zs4StringBuffer * hash)
{
	if (!str || !str[0] || !hash)
		return zs4FAILURE;

	char buffer[SHA512_DIGEST_LENGTH + 1]; memset(buffer, 0, sizeof(buffer));
	SHA512((unsigned char*)str, strlen(str), (unsigned char*)buffer);

	hash->clear();
	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
	{
		hash->writeHex(buffer[i]);
	}

	return zs4SUCCESS;
}

const char * tab_zs4_crypt::RandomBytes(int len, zs4StringBuffer * rand)
{
	static zs4StringBuffer internal_private_buffer;
	if (rand == NULL)rand = &internal_private_buffer;

	static zs4StringBuffer buf;

	if (1 != RAND_bytes((unsigned char *)buf.str, len))
		return NULL;

	rand->clear();
	for (int i = 0; i < len; i++)
	{
		rand->writeHex(buf.str[i]);
	}

	return rand->str;
}

