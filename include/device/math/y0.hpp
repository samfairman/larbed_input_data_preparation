#ifndef PGJVUWFIEQPKLQCLOTPRNKDPVOFGAFSIULEIYMEJAICTQRIUWOAHDRFHKWQMWREUQGHRYKDTV
#define PGJVUWFIEQPKLQCLOTPRNKDPVOFGAFSIULEIYMEJAICTQRIUWOAHDRFHKWQMWREUQGHRYKDTV

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct y0;

    template<> struct y0<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::y0f(x);
        }
    };//struct y0<float>

    template<> struct y0<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::y0(x);
        }
    };//struct y0<double>

    template< typename Type >
    struct y0< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct y0<complex<...> >

}//namespace device

#endif//PGJVUWFIEQPKLQCLOTPRNKDPVOFGAFSIULEIYMEJAICTQRIUWOAHDRFHKWQMWREUQGHRYKDTV
