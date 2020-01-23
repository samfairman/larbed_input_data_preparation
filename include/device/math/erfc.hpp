#ifndef UTDPSCPYCVHYRNNNDTJEBLHLBJCORXOOBDJRGCFAHQWDVIJPAVGHODNFRAFAUMSCOPCNQEDMS
#define UTDPSCPYCVHYRNNNDTJEBLHLBJCORXOOBDJRGCFAHQWDVIJPAVGHODNFRAFAUMSCOPCNQEDMS

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct erfc;

    template<> struct erfc<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfcf(x);
        }
    };//struct erfc<float>

    template<> struct erfc<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfc(x);
        }
    };//struct erfc<double>

    template< typename Type >
    struct erfc< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct erfc<complex<...> >

}//namespace device

#endif//UTDPSCPYCVHYRNNNDTJEBLHLBJCORXOOBDJRGCFAHQWDVIJPAVGHODNFRAFAUMSCOPCNQEDMS
