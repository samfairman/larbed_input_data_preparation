#ifndef TNISSHBNEBFVUOMTTYIYPBJHBQRESMGFNMSUJAEKJODWPQXSJULLWJMOAVYWWBITRPSXYVVAO
#define TNISSHBNEBFVUOMTTYIYPBJHBQRESMGFNMSUJAEKJODWPQXSJULLWJMOAVYWWBITRPSXYVVAO

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct erfcx;

    template<> struct erfcx<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfcxf(x);
        }
    };//struct erfcx<float>

    template<> struct erfcx<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfcx(x);
        }
    };//struct erfcx<double>

    template< typename Type >
    struct erfcx< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct erfcx<complex<...> >

}//namespace device

#endif//TNISSHBNEBFVUOMTTYIYPBJHBQRESMGFNMSUJAEKJODWPQXSJULLWJMOAVYWWBITRPSXYVVAO
