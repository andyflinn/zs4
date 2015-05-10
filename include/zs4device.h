
#include <zs4error.h>

#ifndef device
#define device char
#define intclass byte
typedef char byte_t;
#endif

#ifndef ZS4LARGE
#	define ZS4LARGE unsigned long long
#endif

typedef class intclass
{
public:
	static const ZS4LARGE PRECISION = (ZS4LARGE)(unsigned device)(sizeof(device) << 3);
	static const ZS4LARGE MASK = (ZS4LARGE)(unsigned device)(~0);
	static const ZS4LARGE MAX = MASK;
	static const ZS4LARGE MIN = (ZS4LARGE)((device)0);
	static const ZS4LARGE SIGBIT = (ZS4LARGE)(PRECISION - 1);
	static const ZS4LARGE PROBABILITY = (ZS4LARGE)(1 << PRECISION);

	static const unsigned device * zs4(){ static const unsigned device zs4[] = { 'z', 's', '4', 0 }; return zs4; }

	inline static unsigned device * NEWLINE(){ static unsigned device r[] = { '\n', 0 }; return r; }

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

	inline static unsigned device len(const unsigned device * str, const unsigned device * terminator = nullptr){
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


	inline static unsigned device strcmp(const unsigned device * str1, const unsigned device * str2){
		for (;;)
		{
			if (*str1 == 0 && *str2 == 0)
				return 0;

			if (*str1 != *str2)
				return *str1 - *str2;

			str1++; str2++;
		}
	}

	typedef class symbol
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
			inline unsigned device lookup(const unsigned device symbol){

				for (unsigned device i = 0; i < count(); i++){
					if ((unsigned device)data()[i] == (unsigned device)symbol)
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
			inline unsigned device get(const unsigned device * from, unsigned device * to, unsigned device max){
				unsigned device r = 0;
				if (max < 2) return r;

				*to = 0;
				for (unsigned device i = 0; i < (max - 1); i++){
					if (lookup(from[i]) == (unsigned device)(~0))
						break;
					*to++ = from[i];
					*to = 0;
					r++;
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

		template <class symbolset>
		bool is(unsigned device c){
			symbolset set;
			if ((unsigned device)(~0) == set.lookup(c))
				return false;
			return true;
		}
	}symbol;

	typedef class storage
	{
	public:

#define	INLINE_BITS_FUNCTION() inline virtual ZS4LARGE bits(void)const
		INLINE_BITS_FUNCTION(){ return (sizeof(*this) << 3); }

#define INLINE_CONNECT_FUNCTION() inline virtual e connect(stream * in, stream * out)

		inline ZS4LARGE addressBits(void)const{ ZS4LARGE w = 1; while (((ZS4LARGE)1 << w)<bits())w++; return w; }
		inline ZS4LARGE messageBits(void)const{ return (bits() - addressBits()); }

	}storage;

#define	INLINE_RESET_FUNCTION() inline virtual void reset(void)

	typedef class stream : public storage{
	public:
		static const unsigned device seek_cur = 1;
		static const unsigned device seek_end = 2;
		static const unsigned device seek_set = 0;

#define	INLINE_READ_FUNCTION() inline virtual e read(unsigned device & c)
		INLINE_READ_FUNCTION(){return FAILURE;}
#define	INLINE_WRITE_FUNCTION() inline virtual e write(unsigned device c)
		INLINE_WRITE_FUNCTION(){return FAILURE;	}
#define	INLINE_READABLE_FUNCTION() inline virtual unsigned device readable(void)
		INLINE_READABLE_FUNCTION(){	return 0; }
#define	INLINE_WRITEABLE_FUNCTION() inline virtual unsigned device writeable(void)
		INLINE_WRITEABLE_FUNCTION(){return 0;}
#define	INLINE_FLUSH_FUNCTION() inline virtual e flush(void)
		INLINE_FLUSH_FUNCTION(){ return SUCCESS; }
#define	INLINE_CLOSE_FUNCTION() inline virtual e close(void)
		INLINE_CLOSE_FUNCTION(){return SUCCESS;}
#define	INLINE_REWIND_FUNCTION() inline virtual e rewind(void)
		INLINE_REWIND_FUNCTION(){return seek(0, SEEK_SET);}
#define	INLINE_SEEKEND_FUNCTION() inline virtual e seekEnd(void)
		INLINE_SEEKEND_FUNCTION(){return seek(0, seek_end);}
#define	INLINE_SEEK_FUNCTION() inline virtual e seek(ZS4LARGE offset, int origin)
		INLINE_SEEK_FUNCTION(){return FAILURE;}
#define	INLINE_TELL_FUNCTION() inline virtual e tell(ZS4LARGE & pPos)
		INLINE_TELL_FUNCTION(){return FAILURE;}
#define	INLINE_SIZE_FUNCTION() inline virtual e size(ZS4LARGE & s)
		INLINE_SIZE_FUNCTION(){
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

#define	INLINE_WRITESTRING_FUNCTION() inline virtual e write(const unsigned device * str)
		INLINE_WRITESTRING_FUNCTION(){
			if (str == nullptr || (*str) == 0)
				return NODATA;

			unsigned device l = len(str);
			for (unsigned char i = 0; i < l; i++){
				if (SUCCESS != write(str[i]))
					return FAILURE;
			}
			return SUCCESS;
		}

		inline e writeInteger(symbol::set&set, unsigned device data, unsigned device base = 10){

			unsigned device remainder = data;

			bool NOT_ZERO = false;

			unsigned device MAX = (~0);
			unsigned device count = 1;
			ZS4LARGE large = 1;
			while (large < (MAX / base)){
				large *= base; count++;
			}

			ZS4LARGE accumulator;
			while (count)
			{
				if (0 != (accumulator = remainder / large))
				{
					remainder -= (unsigned device)(ZS4LARGE)(accumulator*large);
					NOT_ZERO = true;
				}

				if (NOT_ZERO){
					if (SUCCESS != write((char)(set.data()[accumulator])))
						return BUFFEROVERFLOW;
				}

				large /= base;
				count--;
			}

			if (!NOT_ZERO)
			{
				if (SUCCESS != write((char)(set.data()[0])))
					return BUFFEROVERFLOW;
			}
			return SUCCESS;
		}
		inline e writeJsonString(const unsigned device * out)
		{
			for (const unsigned device * str = out; str && *str; str++)
			{
				switch (*str)
				{
				case '\\': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('\\'))return FAILURE; break;
				case '"': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('\"'))return FAILURE;  break;
				case '/': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('/'))return FAILURE;  break;
				case '\b': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('b'))return FAILURE;  break;
				case '\f': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('f'))return FAILURE;  break;
				case '\n': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('n'))return FAILURE;  break;
				case '\r': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('r'))return FAILURE;  break;
				case '\t': if (SUCCESS != write('\\'))return FAILURE; if (SUCCESS != write('t'))return FAILURE;  break;
				default: if (SUCCESS != write(*str))return FAILURE; break;
				}
			}
			return SUCCESS;
		}

		inline virtual e jInteger(const unsigned device n, unsigned device data, unsigned char base = 10){
			symbol::numeric num;
			jNameColon(n);
			return writeInteger(num,data, base);
		}
		inline virtual e jNameColon(const unsigned device n){
			symbol::name enam;
			write('"');
			writeInteger(enam, n, enam.count());
			write('"');
			return write(':');
		}
		inline virtual e jStart(const unsigned device n){
			jNameColon(n);
			return write('{');
		}
		inline virtual e jStart(const unsigned device * n = nullptr){
			if (n != nullptr) {
				write('"');
				write(n);
				write('"');
				write(':');
			}
			return write('{');
		}
		inline virtual e jEnd(){ return write('}'); }
		inline virtual e jDone(){ return write('\n'); }
		inline virtual e jError(e error){
			write('e');
			write('r');
			write('r');
			write('o');
			write('r');
			write('=');
			write('t');
			write('r');
			write('u');
			write('e');
			write(';');
			write('\n');
			return error;
		}
		inline virtual e jNull(){
			write('n');
			write('u');
			write('l');
			write('l');
			return write('\n');
		}
		inline virtual e jComma(){return write(',');}

	}stream;

	typedef class bytestream : public stream
	{
		zs4::byte::stream * stream = nullptr;
	public:
		inline bytestream(zs4::byte::stream * bs){
			stream = bs;
		}

		INLINE_READ_FUNCTION(){
			zs4::byte::integer b;
			e error = stream->read(b.data);
			if (error)return error;
			c = (unsigned device)b.data;
			return SUCCESS;
		}
		INLINE_WRITE_FUNCTION(){
			zs4::byte::integer b;
			b.data = (unsigned char)c;
			return stream->write(b.data);
		}
		INLINE_READABLE_FUNCTION(){
			return (unsigned device)stream->readable();
		}
		INLINE_WRITEABLE_FUNCTION(){
			return (unsigned device)stream->writeable();
		}
		INLINE_FLUSH_FUNCTION(){ return stream->flush(); }
		INLINE_CLOSE_FUNCTION(){ return stream->close(); }
		INLINE_REWIND_FUNCTION(){ return stream->rewind(); }
		INLINE_SEEKEND_FUNCTION(){ return stream->seekEnd(); }
		INLINE_SEEK_FUNCTION(){ return stream->seek(offset,origin); }
		INLINE_TELL_FUNCTION(){ return stream->tell(pPos); }
		INLINE_SIZE_FUNCTION(){ return stream->size(s); }
	}bytestream;

	typedef class integer
	{
	public:
		unsigned device data = 0;

		// storage support
		inline static unsigned device bitSet(unsigned device d, unsigned device i){ i %= PRECISION; d |= (unsigned device)((unsigned device)1 << (unsigned device)i); return d; }
		inline static unsigned device bitClear(unsigned device d, unsigned device i){ i %= PRECISION; d &= (unsigned device)((unsigned device)~((unsigned device)1 << (unsigned device)i)); return d; }
		inline static bool bitGet(unsigned device d, unsigned device i){ i %= PRECISION; if (d & (unsigned device)((unsigned device)1 << (unsigned device)i))return true; return false; }
		inline static bool bitGetMS(unsigned device d){ return bitGet(d, (PRECISION - 1)); }
		inline static bool bitGetLS(unsigned device d){ return bitGet(d, 0); }

		INLINE_RESET_FUNCTION(){ data = 0; }
		inline unsigned device cmp(device c)const{ return data - c; }

		inline e io(unsigned device * in, stream * out){
			e error = SUCCESS;
			symbol::decimal sdec;
			symbol::opcode opcode;
			unsigned device opc[3];

			unsigned device opCount = opcode.get(in, opc, 3);
			if (opCount == 0)
				goto return_value;
			else in = &in[opCount];

			if (opCount == 1){
				if (*opc == '='){
					if (SUCCESS != (error = set(sdec, in)))
						return out->jError(error);
					goto return_value;
				}
				if (*opc == '+'){
					integer addval; addval.data = 0;
					if (SUCCESS != (error = addval.set(sdec, in)))
						return out->jError(error);
					addval.data += data;
					out->writeInteger(sdec, addval.data, 10);
					return out->jDone();
				}
				if (*opc == '-'){
					integer addval; addval.data = 0;
					if (SUCCESS != (error = addval.set(sdec, in)))
						return out->jError(error);
					addval.data = (data-addval.data);
					out->writeInteger(sdec, addval.data, 10);
					return out->jDone();
				}
				if (*opc == '|'){
					integer addval; addval.data = 0;
					if (SUCCESS != (error = addval.set(sdec, in)))
						return out->jError(error);
					addval.data |= data;
					out->writeInteger(sdec, addval.data, 10);
					return out->jDone();
				}
				if (*opc == '&'){
					integer addval; addval.data = 0;
					if (SUCCESS != (error = addval.set(sdec, in)))
						return out->jError(error);
					addval.data &= data;
					out->writeInteger(sdec, addval.data, 10);
					return out->jDone();
				}
				goto return_value;
			}

			if (opCount == 2){
				if (opc[1] == '=')
				{
					if (*opc == '+'){
						integer addval; addval.data = 0;
						if (SUCCESS != (error = addval.set(sdec, in)))
							return out->jError(error);
						data += addval.data;
						goto return_value;
					}
					if (*opc == '-'){
						integer addval; addval.data = 0;
						if (SUCCESS != (error = addval.set(sdec, in)))
							return out->jError(error);
						data -= addval.data;
						goto return_value;
					}
					if (*opc == '|'){
						integer addval; addval.data = 0;
						if (SUCCESS != (error = addval.set(sdec, in)))
							return out->jError(error);
						data |= addval.data;
						goto return_value;
					}
					if (*opc == '&'){
						integer addval; addval.data = 0;
						if (SUCCESS != (error = addval.set(sdec, in)))
							return out->jError(error);
						data &= addval.data;
						goto return_value;
					}
					goto return_value;
				}

				if (opc[0] == '+' && opc[1] == '+')
				{
					data++;
					goto return_value;
				}

				if (opc[0] == '-' && opc[1] == '-')
				{
					data--;
					goto return_value;
				}
			}
			return_value:
			out->writeInteger(sdec, data, 10);
			return out->jDone();
		}

		inline e set(symbol::set&set, unsigned device * s){
			//data = 0;

			for (unsigned device i = 0; s[i] != 0 && s[i] != '\n'; i++){
				unsigned device lu = set.lookup((unsigned device)s[i]);
				if (lu >= set.count()){
					//data = 0;
					return FAILURE;
				}

				ZS4LARGE nu = (ZS4LARGE)((ZS4LARGE)((ZS4LARGE)data*(ZS4LARGE)set.count()) + (ZS4LARGE)lu);
				if ((ZS4LARGE)nu > (unsigned device)MAX){
					return FAILURE;
				}
				data = (unsigned device)nu;
			}

			return SUCCESS;
		}
		inline e write(stream & out, symbol::set & set, bool sign = false)const{
			unsigned device dta = data;

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

	}integer;

	typedef class object : public stream{
		unsigned device * store;
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
			char * p = (char*)store;
			for (unsigned device i = 0; i < storesize; i++){ p[i] = 0; }
		}
		inline unsigned device itemSpace(){
			return stacktop - limit;
		}

		inline unsigned device itemSize(){ return 2; }
		typedef struct item {
		public:
			unsigned device nam;
			unsigned device val;
		}item;
		inline e itemNameSet(item & i, unsigned device * n){
			symbol::name set;
			e error = SUCCESS;
			integer w;
			if ((error = w.set((symbol::set&)set, n)))
				return error;
			i.nam = w.data;
			return SUCCESS;
		}
		inline item * itemArray(void){ return (item*)&store[stacktop]; }
		inline unsigned device itemCount(void){ return ((storesize - stacktop) / 2); }
		inline e itemFind(unsigned device & d, unsigned device * str){
			item * arr = itemArray();
			unsigned device c = itemCount();
			item var; var.nam = var.val = 0;
			if (SUCCESS != itemNameSet(var, str)){ return BADNAME; }

			for (unsigned device i = 0; i < c; i++)
			{
				if (arr[i].nam == var.nam){
					d = i;
					return SUCCESS;
				}
			}

			return NOTFOUND;
		}

		inline virtual e jInteger(const unsigned device n, unsigned device data, unsigned char base = 10){return out->jInteger(n, data, base);}
		inline virtual e jNameColon(const unsigned device n){return out->jNameColon(n);}
		inline virtual e jStart(const unsigned device n){return out->jStart(n);}
		inline virtual e jStart(const unsigned device * n = nullptr){return out->jStart(n);}
		inline virtual e jEnd(){ return out->jEnd(); }
		inline virtual e jDone(){ return out->jDone(); }
		inline virtual e jError(e error){return out->jError(error);}
		inline virtual e jNull(){return out->jNull();}
		inline virtual e jComma(){ return out->jComma(); }

		inline e onc(){
			jStart(zs4());
			{
				symbol::name enam;
				jStart(enam.lookup('i')); //info
				{
					jStart(enam.lookup('m')); // memory
					{
						jInteger(enam.lookup('s'), storesize);
						jComma();

						jInteger(enam.lookup('b'), buffer);
						jComma();

						jInteger(enam.lookup('l'), limit);
						jComma();

						jInteger(enam.lookup('u'), (storesize - stacktop));
					}
					jEnd(); // memory

					jComma();

					jStart(enam.lookup('c')); // memory
					{
						jInteger(enam.lookup('c'), children);
						//jComma();

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
					for (device i = 0; i < c; i++)
					{
						jComma();
						jInteger(p[i].nam, p[i].val);
					}

				}
			}
			jEnd();

			return jDone();
		}

#		define INLINE_ONSCAN_FUNCTION() inline virtual e onScan(unsigned device * str)
		INLINE_ONSCAN_FUNCTION(){
			unsigned device wk;
			e error = FAILURE;
			symbol symbol;
			item var; var.nam = var.val = 0;
			// cut leading space;
			while (symbol.is<symbol::space>(*str))str++;
			switch (*str){
			case '+':{
				if (itemSpace() < 2){
					return jError(NOMEMORY);
				}

				str++;
				if (error = itemNameSet(var, str)){
					return jError(BADNAME);
				}

				var.val = 0;
				if (SUCCESS == itemFind(wk, str)){
					return jError(ALREADYEXISTS);
				}


				stacktop -= itemSize();
				(*itemArray()) = var;

				out->write('0');
				return jDone();
			}
			case '-':{
				str++;
				unsigned device iRemove = 0;
				if (SUCCESS != itemFind(iRemove, str)){
					return jError(NOTFOUND);
				}

				item * arr = itemArray();

				for (unsigned device i = iRemove; i > 0; i--){
					arr[i] = arr[i - 1];
				}
				stacktop += itemSize();

				return jDone();
			}
			default:{
				integer value; value.data = 0;
				symbol::name enam;
				symbol::decimal edec;

				unsigned device end_save;

				item * p = itemArray();

				unsigned device *name = str;
				unsigned device name_length = 0;
				while (symbol.is<symbol::name>(*str)){ str++; name_length++; }
				unsigned device * name_end = str;
				if (name_length == 0)
					return jError(BADNAME);

				end_save = *name_end; *name_end = 0;
				unsigned device item_index = 0;
				e item_find_result = itemFind(item_index, name);
				*name_end = end_save;

				if (SUCCESS == item_find_result){
					value.data = p[item_find_result].val;
					if (error = value.io(name_end, out))
						return error;
					p[item_find_result].val = value.data;
					return SUCCESS;
				}
				else{
					return jNull();
				}


			}}//switch()


			return jDone();
		}
#		define INLINE_ONINTEGER_FUNCTION() inline virtual e onInteger(unsigned device & c)
		INLINE_ONINTEGER_FUNCTION(){
			if (in == nullptr || out == nullptr) return FAILURE;

			if (use < 1)
				return FAILURE;

			if (0 == ecmp(store,NEWLINE()))
			{
				rewind();
				if (store[0] == '?'){ return onv(); }
				else { return onScan(store); }
			}

			if (use >= (ulim()))
			{
				unsigned device c;
				while (in->readable()){
					in->read(c);
					if (c == '\n')
						break;
				}
				rewind();
				return jError(BUFFEROVERFLOW);
			}

			return WAITING;
		}
	public:
#		define INLINE_INSTANCE() inline object(unsigned device * m, unsigned device s, stream * i, stream * o)
		INLINE_INSTANCE(){
			store = m;
			if (s <= MAX) { storesize = (unsigned device)s; }
			else { storesize = MAX; }
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

			unsigned device c = 0;
			e error = SUCCESS;

			while (in->readable()){
				if ((error = in->read(c)))
					return error;

				if ((error = write(c)))
					return error;

				error = onInteger(c);
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
#undef symbolclass
#undef intclass
#undef device
