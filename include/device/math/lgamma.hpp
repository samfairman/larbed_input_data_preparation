#ifndef NDODFUPVEVKQENCQUMNPIRYNTTFBQGYTNFAMWIOGTCDBEBJSJHTOLTASPICRWHGWBHNDJAHCD
#define NDODFUPVEVKQENCQUMNPIRYNTTFBQGYTNFAMWIOGTCDBEBJSJHTOLTASPICRWHGWBHNDJAHCD

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct lgamma;

    template<> struct lgamma<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::lgammaf(x);
        }
    };//struct lgamma<float>

    template<> struct lgamma<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::lgamma(x);
        }
    };//struct lgamma<double>

    template< typename Type >
    struct lgamma< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct lgamma<complex<...> >

}//namespace device

#endif//NDODFUPVEVKQENCQUMNPIRYNTTFBQGYTNFAMWIOGTCDBEBJSJHTOLTASPICRWHGWBHNDJAHCD
