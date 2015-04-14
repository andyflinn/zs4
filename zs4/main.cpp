#include <zs4bits.h>
#include <zs4jsonparser.h>
#include <jsonobject.h>
#include <zs4fs.h>
#include <zs4file.h>

int main(int argc, char **argv)
{
	printf("sizeof(int) equals %d\n", (int)sizeof(int));
	printf("sizeof(size_t) equals %d\n", (int)sizeof(size_t));
	printf("sizeof(void*) equals %d\n", (int)sizeof(void*));
	zs4stdout out;
	
	if (argc > 1)
	{
		if (!strcmp("dir",argv[1]))
		{
			zs4fs fs;
			out.write("getting list... ");
			size_t count = fs.List(".",true);
			out.write((int)count);
			out.write(" entries...\n");
			if ( count > 0 )
			{
				for (size_t i = 0 ; i < count; i++){
					out.write((int)(1+i));
					out.write(". \"");
					out.write(fs.statArray[i]->zs4string::str);
					out.write("\"\n");
				}
			}
			else
			{
				out.write("no directory entries...");
			}
		}
	}


	getchar();
	return 0;
}
