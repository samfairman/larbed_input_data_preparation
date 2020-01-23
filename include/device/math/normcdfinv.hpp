#ifndef WNXRGHGMPJTLBSVACQEVQOJWMMCMBIVBVACQQPAUANHXTFWBPPSCKECVQXPPQQMTIGDCYQDAA
#define WNXRGHGMPJTLBSVACQEVQOJWMMCMBIVBVACQQPAUANHXTFWBPPSCKECVQXPPQQMTIGDCYQDAA

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct normcdfinv;

    template<> struct normcdfinv<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::normcdfinvf(x);
        }
    };//struct normcdfinv<float>

    template<> struct normcdfinv<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::normcdfinv(x);
        }
    };//struct normcdfinv<double>

    template< typename Type >
    struct normcdfinv< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct normcdfinv<complex<...> >

}//namespace device

#endif//WNXRGHGMPJTLBSVACQEVQOJWMMCMBIVBVACQQPAUANHXTFWBPPSCKECVQXPPQQMTIGDCYQDAA
