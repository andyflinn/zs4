#include <stdio.h>
#include <zs4.h>
#include <zs4util.h>

#define P(n) printf("%s: %d\n",#n,(int)n())

int main(int argc, char **argv)
{

	util::in in;
	util::out out;

	char buffer[255];
	zs4::byte::object object((unsigned byte_t*)&buffer, sizeof(buffer), &in, &out);

	for (;;){
		if (SUCCESS != object.tickle())
		{
			printf("press ctrl c to quit\n");
		}
	}

	DBG_GETCHAR;

	return 0;
}
