#include <stdio.h>
#include <zs4.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

int main(int argc, char **argv)
{
	zs4::null<ZS4CHAR> zs4;
	ZS4CHAR data[zs4::symbol<ZS4CHAR>::ARRAY_PRECISION];

	printf("sizeof(z) returns (%d)\n", (int)sizeof(zs4));
	
	while (gets((char*)data)){

		zs4.shell(data, sizeof(data));
		puts((char*)data);
	}
	getchar();

	return 0;
}
