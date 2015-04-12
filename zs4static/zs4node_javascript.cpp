#include "zs4node.h"

const char * zs4node::zs4_javascript::name(void)
{
	static const char * login = ZS4_JAVASCRIPT;
	return login;
}

zs4error zs4node::zs4_javascript::get(zs4stream * out)
{
	const json_value * obj_body = getString(object->Object(), ZS4"."ZS4_JAVASCRIPT"."ZS4_BODY);

	if (obj_body)
		JSON_WriteStringValue(out, ZS4_BODY, obj_body->u.string.ptr);
	else
		JSON_WriteStringValue(out, ZS4_BODY, "");

	return zs4SUCCESS;
}

bool zs4node::zs4_javascript::set(const json_value * in, zs4stream * out, const char * var, const json_value * val)
{
	if (val == NULL)
		return false;

	const json_value * val_body = NULL;

	if (val->type == json_object && !strcmp(var, ZS4"."ZS4_JAVASCRIPT))
		val_body = getString(val, ZS4_BODY);
	else
	if (val->type == json_string && !strcmp(var, ZS4"."ZS4_JAVASCRIPT"."ZS4_BODY))
		val_body = val;

	if (val_body == NULL)
		return false;

	//const char * zs4 = object->varStart(var, ZS4"."zs4_javascript);

	const json_value * obj_body = getString(object->Object(), ZS4"."ZS4_JAVASCRIPT"."ZS4_BODY);

	if (val_body)
		JSON_WriteStringValue(out, ZS4_BODY, val_body->u.string.ptr);
	else if (obj_body)
		JSON_WriteStringValue(out, ZS4_BODY, obj_body->u.string.ptr);
	else
		JSON_WriteStringValue(out, ZS4_BODY, "");

	return true;
}


