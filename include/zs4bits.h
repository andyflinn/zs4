/* ******************************************************************
   Copyright (C) 1996-2001  Thugs at Bay Inc, All Rights Reserved.

   This program is NOT free software; you can NOT redistribute it.

   Thugs at Bay Contact information:
   email: info@thugsatbay.com or
   phone: 416 534 3562

** *************************************************************** */

#ifndef ZS4_BITS_H
#define ZS4_BITS_H

template <class inttype, class enumtype>
class zs4bits
{
	inttype value;
	inttype * dta;
public:

	inline zs4bits(inttype * init = nullptr){
		if (init != nullptr)
		{
			dta = init;
		}
		else
		{
			dta = &value;

		}
	}
	inline virtual ~zs4bits(){
	}

	inline void init(inttype * init){
		dta = init;
	}
	inline void clrAll(void){
		*dta = 0;
	}
	inline inttype getAll(void)const{
		return *dta;
	}
	inline void setAll(void){
		*dta |= (~0);
	}
	inline void setAll(inttype v){
		*dta = v;
	}
	inline const size_t bytes(void) const {
		return (sizeof(inttype));
	}
	inline const size_t bits(void) const {
		return (bytes() * 8);
	}
	inline static const inttype mask(enumtype idx){
		return (inttype)((inttype)1 << idx);
	}

	inline void put(enumtype idx, bool true_or_false){
		if (idx >= (int)bits() || idx < 0)
			return;

		if	( true_or_false )
			set(idx);
		else
			clr(idx);
	}
	inline bool get(enumtype idx) const {
		if (idx >= (int)bits() || idx < 0)
			return false;

		if (*dta & mask(idx))
			return true;

		return false;
	}
	inline void set(enumtype idx){
		if (idx >= (int)bits() || idx < 0)
			return;

		*dta |= mask(idx);
	}
	inline void clr(enumtype idx){
		if (idx >= (int)bits() || idx < 0)
			return;

		*dta &= (~mask(idx));
	}

#define enum_bit(it,et,i,n) \
inline void n ## _alone(void){set((et)i);} \
inline void n ## _set(void){set((et)i);} \
inline void n ## _clr(void){clr((et)i);} \
inline void n ## _put(bool t){put((et)i,t);} \
inline bool n ## _get(void)const{return get((et)i);} \
inline static it n ## _mask(void){return mask((et)i);} \
inline static const char * n ## _str(void){static const char * s = #n; return s;}
};

#endif

