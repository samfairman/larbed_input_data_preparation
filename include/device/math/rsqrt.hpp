#ifndef _RSQRT_HPP_INCLUDED_FDPJI93IUHASFD897Y34AHSFDKJVJIHFAS3Y78YAFDSJHDSJKAFD
#define _RSQRT_HPP_INCLUDED_FDPJI93IUHASFD897Y34AHSFDKJVJIHFAS3Y78YAFDSJHDSJKAFD 

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct rsqrt;

    template<> struct rsqrt<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::rsqrtf(x);
        }
    };//struct rsqrt<float>

    template<> struct rsqrt<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::rsqrt(x);
        }
    };//struct rsqrt<double>

    template< typename Type >
    struct rsqrt< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct rsqrt<complex<...> >

}//namespace device

#endif//_RSQRT_HPP_INCLUDED_FDPJI93IUHASFD897Y34AHSFDKJVJIHFAS3Y78YAFDSJHDSJKAFD 

