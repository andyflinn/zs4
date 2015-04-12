#include "zs4node.h"
//#include "tab_zs4_http.h"

zs4node::zs4_link::zs4_link(void)
{
//	request.clean();
	demon_id = -1;
};

zs4node::zs4_link::~zs4_link()
{
};

const char * zs4node::zs4_link::name(void)
{
	static const char * link = ZS4_LINK;
	return link;
}

zs4error zs4node::zs4_link::get(zs4stream * out)
{
	const json_value * obj_demon = getString(object->Object(), ZS4"."ZS4_LINK"."ZS4_DEMON);
	if (obj_demon)
		JSON_WriteStringValue(out, ZS4_DEMON, obj_demon->u.string.ptr);
	else
		JSON_WriteStringValue(out, ZS4_DEMON, "");
	out->write(",");

	const json_value * obj_run = getBoolean(object->Object(), ZS4"."ZS4_LINK"."ZS4_RUN);
	if (obj_run && obj_run->u.boolean && demon_id >= 0)
		JSON_WriteBoolValue(out, ZS4_RUN, true);
	else
		JSON_WriteBoolValue(out, ZS4_RUN, false);
	out->write(",");

	/*
	if (!userIsObject())
	{
		out->write("\"config\":");

		if (config.check())
		{
			out->write(config.str);
			out->write(",");
		}
		else
		{
			out->write("{},");
		}
	}
	request.writeOutstanding(out,userIsObject());*/
	
	return zs4SUCCESS;
}

bool zs4node::zs4_link::set(const json_value * in, zs4stream * out, const char * var, const json_value * val)
{
	return false;
}


