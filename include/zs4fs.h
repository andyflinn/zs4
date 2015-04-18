#ifndef ZS4_FS_H
#define ZS4_FS_H

#include <zs4file.h>

#ifndef ZS4_MAX_DIR_SIZE
#define ZS4_MAX_DIR_SIZE (1024)
#endif

#ifndef TAB_FS_MAX_PATH_LENGTH
#define TAB_FS_MAX_PATH_LENGTH (4096)
#endif

#define ZS4_STDIN (*zs4fs::in())
#define ZS4_STDOUT (*zs4fs::out())

class zs4fs : public zs4object
{
public:
	inline zs4fs(){
		count = 0;
	}
	inline virtual ~zs4fs(){
	}

	inline static bool isFile(const char * path){
		struct stat ino;

		if (stat(path, &ino))
			return false;

		if (S_ISREG(ino.st_mode))
			return true;

		return false;
	}
	inline static bool isDir(const char * path){
		struct stat ino;

		if (stat(path, &ino))
			return false;

		if (S_ISDIR(ino.st_mode))
			return true;

		return false;
	}
	inline static zs4error cd(const char * nu){
		return (zs4error)chdir(nu);
	}
	inline static zs4error pwd(zs4string * cd){
		char * buffer;
		char buf[1024]; buf[0] = 0;
		char *getcwd(char *buf, size_t size);
		buffer = getcwd(buf, 1024);
		return cd->set(buffer);
	}
	inline static zs4error mkDir(const char * name){
		char dirnam[TAB_FS_MAX_PATH_LENGTH];
		char pdir[TAB_FS_MAX_PATH_LENGTH];

		strncpy(dirnam, name, sizeof(dirnam));

		char * f = (char*)dirnam, *t = pdir;

		while (*f != 0)
		{
			//char sav = *f;
			*t++ = *f++; *t = 0;
			if ((*f == '/') || (*f == 0))
			{
#ifdef _WIN32
				_mkdir(pdir);
#else
				mkdir(pdir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
			}
		}

		if (!isDir(name))
		{
			return zs4FAILURE;
		}

		return zs4SUCCESS;
	}
	inline static zs4error rmFile(const char * name){
		if (!unlink(name)) return zs4SUCCESS;
		return zs4FAILURE;
	}
	inline static zs4error rmDir(const char * name){
		if (!rmdir(name)) return zs4SUCCESS;
		return zs4FAILURE;
	}
	inline static zs4error info(const char * objectname, zs4stat * info){
		if (objectname == nullptr || objectname[0] == 0 || info == nullptr)
			return zs4FAILURE;

		return info->info(objectname);
	}
	inline static zs4stream * in(void){ static zs4stdin in; return &in; }
	inline static zs4stream * out(void){ static zs4stdout out; return &out; }

	inline void sort(qsort_compare_foo* foo){
		if (count < 2)
			return;

		qsort(statArray, count, sizeof(zs4stat **), foo);
	}
	inline void sortNameAscend(void){
		sort(zs4string::compareValueAscend);
	}
	inline void sortNameDescend(void){
		sort(zs4string::compareValueDescend);
	}
	inline void sortLengthAscend(void){
		sort(zs4string::compareLengthAscend);
	}
	inline void sortLengthDescend(void){
		sort(zs4string::compareLengthDescend);
	}
	inline time_t created(const char * fnam){
		zs4stat info;

		if ((!zs4fs::isFile(fnam))
			|| (zs4SUCCESS != zs4fs::info(fnam, &info))
			)
			return 0;

		return info.created;
	}
	inline time_t modified(const char * fnam){
		zs4stat info;

		if ((!zs4fs::isFile(fnam))
			|| (zs4SUCCESS != zs4fs::info(fnam, &info))
			)
			return 0;

		return info.modified;
	}

	size_t list(const char * name, bool hidden_files);

	inline zs4stat * nuStat(void)	{
		if (count >= (ZS4_MAX_DIR_SIZE - 1))
			return nullptr;

		statData[count].clear();
		zs4stat * ret = &statData[count];
		statArray[count] = &statData[count];
		count++;
		return ret;
	}
	size_t count;
	zs4stat * statArray[ZS4_MAX_DIR_SIZE];
	zs4stat statData[ZS4_MAX_DIR_SIZE];
};

#endif

