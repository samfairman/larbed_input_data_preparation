#ifndef IBKOGSMLYLFKRVKJTFYSGELFKNIOLXMUCKUNIAUYUROTNFCDACNTJCCMXYTSKMQYQNVXIFGQE
#define IBKOGSMLYLFKRVKJTFYSGELFKNIOLXMUCKUNIAUYUROTNFCDACNTJCCMXYTSKMQYQNVXIFGQE

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct tanh;

    template<> struct tanh<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::tanhf(x);
        }
    };//struct tanh<float>

    template<> struct tanh<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::tanh(x);
        }
    };//struct tanh<double>

    template< typename Type >
    struct tanh< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct tanh<complex<...> >

}//namespace device

#endif//IBKOGSMLYLFKRVKJTFYSGELFKNIOLXMUCKUNIAUYUROTNFCDACNTJCCMXYTSKMQYQNVXIFGQE
