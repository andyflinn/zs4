#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

typedef __int64 zs4int;
typedef double zs4float;
typedef bool zs4bool;

typedef enum {
	zs4SUCCESS = 0,
	zs4FAILURE,
	zs4BUFFEROVERFLOW,
	zs4NODATA,
	zs4FILEINFOERROR,
	zs4FILEOPENERROR,
	zs4ERRORCOUNT
} zs4error;

#endif
