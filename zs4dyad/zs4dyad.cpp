#include "zs4dyad.h"
#include "dyad.h"
#include <zs4fs.h>

zs4dyad::zs4dyad(void)
{
	::dyad_init();
}

zs4dyad::~zs4dyad(void)
{
	::dyad_shutdown();
}

void zs4dyad::on_Panic(const char* msg)
{

}

void zs4dyad::Run(const char * path)
{
	if (path&&path[0])
	{
		if (!zs4fs::IsDir(path)||chdir(path))
			exit(-1);
	}

	dyad_atPanic(zs4dyad::on_Panic);

	s = dyad_newStream();

	dyad_addListener(s, DYAD_EVENT_ERROR, on_Error, this);
	dyad_addListener(s, DYAD_EVENT_ACCEPT, on_Accept, this);
	dyad_addListener(s, DYAD_EVENT_LISTEN, on_Listen, this);
	dyad_listen(s, ZS4_DEFAULT_PORT);

	while (dyad_getStreamCount() > 0) {
		dyad_update();
	}
}

void zs4dyad::on_Error(dyad_Event*e)
{

}

void zs4dyad::on_Accept(dyad_Event*e)
{
	zs4dyad * dyad = (zs4dyad *)e->udata;
	
	zs4streamseverprocess * proc = dyad->allocProcess();
	if (proc == NULL)
	{
		dyad_close(e->remote);
		return;
	}
	proc->stream.s = e->remote;

	dyad_addListener(e->remote, DYAD_EVENT_DATA, dyadsocket::on_data, proc);
	dyad_addListener(e->remote, DYAD_EVENT_CLOSE, dyadsocket::on_close, proc);
	dyad_addListener(e->remote, DYAD_EVENT_ERROR, dyadsocket::on_error, proc);
	dyad_addListener(e->remote, DYAD_EVENT_READY, dyadsocket::on_ready, proc);
	dyad_addListener(e->remote, DYAD_EVENT_TICK, dyadsocket::on_tick, proc);
}

void zs4dyad::on_Listen(dyad_Event*e)
{

}


