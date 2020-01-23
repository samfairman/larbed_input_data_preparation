#ifndef PEBMKVGXESWQGSDFFITTELRBQFROANDEBEQYNCYMOYBNTBAETLQSAARLCVVLIEYQDXPSYCEAN
#define PEBMKVGXESWQGSDFFITTELRBQFROANDEBEQYNCYMOYBNTBAETLQSAARLCVVLIEYQDXPSYCEAN

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct expm1;

    template<> struct expm1<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::expm1f(x);
        }
    };//struct expm1<float>

    template<> struct expm1<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::expm1(x);
        }
    };//struct expm1<double>

    template< typename Type >
    struct expm1< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct expm1<complex<...> >

}//namespace device

#endif//PEBMKVGXESWQGSDFFITTELRBQFROANDEBEQYNCYMOYBNTBAETLQSAARLCVVLIEYQDXPSYCEAN
