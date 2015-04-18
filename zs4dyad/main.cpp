#include "zs4dyad.h"

#include <zs4json.h>

int main(int argc, char **argv)
{
	const char * arg = nullptr;
	if (argc > 1)
	{
		arg = argv[1];
		zs4StringBuffer wk;

		const char ** arr = nullptr;
		if (size_t count = wk.tokenize(arg,"/\\",&arr))
		{
			for (size_t i = 0; i < count; i++)
			{
				printf("tok %3d: \"%s\"\n", (int)i, arr[i]);
			}
		}
	}

	zs4jsonParser json;
	const json_value * jv = json.parseFile("session.json");
	
	zs4dyad * dyad = new zs4dyad();

	dyad->Run();

	getchar();
	return 0;
}
