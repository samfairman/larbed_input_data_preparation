#ifndef _SQRT_HPP_INCLUDED_SONASFPOIJ4LKAJFPOIH4JEAJH498YAFIOUH4089YAFKLH498YAFK
#define _SQRT_HPP_INCLUDED_SONASFPOIJ4LKAJFPOIH4JEAJH498YAFIOUH4089YAFKLH498YAFK 

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct sqrt;

    template<> struct sqrt<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sqrtf(x);
        }
    };//struct sqrt<float>

    template<> struct sqrt<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sqrt(x);
        }
    };//struct sqrt<double>

    template< typename Type >
    struct sqrt< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct sqrt<complex<...> >

}//namespace device

#endif//_SQRT_HPP_INCLUDED_SONASFPOIJ4LKAJFPOIH4JEAJH498YAFIOUH4089YAFKLH498YAFK 
