#include "tinydir.h"
#include <zs4fs.h>

size_t zs4fs::list(const char * name, bool hidden_files){

	count = 0;

	if (isFile(name))
		return 0;

	if (!isDir(name))
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

		if (strcmp(file.name, ".") && strcmp(file.name, "..") && strcmp(file.name, ".zs4"))
		{

			if ((nullptr == (nu = nuStat())) || zs4SUCCESS != nu->info(file.name))
				break;
		}
		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	return count;
}
