#ifndef YLSPPMLIQNBGAWQABWGGNPOIIPAGRDXVEWANTYDOCOMUPCVDXQADTTKDGUOCSLFCLLTEGODXY
#define YLSPPMLIQNBGAWQABWGGNPOIIPAGRDXVEWANTYDOCOMUPCVDXQADTTKDGUOCSLFCLLTEGODXY

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct jn;

    template<> struct jn<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const int n, const value_type x ) const
        {
            return ::jnf(n,x);
        }
    };//struct jn<float>

    template<> struct jn<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const int n, const value_type x ) const
        {
            return ::jn(n, x);
        }
    };//struct jn<double>

    template< typename Type >
    struct jn< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const int n, const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct jn<complex<...> >

}//namespace device

#endif//YLSPPMLIQNBGAWQABWGGNPOIIPAGRDXVEWANTYDOCOMUPCVDXQADTTKDGUOCSLFCLLTEGODXY
