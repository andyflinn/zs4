#include "zs4node.h"
#include "../include/zs4fs.h"
#include "../include/zs4file.h"
//#include "tab_fs.h"


const char * zs4node::rootFolder = NULL;
const char * zs4node::urlRoot = ZS4_ROOT_ID;
const char * zs4node::urlPublic = ZS4_PUBLIC_ID;
const char * zs4node::urlUser = NULL;
bool zs4node::urlPublicInitialized = false;
zs4node * zs4node::objectUser = NULL;
tab_zs4_http * zs4node::server = NULL;

//zs4stream buf zs4node::session;

zs4node::zs4node(void)
{ 
	authorizer = this;
	featureCount = 0;
	feature.object = this;

	featureAdd(&link);
	featureAdd(&child);
	featureAdd(&javascript);
	featureAdd(&html);
	featureAdd(&login);

	objectParent = NULL;
	connLoaded = false;
	connCount = 0;
};

zs4node::~zs4node(void)
{
	for (int i = 0; i < connCount; i++)
		delete conn[i];
};

const char * zs4node::zs4::name(void)
{
	static const char * zs4 = ZS4;
	return zs4;
}

bool zs4node::zs4::userOwnsObject(void)
{
	if (strcmp(object->urlObject, object->urlUser)
		&& !strncmp(object->urlObject, object->urlUser, strlen(object->urlUser))
		)
		return true;

	return false;
}

bool zs4node::zs4::userIsObject(void)
{
	if (!strcmp(object->urlObject, object->urlPublic))
		return false;

	if (!strcmp(object->urlUser, object->urlObject))
		return true;

	return false;
}

bool zs4node::zs4::isItem(void)
{
	const json_value * obj_item = getBoolean(object->Object(), ZS4"."ZS4_LINK"."ZS4_ITEM);

	if (obj_item != NULL && obj_item->u.boolean)
		return true;

	return false;
}
int zs4node::zs4::countProperties(void)
{
	int returnValue = 0;

	const json_value * o = object->Object();
	if (NULL == o || o->type != json_object)
		return returnValue;

	for (unsigned int i = 0; i < o->u.object.length; i++)
	{
		if (!strcmp(ZS4, o->u.object.values[i].name))
			continue;

		returnValue++;
	}
	return returnValue;
}
int zs4node::zs4::countLinks(void)
{
	object->connLoad();
	return object->connCount;
}
int zs4node::zs4::version(void)
{
	const json_value * ver = getInteger(object->Object(), ZS4"."ZS4_VER);
	if (ver)
		return ver->u.integer;

	return 0;
}
zs4error zs4node::zs4::get(zs4stream * out)
{
	bool gettingRootObject = false;
	if (!strcmp(object->urlObject, ZS4_ROOT_ID))
		gettingRootObject = true;

	JSON_WriteObjectStart(out);

	// url
	JSON_WriteStringValue(out, ZS4_URL, object->urlObject);

	// version
	out->write(",");
	if (!strcmp(object->urlObject, ZS4_ROOT_ID))
		JSON_WriteIntegerValue(out, ZS4_VER, ZS4_VERSION);
	else
		JSON_WriteIntegerValue(out, ZS4_VER, version());

	out->write(",");
	JSON_WriteBoolValue(out, ZS4_AM, object->login.userIsObject());

	out->write(",");
	JSON_WriteBoolValue(out, ZS4_OWN, object->login.userOwnsObject());

	zs4JsonString featPath;
	zs4JsonText get;
	for (int i = 0; i < object->featureCount; i++)
	{
		featPath.set(ZS4"."); featPath.write(object->feat[i]->name());
		if (NULL == getValue(object->Object(), featPath.str))
			continue;

		featPath.set("get."ZS4"."); featPath.write(object->feat[i]->name());
		if (!object->authorize(featPath.str))
			continue;

		get.clear();
		if (zs4SUCCESS == object->feat[i]->get(&get))
		{
			out->write(",");
			JSON_WriteObjectStart(out, object->feat[i]->name());
			out->write(get.str);
			JSON_WriteObjectEnd(out);
		}
	}

	// errors
	out->write(",");
	JSON_WriteStringValue(out, ZS4_ERR, object->error.str);

	JSON_WriteObjectEnd(out);

	return zs4SUCCESS;
}
bool zs4node::zs4::set(const json_value * in, zs4stream * out, const char * var, const json_value * val)
{
	bool settingRootObject = false;
	if (!strcmp(object->urlObject, ZS4_ROOT_ID))
		settingRootObject = true;

	JSON_WriteObjectStart(out);

	// variable
	JSON_WriteStringValue(out, ZS4_VAR, object->url2VarName(object->urlObject));

	// version
	out->write(",");
	const json_value * ver = getInteger(object->Object(), ZS4"."ZS4_VER);
	if (settingRootObject)
	{
		JSON_WriteIntegerValue(out, ZS4_VER, ZS4_VERSION);
	}
	else
	{
		JSON_WriteIntegerValue(out, ZS4_VER,version()+1);
	}

	zs4json init;
	zs4JsonText change;
	for (int i = 0; i < object->featureCount; i++)
	{
		const json_value * feat = getValue(in,object->feat[i]->name());
		zs4JsonString featVar; featVar.set("zs4."); featVar.write(object->feat[i]->name());

		// evaluate if this feature should be added
		if (feat == NULL)
		{
			bool initFeat = settingRootObject;
			if (userOwnsObject() && objectUser != NULL&&getObject(objectUser->Object(), featVar.str))
			{
				//ZS4_DEBUG_STRING("contemplating add feature", featVar.str)
				if (var != NULL
					&&	!strcmp(var, featVar.str)
					&&	val != NULL
					&&	val->type == json_object
					&&	val->u.object.length == 0
					)
					initFeat = true;
				
			}

			if (!strcmp(object->urlObject, object->urlPublic)
				&& !strcmp(object->feat[i]->name(), ZS4_LOGIN)
				)
				initFeat = false;

			if (initFeat)
			{
				 init.Parse("{}");
				 feat = init.Object();
			}
			if (feat == NULL)
			{
				//ZS4_DEBUG_STRING("feature not found", object->feat[i]->name())
					continue;
			}
			//ZS4_DEBUG_STRING("added feature", featVar.str)
		}

		// evaluate if this feature should be deleted
		if (userOwnsObject())
		{
			//ZS4_DEBUG_STRING("contemplating remove feature", featVar.str)
			if (var != NULL
				&&	!strcmp(var, featVar.str)
				&& val == NULL
				)
			{
				//ZS4_DEBUG_STRING("removed feature", featVar.str)
					continue;
			}
		}

		change.clear();
		out->write(",");
		if (object->feat[i]->set(feat, &change, var, val))
		{
			JSON_WriteObjectStart(out, object->feat[i]->name());
			out->write(change.str);
			JSON_WriteObjectEnd(out);
		}
		else
		{
			out->write("\""); out->write(object->feat[i]->name()); out->write("\":");
			filterObject(feat, out);
		}
	}

	JSON_WriteObjectEnd(out);

	return true;
}

bool zs4node::authorize(const char * zs4Property)
{
	if (!strcmp(urlObject,urlPublic))
	{
		if (	!strcmp(zs4Property, "get.zs4.login")
			||	!strcmp(zs4Property, "set.zs4.login")
			)
			return false;

		if (!feature.userOwnsObject()
			&& !strnicmp(zs4Property, "set.", 4)
			)
			return false;
	}

	if ((!strcmp(zs4Property, "get.zs4"))
		|| (login.configured() && !strcmp(zs4Property, "get.zs4.login"))
		|| !strcmp(zs4Property, "get.zs4.function")
		)
		return true;

	// user owns object
	if (!strncmp(urlUser, urlObject, strlen(urlUser)))
		return true;

	if (login.configured())
	{
		if (	!strcmp(zs4Property, "zs4.login")
			|| !strcmp(zs4Property, "set.zs4.login")
			|| !strcmp(zs4Property, "set.zs4.login.password")
			)
			return true;
	}

	return false;
}

bool zs4node::setFilter(const json_value * in, zs4stream * out, const char * path, void * ctx)
{
	//ZS4_DEBUG(false);

	changeStruct * cv = (changeStruct*)ctx;
	if (cv == NULL)
		return false;

	zs4node * object = (zs4node*)cv->json;

	bool ret = false;
	zs4JsonText buf;
	if (strcmp(path, ZS4))
	{
		if (object->feature.userIsObject()
			|| object->feature.userOwnsObject()
			)
		{
			ret = changeFilter(in, &buf, path, ctx);
		}
	}
	else
	{
		ret = object->feature.set(in, &buf, cv->path, cv->value);
	}

	out->write(buf.str);

	return ret;
}

const json_value * zs4node::set(const char * path, const json_value * value)
{
	// ZS4_DEBUG(false);

	if (path == NULL || path[0] == 0)
		return JObj;

	changeStruct ctx = { this, path, value, false };
	if (!getValue(JObj, path))
		ctx.add = true;

	zs4JsonText buf;
	if (!filterObject(JObj, &buf, setFilter, "", &ctx))
		return JObj;

	static zs4json test;
	if (test.Parse(buf.str))
		Parse(buf.str);

	return JObj;
}

bool zs4node::getFilter(const json_value * in, zs4stream * out, const char * path, void * ctx)
{
	// ZS4_DEBUG(false);

	changeStruct * cv = (changeStruct*)ctx;
	if (cv == NULL)
		return false;

	zs4node * object = (zs4node*)cv->json;

	if (!strcmp(path, ZS4))
	{
		object->feature.get(out);
		return true;
	}

	if (object->feature.userIsObject()
		|| object->feature.userOwnsObject()
		)
	{
		if (in == NULL
			&&path[0]==0
			&&object->child.load()
			&&object->connLoad()
			)
		{
			for (int i = 0; i < object->connCount; i++)
			{
				if (i)out->write(",");
				out->write("\""); out->write(object->conn[i]->connName.str); out->write("\":");
				object->conn[i]->get(out);
			}

			return true;
		}
		return false;
	}

	return true;
}

zs4error zs4node::InitializeDiskObject(zs4JsonText * result, const char * url)
{
	zs4json dfJson;
	zs4file diskfile;

	zs4JsonString filnam; filnam.set(url2FileName(url));
	
	if ( dfJson.ParseFile(filnam.str)
		&& dfJson.Object()->type==json_object
		&&	getObject(dfJson.Object(), ZS4)
		)
	{
		result->clear();
		return zs4FAILURE;// result->set(dfJson.str);
	}
	
	zs4JsonString dir; url2DirName(url,&dir);
	if (!zs4fs::IsDir(dir.str))
		zs4fs::MkDir(dir.str);

	zs4file file;
	if (zs4SUCCESS != file.openWrite(filnam.str))
		return zs4FAILURE;

	result->clear();

	JSON_WriteObjectStart(result);
	{
		JSON_WriteObjectStart(result, ZS4);
			JSON_WriteStringValue(result, "var", url2VarName(url));
			result->write(",");
			JSON_WriteIntegerValue(result, "ver", 0);
		JSON_WriteObjectEnd(result);
	}
	JSON_WriteObjectEnd(result);

	return file.write(result->str);
}

bool zs4node::Execute(const char ** patt, const json_value * in, zs4stream * out)
{
	if ((rootFolder == NULL)
		|| (rootFolder[0] == 0)
		)
	{
		out->write(ZS4_ERROR("root.arg.bad"));
		return false;
	}

	if (const json_value * jsess = getString(in, ZS4_SESSION))
		session.set(jsess->u.string.ptr);
	else
		session.clear();

	zs4JsonText json;
	zs4JsonString this_filename;
	if (NULL == Object())
	{
		ParseFile(url2FileName(urlObject, &this_filename));
		if (NULL == Object())
		{
			if (strcmp(urlObject, ZS4_ROOT_ID))
				return (zs4SUCCESS == out->write(ZS4_ERROR("not.found")));

			if (zs4SUCCESS != InitializeDiskObject(&json, "/"))
				return (zs4SUCCESS == out->write(ZS4_ERROR("root.file")));

			if (NULL == Parse(json.str))
				return (zs4SUCCESS == out->write(ZS4_ERROR("root.parse")));
		}
	}

	//at this point we have a loaded object that is valid
	// ZS4_DEBUG_STRING("urlObject", urlObject);
	// now we need to set up the user ID

	// Configure User
	if (urlUser == NULL || urlUser[0] == 0 || urlUser == urlPublic)
	{
		if (	!strcmp(urlObject, ZS4_ROOT_ID)
			&&	!login.configured()
			)
		{
			// ZS4_DEBUG_STRING("user is", ZS4_ROOT_ID);
			urlUser = urlRoot;
		}
		else
		if (const json_value * osess = getString(Object(),ZS4"."ZS4_LOGIN"."ZS4_SESSION) )
		{
			if (	session.check()
				&&	!strcmp(session.str,osess->u.string.ptr)
				)
			{
				// ZS4_DEBUG_STRING("session user is", urlObject);
				urlUser = urlObject;
				objectUser = this;
			}
		}

		if (urlUser == NULL || urlUser[0] == 0)
		{
			if (!urlPublicInitialized
				&& zs4SUCCESS != InitializeDiskObject(&json, urlPublic)
				)
			{
				// ZS4_DEBUG_STRING("FAILURE: ", urlUser);
				return (zs4SUCCESS == out->write(ZS4_ERROR("public.file")));
			}
			urlPublicInitialized = true;
			urlUser = urlPublic;
			// ZS4_DEBUG_STRING("user", urlPublic);
		}
	}

	if (patt == NULL || patt[0] == NULL || patt[0][0] == 0)
	{
		return exec(in, out);
	}
	else if (zs4node * child = connLoad(patt[0]))
	{
		return child->Execute(&patt[1], in, out);
	}
	// ZS4_DEBUG_STRING("connection.not.found", patt[0]);
	return (zs4SUCCESS == out->write(ZS4_ERROR("connection.not.found")));
}

int zs4node::connLoad(void)
{
	// ZS4_DEBUG(false);
	if (connLoaded)
		return connCount;

	size_t tokenCount = 0;
	zs4StringBuffer token;
	zs4StringBuffer zs4FileName;
	zs4fs fs;
	size_t count = fs.List(url2DirName(urlObject),true);
	for (size_t i = 0; i < count; i++)
	{
		if (!fs.IsDir(fs.statArray[i]->str))
			continue;

		zs4FileName.set(fs.statArray[i]->str);
		zs4FileName.write(ZS4_DOT_EXT);

		if (!fs.IsFile(zs4FileName.str))
			continue;

		const char ** path = NULL;
		tokenCount = token.tokenize(fs.statArray[i]->str, "/\\", &path);
		if (path == NULL || tokenCount < 2)
			continue;

		connLoad(path[tokenCount - 1]);
	}

	connLoaded = true;
	return connCount;
}

zs4node * zs4node::connCreate(const char * name)
{
	if (zs4node * exists = connLoad(name))
		return exists;

	connLoad();
	if (connCount >= ZS4_MAX_CONNECTIONS)
		return NULL;

	zs4JsonString nurl;
	zs4JsonText nuobj;
	nurl.set(urlObject);
	nurl.write(name);
	nurl.lastChar('/');
	InitializeDiskObject(&nuobj, nurl.str);

	return connLoad(name);
}

zs4node * zs4node::connDelete(const char * name)
{
	// ZS4_DEBUG(false);
	zs4node * exists = connLoad(name);
	if (exists == NULL)
	{
		// ZS4_DEBUG_STRING(name,"not found");
		return NULL;
	}

	zs4JsonString delurl, deldir;
	delurl.set(urlObject);
	delurl.write(name);
	delurl.lastChar('/');

	if (!strcmp(delurl.str, urlPublic))
	{
		// ZS4_DEBUG_STRING("cannot delete",delurl.str);
		return exists;
	}

	// ZS4_DEBUG_STRING("deleting", delurl.str);
	const char * dir = url2DirName(delurl.str, &deldir);
	if (dir != NULL && deldir.check() && zs4fs::IsDir(deldir.str))
	{
		//zs4fs::ClearDir(deldir.str);
		zs4fs::RmDir(deldir.str);

		bool found = false; connCount--;
		for (int i = 0; i < connCount; i++)
		{
			if (conn[i] == exists)found = true;
			if (found)conn[i] = conn[i + 1];
		}

		return NULL;
	}

	return exists;
}

zs4node * zs4node::connFind(const char * name)
{
	for (int i = 0; i < connCount; i++)
	{
		if (!strcmp(name, conn[i]->objectName()))
			return conn[i];
	}

	connLoad();

	for (int i = 0; i < connCount; i++)
	{
		if (!strcmp(name, conn[i]->objectName()))
			return conn[i];
	}

	return NULL;
}

zs4node * zs4node::connLoad(const char * name)
{
	if (!isName(name) || connCount >= ZS4_MAX_CONNECTIONS)
		return NULL;

	for (int i = 0; i < connCount; i++)
	{
		if (!strcmp(name, conn[i]->objectName()))
			return conn[i];
	}

	zs4JsonString url;
	url.set(urlObject); url.write(name); url.write("/");

	zs4node * nu = new zs4node();
	if (nu == NULL)
		return NULL;

	zs4JsonString fnam;
	const char * f = url2FileName(url.str, &fnam);
	if (f==NULL
		|| !zs4fs::IsFile(f)
		|| NULL == nu->ParseFile(f)
		)
	{
		delete nu;
		return NULL;
	}

	nu->connName.set(name);
	nu->connUrl.set(url.str);
	nu->urlObject = nu->connUrl.str;
	nu->urlUser = urlUser;
	nu->objectParent = this;

	conn[connCount++] = nu;

	return nu;
}

bool zs4node::get(zs4stream * out)
{
	// ZS4_DEBUG(false);

	changeStruct ctx = { this, NULL, NULL, false };
	zs4JsonText buf;

	filterObject(JObj, &buf);
	// ZS4_DEBUG_STRING("before get()", buf.str);
	buf.clear();

	filterObject(JObj, &buf, getFilter, "", &ctx);

	// ZS4_DEBUG_STRING("after get()", buf.str);

	out->write(buf.str);

	return true;
}

bool zs4node::exec(const json_value * in, zs4stream * out)
{
	// ZS4_DEBUG(false);

	connLoad();

	if (in != NULL)
	{
		error.clear();

		const json_value * val = getValue(in, "val");
		if (const json_value * var = getString(in, "var"))
		{
			zs4StringBuffer authPath; authPath.set("set."); authPath.write(var->u.string.ptr);

			if (var && authorize(authPath.str))
			{
				if (set(var->u.string.ptr, val))
					save(Object());
			}
		}

		return get(out);
	}

	// ZS4_DEBUG_STRING("writing ", "html");
	out->write("<!DOCTYPE html>\n");
	
	out->write("<html><head>\n");
	out->write("   <meta http-equiv=\"Content-Type\" content=\"text/html charset=utf-8\" />\n");
	out->write("   <title>zs4</title>\n");
	out->write("   <link rel=\"stylesheet\" type=\"text/css\" href=\"/zs4.css\" />\n");
	out->write("   <script src=\"/"ZS4".js\"></script>\n");
	out->write("</head>\n");

	out->write("<body");
	bool onload_done = false;
	if (const json_value * onload = getString(Object(),ZS4"."ZS4_HTML"."ZS4_ONLOAD) )
	{
		if (onload->u.string.ptr[0])
		{
			out->write(" onload=\"");
				out->write(onload->u.string.ptr);
			out->write("\"");
			onload_done = true;
		}
	}
	if (!onload_done)
	{
		out->write(" onload=\"zs4.zs4.html.onload()\"");
		//out->write(" onload=\"zs4.zs4.connect()\"");
		onload_done = true;
	}
	out->write(">\n");

	out->write("</body></html>\n");

	return true;
}

zs4error zs4node::save(const json_value * json)
{
	zs4file file;
	if (zs4SUCCESS != file.openWrite(url2FileName(urlObject)))
		return zs4FAILURE;

	JSON_WriteObjectStart(&file);
	JSON_WriteValue(&file, json);
	JSON_WriteObjectEnd(&file);

	return zs4SUCCESS;
}


const char * zs4node::url2FileName(const char * url, zs4JsonString * result)
{
	static zs4JsonString buf;
	if (result == NULL)result = &buf;

	url2DirName(url, result);
	result->write(ZS4_DOT_EXT);
	
	return result->str;
}

const char * zs4node::url2DirName(const char * url, zs4JsonString * result)
{
	static zs4JsonString buf;
	if (result == NULL)result = &buf;

	zs4JsonString work;
	work.set(url);
	strPlatformizePath(work.str);
	//bool work_ends_with_sep = false;
	result->set(rootFolder);
	result->write(work.str);
	strPlatformizePath(result->str);
	result->lastChar(PATH_SEPARATOR_CHAR);


	return result->str;
}

const char * zs4node::url2VarName(const char * url, zs4JsonString * result)
{

	static zs4JsonString buf;
	if (result == NULL)result = &buf;
	result->clear();

	zs4JsonString wk; size_t count = 0;
	const char ** arr = NULL;
	count = wk.tokenize(url, "/\\", &arr);
	for (size_t i = 0; i < count; i++)
	{
		if (i>0)result->write(".");
		result->write(arr[i]);
	}
	return result->str;
}

zs4error zs4node::WriteErrorMessage(const char * errmsg)
{
	if (errmsg == NULL || errmsg[0] == 0)
	{
		error.clear();
		return zs4SUCCESS;
	}

	error.write(errmsg);
	error.write("\n");

	return zs4SUCCESS;
}

const json_value * zs4node::resolveValue(const char * path)
{
	const json_value * ret = getValue(Object(), path);
	if (ret != NULL)
		return ret;

	zs4JsonString wk; const char ** tok = NULL;
	size_t pc = wk.tokenize(path, ".", &tok);

	if (tok == NULL || pc <= 0)
		return NULL;

	zs4node * conn = connLoad(tok[0]);
	if (conn == NULL)
		return NULL;

	if (pc == 1)
		return conn->Object();

	zs4JsonString nuPath;
	for (size_t i = 1; i < pc; i++)
	{
		if (nuPath.check())nuPath.write(".");
		nuPath.write(tok[i]);
	}

	return conn->resolveValue(nuPath.str);
}
