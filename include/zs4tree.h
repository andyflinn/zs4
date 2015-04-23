#ifndef ZS4_TREE
#define ZS4_TREE

#include <zs4json.h>

class zs4tree : public jsonObject
{
public:
	typedef enum {
		async,
		wait,
		done,
		error,
		flagCount
	} flagsEnum;

	class treeFlags : public intbits<zs4int, flagsEnum>
	{
	public:
		inline treeFlags(void){}
		inline virtual ~treeFlags(void){}
		enum_bit(zs4int, flagsEnum, async);
		enum_bit(zs4int, flagsEnum, wait);
		enum_bit(zs4int, flagsEnum, done);
		enum_bit(zs4int, flagsEnum, error);
	};

	class flags : public jsonInt
	{
	public:
		treeFlags bit;
		inline flags(void){
			bit.init(&value);
		}
		inline virtual ~flags(void){}
	};

	inline zs4tree(bool async = false){
		flags.bit.async_put(async); 
		member(flags);
	}
	inline virtual ~zs4tree(void){}
	
	flags flags;
};

#endif

