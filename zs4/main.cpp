#include <zs4machine.h>

int main(int argc, char **argv)
{
	zs4pipe pipe;
	zs4StringBuffer str;
	pipe = str;
	zs4machine machine;

	if (argc == 1)
	{
		if (!zs4fs::isFile(DOT_ZS4))
		{
			ZS4_STDOUT.write("not a zs4 folder.\n");
		}
	}

	machine.save(zs4fs::out());

	DBG_GETCHAR;

	return 0;
}
