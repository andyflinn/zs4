#include <stdio.h>
#include <zs4types.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

int main(int argc, char **argv)
{
	//typedef struct {char c[3];} medium;
	//typedef unsigned char medium;
	//device<medium, double>::machine & b = (*(new device<medium, double>::machine()));
	
	device<char,double>::stack b;


	printf("sizeof(b)=%d\n", (int)sizeof(device<char, double>::stack));

	getchar();
	
	return 0;
}
