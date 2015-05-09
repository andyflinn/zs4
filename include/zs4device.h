
#include <zs4config.h>

#ifndef device
#define device char
#define intclass byte
#endif

typedef class intclass
{
public:

	typedef class event
	{
	public:
		typedef class set
		{
		protected:
			inline static const unsigned device * ASCII(void){
				static const unsigned device ASCII[128] = {
					0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
					0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
					0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
					0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
					0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
					0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
					0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
					0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
				};
				return ASCII;
			}
			inline bool valueReverse(){ return false; }
		public:
			inline virtual const unsigned device count(void) = 0;
			inline virtual const unsigned device * data(void) = 0;
			inline unsigned device lookup(ZS4CHAR event){

				for (unsigned device i = 0; i < count(); i++){
					if ((unsigned device)data()[i] == (unsigned device)event)
					{
						if (valueReverse()) { return (unsigned device)(count() - i); }
						return (unsigned device)i;
					}
				}
				return (unsigned device)(~0);
			}
			inline unsigned device bits(void){
				unsigned device m = (~0)>>1;
				unsigned device r = (unsigned device)((sizeof(unsigned device) << 3) - 1);
				while (((m >> 1)&((unsigned device)count())) >= count()){
					m >>= 1; r--;
				}
				return r;
			}
		}set;
		typedef class name : public set
		{
		public:
			inline virtual const unsigned device count(void){ return 26; }
			inline virtual const unsigned device * data(void){
				return &(ASCII())['a'];
			}

		}name;
		typedef class space : public set
		{
		public:
			typedef enum {
				s, a, b, f, n, r, t, v,
				SIZE
			} index;
			inline virtual const unsigned device count(void){ return SIZE; }
			inline virtual const unsigned device * data(void){
				static unsigned device data[SIZE] = { ' ', '\a', '\b', '\f', '\n', '\r', '\t', '\v' };
				return data;
			}

		}space;
		typedef class numeric : public set
		{
		public:
			typedef enum {
				n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
				SIZE
			} index;
			inline virtual const unsigned device count(void){ return (unsigned device)SIZE; }
			inline virtual const unsigned device * data(void){
				static unsigned device data[SIZE] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
				return data;
			}
		}numeric;
		typedef class binary : public numeric
		{
		public:
			inline virtual const unsigned device count(void){ return 2; }
		}binary;
		typedef class octal : public numeric
		{
		public:
			inline virtual const unsigned device count(void){ return 8; }
		}octal;
		typedef class decimal : public numeric
		{
		public:
			inline virtual const unsigned device count(void){ return 10; }
		}decimal;
		typedef class hexadecimal : public numeric
		{
		public:
			inline virtual const unsigned device count(void){ return 16; }
		}hexadecimal;
		typedef class opcode : public set
		{
		public:
			typedef enum {
				_equal_, _or_, _and_, _plus_, _minus_,
				SIZE
			} index;
			inline virtual const unsigned device count(void){ return (unsigned device)SIZE; }
			inline virtual const unsigned device * data(void){
				static unsigned device data[SIZE] = {
					'=', '|', '&', '+', '-' };
				return data;
			}

		}opcode;
		typedef class container : public set
		{
		public:
			typedef enum {
				parenthesis, curly, square, less,
				SIZE
			} index;
			inline virtual const unsigned device count(void){ return (unsigned device)SIZE; }

			inline virtual const unsigned device * data(void){
				static unsigned device data[SIZE] = {
					'(', '{', '[', '<' };
				return data;
			}

			inline virtual const unsigned device * end(void){
				static unsigned device data[SIZE] = {
					')', '}', ']', '>' };
				return data;
			}

		}container;

		template <class eventset>
		bool is(unsigned device c){
			eventset set;
			if ((unsigned device)(~0) == set.lookup(c))
				return false;
			return true;
		}
	}event;

	typedef class integer : public storage
	{
	public:
		unsigned device data = 0;

		static const ZS4LARGE PRECISION = (ZS4LARGE)(unsigned device)(sizeof(device) << 3);
		static const ZS4LARGE MASK = (ZS4LARGE)(unsigned device)(~0);
		static const ZS4LARGE MAX = MASK;
		static const ZS4LARGE MIN = (ZS4LARGE)((device)0);
		static const ZS4LARGE SIGBIT = (ZS4LARGE)(PRECISION - 1);
		static const ZS4LARGE PROBABILITY = (ZS4LARGE)(1 << PRECISION);

		// storage support
		INLINE_BITS_FUNCTION(){
			return PRECISION;
		}
		inline static unsigned device bitSet(unsigned device d, unsigned device i){ i %= PRECISION; d |= (unsigned device)((unsigned device)1 << (unsigned device)i); return d; }
		inline static unsigned device bitClear(unsigned device d, unsigned device i){ i %= PRECISION; d &= (unsigned device)((unsigned device)~((unsigned device)1 << (unsigned device)i)); return d; }
		inline static bool bitGet(unsigned device d, unsigned device i){ i %= PRECISION; if (d & (unsigned device)((unsigned device)1 << (unsigned device)i))return true; return false; }
		inline static bool bitGetMS(unsigned device d){ return bitGet(d, (PRECISION - 1)); }
		inline static bool bitGetLS(unsigned device d){ return bitGet(d, 0); }

		inline static unsigned device cmp(unsigned device c1, unsigned device c2){
			return c1 - c2;
		}
		inline static unsigned device cmp(const unsigned device * str1, const unsigned device * str2, const unsigned device * terminator = nullptr){
			if (terminator == nullptr){
				for (;;)
				{
					if (*str1 == 0 && *str2 == 0)
						return 0;

					if (*str1 != *str2)
						return *str1 - *str2;

					str1++; str2++;
				}

			}
			else{
				for (;;)
				{
					if (count(str1, terminator) && count(str2, terminator))
						return 0;

					if (*str1 != *str2)
						return *str1 - *str2;

					str1++; str2++;
				}
			}
		}
		inline static unsigned device ncmp(const unsigned device * str1, const unsigned device * str2, unsigned device n){
			for (unsigned device i = 0; i < n; i++)
			{
				unsigned device c1 = *str1++;
				unsigned device c2 = *str2++;
				if (c1 == 0 && c2 == 0) return 0;
				if (c1 != c2) return c1 - c2;
			}

			return 0;
		}

		inline static unsigned device len(const unsigned device * str, unsigned device * terminator = nullptr){
			unsigned device ret = 0;
			if (terminator == nullptr){
				while (*str){ str++; ret++; }
			}
			else{
				while (0 != (*str) && (0 == count(terminator, *str))){ str++; ret++; }
			}
			return ret;
		}
		inline static unsigned device count(const unsigned device * str, unsigned device c){
			if (str == 0)
				return 0;

			unsigned device ret = 0;

			while (*str != 0)
			{
				if (c == *str)
					ret++;
				str++;
			}

			return ret;
		}
		inline static unsigned device count(const unsigned device * s, const unsigned device * chrs){
			unsigned device ret = 0;
			for (const unsigned device * cp = s; cp && *cp; cp++)
			{
				for (const unsigned device * p = chrs; p && *p; p++)
				{
					if (*cp == *p)
						ret++;
				}
			}

			return ret;
		}
		inline static unsigned device swap(unsigned device org, unsigned device * str, unsigned device nu){
			unsigned device ret = 0;
			while (*str != 0) { if (*str == org) { *str = nu; ret++; } str++; }
			return ret;
		}
		inline static unsigned device ecmp(const unsigned device * str, const unsigned device * end){
			unsigned device len_str = len(str);
			unsigned device len_end = len(end);

			if (len_end > len_str)
				return 1;


			return cmp(&str[len_str - len_end], end);
		}

		INLINE_RESET_FUNCTION(){ data = 0; }
		inline signed cmp(device c)const{return data - c;}

		inline e io(stream * in, stream * out){
			device o = 0;
			device v = 0;

			return SUCCESS;
		}


		inline e set(event::set&set,const char * s){
			data = 0;
			//symbolset set;
			for (ZS4CHAR i = 0; s[i] != 0 && s[i] != '\n'; i++){
				ZS4CHAR lu = set.lookup((ZS4CHAR)s[i]);
				if (lu >= set.count()){
					data = 0;
					return FAILURE;
				}

				ZS4LARGE nu = (ZS4LARGE)((ZS4LARGE)((ZS4LARGE)data*(ZS4LARGE)set.count()) + (ZS4LARGE)lu);
				if ((ZS4LARGE)nu > (ZS4LARGE)MAX){
					data = (device)MAX;
					return (e)MAX;
				}
				data = (device)nu;
			}

			return SUCCESS;
		}
		inline e write(stream & out, zs4::event::set & set, bool sign = false)const{
			device dta = data;

			if (sign){
				if ((ZS4LARGE)dta & (ZS4LARGE)(1 << SIGBIT))
				{
					if (SUCCESS != out.write('-'))
						return FAILURE;

					dta = (~dta);
				}
			}

			ZS4LARGE remainder = dta;
			bool NOT_ZERO = false;

			ZS4LARGE MAX = (~0);
			ZS4LARGE count = 1;
			ZS4LARGE large = 1;
			while (large < (MAX / set.count())){
				large *= set.count(); count++;
			}

			ZS4LARGE accumulator;
			while (count)
			{
				if (0 != (accumulator = remainder / large))
				{
					remainder -= (accumulator*large);
					NOT_ZERO = true;
				}

				if (NOT_ZERO){
					if (SUCCESS != out.write((char)(set.data()[accumulator])))
						return BUFFEROVERFLOW;
				}

				large /= set.count();
				count--;
			}

			if (!NOT_ZERO)
			{
				if (SUCCESS != out.write((char)(set.data()[0])))
					return BUFFEROVERFLOW;
			}

			return SUCCESS;
		}

		// C OPERATORS
		inline operator device()const{ return data; }
		inline operator unsigned device()const{ return data; }

		inline operator integer*()const{ return(integer*)&data; }
		inline operator integer&()const{ return(integer&)data; }

		inline unsigned device & operator &(integer &d){ data = (unsigned device) d.data; return data; }
		inline unsigned device & operator &(device &d){ data = (unsigned device) d; return data; }
		inline unsigned device & operator &(int &d){ data = (unsigned device) d; return data; }

		inline unsigned device & operator =(integer &d){ data = (unsigned device) d.data; return data; }
		inline unsigned device & operator =(device &d){ data = (unsigned device) d; return data; }
		inline unsigned device & operator =(int &d){ data = (unsigned device) d; return data; }

		inline operator bool()const{ if (data != 0) { return true; } return false; }
		inline unsigned device & operator =(bool b){ if (b) data = (~0); else data = 0;  return data; }

		inline operator ZS4ANALOG()const{
			ZS4ANALOG r = 0.0;
			ZS4ANALOG h = 0.5;
			for (ZS4CHAR i = PRECISION; i > 0; i--){
				if ((ZS4LARGE)data | (ZS4LARGE)(1 << (i - 1))) r += h;
				h /= 2.0;
			}
			return r;
		}
		inline unsigned device & operator =(ZS4ANALOG a){
			if (a < 0.0) a = 0.0;
			if (a > 1.0) a = 1.0;

			data = (ZS4CHAR)((ZS4ANALOG)((ZS4ANALOG)MAX * (ZS4ANALOG)a));
			return data;
		}

	}integer;

	typedef class object : public stream{
	#	define INLINE_TICKLE_FUNCTION() inline virtual e tickle(void)
	#	define INLINE_ONCHAR_FUNCTION() inline virtual e onChar(char & c)
	#	define INLINE_ONLINE_FUNCTION() inline virtual e onLine(char * str)
	#	define INLINE_INSTANCE() inline object(char * m, ZS4LONG s, stream * i, stream * o)

		char * store;
		unsigned device storesize;
		unsigned device stacktop;
		unsigned device limit;
		unsigned device children;
		unsigned device buffer;
		unsigned device use;
		stream * in;
		stream * out;
		inline unsigned device ulim(){ return (buffer - 2); }
	protected:
		INLINE_BITS_FUNCTION(){
			return (ZS4LARGE)(storesize << 3);
		}
		INLINE_RESET_FUNCTION(){
			memset(store, 0, storesize);
		}
		inline unsigned device itemSpace(){
			return stacktop - limit;
		}
		inline e response(char c){
			return out->write(c);
		}
		inline e responseString(const char * s){
			return out->writeString(s);
		}
		inline e responseInteger(unsigned long long data, unsigned char base = 10){
			return out->writeInteger(data,base);
		}
		typedef struct item {
		public:
			device nam;
			device val;
		}item;
		inline e itemNameSet(item & i, const char * n){
			event::name set;
			e error = SUCCESS;
			integer w;
			if (error = w.set((event::set&)set, n))
				return error;
			i.nam = w.data;
			return SUCCESS;
		}
		inline item * itemArray(void){ return (item*)&store[stacktop]; }
		inline unsigned device itemCount(void){ return ((storesize - stacktop) / sizeof(item)); }
		inline e itemFind(device & d, const char * str){
			item * arr = itemArray();
			device c = itemCount();
			item var; var.nam = var.val = 0;
			if (SUCCESS != itemNameSet(var, str)){ return BADNAME; }

			for (device i = 0; i < c; i++)
			{
				if (arr[i].nam == var.nam){
					d = i;
					return SUCCESS;
				}
			}

			return NOTFOUND;
		}

		inline virtual e jStart(const char * n = nullptr){ if (n != nullptr) { response('"'); responseString(n); response('"'); response(':'); }; return response('{'); }
		inline virtual e jEnd(){ return response('}'); }

		inline e onc(){
			jStart("zs4");
			{
				jStart("i"); //info
				{
					jStart("m"); // memory
					{
						responseString("\"s\":"); // total
						responseInteger(storesize);
						response(',');

						responseString("\"b\":"); // available
						responseInteger(buffer);
						response(',');

						responseString("\"l\":"); // available
						responseInteger(limit);
						response(',');

						responseString("\"u\":"); // used
						responseInteger(storesize - stacktop);
					}
					jEnd(); // memory

					response(',');

					jStart("c"); // memory
					{
						responseString("\"i\":"); // total
						responseInteger(children);
						//response(',');

					}
					jEnd(); // memory
				}
				jEnd();  //info
			}
			return jEnd(); // zs4
		}

		inline virtual e onv(void){

			jStart();
			{
				onc();
				// and now the actual content....
				device c = itemCount();
				item * p = itemArray();

				if (c){
					integer b; b.data = 0;
					zs4::event::name nam;
					zs4::event::decimal dec;

					for (device i = 0; i < c; i++)
					{
						response(',');
						response('"');
						b.data = p[i].nam;
						b.write(*out,nam);
						response('"');
						response(':');
						b.data = p[i].val;
						b.write(*out,dec);
					}

				}
			}
			jEnd();

			return response('\n');
		}

		INLINE_ONLINE_FUNCTION(){
			device wk;
			e error = FAILURE;
			zs4::event event;
			item var;
			// cut leading space;
			while (event.is<zs4::event::space>((ZS4CHAR)*str))str++;
			switch (*str){
			case '+':{
				if (itemSpace() < (sizeof(var))){
					responseString("error no memory\n");
					return NOMEMORY;
				}

				str++;
				if (error = itemNameSet(var, str)){
					responseString("error invalid name\n");
					return BADNAME;
				}
				var.val = 0;

				if (SUCCESS == itemFind(wk, str)){
					responseString("error exists\n");
					return ALREADYEXISTS;
				}


				stacktop -= sizeof(item);
				item * eye = (item*)&store[stacktop];
				*eye = var;

				responseString("added\n");
				return SUCCESS;
			}
			case '-':{
				str++;
				device iRemove = 0;
				if (SUCCESS != itemFind(iRemove, str)){
					responseString("error not found\n");
					return NOTFOUND;
				}

				item * arr = itemArray();
				device cnt = itemCount();

				for (device i = iRemove; i > 0; i--){
					arr[i] = arr[i - 1];
				}
				stacktop += sizeof(item);

				responseString("removed\n");
				return SUCCESS;
			}
			}

			return response('\n');
		}
		INLINE_ONCHAR_FUNCTION(){
			if (in == nullptr || out == nullptr) return FAILURE;

			if (use < 1)
				return FAILURE;

			if (store[use - 1] == '\n')
			{
				rewind();
				if (!strcmp(store, "?\n")){ return onv(); }
				else { return onLine(store); }
			}

			if (use >= (ulim()))
			{
				char c;
				while (in->readable()){
					in->read(c);
					if (c == '\n')
						break;
				}
				rewind();
				responseString("error buffer overflow\n");
				return BUFFEROVERFLOW;
			}

			return WAITING;
		}
	public:
		INLINE_INSTANCE(){
			store = m;
			if (s <= integer::MAX) { storesize = (unsigned device)s; }
			else { storesize = integer::MAX; }
			reset();
			stacktop = storesize;
			buffer = storesize / 4; if (buffer > 256){ buffer = (unsigned device)256; }
			limit = (storesize - buffer);
			children = 0;
			use = 0;
			in = i;
			out = o;
		}
		inline virtual e tickle(void){
			if (in == nullptr || out == nullptr) return FAILURE;

			char c = 0;
			e error = SUCCESS;

			while (in->readable()){
				if ((error = in->read(c)))
					return error;

				if ((error = write(c)))
					return error;

				error = onChar(c);
				if (error == WAITING)
					continue;

				if (error)
					return error;

				break;
			}

			return error;
		}

		INLINE_READABLE_FUNCTION(){
			return (use);
		}
		INLINE_WRITEABLE_FUNCTION(){
			return (ulim() - use);
		}

		INLINE_READ_FUNCTION(){
			if (use >= ulim())
				return WAITING;

			c = store[use];
			store[use] = 0;
			use++;

			return SUCCESS;
		}
		INLINE_WRITE_FUNCTION(){
			if (use >= ulim())
				return WAITING;

			store[use++] = c;
			store[use] = 0;

			return SUCCESS;
		}
		INLINE_SIZE_FUNCTION(){
			s = use;
			return SUCCESS;
		}
		INLINE_REWIND_FUNCTION(){use = 0;return SUCCESS;}
	}object;

}intclass;

#undef objectclass
#undef eventclass
#undef intclass
#undef device
