#ifndef WRJOWJAQRVUTIWDYKQEPJGKBVVTDANKEPVRAEVYTBDYYJERLIBXEKMCRBMVWFDRWTRTINXHXI
#define WRJOWJAQRVUTIWDYKQEPJGKBVVTDANKEPVRAEVYTBDYYJERLIBXEKMCRBMVWFDRWTRTINXHXI

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct floor;

    template<> struct floor<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::floorf(x);
        }
    };//struct floor<float>

    template<> struct floor<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::floor(x);
        }
    };//struct floor<double>

    template< typename Type >
    struct floor< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct floor<complex<...> >

}//namespace device

#endif//WRJOWJAQRVUTIWDYKQEPJGKBVVTDANKEPVRAEVYTBDYYJERLIBXEKMCRBMVWFDRWTRTINXHXI
