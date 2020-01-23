#ifndef RXTAWWNDVRVEVSMUMRIJYSPQXHPNNWRLRHJDRVLSFIVCSKHKTNDWUFCFFLQSERRDMNITYBMBW
#define RXTAWWNDVRVEVSMUMRIJYSPQXHPNNWRLRHJDRVLSFIVCSKHKTNDWUFCFFLQSERRDMNITYBMBW

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct yn;

    template<> struct yn<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const int n, const value_type x ) const
        {
            return ::ynf(n, x);
        }
    };//struct yn<float>

    template<> struct yn<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const int n, const value_type x ) const
        {
            return ::yn(n, x);
        }
    };//struct yn<double>

    template< typename Type >
    struct yn< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const int n, const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct yn<complex<...> >

}//namespace device

#endif//RXTAWWNDVRVEVSMUMRIJYSPQXHPNNWRLRHJDRVLSFIVCSKHKTNDWUFCFFLQSERRDMNITYBMBW
