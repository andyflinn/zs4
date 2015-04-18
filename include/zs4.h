#ifndef ZS4_H
#define ZS4_H

#include <zs4json.h>
#include <zs4fs.h>

#define DOT_ZS4 ".zs4"

ZS4_ARRAYBUFFER(zs4Children, 8);

class zs4 : public jsonObject
{
public:
	typedef enum {
		initialized,
		persistent,
	zs4flagCount} zs4flagsEnum;

	class zs4flags : public zs4bits<json_int_t, zs4flagsEnum>
	{
	public:
		inline zs4flags(void){}
		inline virtual ~zs4flags(void){}
		enum_bit(json_int_t, zs4flagsEnum, 0, initialized);
		enum_bit(json_int_t, zs4flagsEnum, 1, persistent);
	};

	class flags : public jsonInt
	{
	public:
		zs4flags bit;
		inline flags(void){
			bit.init(&value);
		}
		inline virtual ~flags(void){}
	};

	inline zs4(void){
	}

	inline virtual ~zs4(void){

	}

	flags flags;
};

#endif

