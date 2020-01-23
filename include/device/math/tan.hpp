#ifndef WNUCIFNMNMEDUGYVHWSYNAAVMJKVHFBLJTHDVXUEENEPBNFYQDUXELCKDBTEIPQIHPYFEKPIF
#define WNUCIFNMNMEDUGYVHWSYNAAVMJKVHFBLJTHDVXUEENEPBNFYQDUXELCKDBTEIPQIHPYFEKPIF

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct tan;

    template<> struct tan<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::tanf(x);
        }
    };//struct tan<float>

    template<> struct tan<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::tan(x);
        }
    };//struct tan<double>

    template< typename Type >
    struct tan< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct tan<complex<...> >

}//namespace device

#endif//WNUCIFNMNMEDUGYVHWSYNAAVMJKVHFBLJTHDVXUEENEPBNFYQDUXELCKDBTEIPQIHPYFEKPIF
