#ifndef YKSFNJJNMGYYMRBOACWGWXFOAKIAYQTVTONQOQYYCRDIXEDBLTSWHOSCPDRVURONDHVDSVKYP
#define YKSFNJJNMGYYMRBOACWGWXFOAKIAYQTVTONQOQYYCRDIXEDBLTSWHOSCPDRVURONDHVDSVKYP

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct acosh;

    template<> struct acosh<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::acoshf(x);
        }
    };//struct acosh<float>

    template<> struct acosh<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::acosh(x);
        }
    };//struct acosh<double>

    template< typename Type >
    struct acosh< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct acosh<complex<...> >

}//namespace device

#endif//YKSFNJJNMGYYMRBOACWGWXFOAKIAYQTVTONQOQYYCRDIXEDBLTSWHOSCPDRVURONDHVDSVKYP
