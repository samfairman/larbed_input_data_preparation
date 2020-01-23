#ifndef PSPHBGKMBXDRCCJNYGSKABBQDAVOFLOSQWLSLDMNGWGKSBLKKCGXOPUVCRUHUHYNRGKRIHBOU
#define PSPHBGKMBXDRCCJNYGSKABBQDAVOFLOSQWLSLDMNGWGKSBLKKCGXOPUVCRUHUHYNRGKRIHBOU

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct exp10;

    template<> struct exp10<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::exp10f(x);
        }
    };//struct exp10<float>

    template<> struct exp10<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::exp10(x);
        }
    };//struct exp10<double>

    template< typename Type >
    struct exp10< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct exp10<complex<...> >

}//namespace device

#endif//PSPHBGKMBXDRCCJNYGSKABBQDAVOFLOSQWLSLDMNGWGKSBLKKCGXOPUVCRUHUHYNRGKRIHBOU
