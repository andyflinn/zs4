#ifndef ZS4_UTIL
#define ZS4_UTIL

#include <zs4config.h>

	class c
	{
	public:
		inline static bool charUpperable(char c)	{
			if (c >= 'a' && c <= 'z')
				return true;

			return false;
		}
		inline static bool charLowerable(char c){
			if (c >= 'A' && c <= 'Z')
				return true;

			return false;
		}
		inline static char charMakeUpper(char c){
			if (charUpperable(c))
				return (c - 0x020);

			return c;
		}
		inline static char charMakeLower(char c){
			if (charLowerable(c))
				return (c + 0x020);

			return c;
		}
		inline static int charCompare(char c1, char c2){
			return c1 - c2;
		}

		inline static unsigned char strlen(const char * str){
			unsigned char ret = 0;
			while (str != nullptr && (*str != 0)){
				ret++;
			}
			return ret;
		}
		inline static int strcmp(const char * str1, const char * str2){
			for (;;)
			{
				if (*str1 == 0 && *str2 == 0)
					return 0;

				if (*str1 != *str2)
					return *str1 - *str2;

				str1++; str2++;
			}
		}
		inline static int stricmp(const char * str1, const char * str2){
			for (;;)
			{
				register char c1 = *str1++;
				register char c2 = *str2++;

				if (c1 == 0 && c2 == 0)
					return 0;

				c1 = charMakeLower(c1);
				c2 = charMakeLower(c2);

				if (c1 != c2)
					return c1 - c2;
			}
		}
		inline static int strncmp(const char * str1, const char * str2, ZS4LARGE n){
			char c1, c2, *s1 = (char *)str1, *s2 = (char *)str2;
			for (ZS4LARGE i = 0; i < n; i++)
			{
				c1 = *s1++;
				c2 = *s2++;
				if (c1 == 0 && c2 == 0) return 0;
				if (c1 != c2) return c1 - c2;
			}

			return 0;
		}

		inline static int strnicmp(const char * str1, const char * str2, ZS4LARGE n){
			char c1, c2, *s1 = (char *)str1, *s2 = (char *)str2;
			for (ZS4LARGE i = 0; i < n; i++)
			{
				c1 = *s1++;
				c2 = *s2++;
				if (c1 == 0 && c2 == 0) return 0;
				c1 = charMakeLower(c1);
				c2 = charMakeLower(c2);
				if (c1 != c2) return c1 - c2;
			}

			return 0;
		}
		inline static int strcharcount(const char * s, const char * chrs){
			int ret = 0;
			for (const char * cp = s; cp && *cp; cp++)
			{
				for (const char * p = chrs; p && *p; p++)
				{
					if (*cp == *p)
						ret++;
				}
			}

			return ret;
		}
		inline static int strcharcount(const char * s, const char c){
			char ch[2] = { c, 0 };
			return strcharcount(s, ch);
		}
		inline static int strcharswap(char org, char * str, char nu){
			int ret = 0;
			while (*str != 0) { if (*str == org) { *str = nu; ret++; } str++; }
			return ret;
		}
		inline static int striend(const char * str, const char * end){
			ZS4LARGE len_str = strlen(str);
			ZS4LARGE len_end = strlen(end);

			if (len_end > len_str)
				return 1;


			return stricmp(&str[len_str - len_end], end);
		}
		inline static int strend(const char * str, const char * end){
			ZS4LARGE len_str = strlen(str);
			ZS4LARGE len_end = strlen(end);

			if (len_end > len_str)
				return 1;


			return strcmp(&str[len_str - len_end], end);
		}
	};

	typedef class stream : public storage{
	public:
		inline stream(){}
		inline virtual e read(char & c){
			return FAILURE;
		}
		#define	INLINE_READ_FUNCTION() inline virtual e read(char & c)
		inline virtual e write(char c){
			return FAILURE;
		}
		#define	INLINE_WRITE_FUNCTION() inline virtual e write(char c)
		inline virtual ZS4LARGE readable(void){
			return 0;
		}
		#define	INLINE_READABLE_FUNCTION() inline virtual ZS4LARGE readable(void)
		inline virtual ZS4LARGE writeable(void){
			return 0;
		}
		#define	INLINE_WRITEABLE_FUNCTION() inline virtual ZS4LARGE writeable(void)
		inline virtual e flush(void){
			return FAILURE;
		}
		#define	INLINE_FLUSH_FUNCTION() inline virtual e flush(void)
		inline virtual e close(void){
			return FAILURE;
		}
		#define	INLINE_CLOSE_FUNCTION() inline virtual e close(void)
		inline virtual e rewind(void){
			return seek(0, SEEK_SET);
		}
		#define	INLINE_REWIND_FUNCTION() inline virtual e rewind(void)
		inline virtual e seekEnd(void){
			return seek(0, SEEK_END);
		}
		#define	INLINE_SEEKEND_FUNCTION() inline virtual e seekEnd(void)
		inline virtual e seek(ZS4LARGE offset, int origin){
			return FAILURE;
		}
		#define	INLINE_SEEK_FUNCTION() inline virtual e seek(ZS4LARGE offset, int origin)
		inline virtual e tell(ZS4LARGE & pPos){
			return FAILURE;
		}
		#define	INLINE_TELL_FUNCTION() inline virtual e tell(ZS4LARGE & pPos)
		inline virtual e size(ZS4LARGE & s){
			e err;
			ZS4LARGE pos = 0;
			ZS4LARGE size = 0;

			if ((err = tell(pos)) != SUCCESS)
				return err;

			if ((err = seek(0, SEEK_END)) != SUCCESS)
				return err;

			if ((err = tell(size)) != SUCCESS)
				return err;

			if ((err = seek(pos, SEEK_SET)) != SUCCESS)
				return err;

			s = size;

			return SUCCESS;
		}
		#define	INLINE_SIZE_FUNCTION() inline virtual e size(ZS4LARGE & s)

		inline virtual e writeString(const char * str){
			if (str == nullptr || (*str) == 0)
				return NODATA;

			unsigned char len = (unsigned char)strlen(str);
			for (unsigned char i = 0; i < len; i++){
				if (SUCCESS != write(str[i]))
					return FAILURE;
			}
			return SUCCESS;
		}
		#define	INLINE_WRITESTRING_FUNCTION() inline virtual e write(const char * str)

		inline e writeInteger(unsigned long long data, unsigned char base = 10){

			if (data & (1 << 63))
			{
				if (SUCCESS != write('-'))
					return FAILURE;

				data = (~data);
			}


			ZS4LARGE remainder = data;
			bool NOT_ZERO = false;

			ZS4LARGE MAX = (~0);
			ZS4LARGE count = 0;
			ZS4LARGE large = 1;
			while (large < (MAX/base)){
				large *= base; count++;
			}

			ZS4LARGE accumulator;
			zs4::symbol::numeric num;
			while (count)
			{
				accumulator = 0;
				while (remainder > large)
				{
					remainder-=large;
					accumulator++;
					NOT_ZERO = true;
				}

				if (NOT_ZERO){
					if (SUCCESS != write((char)(num.data()[accumulator])))
						return BUFFEROVERFLOW;
				}

				large /= base;
				count--;
			}

			if (remainder)
			{
				if (SUCCESS != write((char)(num.data()[remainder])))
					return BUFFEROVERFLOW;

			}
			else if (!NOT_ZERO)
			{
				if (SUCCESS != write((char)(num.data()[0])))
					return BUFFEROVERFLOW;
			}
			return SUCCESS;
		}
		inline e writeJsonString(const char * out)
		{
			for (const char * str = out; str && *str; str++)
			{
				switch (*str)
				{
				case '\\': if (SUCCESS != writeString("\\\\"))return FAILURE; break;
				case '"': if (SUCCESS != writeString("\\\""))return FAILURE; break;
				case '/': if (SUCCESS != writeString("\\/"))return FAILURE; break;
				case '\b': if (SUCCESS != writeString("\\b"))return FAILURE; break;
				case '\f': if (SUCCESS != writeString("\\f"))return FAILURE; break;
				case '\n': if (SUCCESS != writeString("\\n"))return FAILURE; break;
				case '\r': if (SUCCESS != writeString("\\r"))return FAILURE; break;
				case '\t': if (SUCCESS != writeString("\\t"))return FAILURE; break;
				default: if (SUCCESS != write(*str))return FAILURE; break;
				}
			}
			return SUCCESS;
		}
	}stream;

	typedef class json{
	protected:
		typedef long long json_int;
		typedef struct
		{
			long long max_memory;
			int settings;
		} json_settings;

#		define json_relaxed_commas 1

		typedef enum
		{
			json_none,
			json_object,
			json_array,
			json_integer,
			json_double,
			json_string,
			json_boolean,
			json_null

		} json_type;

		typedef struct _json_value
		{
			struct _json_value * parent;

			json_type type;

			union
			{
				int boolean;
				long long integer;
				double dbl;

				struct
				{
					json_int length;
					char * ptr; /* null terminated */

				} string;

				struct
				{
					json_int length;

					struct
					{
						char * name;
						struct _json_value * value;

					} *values;

				} object;

				struct
				{
					json_int length;
					struct _json_value ** values;

				} array;

			} u;

			union
			{
				struct _json_value * next_alloc;
				void * object_mem;

			} _reserved;

		} json_value;

	public:
		typedef class parser
		{
			json_value * JObj;
			ZS4CHAR buffer[ZS4_PARSER_SIZE];
			ZS4LARGE len;

			inline virtual ZS4CHAR * zs4alloc(ZS4LARGE size){
				if (size > (ZS4_PARSER_SIZE - len))
					return nullptr;

				ZS4CHAR * mem = &buffer[len];
				len += size;

				memset(mem, 0, size);

				return mem;
			}

		public:
			inline parser(void){
				len = 0;
				JObj = nullptr;
			}

			inline json_value * value(void){ return JObj; }
			inline json_value * parse(const char * json){

				len = 0;
				JObj = nullptr;

				json_settings settings; memset(&settings, 0, sizeof(json_settings));
				settings.max_memory = sizeof(buffer);

				if (json_value * nuJv = json_parse_ex(&settings, json))
				{
					JObj = nuJv;
					return nuJv;
				}

				return nullptr;
			}
		private:
			inline static ZS4SHORT hex_value(char c)
			{
				if (c >= 'A' && c <= 'F')
					return (c - 'A') + 10;

				if (c >= 'a' && c <= 'f')
					return (c - 'a') + 10;

				if (c >= '0' && c <= '9')
					return c - '0';

				return 0xFF;
			}

			typedef struct
			{
				json_settings settings;
				int first_pass;

				json_int used_memory;

				// 2 members added by zs4
				ZS4LARGE device_max;
				ZS4LARGE ulong_max;

			} json_state;

			inline int new_value
				(json_state * state, json_value ** top, json_value ** root, json_value ** alloc, json_type type)
			{
				json_value * value;
				ZS4LARGE values_size;

				if (!state->first_pass)
				{
					value = *top = *alloc;
					*alloc = (*alloc)->_reserved.next_alloc;

					if (!*root)
						*root = value;

					switch (value->type)
					{
					case json_array:

						if (!(value->u.array.values = (json_value **)this->zs4alloc
							(((ZS4LARGE)value->u.array.length + 1) * sizeof(json_value *))))
						{
							return 0;
						}

						value->u.array.length = 0;
						break;

					case json_object:

						values_size = (ZS4LARGE)(sizeof(*value->u.object.values) * (ZS4LARGE)value->u.object.length);

						if (!((*(void **)&value->u.object.values) = this->zs4alloc
							(values_size + ((ZS4LARGE)value->u.object.values))))
						{
							return 0;
						}

						value->_reserved.object_mem = (*(char **)&value->u.object.values) + values_size;

						value->u.object.length = 0;
						break;

					case json_string:

						if (!(value->u.string.ptr = (char *)this->zs4alloc
							((ZS4LARGE)(value->u.string.length + 1) * sizeof(char))))
						{
							return 0;
						}

						value->u.string.length = 0;
						break;

					default:
						break;
					};

					return 1;
				}

				value = (json_value *)this->zs4alloc(sizeof(json_value));

				if (!value)
					return 0;

				if (!*root)
					*root = value;

				value->type = type;
				value->parent = *top;

				if (*alloc)
					(*alloc)->_reserved.next_alloc = value;

				*alloc = *top = value;

				return 1;
			}

#define e_off \
	((int)(i - cur_line_begin))

#define whitespace \
   case '\n': ++cur_line;  cur_line_begin = i; \
   case ' ': case '\t': case '\r'

#define string_add(b)  \
	do { if (!state.first_pass) string[string_length] = b;  ++string_length; } while (0);

			const static long
				flag_next = 1, flag_reproc = 2, flag_need_comma = 4, flag_seek_value = 8,
				flag_escaped = 16, flag_string = 32, flag_need_colon = 64, flag_done = 128,
				flag_num_negative = 256, flag_num_zero = 512, flag_num_e = 1024,
				flag_num_e_got_sign = 2048, flag_num_e_negative = 4096;

			inline json_value * json_parse_ex(json_settings * settings, const char * json)
			{
				char error[128];
				ZS4LARGE cur_line;
				const char * cur_line_begin, *i;
				json_value * top, *root, *alloc = 0;
				json_state state;
				long flags;
				long num_digits, num_fraction, num_e;

				error[0] = '\0';

				memset(&state, 0, sizeof(json_state));
				memcpy(&state.settings, settings, sizeof(json_settings));

				memset(&state.device_max, 0xFF, sizeof(state.device_max));
				memset(&state.ulong_max, 0xFF, sizeof(state.ulong_max));

				state.device_max -= 8; /* limit of how much can be added before next check */
				state.ulong_max -= 8;

				for (state.first_pass = 1; state.first_pass >= 0; --state.first_pass)
				{
					ZS4SHORT uchar;
					ZS4CHAR uc_b1, uc_b2, uc_b3, uc_b4;
					char * string;
					ZS4LARGE string_length;

					top = root = 0;
					flags = flag_seek_value;

					cur_line = 1;
					cur_line_begin = json;

					for (i = json;; ++i)
					{
						char b = *i;

						if (flags & flag_done)
						{
							if (!b)
								break;

							switch (b)
							{
							whitespace:
								continue;

							default:
								goto e_failed;
							};
						}

						if (flags & flag_string)
						{
							if (!b)
							{
								goto e_failed;
							}

							if (string_length > state.device_max)
								goto e_overflow;

							if (flags & flag_escaped)
							{
								flags &= ~flag_escaped;

								switch (b)
								{
								case 'b':  string_add('\b');  break;
								case 'f':  string_add('\f');  break;
								case 'n':  string_add('\n');  break;
								case 'r':  string_add('\r');  break;
								case 't':  string_add('\t');  break;
								case 'u':

									if ((uc_b1 = (ZS4CHAR)hex_value(*++i)) == 0xFF || (uc_b2 = (ZS4CHAR)hex_value(*++i)) == 0xFF
										|| (uc_b3 = (ZS4CHAR)hex_value(*++i)) == 0xFF || (uc_b4 = (ZS4CHAR)hex_value(*++i)) == 0xFF)
									{
										goto e_failed;
									}

									uc_b1 = uc_b1 * 16 + uc_b2;
									uc_b2 = uc_b3 * 16 + uc_b4;

									uchar = ((char)uc_b1) * 256 + uc_b2;

									if (sizeof(char) >= sizeof(ZS4SHORT) || (uc_b1 == 0 && uc_b2 <= 0x7F))
									{
										string_add((char)uchar);
										break;
									}

									if (uchar <= 0x7FF)
									{
										if (state.first_pass)
											string_length += 2;
										else
										{
											string[string_length++] = 0xC0 | ((uc_b2 & 0xC0) >> 6) | ((uc_b1 & 0x7) << 2);
											string[string_length++] = 0x80 | (uc_b2 & 0x3F);
										}

										break;
									}

									if (state.first_pass)
										string_length += 3;
									else
									{
										string[string_length++] = 0xE0 | ((uc_b1 & 0xF0) >> 4);
										string[string_length++] = 0x80 | ((uc_b1 & 0xF) << 2) | ((uc_b2 & 0xC0) >> 6);
										string[string_length++] = 0x80 | (uc_b2 & 0x3F);
									}

									break;

								default:
									string_add(b);
								};

								continue;
							}

							if (b == '\\')
							{
								flags |= flag_escaped;
								continue;
							}

							if (b == '"')
							{
								if (!state.first_pass)
									string[string_length] = 0;

								flags &= ~flag_string;
								string = 0;

								switch (top->type)
								{
								case json_string:

									top->u.string.length = string_length;
									flags |= flag_next;

									break;

								case json_object:

									if (state.first_pass)
										(*(char **)&top->u.object.values) += string_length + 1;
									else
									{
										top->u.object.values[top->u.object.length].name
											= (char *)top->_reserved.object_mem;

										(*(char **)&top->_reserved.object_mem) += string_length + 1;
									}

									flags |= flag_seek_value | flag_need_colon;
									continue;

								default:
									break;
								};
							}
							else
							{
								string_add(b);
								continue;
							}
						}

						if (flags & flag_seek_value)
						{
							switch (b)
							{
							whitespace:
								continue;

							case ']':

								if (top->type == json_array)
									flags = (flags & ~(flag_need_comma | flag_seek_value)) | flag_next;
								else if (!(state.settings.settings & json_relaxed_commas))
								{
									goto e_failed;
								}

								break;

							default:

								if (flags & flag_need_comma)
								{
									if (b == ',')
									{
										flags &= ~flag_need_comma;
										continue;
									}
									else
									{
										goto e_failed;
									}
								}

								if (flags & flag_need_colon)
								{
									if (b == ':')
									{
										flags &= ~flag_need_colon;
										continue;
									}
									else
									{
										goto e_failed;
									}
								}

								flags &= ~flag_seek_value;

								switch (b)
								{
								case '{':

									if (!new_value(&state, &top, &root, &alloc, json_object))
										goto e_alloc_failure;

									continue;

								case '[':

									if (!new_value(&state, &top, &root, &alloc, json_array))
										goto e_alloc_failure;

									flags |= flag_seek_value;
									continue;

								case '"':

									if (!new_value(&state, &top, &root, &alloc, json_string))
										goto e_alloc_failure;

									flags |= flag_string;

									string = top->u.string.ptr;
									string_length = 0;

									continue;

								case 't':

									if (*(++i) != 'r' || *(++i) != 'u' || *(++i) != 'e')
										goto e_unknown_value;

									if (!new_value(&state, &top, &root, &alloc, json_boolean))
										goto e_alloc_failure;

									top->u.boolean = 1;

									flags |= flag_next;
									break;

								case 'f':

									if (*(++i) != 'a' || *(++i) != 'l' || *(++i) != 's' || *(++i) != 'e')
										goto e_unknown_value;

									if (!new_value(&state, &top, &root, &alloc, json_boolean))
										goto e_alloc_failure;

									flags |= flag_next;
									break;

								case 'n':

									if (*(++i) != 'u' || *(++i) != 'l' || *(++i) != 'l')
										goto e_unknown_value;

									if (!new_value(&state, &top, &root, &alloc, json_null))
										goto e_alloc_failure;

									flags |= flag_next;
									break;

								default:

									if (isdigit(b) || b == '-')
									{
										if (!new_value(&state, &top, &root, &alloc, json_integer))
											goto e_alloc_failure;

										if (!state.first_pass)
										{
											while (isdigit(b) || b == '+' || b == '-'
												|| b == 'e' || b == 'E' || b == '.')
											{
												b = *++i;
											}

											flags |= flag_next | flag_reproc;
											break;
										}

										flags &= ~(flag_num_negative | flag_num_e |
											flag_num_e_got_sign | flag_num_e_negative |
											flag_num_zero);

										num_digits = 0;
										num_fraction = 0;
										num_e = 0;

										if (b != '-')
										{
											flags |= flag_reproc;
											break;
										}

										flags |= flag_num_negative;
										continue;
									}
									else
									{
										goto e_failed;
									}
								};
							};
						}
						else
						{
							switch (top->type)
							{
							case json_object:

								switch (b)
								{
								whitespace:
									continue;

								case '"':

									if (flags & flag_need_comma && (!(state.settings.settings & json_relaxed_commas)))
									{
										goto e_failed;
									}

									flags |= flag_string;

									string = (char *)top->_reserved.object_mem;
									string_length = 0;

									break;

								case '}':

									flags = (flags & ~flag_need_comma) | flag_next;
									break;

								case ',':

									if (flags & flag_need_comma)
									{
										flags &= ~flag_need_comma;
										break;
									}

								default:

									goto e_failed;
								};

								break;

							case json_integer:
							case json_double:

								if (isdigit(b))
								{
									++num_digits;

									if (top->type == json_integer || flags & flag_num_e)
									{
										if (!(flags & flag_num_e))
										{
											if (flags & flag_num_zero)
											{
												goto e_failed;
											}

											if (num_digits == 1 && b == '0')
												flags |= flag_num_zero;
										}
										else
										{
											flags |= flag_num_e_got_sign;
											num_e = (num_e * 10) + (b - '0');
											continue;
										}

										top->u.integer = (top->u.integer * 10) + (b - '0');
										continue;
									}

									num_fraction = (num_fraction * 10) + (b - '0');
									continue;
								}

								if (b == '+' || b == '-')
								{
									if ((flags & flag_num_e) && !(flags & flag_num_e_got_sign))
									{
										flags |= flag_num_e_got_sign;

										if (b == '-')
											flags |= flag_num_e_negative;

										continue;
									}
								}
								else if (b == '.' && top->type == json_integer)
								{
									if (!num_digits)
									{
										goto e_failed;
									}

									top->type = json_double;
									top->u.dbl = (double)top->u.integer;

									num_digits = 0;
									continue;
								}

								if (!(flags & flag_num_e))
								{
									if (top->type == json_double)
									{
										if (!num_digits)
										{
											goto e_failed;
										}

										top->u.dbl += ((double)num_fraction) / (pow(10, (double)num_digits));
									}

									if (b == 'e' || b == 'E')
									{
										flags |= flag_num_e;

										if (top->type == json_integer)
										{
											top->type = json_double;
											top->u.dbl = (double)top->u.integer;
										}

										num_digits = 0;
										flags &= ~flag_num_zero;

										continue;
									}
								}
								else
								{
									if (!num_digits)
									{
										goto e_failed;
									}

									top->u.dbl *= pow(10, (double)(flags & flag_num_e_negative ? -num_e : num_e));
								}

								if (flags & flag_num_negative)
								{
									if (top->type == json_integer)
										top->u.integer = -top->u.integer;
									else
										top->u.dbl = -top->u.dbl;
								}

								flags |= flag_next | flag_reproc;
								break;

							default:
								break;
							};
						}

						if (flags & flag_reproc)
						{
							flags &= ~flag_reproc;
							--i;
						}

						if (flags & flag_next)
						{
							flags = (flags & ~flag_next) | flag_need_comma;

							if (!top->parent)
							{
								/* root value done */

								flags |= flag_done;
								continue;
							}

							if (top->parent->type == json_array)
								flags |= flag_seek_value;

							if (!state.first_pass)
							{
								json_value * parent = top->parent;

								switch (parent->type)
								{
								case json_object:

									parent->u.object.values
										[parent->u.object.length].value = top;

									break;

								case json_array:

									parent->u.array.values
										[parent->u.array.length] = top;

									break;

								default:
									break;
								};
							}

							if ((++top->parent->u.array.length) > (json_int)state.device_max)
								goto e_overflow;
							top = top->parent;

							continue;
						}
					}

					alloc = root;
				}

				return root;

			e_unknown_value:
			e_alloc_failure :
			e_overflow :
				   e_failed :

							if (state.first_pass)
								alloc = root;

							while (alloc)
							{
								top = alloc->_reserved.next_alloc;
								alloc = top;
							}

							return 0;
			}
		};

		typedef	class value : public storage
		{
		public:
			inline virtual e init(void){
				return FAILURE;
			}
			inline virtual e save(stream & out) = 0;
			inline virtual value & operator =(const char *in) = 0;
			inline virtual value & operator =(const json_value * in) = 0;
		}value;

		typedef	class boolean : public value
		{
			const char * troo = "true";
			const char * falz = "false";
		public:
			bool v;
			inline boolean(){ v = false; }
			inline virtual ~boolean(){}
			inline virtual e save(stream & out){
				if (v) return out.writeString(troo);
				else return out.writeString(falz);
			}

			inline virtual value & operator =(const char *in){
				if (!c::strcmp(in, troo))
					v = true;
				else v = false;
				return (*this);
			}
			inline virtual value & operator =(const json_value * in){
				if (in != nullptr && in->type == json_boolean && in->u.boolean)
					v = true;
				else v = false;

				return (*this);
			}
		}boolean;

		typedef	class integer : public value
		{
			static json_int atoi(const char * s, ZS4CHAR base = 10){
				const json_int MAX = (~0);
				json_int data;
				zs4::symbol::numeric num;

				bool negative = false;
				if (*s == '-'){ s++; negative = true; }

				for (ZS4CHAR i = 0; s[i] != 0 && s[i] != '\n'; i++){
					ZS4LARGE lu = num.lookup((ZS4CHAR)s[i], base);
					if (lu >= (ZS4LARGE)MAX){
						data = 0;
						return data;
					}

					ZS4LARGE nu = (ZS4LARGE)((ZS4LARGE)((ZS4LARGE)data*(ZS4LARGE)base) + (ZS4LARGE)lu);
					if ((ZS4LARGE)nu > (ZS4LARGE)MAX){
						data = MAX;
						return MAX;
					}
					data = nu;
				}

				if (negative) data = (-data);

				return data;
			}
		public:
			json_int v;
			inline integer(){ v = false; }
			inline virtual ~integer(){}
			inline virtual e save(stream & out){
				return out.writeInteger(v);
			}

			inline virtual value & operator =(const char *in){
				v = atoi(in);
				return(*this);
			}
			inline virtual value & operator =(const json_value * in){
				if (in != nullptr && in->type == json_integer)
					v = in->u.integer;
				else v = 0;
				return (*this);
			}
		}integer;

		typedef class analog : public value
		{
		public:
			ZS4ANALOG v;
			inline analog(){ v = 0.0; }
			inline virtual ~analog(){}
			inline virtual e save(stream & out){
				char buf[128];
				sprintf(buf, "%g", v);
				return out.writeString(buf);
			}

			inline virtual value & operator =(const char *in){
				v = atof(in);
				return(*this);
			}
			inline virtual value & operator =(const json_value * in){
				if (in != nullptr && in->type == json_double)
					v = in->u.dbl;
				else v = 0;
				return (*this);
			}
		}analog;

		typedef class string : public value
		{
			char v[256];
		public:
			inline string(){ memset(v, 0, sizeof(v)); }
			inline virtual ~string(){}
			inline virtual e save(stream & out){
				return out.writeJsonString(v);
			}

			inline virtual value & operator =(const char *in){
				if (strlen(in)>(sizeof(v) - 1))
					return(*this);
				strcpy(v, in);
				return(*this);
			}
			inline virtual value & operator =(const json_value * in){
				if (in == nullptr || in->type != json_string || in->u.string.length > (sizeof(v) - 1))
					return (*this);

				strcpy(v, in->u.string.ptr);
				return(*this);
			}
		}string;

		/*
		typedef class object : public value
		{
			char * data;
			size_t size;
		public:
			inline object(){
				data=nullptr;
				size = 0;
			}
			inline virtual ~object(){}
			inline virtual e save(stream & out){
				return out.writeJsonString(v);
			}

			inline virtual value & operator =(const char *in){
				if (strlen(in)>(sizeof(v) - 1))
					return(*this);
				strcpy(v, in);
				return(*this);
			}
			inline virtual value & operator =(const json_value * in){
				if (in == nullptr || in->type != json_string || in->u.string.length > (sizeof(v) - 1))
					return (*this);

				strcpy(v, in->u.string.ptr);
				return(*this);
			}
		}object;
		*/
	}json;


	typedef class fileinfo
	{
		ZS4CHAR buffer[256];
	public:
		inline fileinfo()
		{
			clear();
		}
		inline e clear(void){
			buffer[0] = 0;
			size = 0;
			created = modified = 0;
			readonly = hidden = isdir = false;
			slash_count = 0;
			return SUCCESS;
		}
		inline static int CompareSlashCountAscend(const void * v1, const void * v2)
		{
			register fileinfo * c1 = ((fileinfo**)v1)[0];
			register fileinfo * c2 = ((fileinfo**)v2)[0];

			return c1->slash_count - c2->slash_count;
		}
		inline static int CompareSlashCountDescend(const void * v1, const void * v2)
		{
			return -CompareSlashCountAscend(v1, v2);
		}
		inline static int CompareFileSizeAscend(const void * v1, const void * v2)
		{
			register fileinfo * c1 = ((fileinfo**)v1)[0];
			register fileinfo * c2 = ((fileinfo**)v2)[0];

			if (c1->isdir)
			{
				if (c2->isdir)
					return 0;

				return -1;
			}
			else
				if (c2->isdir)
					return 1;

			if (c1->size < c2->size)
				return -1;

			if (c1->size > c2->size)
				return 1;

			return 0;
		}
		inline static int CompareFileSizeDescend(const void * v1, const void * v2)
		{
			return -CompareFileSizeAscend(v1, v2);
		}
		inline e info(const char * objectname)
		{
			if (strlen(objectname) > sizeof(buffer))
				return FAILURE;

			e err = SUCCESS;

			struct stat buf;
			memset(&buf, 0, sizeof(buf));

			if (stat((const char*)objectname, &buf))
				return FAILURE;

			size = buf.st_size;
			created = buf.st_mtime;
			modified = buf.st_mtime;

			isdir = (S_ISDIR(buf.st_mode));

			strcpy((char*)buffer, (const char*)objectname);

			slash_count = c::strcharcount(objectname, "/\\");
			return err;
		}

		size_t size;
		time_t created;
		time_t modified;
		bool readonly, hidden, isdir;
		int slash_count;
	}fileinfo;
	typedef class file : public stream
	{
	protected:
		ZS4LARGE read_able;
		fileinfo info;
		FILE * handle;
		bool open_for_write;
	public:
		inline file(void){
			handle = nullptr;
			close();
		};
		inline virtual ~file(void){
			close();
		};

		inline e openRead(const char * name){
			close();

			if (SUCCESS != info.info(name))
				return FILEINFOERROR;

			handle = fopen(name, "rb");
			if (handle == nullptr)
				return FILEOPENERROR;

			read_able = info.size;
			open_for_write = false;
			return SUCCESS;
		}
		inline e openWrite(const char * name){
			close();
			handle = fopen(name, "w+");
			if (handle == nullptr)
				return FILEOPENERROR;

			info.info(name);
			open_for_write = true;
			return SUCCESS;
		}
		inline e close(void){
			if (handle != nullptr)
			{
				fclose(handle);
				handle = nullptr;
			}
			read_able = 0;
			info.clear();
			open_for_write = false;
			return SUCCESS;
		}

		INLINE_READABLE_FUNCTION(){
			if (handle == nullptr) return 0;
			return read_able;
		}
		INLINE_WRITEABLE_FUNCTION(){
			if (handle == nullptr) return 0;
			return (~0);
		}

		INLINE_READ_FUNCTION(){
			if (!readable())
				return FAILURE;

			c = fgetc(handle);
			if (c == EOF)
				return FAILURE;

			return SUCCESS;
		}
		INLINE_WRITE_FUNCTION(){
			if (!writeable())
				return FAILURE;

			char b = c;
			if (0 == fwrite(&b, 1, 1, handle))
				return FAILURE;

			return SUCCESS;
		}
		INLINE_SEEK_FUNCTION(){
			if (handle == nullptr)
				return FAILURE;

			return (e)fseek((FILE*)handle, (long)offset, (int)origin);
		}
		INLINE_TELL_FUNCTION(){
			if (handle == nullptr)
			{
				pPos = 0;
				return FAILURE;
			}

			pPos = ftell((FILE*)handle);

			return SUCCESS;
		}
		INLINE_SIZE_FUNCTION(){
			if (nullptr == handle)
			{
				s = 0;
				return FAILURE;
			}

			if (open_for_write)
			{
				return FAILURE;
			}

			s = info.size;
			return SUCCESS;
		}

	}file;
	typedef class in : public file
	{
	public:
		INLINE_MEMORY_FUNCTION(){return nullptr;} 
		INLINE_BITS_FUNCTION(){ return 0; }

		INLINE_READABLE_FUNCTION(){ return 1; }

		inline in(void){
			handle = stdin;
		};
		inline virtual ~in(void){
			handle = nullptr;
		};
	}in;
	typedef  class out : public file
	{
	public:
		INLINE_MEMORY_FUNCTION(){ return nullptr; }
		INLINE_BITS_FUNCTION(){ return 0; }

		INLINE_WRITEABLE_FUNCTION(){ return 1; }
		INLINE_WRITESTRING_FUNCTION(){
			puts(str);
			return SUCCESS;
		}
		inline out(void){
			handle = stdout;
		};
		inline virtual ~out(void){
			handle = nullptr;
		};
	}out;
	typedef class fs
	{
	public:
		inline fs(){
			count = 0;
		}
		inline virtual ~fs(){
		}
		static const ZS4LARGE ZS4_MAX_DIR_SIZE = 256;
		static const ZS4LARGE TAB_FS_MAX_PATH_LENGTH = 256;

		inline static bool isFile(const char * path){
			struct stat ino;

			if (stat((const char *)path, &ino))
				return false;

			if (S_ISREG(ino.st_mode))
				return true;

			return false;
		}
		inline static bool isDir(const char * path){
			struct stat ino;

			if (stat((const char *)path, &ino))
				return false;

			if (S_ISDIR(ino.st_mode))
				return true;

			return false;
		}
		inline static e cd(const char * nu){
			return (e)chdir((const char *)nu);
		}
		inline static e mkDir(const char * name){
			char dirnam[TAB_FS_MAX_PATH_LENGTH];
			char pdir[TAB_FS_MAX_PATH_LENGTH];

			strncpy(dirnam, (const char *)name, sizeof(dirnam));

			char * f = (char*)dirnam, *t = pdir;

			while (*f != 0)
			{
				//char sav = *f;
				*t++ = *f++; *t = 0;
				if ((*f == '/') || (*f == 0))
				{
#ifdef _WIN32
					_mkdir(pdir);
#else
					mkdir(pdir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
				}
			}

			if (!isDir(name))
			{
				return FAILURE;
			}

			return SUCCESS;
		}
		inline static e rmFile(const char * name){
			if (!unlink((const char *)name)) return SUCCESS;
			return FAILURE;
		}
		inline static e rmDir(const char * name){
			if (!rmdir((const char *)name)) return SUCCESS;
			return FAILURE;
		}
		inline static e info(const char * objectname, fileinfo * info){
			if (objectname == nullptr || objectname[0] == 0 || info == nullptr)
				return FAILURE;

			return info->info(objectname);
		}

		inline static time_t created(const char * fnam){
			fileinfo info;

			if ((!isFile(fnam))
				|| (SUCCESS != fs::info(fnam, &info))
				)
				return 0;

			return info.created;
		}
		inline static time_t modified(const char * fnam){
			fileinfo info;

			if ((!fs::isFile(fnam))
				|| (SUCCESS != fs::info(fnam, &info))
				)
				return 0;

			return info.modified;
		}
		inline size_t list(const char * name, bool hidden_files){

			count = 0;

			if (isFile(name))
				return 0;

			if (!isDir(name))
				return 0;

			fileinfo * nu;

			tinydir_dir dir;
			if (tinydir_open(&dir, ".") == -1)
				return count;

			while (dir.has_next)
			{
				tinydir_file file;
				if (tinydir_readfile(&dir, &file) == -1)
					break;

				if (strcmp(file.name, ".") && strcmp(file.name, "..") && strcmp(file.name, ".zs4"))
				{

					if ((nullptr == (nu = nuStat())) || SUCCESS != nu->info(file.name))
						break;
				}
				tinydir_next(&dir);
			}

			tinydir_close(&dir);
			return count;
		}

		inline fileinfo * nuStat(void)	{
			if (count >= (ZS4_MAX_DIR_SIZE - 1))
				return nullptr;

			statData[count].clear();
			fileinfo * ret = &statData[count];
			statArray[count] = &statData[count];
			count++;
			return ret;
		}
		size_t count;
		fileinfo * statArray[ZS4_MAX_DIR_SIZE];
		fileinfo statData[ZS4_MAX_DIR_SIZE];
	}fs;

#endif
