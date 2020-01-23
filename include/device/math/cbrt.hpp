#ifndef _CBRT_HPP_INCLUDED_SDNLASFDJKLN49HAFSDLUH498HAFDLUH498HAFS08Y4UFOIJAFSDF
#define _CBRT_HPP_INCLUDED_SDNLASFDJKLN49HAFSDLUH498HAFDLUH498HAFS08Y4UFOIJAFSDF 

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct cbrt;

    template<> struct cbrt<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::cbrtf(x);
        }
    };//struct cbrt<float>

    template<> struct cbrt<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::cbrt(x);
        }
    };//struct cbrt<double>

    template< typename Type >
    struct cbrt< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct cbrt<complex<...> >

}//namespace device

#endif//_CBRT_HPP_INCLUDED_SDNLASFDJKLN49HAFSDLUH498HAFDLUH498HAFS08Y4UFOIJAFSDF
