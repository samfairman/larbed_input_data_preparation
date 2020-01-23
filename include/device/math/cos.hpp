#ifndef BIDPNFTYBWVOLMSCCTVLBOPWSHOYPCKVNCDBHFIMQBKWGXPKPYXGLHRETBMLXOPOFUENFTLQE
#define BIDPNFTYBWVOLMSCCTVLBOPWSHOYPCKVNCDBHFIMQBKWGXPKPYXGLHRETBMLXOPOFUENFTLQE

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct cos;

    template<> struct cos<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::cosf(x);
        }
    };//struct cos<float>

    template<> struct cos<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::cos(x);
        }
    };//struct cos<double>

    template< typename Type >
    struct cos< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct cos<complex<...> >

}//namespace device

#endif//BIDPNFTYBWVOLMSCCTVLBOPWSHOYPCKVNCDBHFIMQBKWGXPKPYXGLHRETBMLXOPOFUENFTLQE
