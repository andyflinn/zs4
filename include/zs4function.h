#ifndef ZS4_FUNCTION
#define ZS4_FUNCTION

class zs4function
{
public:
	typedef enum {
		async,
		running,
		con,
		dis,
		flagCount
	} flags;

	inline zs4function(void){ type = tck; }
	inline virtual ~zs4function(void){}
	flags flags;
};

#endif

