#include <stdio.h>
#include <zs4.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

static void storageinfo(const char * name, zs4::storage & store)
{
	/*
	printf("storage information for %s:\n", name);

	printf("%s.bits() is (%lld)\n", name, (ZS4LARGE)store.bits());
	printf("%s.addressBits() is (%lld)\n", name, (ZS4LARGE)store.addressBits());
	printf("%s.messageBits() is (%lld)\n", name, (ZS4LARGE)store.messageBits());
	printf("%s.p8() is (%lld)\n", name, (ZS4LARGE)store.p8());
	printf("%s.p16() is (%lld)\n", name, (ZS4LARGE)store.p16());
	printf("%s.p32() is (%lld)\n", name, (ZS4LARGE)store.p32());
	printf("%s.p64() is (%lld)\n", name, (ZS4LARGE)store.p64());
	putchar('\n');
*/
}

int main(int argc, char **argv)
{
	zs4::event::opcode opcode; printf("opcode.bits() is %d\n", (int)opcode.bits());
	zs4::event::name name; printf("name.bits() is %d\n", (int)name.bits());
	zs4::event::numeric numeric; printf("numeric.bits() is %d\n", (int)numeric.bits());

	zs4::in in;
	zs4::out out;

	char buffer[256];
	zs4::p8::object<short, zs4::p16> object((char*)&buffer, sizeof(buffer), &in, &out);

	storageinfo("object", object);

	for (;;){
		if (zs4::SUCCESS != object.tickle())
		{
			printf("press ctrl c to quit\n");
		}
	}

	DBG_GETCHAR;

	return 0;
}
