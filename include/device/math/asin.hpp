#ifndef BCTIBCAOQSEJTMWSUFOOSXRGCFMVCSGIHIBIKHGDPJQFUCJCTQXNRJWSULHSRSHNCUSNQTJSL
#define BCTIBCAOQSEJTMWSUFOOSXRGCFMVCSGIHIBIKHGDPJQFUCJCTQXNRJWSULHSRSHNCUSNQTJSL

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct asin;

    template<> struct asin<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::asinf(x);
        }
    };//struct asin<float>

    template<> struct asin<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::asin(x);
        }
    };//struct asin<double>

    template< typename Type >
    struct asin< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct asin<complex<...> >

}//namespace device

#endif//BCTIBCAOQSEJTMWSUFOOSXRGCFMVCSGIHIBIKHGDPJQFUCJCTQXNRJWSULHSRSHNCUSNQTJSL
