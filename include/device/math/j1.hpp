#ifndef WFBQRIJCVYDOJTIUOSDGFRKHHDFRNACAKLMEOGXDMRHBSWIQJEULBTUVTODMSCDSLLGHAKMXJ
#define WFBQRIJCVYDOJTIUOSDGFRKHHDFRNACAKLMEOGXDMRHBSWIQJEULBTUVTODMSCDSLLGHAKMXJ

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct j1;

    template<> struct j1<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::j1f(x);
        }
    };//struct j1<float>

    template<> struct j1<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::j1(x);
        }
    };//struct j1<double>

    template< typename Type >
    struct j1< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct j1<complex<...> >

}//namespace device

#endif//WFBQRIJCVYDOJTIUOSDGFRKHHDFRNACAKLMEOGXDMRHBSWIQJEULBTUVTODMSCDSLLGHAKMXJ
