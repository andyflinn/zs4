#include "zs4node.h"
#include "zs4ssl.h"
#include "../include/zs4file.h"

const char * zs4node::zs4_login::name(void)
{
	static const char * login = ZS4_LOGIN;
	return login;
}

bool zs4node::zs4_login::configured(void)
{
	const json_value * obj_salt = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_SALT);
	const json_value * obj_hash = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_HASH);

	if (obj_salt
		&& obj_salt->u.string.ptr[0]
		&& obj_hash
		&& obj_hash->u.string.ptr[0]
		)
		return true;

	return false;
}

zs4error zs4node::zs4_login::get(zs4stream * out)
{
	bool first = true;

	if (strcmp(object->urlObject, object->urlPublic))
	{
		if (!userIsObject() && !userOwnsObject())
		{
			if (!first){ out->write(","); }first = false;
			JSON_WriteStringValue(out, ZS4_PASSWORD, "");
		}

		if (userIsObject() || userOwnsObject())
		{
			if (!first){ out->write(","); }first = false;
			JSON_WriteStringValue(out, ZS4_CHANGE, "");
		}

		const json_value * obj_session = NULL;

		if (object->session.check()
			&& (obj_session = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_SESSION))
			&& (!strcmp(obj_session->u.string.ptr, object->session.str))
			)
		{
			if (!first){ out->write(","); }first = false;
			JSON_WriteStringValue(out, ZS4_SESSION, object->session.str);
		}
	}

	return zs4SUCCESS;
}

bool zs4node::zs4_login::set(const json_value * in, zs4stream * out, const char * var, const json_value * val)
{
	if (val == NULL)
		return false;

	const json_value * val_password = NULL;
	const json_value * val_change = NULL;

	if (val->type == json_object && !strcmp(var, ZS4"."ZS4_LOGIN))
	{
		val_password = getString(val, ZS4_PASSWORD);
		val_change = getString(val, ZS4_CHANGE);
	}
	else if (val->type == json_string)
	{
		if (!strcmp(var, ZS4"."ZS4_LOGIN"."ZS4_PASSWORD))
		{
			val_password = val;
		}
		else
		if (!strcmp(var, ZS4"."ZS4_LOGIN"."ZS4_CHANGE))
		{
			val_change = val;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}


	const json_value * obj_salt = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_SALT);
	const json_value * obj_hash = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_HASH);
	const json_value * obj_session = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_SESSION);
	const json_value * obj_public = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_PUBLIC);
	const json_value * obj_private = getString(object->Object(), ZS4"."ZS4_LOGIN"."ZS4_PRIVATE);

	bool obj_has_password = false;
	if (obj_salt
		&& obj_salt->u.string.ptr[0]
		&& obj_hash
		&& obj_hash->u.string.ptr[0]
		&& obj_session
		&& obj_session->u.string.ptr[0]
		)
	{
		obj_has_password = true;
	}

	bool user_is_logged_in = false;
	if (session.check()
		&& obj_session
		&& obj_session->u.string.ptr[0]
		&& !strcmp(session.str, obj_session->u.string.ptr)
		)
	{
		user_is_logged_in = true;
	}
	else if (!strcmp(object->urlUser, ZS4_ROOT_ID))
	{
		user_is_logged_in = true;
	}

	zs4JsonString work;
	zs4JsonString salt;
	zs4JsonString hash;
	zs4JsonString salted;
	zs4JsonString session;

	// user wants to change login password.
	if (user_is_logged_in&&val_change&&val_change->u.string.ptr[0])
	{
		char *p = NULL;
		zs4JsonString oldpwd;
		zs4JsonString newpwd;

		if (obj_has_password==true)
		{
			for (p = val_change->u.string.ptr; *p != 0 && isspace(*p); p++);
			while (*p != 0 && *p != ':'){ oldpwd.write(*p); p++; }
			if (*p != ':')
			{
				object->WriteErrorMessage(ZS4_ERROR(ZS4_LOGIN".change.is.oldpwd:newpwd"));
				return false;
			}
			p++;
			while (*p != 0){ newpwd.write(*p); p++; }

			// check old password
			salted.set(obj_salt->u.string.ptr); // salt for saving
			salted.write(oldpwd.str);
			tab_zs4_crypt::StringToSha256(salted.str, &hash);
			if (strcmp(hash.str, obj_hash->u.string.ptr))
			{
				object->WriteErrorMessage(ZS4_ERROR(ZS4_LOGIN".change.needs.oldpwd:newpwd"));
				return false;
			}
		}
		else 
		{
			newpwd.set(val_change->u.string.ptr);
		}

		// install new password
		salt.set(tab_zs4_crypt::RandomBytes(ZS4_SALT_SIZE, &work));
		salted.set(salt.str); // salt for saving
		salted.write(newpwd.str);
		tab_zs4_crypt::StringToSha256(salted.str, &hash);
		
		if (obj_session == NULL || obj_session->u.string.ptr[0] == 0) session.set(tab_zs4_crypt::RandomBytes(ZS4_SALT_SIZE, &work));
		else  session.set(obj_session->u.string.ptr);

		JSON_WriteStringValue(out,ZS4_SALT, salt.str);
		out->write(",");
		JSON_WriteStringValue(out, ZS4_HASH, hash.str);
		out->write(",");
		JSON_WriteStringValue(out, ZS4_SESSION, session.str);

		if (!object->session.check())
			object->session.set(session.str);

		return true;
	}

	if (obj_has_password)
	{
		if (!user_is_logged_in && val_password && val_password->u.string.ptr[0])
		{
			//ZS4_DEBUG_STRING("login attempt", val_password->u.string.ptr);

			salted.set(obj_salt->u.string.ptr); // salt for saving
			salted.write(val_password->u.string.ptr);
			tab_zs4_crypt::StringToSha256(salted.str, &hash);
			if (!strcmp(hash.str, obj_hash->u.string.ptr))
			{
				session.set(tab_zs4_crypt::RandomBytes(ZS4_SALT_SIZE, &work));

				JSON_WriteStringValue(out, ZS4_SALT, obj_salt->u.string.ptr);
				out->write(",");
				JSON_WriteStringValue(out, ZS4_HASH, obj_hash->u.string.ptr);
				out->write(",");
				JSON_WriteStringValue(out, ZS4_SESSION,work.str);

				object->urlUser = object->urlObject;
				object->session.set(session.str);

				//ZS4_DEBUG_STRING("login success", session.str);
				return true;
			}
			else
			{
				object->WriteErrorMessage(ZS4_ERROR(ZS4_LOGIN".bad"));
				return false;
			}

		}
//		JSON_WriteStringValue(out, ZS4_SALT, obj_salt->u.string.ptr);
//		out->Write(",");
//		JSON_WriteStringValue(out, ZS4_HASH, obj_hash->u.string.ptr);
//		out->Write(",");
//		JSON_WriteStringValue(out, ZS4_SESSION, obj_session->u.string.ptr);

//		return true;

	}
	return false;
}


