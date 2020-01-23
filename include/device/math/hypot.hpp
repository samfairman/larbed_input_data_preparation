#ifndef OHVWWEWHJDRYLHAQIXBLRTRMYWUYXMCGHEUQPTRDYSDRMAETDQRVPCLIYRBGODOGEXUSUAMNT
#define OHVWWEWHJDRYLHAQIXBLRTRMYWUYXMCGHEUQPTRDYSDRMAETDQRVPCLIYRBGODOGEXUSUAMNT

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct hypot;

    template<> struct hypot<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::hypotf(x, y);
        }
    };//struct hypot<float>

    template<> struct hypot<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::hypot(x, y);
        }
    };//struct hypot<double>

    template< typename Type >
    struct hypot< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct hypot<complex<...> >

}//namespace device

#endif//OHVWWEWHJDRYLHAQIXBLRTRMYWUYXMCGHEUQPTRDYSDRMAETDQRVPCLIYRBGODOGEXUSUAMNT
