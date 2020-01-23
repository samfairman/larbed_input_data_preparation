#ifndef VPOLXWAULXBSTVAMBCVMYEROYLFHGYAENXGFGUSRVWDDKRTQGAYRTJNRCPFRPEBTCEPQLIRKV
#define VPOLXWAULXBSTVAMBCVMYEROYLFHGYAENXGFGUSRVWDDKRTQGAYRTJNRCPFRPEBTCEPQLIRKV

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct atan;

    template<> struct atan<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::atanf(x);
        }
    };//struct atan<float>

    template<> struct atan<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::atan(x);
        }
    };//struct atan<double>

    template< typename Type >
    struct atan< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct atan<complex<...> >

}//namespace device

#endif//VPOLXWAULXBSTVAMBCVMYEROYLFHGYAENXGFGUSRVWDDKRTQGAYRTJNRCPFRPEBTCEPQLIRKV
