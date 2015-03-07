#ifndef ZS4_JSON_H
#define ZS4_JSON_H

#include <zs4string.h>
#include <zs4file.h>
#include <zs4jsonparser.h>

#define JT_TRUE "true"
#define JT_FALSE "false"

#ifndef ZS4_JASON_MAX_DEPTH
#define ZS4_JASON_MAX_DEPTH (64)
#endif

#ifndef ZS4_JASON_MAX_PATH
#define ZS4_JASON_MAX_PATH (256)
#endif

#ifndef ZS4_JASON_MAX_TEXT
#define ZS4_JASON_MAX_TEXT (256*256)
#endif

#ifndef ZS4_JASON_MAX_STRING
#define ZS4_JASON_MAX_STRING (256)
#endif

ZS4_STRINGBUFFER(zs4JsonString, ZS4_JASON_MAX_STRING);
ZS4_STRINGBUFFER(zs4JsonText, ZS4_JASON_MAX_TEXT);

typedef struct
{
	json_char * name;
	struct _json_value * value;

} json_property;

// For Creating JSON object in "C"
#define JSON_COMMA ","

typedef int (jsonPropertySort)(const json_property * vA, const json_property * vB);
typedef bool (filterValue)(const json_value * in, zs4stream * out, const char * path, void * ctx);

template <class zs4stringtype>
class zs4json : public zs4object
{
public:
	typedef struct { zs4json * json; const char * path; const json_value * value; bool add; void * udta; } changeStruct;

	inline zs4json(){ parser = &parser1; JObj = NULL; };
	inline virtual ~zs4json(){};
	
	inline const json_value * Object(void) { return JObj; }

	inline const json_value * Parse(const char * str){
		if (json_value * nuJv = parser->Parse(str))
		{
			JObj = nuJv;
			if (parser == &parser1) parser = &parser0;
			else  parser = &parser1;
			return JObj;
		}

		parser_error.set(parser->str);
		return NULL;
	}
	inline const json_value * ParseFile(const char * fnam){
		zs4file file;
		zs4stringtype buf;

		if (zs4SUCCESS != file.openRead(fnam)
			|| zs4SUCCESS != buf.write(&file)
			)
			return NULL;

		return Parse(buf.str);
	}

	inline static int filterObject(const json_value * in, zs4stream * out, filterValue * func = NULL, const char * path = NULL, void * ctx = NULL){
		if (in == NULL || in->type != json_object || out == NULL)
			return 0;

		if (path == NULL)
			path = "";

		bool first = true;
		zs4JsonText	filterBuffer;

		JSON_WriteObjectStart(out);

		for (unsigned int i = 0; i < in->u.object.length; i++)
		{
			zs4JsonString childPath;
			childPath.set(path); if (childPath.check()) childPath.write(".");
			childPath.write(in->u.object.values[i].name);

			const json_value * value = in->u.object.values[i].value;

			filterBuffer.clear();
			if (func && func(value, &filterBuffer, childPath.str, ctx))
			{
				if (!filterBuffer.check())
					continue;

				if (!first) out->write(JSON_COMMA);

				out->write("\"");
				out->write(in->u.object.values[i].name);
				out->write("\":");

				out->write(filterBuffer.str);

				first = false;
			}
			else
			{
				if (!first) out->write(JSON_COMMA);

				out->write("\"");
				out->write(in->u.object.values[i].name);
				out->write("\":");

				if (json_boolean == value->type)
				{
					if (value->u.boolean){ out->write("true"); }
					else{ out->write("false"); }
				}
				else
				if (json_double == value->type)
				{
					out->write(value->u.dbl);
				}
				else
				if (json_integer == value->type)
				{
					out->write((int)value->u.integer);
				}
				else
				if (json_string == value->type)
				{
					out->write("\""); out->writeJson(value->u.string.ptr); out->write("\"");
				}
				else
				if (json_object == value->type)
				{
					filterObject(value, out, func, childPath.str, ctx);
				}

				first = false;
			}

		}

		filterBuffer.clear();
		if (func && func(NULL, &filterBuffer, path, ctx))
		{
			if (filterBuffer.check())
			{
				if (!first) out->write(JSON_COMMA);
				out->write(filterBuffer.str);
			}
		}

		JSON_WriteObjectEnd(out);

		return 1;
	}

	inline const json_value * change(const char * path, const char * value){
		if (path == NULL || path[0] == 0)
			return JObj;

		if (value == 0)
			return change(path, (const json_value*)NULL);

		zs4json json;
		if (const json_value * val = json.Parse(value))
			return change(path, val);

		return JObj;
	}
	inline const json_value * change(const char * path, const json_value * value){
		if (path == NULL || path[0] == 0)
			return JObj;

		changeStruct ctx = { this, path, value, false, NULL };
		if (!getValue(JObj, path))
			ctx.add = true;

		zs4JsonText out;
		if (!filterObject(JObj, &out, changeFilter, "", &ctx))
			return JObj;

		return Parse(out.str);
	}

	inline const json_value * filter(const char * path, const json_value * value, filterValue * func, void * udta = NULL){
		if (path == NULL || path[0] == 0)
			return JObj;

		changeStruct ctx = { this, path, value, false, udta };
		if (!getValue(JObj, path))
			ctx.add = true;

		zs4JsonText out;
		if (!filterObject(JObj, &out, func, "", &ctx))
			return JObj;

		return Parse(out.str);
	}

	inline const json_value * valueGet(const char * path, const json_value * obj = NULL){
		if (obj == NULL)obj = JObj;
		if (obj == NULL)return NULL;
		return getValue(obj, path);
	}
	inline const json_value * objectGet(const char * path, const json_value * obj = NULL){
		if (obj == NULL)obj = JObj;
		if (obj == NULL)return NULL;
		return getObject(obj, path);
	}
	inline const json_value * arrayGet(const char * path, const json_value * obj = NULL){
		if (obj == NULL)obj = JObj;
		if (obj == NULL)return NULL;
		return getArray(obj, path);
	}
	inline const json_value * stringGet(const char * path, const json_value * obj = NULL){
		if (obj == NULL)obj = JObj;
		if (obj == NULL)return NULL;
		return getString(obj, path);
	}
	inline const json_value * integerGet(const char * path, const json_value * obj = NULL){
		if (obj == NULL)obj = JObj;
		if (obj == NULL)return NULL;
		return getInteger(obj, path);
	}
	inline const json_value * booleanGet(const char * path, const json_value * obj = NULL){
		if (obj == NULL)obj = JObj;
		if (obj == NULL)return NULL;
		return getBoolean(obj, path);
	}
	inline const json_value * floatGet(const char * path, const json_value * obj = NULL){
		if (obj == NULL)obj = JObj;
		if (obj == NULL)return NULL;
		return getFloat(obj, path);
	}

	inline static const json_value * getValue(const json_value * JObj, const char * path){
		if (JObj == NULL || JObj->type != json_object)
			return NULL;

		if (path == NULL || path[0] == 0 || path[0] == '.')
			return JObj;

		size_t len = strlen(path);
		if (len >= ZS4_JASON_MAX_PATH)
			return NULL;

		static char JPath[ZS4_JASON_MAX_PATH];
		static const char * JElement[ZS4_JASON_MAX_DEPTH];
		strcpy(JPath, path);

		int JElement_count = 1;
		JElement[0] = JPath;

		for (size_t i = 0; i < len; i++)
		{
			if (JPath[i] == '.')
			{
				JPath[i] = 0;

				JElement[JElement_count++] = &JPath[i + 1];
			}
		}
		JElement[JElement_count] = NULL;

		return ReturnValue(JElement, JObj);
	}
	inline static const json_value * getArray(const json_value * obj, const char * path){
		const json_value * val = getValue(obj, path);
		if ((val == NULL)
			|| (val->type != json_array)
			)
			return NULL;

		return val;
	}
	inline static const json_value * getObject(const json_value * obj, const char * path){
		const json_value * val = getValue(obj, path);
		if ((val == NULL)
			|| (val->type != json_object)
			)
			return NULL;

		return val;
	}
	inline static const json_value * getString(const json_value * obj, const char * path){
		const json_value * val = getValue(obj, path);
		if ((val == NULL)
			|| (val->type != json_string)
			)
			return NULL;

		return val;
	}
	inline static const json_value * getInteger(const json_value * obj, const char * path){
		const json_value * val = getValue(obj, path);
		if ((val == NULL)
			|| (val->type != json_integer)
			)
			return NULL;

		return val;
	}
	inline static const json_value * getBoolean(const json_value * obj, const char * path){
		const json_value * val = getValue(obj, path);
		if ((val == NULL)
			|| (val->type != json_integer)
			)
			return NULL;

		return val;
	}
	inline static const json_value * getFloat(const json_value * obj, const char * path){
		const json_value * val = getValue(obj, path);
		if ((val == NULL)
			|| (val->type != json_double)
			)
			return NULL;

		return val;
	}

	inline static zs4error JSON_WriteObjectStart(zs4stream * out, const char * name = NULL){
		if (!name || !name[0])
			return out->write("{");

		out->write("\"");
		out->write(name);
		out->write("\":{");
		return zs4SUCCESS;
	}
	inline static zs4error JSON_WriteObjectEnd(zs4stream * out){
		return out->write("}");
	}
	inline static zs4error JSON_WriteArrayStart(zs4stream * out, const char * name = NULL){
		if (!name || !name[0])
			return out->write("[");

		out->write("\"");
		out->write(name);
		out->write("\":[");
		return zs4SUCCESS;
	}
	inline static zs4error JSON_WriteArrayEnd(zs4stream * out){
		return out->write("}");
	}
	inline static zs4error JSON_WriteStringValue(zs4stream * out, const char * name, const char * str){
		out->write("\"");
		out->write(name);
		out->write("\":\"");
		out->writeJson(str);
		out->write("\"");
		return zs4SUCCESS;
	}
	inline static zs4error JSON_WriteIntegerValue(zs4stream * out, const char * name, int integer){
		out->write("\"");
		out->write(name);
		out->write("\":");
		out->write((int)integer);
		return zs4SUCCESS;
	}
	inline static zs4error JSON_WriteBoolValue(zs4stream * out, const char * name, bool b){
		out->write("\"");
		out->write(name);
		out->write("\":");
		if (b)
		{
			out->write("true");
		}
		else
		{
			out->write("false");
		}

		return zs4SUCCESS;
	}
	inline static zs4error JSON_WriteFloatValue(zs4stream * out, const char * name, double f){
		out->write("\"");
		out->write(name);
		out->write("\":");
		out->write((double)f);
		return zs4SUCCESS;
	}
	
	inline static int JSON_CountChildrenOfType(const json_value * in, json_type type){
		int ret = 0;
		if (in == NULL || in->type != json_object)
			return ret;

		for (unsigned int i = 0; i < in->u.object.length; i++)
		{
			const json_value * child = in->u.object.values[i].value;

			if (child->type == type)
				ret++;
		}

		return ret;
	}
	inline static int JSON_WriteChildrenOfType(const json_value * in, zs4stream * out, json_type type){
		int ret = 0;
		if (in == NULL || in->type != json_object || out == NULL)
			return ret;

		for (unsigned int i = 0; i < in->u.object.length; i++)
		{
			const json_value * child = in->u.object.values[i].value;
			const char * name = in->u.object.values[i].name;

			if (child->type != type)
				continue;

			out->write(",");

			out->write("\"");
			out->write(name);
			out->write("\":");

			if (type == json_object)
			{
				filterObject(child, out);
			}
			else if (type == json_string)
			{
				out->write("\"");
				out->writeJson(child->u.string.ptr);
				out->write("\"");
			}
			else if (type == json_boolean)
			{
				if (child->u.boolean)
					out->write("true");
				else
					out->write("false");
			}
			else if (type == json_integer)
			{
				out->write((int)child->u.integer);
			}

			ret++;
		}

		return ret;
	}

	inline static bool isName(const char * n){
		if (n == NULL || n[0] == 0) return false;

		bool r = true;
		while (*n)
		{
			if (*n < 'a' || *n >'z')return false;
			n++;
		}
		return true;
	}
	inline static bool isTransformName(const char * n){
		if (n == NULL || n[0] == 0) return false;
		size_t l = strlen(n);
		if (n[0] < 'a' || n[0] >'z')return false;
		if (n[l - 1] < 'a' || n[l - 1] >'z')return false;

		bool r = true;
		while (*n)
		{
			if ((*n < 'a' || *n >'z') && (*n != '_'))return false;
			n++;
		}
		return true;
	}

	inline static const char * integer2name(int i, zs4string * buf){
		static const char NCHAR[] = "abcdefghijklmnopqrstuvwxyz";
		static const int NCNT = (sizeof(NCHAR)-1);
		static const int limit = (0x7fffffff / (NCNT*NCNT));
		static int start = NCNT;
		if (start == NCNT){ while (start<limit){ start *= NCNT; } }

		if (i == 0)
		{
			buf->set("a");
			return buf->str;
		}

		bool write = false;
		int rem = i;
		for (int x = start; x > 0; x /= NCNT)
		{
			int div = rem / x;
			if (div == 0)
			{
				if (write)
					buf->write('a');
				continue;
			}

			write = true;
			buf->write(NCHAR[div]);
			rem = rem % x;
		}

		return buf->str;
	}

	inline json_value * getWriteValue(json_value * parent = NULL, const char * path = NULL){
		if (parent == NULL)
			parent = JObj;

		if (parent == NULL || path == NULL || path[0] == 0)
			return parent;

		const json_value * val = getValue(parent, path);
		if (val == NULL)
			return NULL;

		return (json_value *)val;
	}
	inline static void sortObjectProperties(json_value*jo, jsonPropertySort * compareFunc = NULL){
		if (jo == NULL || jo->type != json_object)
			return;

		if (compareFunc == NULL)
			compareFunc = comparePropertyName;

		qsort(jo->u.object.values, jo->u.object.length, sizeof(json_property), (qsort_compare_foo*)compareFunc);
	}
	inline static zs4error JSON_WriteValue(zs4stream * out, const json_value * jv){
		if (out == NULL || jv == NULL)
			return zs4FAILURE;

		if (jv->type == json_string)
		{
			out->write("\"");
			out->writeJson(jv->u.string.ptr);
			out->write("\"");
		}
		else
		if (jv->type == json_double)
		{
			out->write(jv->u.dbl);
		}
		else
		if (jv->type == json_integer)
		{
			out->write((int)jv->u.integer);
		}
		else
		if (jv->type == json_boolean)
		{
			if (jv->u.boolean)
				out->write("true");
			else
				out->write("false");
		}
		else
		if (jv->type == json_object)
		{
			bool first = true;

			for (unsigned int i = 0; i < jv->u.object.length; i++)
			{
				if (!first) out->write(JSON_COMMA);

				if (jv->u.object.values[i].value->type == json_object)
				{
					JSON_WriteObjectStart(out, jv->u.object.values[i].name);
					JSON_WriteValue(out, jv->u.object.values[i].value);
					JSON_WriteObjectEnd(out);
				}
				else
				if (jv->u.object.values[i].value->type == json_array)
				{
					JSON_WriteArrayStart(out, jv->u.object.values[i].name);
					JSON_WriteValue(out, jv->u.object.values[i].value);
					JSON_WriteArrayEnd(out);
				}
				else
				{
					out->write("\"");
					out->write(jv->u.object.values[i].name);
					out->write("\":");
					JSON_WriteValue(out, jv->u.object.values[i].value);
				}

				first = false;
			}
		}
		else
		if (jv->type == json_array)
		{
			bool first = true;

			for (unsigned int i = 0; i < jv->u.array.length; i++)
			{
				if (!first) out->write(JSON_COMMA);

				if (jv->u.array.values[i]->type == json_object)
				{
					JSON_WriteObjectStart(out);
					JSON_WriteValue(out, jv->u.array.values[i]);
					JSON_WriteObjectEnd(out);
					first = false;
				}
				else
				if (jv->u.array.values[i]->type == json_array)
				{
					JSON_WriteArrayStart(out);
					JSON_WriteValue(out, jv->u.array.values[i]);
					JSON_WriteArrayEnd(out);
					first = false;
				}
				else
				{
					JSON_WriteValue(out, jv->u.array.values[i]);
					first = false;
				}
			}

		}

		return zs4SUCCESS;
	}

protected:
	inline static int comparePropertyName(const json_property * vA, const json_property * vB){
		int ret = strcmp(vA->name, vB->name);
		return ret;
	}
	inline static const char * varStart(const char * str, const char * start){
		size_t beg = strlen(start);
		if ((!strncmp(str, start, beg))
			)
		{
			if (str[beg] == '.')
				return &str[beg + 1];

			return &str[beg];
		}
		return NULL;
	};
	inline static const json_value * ReturnValue(const char ** Path, const json_value * parent){
		if ((parent == NULL)
			|| (parent->type != json_object)
			|| (Path == NULL)
			|| (Path[0] == NULL)
			)
			return NULL;

		for (unsigned int i = 0; i < parent->u.object.length; i++)
		{
			if (strcmp(Path[0], parent->u.object.values[i].name))
				continue;

			if (Path[1] == NULL)
			{
				return parent->u.object.values[i].value;
			}

			return ReturnValue(&Path[1],parent->u.object.values[i].value);
		}

		return NULL;
	}
	inline static bool changeFilter(const json_value * in, zs4stream * out, const char * path, void * ctx){
		changeStruct * cv = (changeStruct*)ctx;
		if (cv == NULL || cv->path == NULL || strncmp(path, cv->path, strlen(path)))
			return false;

		if (in == NULL)
		{
			if (cv->value == NULL || !cv->add)
				return false;

			const char * vs = varStart(cv->path, path);
			if (vs == NULL || strcharcount(vs, '.'))
				return false;

			out->write("\""); out->write(vs); out->write("\":");

			if (cv->value->type == json_object) out->write("{");

			JSON_WriteValue(out, cv->value);

			if (cv->value->type == json_object) out->write("}");

			return true;
		}

		if (!strcmp(path, cv->path))
		{
			if (NULL == cv->value)
				return true;

			JSON_WriteValue(out, cv->value);
			return true;
		}
		return false;
	}

	json_value * JObj;

private:
	json_error parser_error;

	zs4jsonParser<zs4stringtype> * parser;
	zs4jsonParser<zs4stringtype> parser0;
	zs4jsonParser<zs4stringtype> parser1;
};

#endif

