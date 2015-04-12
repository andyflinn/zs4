#include "zs4node.h"

const char * zs4node::zs4_html::name(void)
{
	static const char * login = ZS4_HTML;
	return login;
}

zs4error zs4node::zs4_html::get(zs4stream * out)
{
	const json_value * obj_onload = getString(object->Object(), ZS4"."ZS4_HTML"."ZS4_ONLOAD);

	if (obj_onload)
		JSON_WriteStringValue(out, ZS4_ONLOAD, obj_onload->u.string.ptr);
	else
		JSON_WriteStringValue(out, ZS4_ONLOAD, "");

	return zs4SUCCESS;
}

bool zs4node::zs4_html::set(const json_value * in, zs4stream * out, const char * var, const json_value * val)
{
	if (val == NULL)
		return false;

	const json_value * val_onload = NULL;

	if (val->type == json_object && !strcmp(var, ZS4"."ZS4_HTML))
		val_onload = getString(val, ZS4_ONLOAD);
	else
	if (val->type == json_string && !strcmp(var, ZS4"."ZS4_HTML"."ZS4_ONLOAD))
		val_onload = val;

	if (val_onload == NULL)
		return false;

	const json_value * obj_onload = getString(object->Object(), ZS4"."ZS4_HTML"."ZS4_ONLOAD);

	if (val_onload)
		JSON_WriteStringValue(out, ZS4_ONLOAD, val_onload->u.string.ptr);
	else if (obj_onload)
		JSON_WriteStringValue(out, ZS4_ONLOAD, obj_onload->u.string.ptr);
	else
		JSON_WriteStringValue(out, ZS4_ONLOAD, "");

	return true;
}


