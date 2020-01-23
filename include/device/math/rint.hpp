#ifndef CBRCXLPTTHFYDQPHJWLOSEGALFRFYBOADBVFTYYKPGCVXCLEKIXVANFBWQGSQQUIQXVHRMVFM
#define CBRCXLPTTHFYDQPHJWLOSEGALFRFYBOADBVFTYYKPGCVXCLEKIXVANFBWQGSQQUIQXVHRMVFM

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct rint;

    template<> struct rint<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::rintf(x);
        }
    };//struct rint<float>

    template<> struct rint<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::rint(x);
        }
    };//struct rint<double>

    template< typename Type >
    struct rint< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct rint<complex<...> >

}//namespace device

#endif//CBRCXLPTTHFYDQPHJWLOSEGALFRFYBOADBVFTYYKPGCVXCLEKIXVANFBWQGSQQUIQXVHRMVFM
