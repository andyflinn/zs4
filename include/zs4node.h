#ifndef ZS4_NODE_H
#define ZS4_NODE_H

#include "../include/zs4json.h"
#include "../include/zs4file.h"

#define ZS4 "zs4"
#define ZS4_VERSION (4)
#define ZS4_DOT_EXT "."ZS4

#define ZS4_ROOT_ID "/"
#define ZS4_PUBLIC_ID "/public/"

#define ZS4_SERVER_LOCALHOST "localhost"
#define ZS4_VAR "var"
#define ZS4_VER "ver"
#define ZS4_URL "url"
#define ZS4_ERR "err"

#define TAB_ZS4_SESSION "session"
// FORM FIELDS
#define ZS4_ERROR(err) "\"zs4.error."err"\""

#define ZS4_MAX_PATH (256)
#define ZS4_MAX_FEATURES (16)
#define ZS4_MAX_CONNECTIONS (256)


#define ZS4_LOGIN "login"

#define ZS4_ACTIVE "active"
//#define ZS4_ADD "zs4add"
#define ZS4_AM "am"
#define ZS4_BODY "body"
#define ZS4_BOOLEAN "boolean"
#define ZS4_CHANGE "change"
#define ZS4_CHILD "child"
#define ZS4_CONFIG "config"
#define ZS4_CONSTANT "constant"
#define ZS4_CREATE "create"
#define ZS4_DELETE "delete"
#define ZS4_DEMON "demon"
#define ZS4_EXPRESSION "exp"
#define ZS4_GET "get"
#define ZS4_JAVASCRIPT "js"
#define ZS4_HASH "hash"
#define ZS4_HTML "html"
#define ZS4_ITEM "item"
#define ZS4_LINK "link"
#define ZS4_LIST "list"
#define ZS4_LOAD "load"
#define ZS4_NULL "null"
#define ZS4_NUMBER "number"
#define ZS4_OBJECT "object"
#define ZS4_ONLOAD "onload"
#define ZS4_OWN "own"
#define ZS4_PASSWORD "password"
#define ZS4_PRIVATE "private"
#define ZS4_PROPERTY "property"
#define ZS4_PUBLIC "public"
#define ZS4_RUN "run"
#define ZS4_SALT "salt"
#define ZS4_SALT_SIZE (32)
#define ZS4_SESSION "session"
#define ZS4_SET "set"
#define ZS4_STRING "string"
#define ZS4_TRANSFORM "transform"
#define ZS4_TYPE "type"
#define ZS4_URL "url"

class tab_zs4_http;

class zs4node : public zs4json
{
public:
	class zs4 : public zs4json
	{
		friend class zs4node;
	public:
		inline void init(zs4node * o){ object = o;}
	protected:
		inline zs4(void){};
		inline virtual ~zs4(){};

		// these here utility methods
		bool userIsObject(void);
		bool userOwnsObject(void);
		bool isItem(void);
		int countLinks(void);
		int countProperties(void);
		int version(void);
		virtual const char * name(void);
		virtual zs4error get(zs4stream * out);
		virtual bool set(const json_value * in, zs4stream * out, const char * var, const json_value * val);
		zs4node * object;
	};
	zs4 feature;

	class zs4_link : public zs4
	{
	public:
		zs4_link(void);
		virtual ~zs4_link();
		virtual const char * name(void);
		virtual zs4error get(zs4stream * out);
		virtual bool set(const json_value * in, zs4stream * out, const char * var, const json_value * val);
		zs4JsonText config;
		int demon_id;
	};

	class zs4_login : public zs4
	{
	public:
		inline zs4_login(void){};
		inline virtual ~zs4_login(){};
		virtual const char * name(void);
		virtual zs4error get(zs4stream * out);
		virtual bool set(const json_value * in, zs4stream * out, const char * var, const json_value * val);
		bool configured(void);
	};

	class zs4_javascript : public zs4
	{
	public:
		inline zs4_javascript(void){};
		inline virtual ~zs4_javascript(){};
		virtual const char * name(void);
		virtual zs4error get(zs4stream * out);
		virtual bool set(const json_value * in, zs4stream * out, const char * var, const json_value * val);
	};

	class zs4_html : public zs4
	{
	public:
		inline zs4_html(void){};
		inline virtual ~zs4_html(){};
		virtual const char * name(void);
		virtual zs4error get(zs4stream * out);
		virtual bool set(const json_value * in, zs4stream * out, const char * var, const json_value * val);
	};

	class zs4_child : public zs4
	{
	public:
		inline zs4_child(void){};
		inline virtual ~zs4_child(){};
		virtual const char * name(void);
		virtual zs4error get(zs4stream * out);
		virtual bool set(const json_value * in, zs4stream * out, const char * var, const json_value * val);

		bool list(void);
		bool load(void);
	};

	zs4_link link;
	zs4_login login;
	zs4_child child;
	zs4_javascript javascript;
	zs4_html html;

	zs4node(void);
	virtual ~zs4node(void);
	
	inline void Reset(void){ rootFolder = urlUser = urlObject = NULL; }; // zs4Argument.Clear(); };

	virtual bool authorize(const char * zs4Property);
	static const char * rootFolder;

	zs4json zs4Argument;

	bool Execute(const char ** path, const json_value * in, zs4stream * out);
	zs4error InitializeDiskObject(zs4JsonText * result, const char * url);

	static const char * url2DirName(const char * url, zs4JsonString * result = NULL);
	static const char * url2FileName(const char * url, zs4JsonString * result = NULL);
	static const char * url2VarName(const char * url, zs4JsonString * result = NULL);
	static const char * urlUser;
	const char * urlObject;
	static const char * urlPublic;
	static const char * urlRoot;
	static zs4node * objectUser;
	inline const char * objectName(void){ return connName.str; };
	zs4error WriteErrorMessage(const char * errmsg);
	//static zs4streambuf session;

	const json_value * resolveValue(const char * path);

	// virtuals that can be implemented by servers
	static tab_zs4_http * server;
	inline virtual bool canDemonize(void) { return false; }
	inline virtual int demonize(zs4node * object) { return -1; };
private:
	static zs4JsonText session;

	zs4JsonString error;
	zs4error save(const json_value * json);
	bool exec(const json_value * in, zs4stream * out);
	bool get(zs4stream * out);
	zs4node * objectParent;
	static bool setFilter(const json_value * in, zs4stream * out, const char * path, void * ctx);
	static bool getFilter(const json_value * in, zs4stream * out, const char * path, void * ctx);
	const json_value * set(const char * path, const json_value * value);
	//zs4error get(const json_value*object, zs4stream * out, const char * path);
	zs4node * authorizer;
	int featureCount;
	zs4 * feat[ZS4_MAX_FEATURES];
	inline zs4 * featureAdd(zs4 * f){ f->init(this); feat[featureCount++] = f; return f; };
	
	zs4JsonString connUrl, connName;
	int connCount; bool connLoaded;
	zs4node * conn[ZS4_MAX_CONNECTIONS];
	int connLoad(void);
	zs4node * connLoad(const char * name);
	zs4node * connFind(const char * name);
	zs4node * connCreate(const char * name);
	zs4node * connDelete(const char * name);
	static bool urlPublicInitialized;

};

#endif

