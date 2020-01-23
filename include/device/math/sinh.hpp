#ifndef VNGJIBHJPCOJUCTVBPPJJYKBHODHLOYQJOEYROHTDCYUQTRDIBHBGVVEEQFIJSBUYMKAKYDWH
#define VNGJIBHJPCOJUCTVBPPJJYKBHODHLOYQJOEYROHTDCYUQTRDIBHBGVVEEQFIJSBUYMKAKYDWH

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct sinh;

    template<> struct sinh<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sinhf(x);
        }
    };//struct sinh<float>

    template<> struct sinh<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sinh(x);
        }
    };//struct sinh<double>

    template< typename Type >
    struct sinh< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct sinh<complex<...> >

}//namespace device

#endif//VNGJIBHJPCOJUCTVBPPJJYKBHODHLOYQJOEYROHTDCYUQTRDIBHBGVVEEQFIJSBUYMKAKYDWH
