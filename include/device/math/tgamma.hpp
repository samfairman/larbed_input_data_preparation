#ifndef FVSGFMAEWYYIRMPERYSYNYRYXEKUDFJDWPMLHGYEKSDISXJIPYXFDVTCYCTSETFRNFEJTQUJJ
#define FVSGFMAEWYYIRMPERYSYNYRYXEKUDFJDWPMLHGYEKSDISXJIPYXFDVTCYCTSETFRNFEJTQUJJ

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct tgamma;

    template<> struct tgamma<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::tgammaf(x);
        }
    };//struct tgamma<float>

    template<> struct tgamma<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::tgamma(x);
        }
    };//struct tgamma<double>

    template< typename Type >
    struct tgamma< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct tgamma<complex<...> >

}//namespace device

#endif//FVSGFMAEWYYIRMPERYSYNYRYXEKUDFJDWPMLHGYEKSDISXJIPYXFDVTCYCTSETFRNFEJTQUJJ
