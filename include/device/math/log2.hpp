#ifndef NMKMKMUFVPMFRXVKACUDPJWPXNQVEABBSVIXFYJBYSUSUQRUTJLFHFKMSNELGUUUPSKXDFREI
#define NMKMKMUFVPMFRXVKACUDPJWPXNQVEABBSVIXFYJBYSUSUQRUTJLFHFKMSNELGUUUPSKXDFREI

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct log2;

    template<> struct log2<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::log2f(x);
        }
    };//struct log2<float>

    template<> struct log2<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::log2(x);
        }
    };//struct log2<double>

    template< typename Type >
    struct log2< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct log2<complex<...> >

}//namespace device

#endif//NMKMKMUFVPMFRXVKACUDPJWPXNQVEABBSVIXFYJBYSUSUQRUTJLFHFKMSNELGUUUPSKXDFREI
