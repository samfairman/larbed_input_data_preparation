#ifndef _STATIC_CHECK_HPP_INCLUDED_ASFD9JIN4NOIUHASFDO9H4AFIUDH48YASFOIUH498YASF
#define _STATIC_CHECK_HPP_INCLUDED_ASFD9JIN4NOIUHASFDO9H4AFIUDH48YASFOIUH498YASF 

namespace device
{
    template<int> struct CompileTimeError;
    template<> struct CompileTimeError<true> {};
}

#ifdef static_check
#undef static_check 
#endif

#define static_check(expr, msg) { device::CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; }


#endif//_STATIC_CHECK_HPP_INCLUDED_ASFD9JIN4NOIUHASFDO9H4AFIUDH48YASFOIUH498YASF 


