#ifndef ALTPXORNMNAKUBKXCBWYAEDJGJNHJNOJWAOTAGVEVUNGJIXMFUXIBEXPOSAEOLRHREVNQCYOU
#define ALTPXORNMNAKUBKXCBWYAEDJGJNHJNOJWAOTAGVEVUNGJIXMFUXIBEXPOSAEOLRHREVNQCYOU

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct round;

    template<> struct round<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::roundf(x);
        }
    };//struct round<float>

    template<> struct round<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::round(x);
        }
    };//struct round<double>

    template< typename Type >
    struct round< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct round<complex<...> >

}//namespace device

#endif//ALTPXORNMNAKUBKXCBWYAEDJGJNHJNOJWAOTAGVEVUNGJIXMFUXIBEXPOSAEOLRHREVNQCYOU
