#ifndef SDSGAREVDMRPMEHHPXKJRBEBQGTFMULVMUSUXILDPVPYTIAIKEFLPUFVQXNFSUJYVUAMJYGGN
#define SDSGAREVDMRPMEHHPXKJRBEBQGTFMULVMUSUXILDPVPYTIAIKEFLPUFVQXNFSUJYVUAMJYGGN

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct ldexp;

    template<> struct ldexp<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::ldexpf(x, y);
        }
    };//struct ldexp<float>

    template<> struct ldexp<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::ldexp(x, y);
        }
    };//struct ldexp<double>

    template< typename Type >
    struct ldexp< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct ldexp<complex<...> >

}//namespace device

#endif//SDSGAREVDMRPMEHHPXKJRBEBQGTFMULVMUSUXILDPVPYTIAIKEFLPUFVQXNFSUJYVUAMJYGGN
