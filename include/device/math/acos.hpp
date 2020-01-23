#ifndef XQEFHIJKBNJBNATGGOVPMTWXROQVBSKGWYHIISAFBDUCUTFVBYAWHYBRTEWYAQJVMGFLFABJN
#define XQEFHIJKBNJBNATGGOVPMTWXROQVBSKGWYHIISAFBDUCUTFVBYAWHYBRTEWYAQJVMGFLFABJN

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct acos;

    template<> struct acos<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::acosf(x);
        }
    };//struct acos<float>

    template<> struct acos<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::acos(x);
        }
    };//struct acos<double>

    template< typename Type >
    struct acos< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct acos<complex<...> >

}//namespace device

#endif//XQEFHIJKBNJBNATGGOVPMTWXROQVBSKGWYHIISAFBDUCUTFVBYAWHYBRTEWYAQJVMGFLFABJN
