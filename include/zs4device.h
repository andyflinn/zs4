
#include <zs4config.h>

#ifndef device
#define device char 
#define devicename "p8" 
#define bussclass p8
#define readfunction(t,f) t f ## _ ## p8(void)
#define writefunction(t,f,a) t f ## _ ## p8(p8 a)
#define mustundefdevice 1 
#endif

typedef class bussclass : public storage
{
public:
	unsigned device data = 0;

	static const char * NAME(){ return (const char *)devicename; }

	static const ZS4LARGE PRECISION = (ZS4LARGE)(unsigned device)(sizeof(device) << 3);
	static const ZS4LARGE MASK = (ZS4LARGE)(unsigned device)(~0);
	static const ZS4LARGE MAX = MASK;
	static const ZS4LARGE MIN = (ZS4LARGE)((device)0);
	static const ZS4LARGE SIGBIT = (ZS4LARGE)(bussclass::PRECISION - 1);
	static const ZS4LARGE PROBABILITY = (ZS4LARGE)(1 << PRECISION);

	// storage support
	INLINE_BITS_FUNCTION(){
		return PRECISION; 
	}
	inline virtual readfunction(ZS4LARGE, size){ return 1; }

	inline static unsigned device bitSet(unsigned device d, unsigned device i){ i %= bussclass::PRECISION; d |= (unsigned device)((unsigned device)1 << (unsigned device)i); return d; }
	inline static unsigned device bitClear(unsigned device d, unsigned device i){ i %= bussclass::PRECISION; d &= (unsigned device)((unsigned device)~((unsigned device)1 << (unsigned device)i)); return d; }
	inline static bool bitGet(unsigned device d, unsigned device i){ i %= bussclass::PRECISION; if (d & (unsigned device)((unsigned device)1 << (unsigned device)i))return true; return false; }
	inline static bool bitGetMS(unsigned device d){ return bitGet(d, (bussclass::PRECISION - 1)); }
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

	template <class symbolset>
	inline e set(const char * s){
		data = 0;
		symbolset set;
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
	template <class symbolset>
	inline e write(stream & out, bool sign = false)const{
		device dta = data;
		symbolset set;

		if (sign){
			if (dta & (1 << SIGBIT))
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

	inline operator bussclass*()const{ return(bussclass*)&data; }
	inline operator bussclass&()const{ return(bussclass&)data; }

	inline unsigned device & operator &(bussclass &d){ data = (unsigned device) d.data; return data; }
	inline unsigned device & operator &(device &d){ data = (unsigned device) d; return data; }
	inline unsigned device & operator &(int &d){ data = (unsigned device) d; return data; }

	inline unsigned device & operator =(bussclass &d){ data = (unsigned device) d.data; return data; }
	inline unsigned device & operator =(device &d){ data = (unsigned device) d; return data; }
	inline unsigned device & operator =(int &d){ data = (unsigned device) d; return data; }


	//inline unsigned device & operator &(device d){ return (data &= d); }

	inline operator bool()const{ if (data != 0) { return true; } return false; }
	inline unsigned device & operator =(bool b){ if (b) data = (~0); else data = 0;  return data; }

	inline operator ZS4ANALOG()const{
		ZS4ANALOG r = 0.0;
		ZS4ANALOG h = 0.5;
		ZS4CHAR tru = 0;
		for (ZS4CHAR i = bussclass::PRECISION; i > 0; i--){
			if ((ZS4LARGE)data | (ZS4LARGE)(1 << (i - 1))) r += h;
			h /= 2.0;
		}
		return r;
	}
	inline unsigned device & operator =(ZS4ANALOG a){
		if (a < 0.0) a = 0.0;
		if (a > 1.0) a = 1.0;

		data = (ZS4CHAR)((ZS4ANALOG)((ZS4ANALOG)bussclass::MAX * (ZS4ANALOG)a));
		return data;
	}

	template <class datatype, class bus>
	class object : public stream
	{
#		define INLINE_TICKLE_FUNCTION() inline virtual e tickle(void)
#		define INLINE_ONCHAR_FUNCTION() inline virtual e onChar(char & c)
#		define INLINE_ONLINE_FUNCTION() inline virtual e onLine(char * str)
#		define INLINE_INSTANCE(type) inline type(char * m, ZS4LONG s, stream * i, stream * o)

		char * store;
		unsigned device storesize;
		unsigned device stacktop;
		unsigned device use;
		stream * in;
		stream * out;
	protected:
		INLINE_BITS_FUNCTION(){
			return (ZS4LARGE)(storesize << 3); 
		}
		INLINE_RESET_FUNCTION(){
			memset(store, 0, storesize); 
		}
		inline unsigned device available(){
			return stacktop - use;
		}

		typedef struct item {
		public:
			datatype nam;
			datatype val;
		}item;
		inline e itemNameSet(item & i, const char * n){
			e error = SUCCESS;
			bus w;
			if (error = (w.set<zs4::event::name>(n)))
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


		inline virtual e jStart(const char * n = nullptr){ if (n != nullptr) { write('"'); writeString(n); write('"'); write(':'); }; return write('{'); }
		inline virtual e jEnd(){ return write('}'); }
		inline virtual e onj(void){
			use = 0;

			jStart();
			{
				jStart("zs4");
				{
					jStart("c"); //constants
					{
						jStart("m"); // context
						{
							jStart("s"); // size
							{
								writeString("\"a\":"); // available
								writeInteger(available());
								write(',');

								writeString("\"t\":"); // total
								writeInteger(storesize);
								write(',');

								writeString("\"u\":"); // used
								writeInteger(storesize - stacktop);
							}
							jEnd(); // size
						}
						jEnd(); // context
						write(',');

						jStart("i"); // context
						{
							device c = itemCount();
							item * p = itemArray();

							writeString("\"s\":"); // available
							writeInteger(sizeof(item));

							write(',');
							writeString("\"c\":"); // total
							writeInteger(c);

							if (c){
								write(',');
								jStart("d"); // context
								{
									bus b; b.data = 0;

									for (device i = 0; i < c; i++)
									{
										if (i) write(',');
										write('"');
										b.data = p[i].nam;
										b.write<zs4::event::name>(*this);
										write('"');
										write(':');
										b.data = p[i].val;
										b.write<zs4::event::decimal>(*this);
									}
								}
								jEnd(); // context
							}
						}
						jEnd(); // context
					}
					jEnd(); //constant
				}
				jEnd();
			}
			jEnd();

			e error = write('\n');

			use = 0;
			return error;
		}

		INLINE_ONLINE_FUNCTION(){
			use = 0;
			device wk;
			e error = FAILURE;
			zs4::event event;
			item var;
			// cut leading space;
			while (event.is<zs4::event::space>((ZS4CHAR)*str))str++;
			switch (*str){
			case '+':{
				if (available() < (sizeof(var) << 1)){
					writeString("error no memory\n");
					return NOMEMORY;
				}

				str++;
				if (error = itemNameSet(var, str)){
					writeString("error invalid name\n");
					return BADNAME;
				}
				var.val = 0;

				if (SUCCESS == itemFind(wk, str)){
					writeString("error exists\n");
					return ALREADYEXISTS;
				}


				stacktop -= sizeof(item);
				item * eye = (item*)&store[stacktop];
				*eye = var;

				writeString("added\n");
				return SUCCESS;
			}
			case '-':{
				str++;
				device iRemove = 0;
				if (SUCCESS != itemFind(iRemove, str)){
					writeString("error not found\n");
					return NOTFOUND;
				}

				item * arr = itemArray();
				device cnt = itemCount();

				for (device i = iRemove; i > 0; i--){
					arr[i] = arr[i - 1];
				}
				stacktop += sizeof(item);

				writeString("removed\n");
				return SUCCESS;
			}
			}

			return SUCCESS;
		}
		INLINE_ONCHAR_FUNCTION(){
			if (in == nullptr || out == nullptr) return FAILURE;

			if (use < 1)
				return FAILURE;

			if (store[use - 1] == '\n')
			{
				use = 0;
				if (!strcmp(store, "?\n")){ return onj(); }
				else { return onLine(store); }
			}

			return WAITING;
		}
	public:
		INLINE_INSTANCE(object){
			store = m;
			if (s <= bussclass::MAX) { storesize = (unsigned device)s; }
			else { storesize = bussclass::MAX; }
			reset();
			stacktop = storesize;
			use = 0;
			in = i;
			out = o;
		}
		INLINE_TICKLE_FUNCTION(){
			if (in == nullptr || out == nullptr) return FAILURE;

			char c = 0;
			e error = SUCCESS;

			for (;;){
				if (error = in->read(c))
					return error;

				if (error = write(c))
					return error;

				error = onChar(c);
				if (error == WAITING)
					continue;

				break;
			}

			out->writeString((const char *)store);
			use = 0;
			return SUCCESS;
		}

		INLINE_READABLE_FUNCTION(){
			return (use);
		}
		INLINE_WRITEABLE_FUNCTION(){
			return (stacktop - use - 1);
		}

		INLINE_READ_FUNCTION(){
			if (use >= (stacktop - 1))
				return FAILURE;

			c = store[use];
			store[use] = 0;
			use++;

			return SUCCESS;
		}
		INLINE_WRITE_FUNCTION(){
			if (use >= (stacktop - 1))
				return FAILURE;

			store[use++] = c;
			store[use] = 0;

			return SUCCESS;
		}
		INLINE_SIZE_FUNCTION(){
			s = use;
			return SUCCESS;
		}
	};


}bussclass;
	
#ifdef mustundefdevice
#undef device
#undef devicename 
#undef bussclass
#undef readfunction
#undef writefunction
#undef mustundefdevice
#endif


