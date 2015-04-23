#ifndef ZS4_FUNCTION
#define ZS4_FUNCTION

#include <zs4json.h>

class zs4function : public jsonObject
{
	friend class zs4;
protected:
	typedef enum {
		async,
		start,
		wait,
		done,
		error,
		flagCount
	} processEnum;

	class processFlags : public intbits<zs4int, processEnum>
	{
	public:
		inline processFlags(void){}
		inline processFlags(zs4int*init){}
		inline virtual ~processFlags(void){}
		enum_bit(zs4int, processEnum, async);
		enum_bit(zs4int, processEnum, start);
		enum_bit(zs4int, processEnum, wait);
		enum_bit(zs4int, processEnum, done);
		enum_bit(zs4int, processEnum, error);
		inline zs4int runningStateMask(){ return (start_mask() | done_mask() | wait_mask() | error_mask()); }
		inline void clearRunningState(void) { clrMask(runningStateMask()); };
	};

public:
	class flags : public jsonInt
	{
	public:
		processFlags bit;
		inline flags(void){
			bit.init(value);
			bit.clearRunningState();
		}
		inline virtual ~flags(void){}
	};

	inline zs4function(void){
		index = 0;
	}

	inline virtual ~zs4function(void){}

	inline virtual zs4error add(zs4function*v, const char * name){
		return jsonObject::add(v, name);
	}

	processEnum tickle(void){
		for (;;)
		{
			processEnum ret = onTick();
			if (ret == done || ret == error || ret == wait)
				return ret;
		}
	}
protected:

	virtual inline processEnum onTick(void){
		size_t count = child.count();
		if (count == NULL)
			return done;

		zs4function ** arr = (zs4function **)child.arr();

		for (size_t i = 0; i < count; i++){
			zs4function * f = arr[i];

			f->flags.bit.clearRunningState();
			f->flags.bit.error_clr();
			f->flags.bit.wait_clr();
			f->flags.bit.start_set();

		}
		return done;
	}
	flags flags;

private:
	size_t index;
	inline virtual zs4error add(jsonValue*v, const char * name){
		return jsonObject::add(v, name);
	}
};

#endif

