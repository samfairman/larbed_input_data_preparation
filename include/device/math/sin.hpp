#ifndef MIWEAKIQEFIEWGUGRHWWDQEXLAPQRVUUGHKEDYHQYAUPSODHEUOAAQSRBOTUGJIMFIJGNFCJC
#define MIWEAKIQEFIEWGUGRHWWDQEXLAPQRVUUGHKEDYHQYAUPSODHEUOAAQSRBOTUGJIMFIJGNFCJC

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct sin;

    template<> struct sin<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sinf(x);
        }
    };//struct sin<float>

    template<> struct sin<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sin(x);
        }
    };//struct sin<double>

    template< typename Type >
    struct sin< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct sin<complex<...> >

}//namespace device

#endif//MIWEAKIQEFIEWGUGRHWWDQEXLAPQRVUUGHKEDYHQYAUPSODHEUOAAQSRBOTUGJIMFIJGNFCJC
