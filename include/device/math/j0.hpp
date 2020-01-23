#ifndef TFMRUWRIXXFVPIMVDIALNHLGKJUCOBRSXOOKLIJIFFFIHIFILDGLQTXBGXCKLIYPSYQHBEPTW
#define TFMRUWRIXXFVPIMVDIALNHLGKJUCOBRSXOOKLIJIFFFIHIFILDGLQTXBGXCKLIYPSYQHBEPTW

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct j0;

    template<> struct j0<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::j0f(x);
        }
    };//struct j0<float>

    template<> struct j0<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::j0(x);
        }
    };//struct j0<double>

    template< typename Type >
    struct j0< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct j0<complex<...> >

}//namespace device

#endif//TFMRUWRIXXFVPIMVDIALNHLGKJUCOBRSXOOKLIJIFFFIHIFILDGLQTXBGXCKLIYPSYQHBEPTW
