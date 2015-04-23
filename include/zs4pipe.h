#ifndef ZS4_PIPE
#define ZS4_PIPE

#include <zs4ring.h>

ZS4_STRINGBUFFER(zs4pipeBuffer, 4);

class zs4pipe : public zs4stream
{
	zs4pipeBuffer defaultPipeBuffer;
public:

	inline zs4pipe(void){
		setPipeBuffer(defaultPipeBuffer);
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

	inline virtual size_t pushable(void){ return req.writeable(); }
	inline virtual size_t pullable(void){ return rep.readable(); }

	inline zs4error push(char c){
		if (pushable())
		{
			req.writeChar(c);
			return zs4SUCCESS;
		}
		return zs4FAILURE;
	}
	
	inline zs4error pull(char * c){
		if (pullable())
		{
			rep.readChar(c);
			return zs4SUCCESS;
		}
		return zs4FAILURE;
	}

protected:
	inline virtual size_t readable(void){return req.readable();}
	inline virtual size_t writeable(void){return rep.writeable();}

	inline zs4error write(char c){ if (0 == writeable())return zs4BUFFEROVERFLOW; rep.writeChar(c); return zs4SUCCESS; }
	inline zs4error read(char * c){ if (0 == readable())return zs4NODATA; req.readChar(c); return zs4SUCCESS; }

	inline void setPipeBuffer(zs4string&buf){ buf.halfs(req.buffer, rep.buffer); }
	inline void operator = (zs4string&buf){ setPipeBuffer(buf); }

private:
	zs4ring req;
	zs4ring rep;
};

#endif
