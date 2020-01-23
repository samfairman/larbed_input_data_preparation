#ifndef OCISOECKLCCEGONPROQDIPFUKRIBCYFQUYDQPOPBMTSOSESQAHCWAXBWGJOWNMTKOIKQVJVAO
#define OCISOECKLCCEGONPROQDIPFUKRIBCYFQUYDQPOPBMTSOSESQAHCWAXBWGJOWNMTKOIKQVJVAO

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct cosh;

    template<> struct cosh<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::coshf(x);
        }
    };//struct cosh<float>

    template<> struct cosh<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::cosh(x);
        }
    };//struct cosh<double>

    template< typename Type >
    struct cosh< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct cosh<complex<...> >

}//namespace device

#endif//OCISOECKLCCEGONPROQDIPFUKRIBCYFQUYDQPOPBMTSOSESQAHCWAXBWGJOWNMTKOIKQVJVAO
