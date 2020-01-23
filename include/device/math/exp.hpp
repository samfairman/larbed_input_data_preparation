#ifndef QCUMNCPJOLWKKEKCTUFWYKXQMFXTOVENDVKBMILUQISTHKEOIDMUEATDXXBLOGXTTOQQVYWEM
#define QCUMNCPJOLWKKEKCTUFWYKXQMFXTOVENDVKBMILUQISTHKEOIDMUEATDXXBLOGXTTOQQVYWEM

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct exp;

    template<> struct exp<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::expf(x);
        }
    };//struct exp<float>

    template<> struct exp<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::exp(x);
        }
    };//struct exp<double>

    template< typename Type >
    struct exp< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct exp<complex<...> >

}//namespace device

#endif//QCUMNCPJOLWKKEKCTUFWYKXQMFXTOVENDVKBMILUQISTHKEOIDMUEATDXXBLOGXTTOQQVYWEM
