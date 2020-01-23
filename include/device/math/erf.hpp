#ifndef CBTQHXVVMCQXKPBRCHIXDHLBGSQHSHALHFFVQNXSJOVEGEKAENEYRRYQSNKKHHWTRCCGJVHBC
#define CBTQHXVVMCQXKPBRCHIXDHLBGSQHSHALHFFVQNXSJOVEGEKAENEYRRYQSNKKHHWTRCCGJVHBC

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct erf;

    template<> struct erf<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erff(x);
        }
    };//struct erf<float>

    template<> struct erf<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erf(x);
        }
    };//struct erf<double>

    template< typename Type >
    struct erf< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct erf<complex<...> >

}//namespace device

#endif//CBTQHXVVMCQXKPBRCHIXDHLBGSQHSHALHFFVQNXSJOVEGEKAENEYRRYQSNKKHHWTRCCGJVHBC
