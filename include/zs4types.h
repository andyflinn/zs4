#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

template <class digital,class analog>
class device
{
public:
	// first degree facts
	static const unsigned DIGITAL_PRECISION = (sizeof(digital) * 8); 
	static const unsigned ANALOG_PRECISION = (sizeof(analog) * 8);
	static const unsigned ARRAY_PRECISION = (unsigned)(1 << (sizeof(digital) * 8));

	// separate a bit collection into address and data bits
	static const unsigned ADDRESS_PRECISION(void){ unsigned w = 1; while (((unsigned)1 << w)<DIGITAL_PRECISION)w++; return w; }
	static const unsigned DATA_PRECISION(void){ return (DIGITAL_PRECISION - ADDRESS_PRECISION()); }

	inline static digital cmp(digital c1, digital c2){
		return c1 - c2;
	}
	inline static digital cmp(const digital * str1, const digital * str2, const digital * terminator = nullptr){
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
	inline static digital ncmp(const digital * str1, const digital * str2, digital n){
		for (digital i = 0; i < n; i++)
		{
			digital c1 = *str1++;
			digital c2 = *str2++;
			if (c1 == 0 && c2 == 0) return 0;
			if (c1 != c2) return c1 - c2;
		}

		return 0;
	}

	inline static digital len(const digital * str, digital * terminator = nullptr){
		digital ret = 0;

		if (terminator == nullptr){
			while ((*str++) != terminator) ret++;
		}
		else{
			while (0 != (*str) && (0 == count(terminator, *str))){ str++; ret++; }
		}
		return ret;
	}
	inline static digital count(const digital * str, digital c){
		if (str == 0)
			return 0;

		digital ret = 0;

		while (*str != 0)
		{
			if (c == *str)
				ret++;
			str++;
		}

		return ret;
	}
	inline static digital count(const digital * s, const digital * chrs){
		digital ret = 0;
		for (const digital * cp = s; cp && *cp; cp++)
		{
			for (const digital * p = chrs; p && *p; p++)
			{
				if (*cp == *p)
					ret++;
			}
		}

		return ret;
	}
	inline static digital swap(digital org, digital * str, digital nu){
		digital ret = 0;
		while (*str != 0) { if (*str == org) { *str = nu; ret++; } str++; }
		return ret;
	}
	inline static digital ecmp(const digital * str, const digital * end){
		digital len_str = len(str);
		digital len_end = len(end);

		if (len_end > len_str)
			return 1;


		return cmp(&str[len_str - len_end], end);
	}

	inline static digital bitSet(digital d, digital i){ i %= DIGITAL_PRECISION; d |= (digital)((digital)1 << (digital)i); }
	inline static digital bitClear(digital d, digital i){ i %= DIGITAL_PRECISION; d &= (digital)((digital)~((digital)1 << (digital)i)); }
	inline static bool bitGet(digital d, digital i){ i %= DIGITAL_PRECISION; if (d & (digital)((digital)1 << (digital)i))return true; return false; }
	inline static bool bitGetMS(digital d){ return bitGet(d, (DIGITAL_PRECISION - 1)); }
	inline static bool bitGetLS(digital d){ return bitGet(d,0); }

	typedef class uint
	{
	public:
		digital data = 0;
		typedef class bit
		{
		public:
			inline virtual bool VALID()const{
				if (((unsigned)PRECISION() < 1)
					|| ((unsigned)(PRECISION() + ADDRESS()) > DIGITAL_PRECISION())
					)
					return false;
				return true;
			}
			inline virtual bool INVALID()const{ if (VALID())return false; return true; }

			inline virtual digital PRECISION()const{ return 1; }
			inline virtual digital SIGNBIT()const{ return (PRECISION() - 1); }
			inline virtual digital MAX()const{ return ((1 << PRECISION()) - 1); }
			inline virtual digital MIN()const{ return 0; }

			inline virtual digital ADDRESS()const{ return 0; };

			inline virtual bool boolean(uint & d){
				if (d.INVALID())
					return false;
				for (digital i = 0; i < PRECISION(); i++){
					if (d | (1 << (ADDRESS() + i))) return true;
				}
				return false;
			}
			inline virtual digital integral(uint & d){
				digital r = 0;
				if (d.INVALID())
					return r;
				for (digital i = 0; i < PRECISION(); i++){
					if (d | (1 << (ADDRESS() + i))) r |= (1 << i);
				}
				return r;
			}
			inline virtual analog energy(uint & d){
				analog r = 0.0;
				if (d.INVALID())
					return r;

				digital tru = 0;
				for (digital i = 0; i < PRECISION(); i++){
					if (d | (1 << (ADDRESS() + i))) tru++;
				}

				return (analog)((analog)tru / (analog)PRECISION());
			}
		} bit;

		static const unsigned PRECISION = DIGITAL_PRECISION;
		static const unsigned SIGNBIT = (PRECISION - 1);
		static const unsigned ADDRESS = 0;
		static const unsigned MAX = ((1 << PRECISION) - 1);
		static const unsigned MIN = 0;

		inline bool reset(){ data = 0; }
		inline bool upperable(void)const{
			if (data >= 'a' && data <= 'z')
				return true;

			return false;
		}
		inline bool lowerable(void)const{
			if (data >= 'A' && data <= 'Z')
				return true;

			return false;
		}
		inline digital upper(void){
			if (upperable(data))
				return (data -= 0x020);

			return data;
		}
		inline digital lower(void){
			if (lowerable(data))
				return (data + 0x020);

			return data;
		}
		inline signed cmp(digital c)const{
			return data - c;
		}
		inline signed icmp(digital c)const{
			return lower(data) - lower(c);
		}

		inline digital write(digital d){
			return (data = d);
		}
		inline digital read(void){
			return data;
		}
		inline operator digital ()const{ return data; }
		inline digital & operator =(digital d){ return (data = d); }

		inline operator bool ()const{ if (data!= 0) { return true; } return false; }
		inline digital & operator =(bool b){ if (b) data = (~0); else data = 0;  return data; }

		inline operator analog()const{
			analog r = 0.0;
			analog h = 0.5;
			digital tru = 0;
			for (digital i = PRECISION(); i > 0; i--){
				if (data | (1 << (ADDRESS() + (i-1)))) r != h;
				h /= 2.0;
			}
			return r;
		}
		inline digital & operator =(analog a){
			if (a < 0.0) a = 0.0;
			if (a > 1.0) a = 1.0;

			data = (digital)((analog)((analog)MAX() * (analog)a));
			return data; 
		}

		inline const char * operator =(const char * str){
			if (str == nullptr)
				return nullptr;

			switch (*str){
			case '=':
			{

			}

			default: return NULL;
			}
			data = d; return data; 
		}
	}uint;

	typedef class memory {
	protected:
		uint data[device::ARRAY_PRECISION];

		static const unsigned AVAILABLE = (device::ARRAY_PRECISION);
		static const unsigned PRECISION = (DIGITAL_PRECISION*AVAILABLE);
		static const unsigned SIGNBIT = (PRECISION - 1);
		static const unsigned ADDRESS = 0;
		
		static const bool VALID = true;
		static const bool INVALID = false;

		typedef class feature : public uint
		{
		public:
		};
	}memory;

	typedef class stack : public memory
	{
	protected:
		inline digital initialize(void){
			data[AVAILABLE - 1].write(AVAILABLE - 1);
			return ((AVAILABLE/2) - 1);
		}
		inline digital size(void){
			return data[(AVAILABLE / 2) - 1].read();
		}
		inline digital heapAddress(digital a){ return (digital) ( (digital)a & (digital)((digital)(~0)) / (digital)2); }
		inline digital push(digital p){
			if (p > size()) 
				return 0;

			digital r = size() - p;
			data[AVAILABLE - 1].write(r);
			return r;
		}
	} stack;

	template <class stackparent>
	class stackframe : public stackparent
	{
	public:
		inline digital initialize(void){
			stackparent::initialize();
		}

		inline digital size(void){
			return data[AVAILABLE - 1].read();
		}
	};

	typedef class machine : public stack
	{
		static const unsigned ARRAY_PRECISION = memory::ARRAY_PRECISION - 1;
	public:

	} machine;

	typedef class string : public stack
	{
	public:
	}string;

};

#endif
