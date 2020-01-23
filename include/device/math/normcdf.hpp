#ifndef MMDEYUMQUEUOEVTUCBLAHOJAPJLLYXVEQHBUIRFBWVKAAEIPDNMJVCRIVVCEMUKTHYDDUOMMX
#define MMDEYUMQUEUOEVTUCBLAHOJAPJLLYXVEQHBUIRFBWVKAAEIPDNMJVCRIVVCEMUKTHYDDUOMMX

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct normcdf;

    template<> struct normcdf<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::normcdff(x);
        }
    };//struct normcdf<float>

    template<> struct normcdf<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::normcdf(x);
        }
    };//struct normcdf<double>

    template< typename Type >
    struct normcdf< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct normcdf<complex<...> >

}//namespace device

#endif//MMDEYUMQUEUOEVTUCBLAHOJAPJLLYXVEQHBUIRFBWVKAAEIPDNMJVCRIVVCEMUKTHYDDUOMMX
