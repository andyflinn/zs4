#ifndef ZS4_PIPE
#define ZS4_PIPE

#include <zs4ring.h>

ZS4_STRINGBUFFER(zs4pipeBuffer, 4);

class zs4pipe : public zs4stream
{
public:
	zs4ring req;
	zs4ring rep;

	inline zs4pipe(void){
		reset();
	}

	virtual inline ~zs4pipe(void){
	}

	inline virtual void reset(void){
		req.reset();
		rep.reset();
	}

	inline virtual zs4error close(void){
		stream_state = CLOSED;
		reset();
		return zs4FAILURE;
	}

	inline void operator = (zs4string&buf){ buf.halfs(req.buffer,rep.buffer); }

};

#endif
