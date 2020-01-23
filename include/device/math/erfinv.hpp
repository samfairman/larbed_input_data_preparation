#ifndef NWSVEWVRCIQCBUYNTPSKAWTWJFDMFSEEDYXBMJRLLJCCSETRSHNRWTOITTWCKLYPWGYYCTSBW
#define NWSVEWVRCIQCBUYNTPSKAWTWJFDMFSEEDYXBMJRLLJCCSETRSHNRWTOITTWCKLYPWGYYCTSBW

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct erfinv;

    template<> struct erfinv<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfinvf(x);
        }
    };//struct erfinv<float>

    template<> struct erfinv<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::erfinv(x);
        }
    };//struct erfinv<double>

    template< typename Type >
    struct erfinv< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct erfinv<complex<...> >

}//namespace device

#endif//NWSVEWVRCIQCBUYNTPSKAWTWJFDMFSEEDYXBMJRLLJCCSETRSHNRWTOITTWCKLYPWGYYCTSBW
