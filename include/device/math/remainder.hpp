#ifndef PECFNBDJRGCJKJXGGXUASWMAVUVCBPNEGOPSIKSLUYNNQBSNCXTCHRPLWNPTRSPFLDVVSVNSV
#define PECFNBDJRGCJKJXGGXUASWMAVUVCBPNEGOPSIKSLUYNNQBSNCXTCHRPLWNPTRSPFLDVVSVNSV

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct remainder;

    template<> struct remainder<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::remainderf(x, y);
        }
    };//struct remainder<float>

    template<> struct remainder<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::remainder(x, y);
        }
    };//struct remainder<double>

    template< typename Type >
    struct remainder< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct remainder<complex<...> >

}//namespace device

#endif//PECFNBDJRGCJKJXGGXUASWMAVUVCBPNEGOPSIKSLUYNNQBSNCXTCHRPLWNPTRSPFLDVVSVNSV
