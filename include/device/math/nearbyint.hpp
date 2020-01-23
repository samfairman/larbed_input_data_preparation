#ifndef DPWESTKHBXFJXFUJWIMGLOKTYFBWSKYAVWTDHVCGJKEJJTFEVCPODTMCTYJOLNFUOUFOUADRM
#define DPWESTKHBXFJXFUJWIMGLOKTYFBWSKYAVWTDHVCGJKEJJTFEVCPODTMCTYJOLNFUOUFOUADRM

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct nearbyint;

    template<> struct nearbyint<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::nearbyintf(x);
        }
    };//struct nearbyint<float>

    template<> struct nearbyint<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::nearbyint(x);
        }
    };//struct nearbyint<double>

    template< typename Type >
    struct nearbyint< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct nearbyint<complex<...> >

}//namespace device

#endif//DPWESTKHBXFJXFUJWIMGLOKTYFBWSKYAVWTDHVCGJKEJJTFEVCPODTMCTYJOLNFUOUFOUADRM
