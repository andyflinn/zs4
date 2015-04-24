#ifndef ZS4_TYPES_H
#define ZS4_TYPES_H

template <class uint>
class device
{
public:
	inline static uint BITDEPTH(void){ return (sizeof(uint) * 8); }

	inline uint probability(uint bitdepth = BITDEPTH()){ return (1 << bitdepth); }
	inline uint addressbits(uint bitdepth = BITDEPTH()){ uint w = 1; while (((uint)1 << w)<bitdepth)w++; return w; }
	inline uint databits(uint bitdepth = BITDEPTH()){ return (bitdepth - addressbits(bitdepth)); }

	class bitfield  
	{
	protected:
		uint address = 0;
		uint data = BITDEPTH();
		inline bitfield(void){}
		virtual inline ~bitfield(void){}
	};

	class test : public bitfield
	{
	public:
		inline test(){ address = 1; data = 3; }
	};

	test t;

	inline uint getAll(void)const{
		return dta;
	}
	inline void setAll(void){
		dta |= (~0);
	}
	inline void setMask(uint v){
		dta |= v;
	}
	inline void put(uint idx, bool true_or_false){
		if (idx >= (int)bits() || idx < 0)
			return;

		if (true_or_false)
			set(idx);
		else
			clr(idx);
	}
	inline bool get(uint idx) const {
		if (idx >= (int)bits() || idx < 0)
			return false;

		if (dta & mask(idx))
			return true;

		return false;
	}
	inline void set(uint idx){
		if (idx >= (int)bits() || idx < 0)
			return;

		dta |= mask(idx);
	}
	inline void clr(uint idx){
		if (idx >= (int)bits() || idx < 0)
			return;

		dta &= (~mask(idx));
	}
};

#endif
