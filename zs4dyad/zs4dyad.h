#ifndef ZS4_DYAD_H
#define ZS4_DYAD_H

#include"zs4file.h"
#include"zs4pipe.h"
#include"zs4streamserver.h"

#include"dyad.h"

class zs4dyad;

ZS4_STRINGBUFFER(dyadTransferBuffer, (16 * 1024));

class dyadsocket : public zs4pipe<dyadTransferBuffer>
{
public:
	inline dyadsocket(void){
		s = NULL;
	}
	inline virtual ~dyadsocket(void)
	{
		close();
	}

	inline virtual zs4error close(void){
		if (s == NULL)
			return zs4FAILURE;

		dyad_end(s);
		dyad_removeAllListeners(s, NULL);
		dyad_close(s);
		s = NULL;
		
		zs4stream::close();
		return zs4FAILURE;
	}

	inline virtual size_t writeBlock(const void * block, size_t size){
		if (s == NULL)
			return 0;

		dyad_write(s, (void*)block, size);

		return size;
	}

	inline virtual size_t writeChar(char c){
		if (s == NULL)
			return 0;

		dyad_write(s, &c, 1);

		return 1;
	}

	inline static void on_data(dyad_Event*e){
		zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess * c = 
			(zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess*)e->udata;
		if ( c && c->stream.s )
		{
			if (e->size != c->stream.req.writeBlock(e->data, e->size))
			{
				dyad_close(c->stream.s);
				c->stream.s = NULL;
			}
			else
			{
				if (zs4SUCCESS != c->handler.handle())
				{
					dyad_close(c->stream.s);
					c->stream.s = NULL;
				}
			}
		}
	}

	inline static void on_ready(dyad_Event*e){
		zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess * c =
			(zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess*)e->udata;
		if (c && c->stream.s)
		{
			size_t trans = c->stream.rep.readable();
			if (trans > 0)
				c->stream.write(&c->stream.rep, trans);
		}
	}

	inline static void on_tick(dyad_Event*e){
		zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess * c =
			(zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess*)e->udata;
		if (c && c->stream.s)
		{
		}
	}

	inline static void on_close(dyad_Event*e){
		zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess * c =
			(zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess*)e->udata;
		if (c && c->stream.s)
		{
			c->stream.s = NULL;
			c->stream.close();
		}
	}

	inline static void on_error(dyad_Event*e){
		zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess * c =
			(zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>::zs4streamseverprocess*)e->udata;
		if (c && c->stream.s)
		{
			c->stream.s = NULL;
			c->stream.close();
		}
	}

	//zs4dyad * dyad;
	dyad_Stream * s;
};

class zs4dyad : public zs4streamserver<dyadsocket, zs4streamhandler<dyadTransferBuffer>>
{
public:

	zs4dyad(void);
	virtual ~zs4dyad(void);

	virtual void Run(const char * path=NULL);

	static void on_Error(dyad_Event*e);
	static void on_Accept(dyad_Event*e);
	static void on_Listen(dyad_Event*e);

	static void on_Panic(const char*msg);

	dyad_Stream * s;
};


#endif
