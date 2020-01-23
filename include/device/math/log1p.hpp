#ifndef KENPFLPRPBTPFRNLURYSKXJLOTDWPWKEBOXXSCUJRMYJMVSHELKNSIBGDXQHRNWFIGQVEQSNN
#define KENPFLPRPBTPFRNLURYSKXJLOTDWPWKEBOXXSCUJRMYJMVSHELKNSIBGDXQHRNWFIGQVEQSNN

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct log1p;

    template<> struct log1p<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::log1pf(x);
        }
    };//struct log1p<float>

    template<> struct log1p<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::log1p(x);
        }
    };//struct log1p<double>

    template< typename Type >
    struct log1p< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct log1p<complex<...> >

}//namespace device

#endif//KENPFLPRPBTPFRNLURYSKXJLOTDWPWKEBOXXSCUJRMYJMVSHELKNSIBGDXQHRNWFIGQVEQSNN
