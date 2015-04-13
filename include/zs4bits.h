/* ******************************************************************
   Copyright (C) 1996-2001  Thugs at Bay Inc, All Rights Reserved.

   This program is NOT free software; you can NOT redistribute it.

   Thugs at Bay Contact information:
   email: info@thugsatbay.com or
   phone: 416 534 3562

** *************************************************************** */

#ifndef ZS4_BITS_H
#define ZS4_BITS_H

#include <sys/types.h>

template <class inttype, class enumtype>
class zs4bits
{
public:
	inttype data;
	
	inline zs4bits()
	{
		clrAll();
	}
	inline virtual ~zs4bits()
	{
	}
	inline void clrAll(void)
	{
		data = 0;
	}
	inline inttype getAll(void){
		return data;
	}
	inline void setAll(void){
		data |= (~0);
	}
	inline const size_t bytes(void) const {
		return (sizeof(inttype));
	}
	inline const size_t bits(void) const {
		return (bytes() * 8);
	}

	inline void put(enumtype idx, bool true_or_false)
	{
		if (idx >= (int)bits() || idx < 0)
			return;

		if	( true_or_false )
			set(idx);
		else
			clr(idx);
	}

	inline bool get(enumtype idx) const
	{
		if (idx >= (int)bits() || idx < 0)
			return false;

		if (data & (1 << idx))
			return true;

		return false;
	}

	inline void set(enumtype idx)
	{
		if (idx >= (int)bits() || idx < 0)
			return;

		data |= (1 << idx);
	}

	inline void clr(enumtype idx)
	{
		if (idx >= (int)bits() || idx < 0)
			return;

		data &= (~(1 << idx));
	}

#define enum_bit(i,n) inline void set_ ## n(void){set(i);} inline void clr_ ## n(void){clr(i);} inline void put_ ## n(bool t){put(i,t);} inline bool get_ ## n(void){return get(i);}
};

#endif

