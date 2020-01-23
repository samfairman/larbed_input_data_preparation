#ifndef KVIYAIALIOCIRFNCQBNGXRKMQFJFTJRUECULVDFQGBVFBWLTHSSOYRFORFDOMWFRIBLMDPPWS
#define KVIYAIALIOCIRFNCQBNGXRKMQFJFTJRUECULVDFQGBVFBWLTHSSOYRFORFDOMWFRIBLMDPPWS

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct erfcinv;

    template<> struct erfcinv<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfcinvf(x);
        }
    };//struct erfcinv<float>

    template<> struct erfcinv<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfcinv(x);
        }
    };//struct erfcinv<double>

    template< typename Type >
    struct erfcinv< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct erfcinv<complex<...> >

}//namespace device

#endif//KVIYAIALIOCIRFNCQBNGXRKMQFJFTJRUECULVDFQGBVFBWLTHSSOYRFORFDOMWFRIBLMDPPWS
