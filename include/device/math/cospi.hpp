#ifndef VCRPRRURTWTBESPYYMYCVOTGUSNETPOBXUECLADSUKEIHFDUHWYBFSEUDWLOFUOABIVVKKUDE
#define VCRPRRURTWTBESPYYMYCVOTGUSNETPOBXUECLADSUKEIHFDUHWYBFSEUDWLOFUOABIVVKKUDE

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct cospi;

    template<> struct cospi<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::cospif(x);
        }
    };//struct cospi<float>

    template<> struct cospi<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::cospi(x);
        }
    };//struct cospi<double>

    template< typename Type >
    struct cospi< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct cospi<complex<...> >

}//namespace device

#endif//VCRPRRURTWTBESPYYMYCVOTGUSNETPOBXUECLADSUKEIHFDUHWYBFSEUDWLOFUOABIVVKKUDE
