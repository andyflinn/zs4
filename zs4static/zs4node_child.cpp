#include "zs4node.h"

zs4JsonText zs4node::session;

const char * zs4node::zs4_child::name(void)
{
	static const char * login = ZS4_CHILD;
	return login;
}
bool zs4node::zs4_child::list(void)
{
	bool list = false;
	const json_value * obj_list = getBoolean(object->Object(), ZS4"."ZS4_CHILD"."ZS4"."ZS4_LIST);
	if (obj_list != NULL&&obj_list->type == json_boolean&&obj_list->u.boolean)
		list = true;

	return list;
}

bool zs4node::zs4_child::load(void)
{
	bool load = false;
	const json_value * obj_load = getBoolean(object->Object(), ZS4"."ZS4_CHILD"."ZS4"."ZS4_LOAD);
	if (obj_load != NULL&&obj_load->type == json_boolean&&obj_load->u.boolean)
		load = true;

	return load;
}

zs4error zs4node::zs4_child::get(zs4stream * out)
{
	bool load = this->load();
	bool list = this->list();

	JSON_WriteObjectStart(out, ZS4);
	JSON_WriteBoolValue(out, ZS4_LIST, list);
	out->write(",");
	JSON_WriteBoolValue(out, ZS4_LOAD, load);
	if (!strncmp(object->urlObject, object->urlUser, strlen(object->urlUser)))
	{
		out->write(",");
		JSON_WriteStringValue(out, ZS4_CREATE, "");
		out->write(",");
		JSON_WriteStringValue(out, ZS4_DELETE, "");
	}
	JSON_WriteObjectEnd(out);

	if (list)
	{
		object->connLoad();

		for (int i = 0; i < object->connCount; i++)
		{
			out->write(",");
			JSON_WriteObjectStart(out, object->conn[i]->objectName());
			JSON_WriteObjectEnd(out);
		}
	}

	return zs4SUCCESS;
}

bool zs4node::zs4_child::set(const json_value * in, zs4stream * out, const char * var, const json_value * val)
{
	if	(val == NULL)
		return false;

	if (val->type == json_boolean
		&&	!strcmp(var, ZS4"."ZS4_CHILD"."ZS4"."ZS4_LIST)
		)
	{
		bool list = false;
		if (val->u.boolean)
			list = true;

		JSON_WriteObjectStart(out, ZS4);
		JSON_WriteBoolValue(out, ZS4_LIST, list);
		out->write(",");
		JSON_WriteBoolValue(out, ZS4_LOAD, this->load());
		JSON_WriteObjectEnd(out);

		return true;
	}

	if (val->type == json_boolean
		&&	!strcmp(var, ZS4"."ZS4_CHILD"."ZS4"."ZS4_LOAD)
		)
	{
		bool load = false;
		if (val->u.boolean)
			load = true;

		JSON_WriteObjectStart(out, ZS4);
		JSON_WriteBoolValue(out, ZS4_LIST, this->list());
		out->write(",");
		JSON_WriteBoolValue(out, ZS4_LOAD, load);
		JSON_WriteObjectEnd(out);

		return true;
	}

	if (val->type == json_string
		&&	object->isName(val->u.string.ptr)
		&& !strcmp(var, ZS4"."ZS4_CHILD"."ZS4"."ZS4_CREATE)
		)
	{
		if (zs4node * exists = object->connLoad(val->u.string.ptr))
		{
			object->WriteErrorMessage(ZS4_ERROR(ZS4_CHILD".already.exists"));
			return false;
		}

		zs4node * nu = object->connCreate(val->u.string.ptr);

		if (nu == NULL)
		{
			object->WriteErrorMessage(ZS4_ERROR(ZS4_CHILD".creation.failed"));
			return false;
		}

		return false;
	}

	if (val->type == json_string
		&&	object->isName(val->u.string.ptr)
		&& !strcmp(var, ZS4"."ZS4_CHILD"."ZS4"."ZS4_DELETE)
		)
	{
		zs4node * exists = object->connLoad(val->u.string.ptr);
		if (exists==NULL)
		{
			object->WriteErrorMessage(ZS4_ERROR(ZS4_CHILD".not.found"));
			return false;
		}

		object->connDelete(val->u.string.ptr);
		return false;
	}

	return false;
}


