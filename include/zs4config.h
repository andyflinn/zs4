 
#ifndef ZS4_CONFIG_H
#define ZS4_CONFIG_H

#	define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>

#include <tinydir.h>

#ifdef _WIN32
#	include <direct.h>
#	pragma warning (disable : 4996)
#	pragma warning (disable : 4244)

#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>

#	define snprintf _snprintf
#	define chdir _chdir

#	ifndef _CRT_SECURE_NO_WARNINGS
#		define _CRT_SECURE_NO_WARNINGS
#	endif

#	if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#		define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#	endif

#	if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#		define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#	endif

#	ifndef PATH_SEPARATOR_CHAR 
#		define PATH_SEPARATOR_CHAR '\\'
#	endif

#	ifndef PATH_SEPARATOR_STR 
#		define PATH_SEPARATOR_STR "\\"
#	endif

#	ifndef BACKSLASHES
#		define BACKSLASHES 1
#	endif

#else // sum kinda posix

	
#include <unistd.h>
#include <dirent.h>

#	ifndef PATH_SEPARATOR_CHAR 
#		define PATH_SEPARATOR_CHAR '/'
#	endif

#	ifndef PATH_SEPARATOR_STR 
#		define PATH_SEPARATOR_STR "/"
#	endif

#	ifndef BACKSLASHES
#		define BACKSLASHES 1
#	endif

#endif

/*	MACROS activated by debug compilation
permit you to override the basic capacity of this server;

*/

#if defined (_DEBUG) || defined (DEBUG)

#	define DBG_GETCHAR 	getchar()

#else

#	define DBG_GETCHAR

#endif

/*	Here's some configuration numbers which
permit you to override the basic capacity of this server;

*/
#ifndef ZS4_DEFAULT_PORT
#define ZS4_DEFAULT_PORT (8000)
#endif

#ifndef ZS4_SERVER_MAX_HEADERS 
#define ZS4_SERVER_MAX_HEADERS (8)
#endif

#ifndef ZS4_SERVER_HEADER_LINE_LENGTH 
#define ZS4_SERVER_HEADER_LINE_LENGTH (128)
#endif

#ifndef ZS4_SERVER_HOSTNAME_LENGTH 
#define ZS4_SERVER_HOSTNAME_LENGTH (64)
#endif

#ifndef ZS4_SERVER_MIMETYPE_LENGTH 
#define ZS4_SERVER_MIMETYPE_LENGTH (32)
#endif

#ifndef ZS4_SERVER_MAX_SLAVES 
#define ZS4_SERVER_MAX_SLAVES (64)
#endif

#ifndef ZS4_SERVER_MAX_CLIENTS_PER_SLAVE 
#define ZS4_SERVER_MAX_CLIENTS_PER_SLAVE (64)
#endif

#ifndef ZS4_SERVER_MAX_CLIENTS_TOTAL 
#define ZS4_SERVER_MAX_CLIENTS_TOTAL (ZS4_SERVER_MAX_SLAVES*ZS4_SERVER_MAX_CLIENTS_PER_SLAVE)
#endif


#endif
