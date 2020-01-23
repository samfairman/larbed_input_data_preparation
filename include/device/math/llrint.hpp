#ifndef TYKXSPAHVUAKFWWJVEKJCBSHPUFLXHVSMTNYYYDXROROHSSDIPPTMUMAMQKSQBEWCKRQODPRV
#define TYKXSPAHVUAKFWWJVEKJCBSHPUFLXHVSMTNYYYDXROROHSSDIPPTMUMAMQKSQBEWCKRQODPRV

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct llrint;

    template<> struct llrint<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::llrintf(x);
        }
    };//struct llrint<float>

    template<> struct llrint<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::llrint(x);
        }
    };//struct llrint<double>

    template< typename Type >
    struct llrint< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct llrint<complex<...> >

}//namespace device

#endif//TYKXSPAHVUAKFWWJVEKJCBSHPUFLXHVSMTNYYYDXROROHSSDIPPTMUMAMQKSQBEWCKRQODPRV
