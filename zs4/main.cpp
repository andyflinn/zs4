#include <stdio.h>
#include <zs4.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

static void storageinfo(const char * name, zs4::storage & store)
{
	printf("storage information for %s:\n", name);

	printf("%s.bits() is (%lld)\n", name, (ZS4LARGE)store.bits());
	printf("%s.addressBits() is (%lld)\n", name, (ZS4LARGE)store.addressBits());
	printf("%s.messageBits() is (%lld)\n", name, (ZS4LARGE)store.messageBits());
	printf("%s.p8() is (%lld)\n", name, (ZS4LARGE)store.p8());
	printf("%s.p16() is (%lld)\n", name, (ZS4LARGE)store.p16());
	printf("%s.p32() is (%lld)\n", name, (ZS4LARGE)store.p32());
	printf("%s.p64() is (%lld)\n", name, (ZS4LARGE)store.p64());

	putchar('\n');
}

int main(int argc, char **argv)
{
	zs4::in in;
	zs4::out out;

	char buffer[65536];
	zs4::object object((char*)&buffer, sizeof(buffer));
	storageinfo("object", object);

	object.connect(&in, &out);

	for (;;){
		if (zs4::SUCCESS != object.tickle())
			break;

	}

	DBG_GETCHAR;

	return 0;
}
