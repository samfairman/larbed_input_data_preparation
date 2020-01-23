#ifndef DMYQPVWTEHCVCHFLGUKWCOCBYUXNNENYNOESQUJRLAJULYAGVHUHWUCDYKLVFCJLVCLHVGKYY
#define DMYQPVWTEHCVCHFLGUKWCOCBYUXNNENYNOESQUJRLAJULYAGVHUHWUCDYKLVFCJLVCLHVGKYY

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct atanh;

    template<> struct atanh<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::atanhf(x);
        }
    };//struct atanh<float>

    template<> struct atanh<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::atanh(x);
        }
    };//struct atanh<double>

    template< typename Type >
    struct atanh< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct atanh<complex<...> >

}//namespace device

#endif//DMYQPVWTEHCVCHFLGUKWCOCBYUXNNENYNOESQUJRLAJULYAGVHUHWUCDYKLVFCJLVCLHVGKYY
