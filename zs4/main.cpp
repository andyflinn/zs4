#include <zs4.h>

#include <stdio.h>
#include <zs4stream.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

int main(int argc, char **argv)
{
	zs4 z;
	printf("sizeof(s) = %d\n", (int)sizeof(z));

	getchar();
	
	return 0;
}
