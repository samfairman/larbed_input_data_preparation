#ifndef PEOVNTBGJBCVLTALQEQTKNUHOLLRREPVKWBPPQCODARUGTLHKTRRXDPSSRTWDKDTXCDQNGAIT
#define PEOVNTBGJBCVLTALQEQTKNUHOLLRREPVKWBPPQCODARUGTLHKTRRXDPSSRTWDKDTXCDQNGAIT

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct sinpi;

    template<> struct sinpi<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sinpif(x);
        }
    };//struct sinpi<float>

    template<> struct sinpi<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::sinpi(x);
        }
    };//struct sinpi<double>

    template< typename Type >
    struct sinpi< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct sinpi<complex<...> >

}//namespace device

#endif//PEOVNTBGJBCVLTALQEQTKNUHOLLRREPVKWBPPQCODARUGTLHKTRRXDPSSRTWDKDTXCDQNGAIT
