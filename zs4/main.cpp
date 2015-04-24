#include <zs4.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

int main(int argc, char **argv)
{

	device<unsigned char> b;

//	b = 0;

	P(b.BITDEPTH);
	P(b.addressbits);
	P(b.databits);

	getchar();
	
	return 0;
}
