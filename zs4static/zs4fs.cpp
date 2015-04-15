#include "tinydir.h"
#include <zs4fs.h>

size_t zs4fs::List(const char * name, bool hidden_files){

	count = 0;

	if (IsFile(name))
		return 0;

	if (!IsDir(name))
		return 0;

	zs4stat * nu;

	tinydir_dir dir;
	if (tinydir_open(&dir, ".") == -1)
		return count;

	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
			break;

		if (strcmp(file.name, ".") && strcmp(file.name, ".."))
		{

			if ((NULL == (nu = nuStat())) || zs4SUCCESS != nu->GetInfo(file.name))
				break;
		}
		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	return count;
}
