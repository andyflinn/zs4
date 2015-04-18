/* ******************************************************************
   Copyright (C) 1996-2015  Thugs at Bay Inc, All Rights Reserved.

   This program is NOT free software; you can NOT redistribute it.

   Thugs at Bay Contact information:
   email: info@thugsatbay.com or
   phone: 416 534 3562

** *************************************************************** */

#ifndef ZS4_JSON_OBJECT
#define ZS4_JSON_OBJECT

#include <zs4bits.h>
#include <zs4array.h>
#include <zs4jsonparser.h>
#include <zs4event.h>
#include <zs4pipe.h>

#ifndef JSON_NAME_SIZE
#define JSON_NAME_SIZE (32)
#endif

ZS4_STRINGBUFFER(json_namebuffer, JSON_NAME_SIZE);
class zs4machine;

class jsonName : private json_namebuffer
{
public:
	inline jsonName(void){}
	inline virtual ~jsonName(void){}
	inline zs4error set(const char * n){
		if (n == nullptr || n[0] == 0 || strlen(n) >= JSON_NAME_SIZE)
			return zs4FAILURE;

		if (!strcmp(n, "zs4"))
			return json_namebuffer::setTrim(n);

		for (const char * p = n; *p != 0; p++)
		{
			if (*p >= 'a' && *p <= 'z')
				continue;

			return zs4FAILURE;
		}

		return json_namebuffer::setTrim(n);
	}
	inline const char * get(void){
		return str;
	}
};

class jsonValue : public zs4pipe
{
public:
	inline jsonValue()
	{
	}
	inline virtual ~jsonValue()
	{
	}

	jsonName name;

	inline virtual zs4error onConnect(zs4event * e){
		reset();
		return zs4SUCCESS;
	}

	inline virtual zs4error init(void){
		return zs4FAILURE;
	}
	inline virtual zs4error save(zs4stream * out) = 0;
	inline virtual zs4error loadValue(const json_value * in) = 0;
	inline virtual zs4error loadString(const char * in){
		return zs4FAILURE;
	}
};

class jsonObject : public jsonValue
{
public:
	zs4array<jsonValue> child;

	inline jsonObject()
	{
	}
	inline virtual ~jsonObject()
	{
	}

	inline virtual zs4error loadString(const char * in){
		if (in == nullptr || in[0] == 0)
			return zs4FAILURE;

		zs4jsonParser parser;
		if ( const json_value * v = parser.parse(in) )
			return loadValue(v);

		return zs4FAILURE;
	}
	inline virtual zs4error loadValue(const json_value * in){
		if (in == nullptr || in->type != json_object)
			return zs4FAILURE;

		zs4error ret = zs4SUCCESS;

		jsonValue ** arr = (jsonValue **)child.arr();
		for (size_t i = 0; i < child.count(); i++)
		{
			const char * nam = arr[i]->name.get();

			bool found = false;
			for (size_t j = 0; j < in->u.object.length; j++)
			{
				if (!strcmp(nam, in->u.object.values[j].name))
				{
					found = true;
					if (zs4SUCCESS != arr[i]->loadValue(in->u.object.values[j].value))
						ret = zs4FAILURE;
					break;
				}
			}

			if (!found)
			{
				ret = zs4FAILURE;
				arr[i]->init();
			}
		}

		return ret;
	}
	inline virtual zs4error save(zs4stream * out){
		out->write('{');
		jsonValue ** arr = (jsonValue **)child.arr();
		for (size_t i = 0; i < child.count(); i++)
		{
			if (i)out->write(',');
			out->write('"');
			out->write(arr[i]->name.get());
			out->write('"');

			out->write(':');
			arr[i]->save(out);
		}
		return out->write('}');
	}

	inline zs4error add(jsonValue*v, const char * name){
		if ((zs4SUCCESS == v->name.set(name)) && (nullptr != child.add(v)))
			return zs4SUCCESS;
		return zs4FAILURE;
	}
};

class jsonBool : public jsonValue
{
public:
	bool value;
	inline jsonBool()	{
		value = false;
	}
	inline virtual ~jsonBool(){
	}
	inline virtual zs4error loadValue(const json_value * in){
		if (in == nullptr || in->type != json_boolean)
			return zs4FAILURE;

		if (in->u.boolean) value = true;
		else value = false;

		return zs4SUCCESS;
	}
	inline virtual zs4error save(zs4stream * out){
		if (value) return out->write("true");
		else return out->write("false");
	}
};

class jsonInt : public jsonValue
{
public:
	json_int_t value;
	inline jsonInt()	{
		value = 0;
	}
	inline virtual ~jsonInt(){
	}
	inline virtual zs4error loadValue(const json_value * in){
		if (in == nullptr || in->type != json_integer)
			return zs4FAILURE;

		value = in->u.integer;
		return zs4SUCCESS;
	}
	inline virtual zs4error save(zs4stream * out){
		return out->writeInt64(value);
	}
};

class jsonFloat : public jsonValue
{
public:
	double value;
	inline jsonFloat()	{
		value = 0.0;
	}
	inline virtual ~jsonFloat(){
	}
	inline virtual zs4error loadValue(const json_value * in){
		if (in == nullptr || in->type != json_double)
			return zs4FAILURE;

		value = in->u.dbl;
		return zs4SUCCESS;
	}
	inline virtual zs4error save(zs4stream * out){
		return out->write(value);
	}
};

class jsonEvent
{
public:
	inline jsonEvent(void){}
	inline virtual ~jsonEvent(void){}
};

#endif

