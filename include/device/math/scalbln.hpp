#ifndef TDKHPJSDBUCFFCNRMASTTNEFMRLUVCWNTFMNSOETNOOPRHWQGDENPIHGJFTCQDXHHMQOKFUVS
#define TDKHPJSDBUCFFCNRMASTTNEFMRLUVCWNTFMNSOETNOOPRHWQGDENPIHGJFTCQDXHHMQOKFUVS

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct scalbln;

    template<> struct scalbln<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::scalblnf(x, y);
        }
    };//struct scalbln<float>

    template<> struct scalbln<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::scalbln(x, y);
        }
    };//struct scalbln<double>

    template< typename Type >
    struct scalbln< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct scalbln<complex<...> >

}//namespace device

#endif//TDKHPJSDBUCFFCNRMASTTNEFMRLUVCWNTFMNSOETNOOPRHWQGDENPIHGJFTCQDXHHMQOKFUVS
