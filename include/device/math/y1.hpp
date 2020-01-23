#ifndef AQFGKKODHPNHADATXAHMTGFLCCKKWKHLRROJEDKDSLPFJOKUFOOAFIOOYNRAFLSEWCRUSKJDU
#define AQFGKKODHPNHADATXAHMTGFLCCKKWKHLRROJEDKDSLPFJOKUFOOAFIOOYNRAFLSEWCRUSKJDU

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct y1;

    template<> struct y1<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::y1f(x);
        }
    };//struct y1<float>

    template<> struct y1<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::y1(x);
        }
    };//struct y1<double>

    template< typename Type >
    struct y1< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct y1<complex<...> >

}//namespace device

#endif//AQFGKKODHPNHADATXAHMTGFLCCKKWKHLRROJEDKDSLPFJOKUFOOAFIOOYNRAFLSEWCRUSKJDU
