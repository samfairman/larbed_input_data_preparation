#ifndef KRJCRFKTDRRSFFWFOMGVEITKJBLOYPIPINOLFHVIOXYYQMVIAVQQROYTIUMFYCXUCTSGNKJFL
#define KRJCRFKTDRRSFFWFOMGVEITKJBLOYPIPINOLFHVIOXYYQMVIAVQQROYTIUMFYCXUCTSGNKJFL

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct log10;

    template<> struct log10<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::log10f(x);
        }
    };//struct log10<float>

    template<> struct log10<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::log10(x);
        }
    };//struct log10<double>

    template< typename Type >
    struct log10< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct log10<complex<...> >

}//namespace device

#endif//KRJCRFKTDRRSFFWFOMGVEITKJBLOYPIPINOLFHVIOXYYQMVIAVQQROYTIUMFYCXUCTSGNKJFL
