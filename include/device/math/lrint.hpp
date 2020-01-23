#ifndef DREUWXETGHCIGMRBAFUIAMDTVHEITNEGQVHDVFJLUQJUQKQWWBIONKEVAINTCXJTLLXLUGKCI
#define DREUWXETGHCIGMRBAFUIAMDTVHEITNEGQVHDVFJLUQJUQKQWWBIONKEVAINTCXJTLLXLUGKCI

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct lrint;

    template<> struct lrint<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::lrintf(x);
        }
    };//struct lrint<float>

    template<> struct lrint<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::lrint(x);
        }
    };//struct lrint<double>

    template< typename Type >
    struct lrint< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct lrint<complex<...> >

}//namespace device

#endif//DREUWXETGHCIGMRBAFUIAMDTVHEITNEGQVHDVFJLUQJUQKQWWBIONKEVAINTCXJTLLXLUGKCI
