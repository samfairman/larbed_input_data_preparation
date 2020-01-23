#ifndef VFMUJDXPIUSMYEDTHQJROSEMRNBJSACMEXQOCITFLCAUCFMBDKGUMPCIANDTAOUDJPMEBWGGM
#define VFMUJDXPIUSMYEDTHQJROSEMRNBJSACMEXQOCITFLCAUCFMBDKGUMPCIANDTAOUDJPMEBWGGM

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct asinh;

    template<> struct asinh<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::asinhf(x);
        }
    };//struct asinh<float>

    template<> struct asinh<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::asinh(x);
        }
    };//struct asinh<double>

    template< typename Type >
    struct asinh< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct asinh<complex<...> >

}//namespace device

#endif//VFMUJDXPIUSMYEDTHQJROSEMRNBJSACMEXQOCITFLCAUCFMBDKGUMPCIANDTAOUDJPMEBWGGM
