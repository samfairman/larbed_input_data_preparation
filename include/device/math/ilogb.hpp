#ifndef VBSBTSJWFANBBKIPTBVCAMDYJFDHSCKEENSFNOBNHXEOITKYKBWMTHBRWEINFUUQRPVMCNFUQ
#define VBSBTSJWFANBBKIPTBVCAMDYJFDHSCKEENSFNOBNHXEOITKYKBWMTHBRWEINFUUQRPVMCNFUQ

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct ilogb;

    template<> struct ilogb<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::ilogbf(x);
        }
    };//struct ilogb<float>

    template<> struct ilogb<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::ilogb(x);
        }
    };//struct ilogb<double>

    template< typename Type >
    struct ilogb< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct ilogb<complex<...> >

}//namespace device

#endif//VBSBTSJWFANBBKIPTBVCAMDYJFDHSCKEENSFNOBNHXEOITKYKBWMTHBRWEINFUUQRPVMCNFUQ
