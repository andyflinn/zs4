#include <stdio.h>
#include <zs4.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

int main(int argc, char **argv)
{
	ZS4CHAR data[ZS4_ARRAY_PRECISION];
	zs4::null zs4;

	printf("sizeof(z) returns (%d)\n", (int)sizeof(zs4));
	
	while (gets((char*)data)){

		zs4.shell(data, ZS4_ARRAY_PRECISION);
		puts((char*)data);
	}
	getchar();

	return 0;
}
