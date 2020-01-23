#ifndef _RCBRT_HPP_INCLUDED_SPIOJASF9P8U4POIAJF0948YUAF1LJH408Y9UAFDKLJBVKJAF98F
#define _RCBRT_HPP_INCLUDED_SPIOJASF9P8U4POIAJF0948YUAF1LJH408Y9UAFDKLJBVKJAF98F 

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct rcbrt;

    template<> struct rcbrt<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::rcbrtf(x);
        }
    };//struct rcbrt<float>

    template<> struct rcbrt<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::rcbrt(x);
        }
    };//struct rcbrt<double>

    template< typename Type >
    struct rcbrt< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct rcbrt<complex<...> >

}//namespace device

#endif//_RCBRT_HPP_INCLUDED_SPIOJASF9P8U4POIAJF0948YUAF1LJH408Y9UAFDKLJBVKJAF98F
