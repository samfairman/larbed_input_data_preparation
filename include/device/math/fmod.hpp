#ifndef PPGXUWGHGATLSOLXYWEDYYRUXALJBSYUXMUWNQWGUFMAYHOQRNYVSDTTQSCXIOKYFNXSPEIHE
#define PPGXUWGHGATLSOLXYWEDYYRUXALJBSYUXMUWNQWGUFMAYHOQRNYVSDTTQSCXIOKYFNXSPEIHE

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct fmod;

    template<> struct fmod<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::fmodf(x, y);
        }
    };//struct fmod<float>

    template<> struct fmod<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::fmod(x, y);
        }
    };//struct fmod<double>

    template< typename Type >
    struct fmod< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct fmod<complex<...> >

}//namespace device

#endif//PPGXUWGHGATLSOLXYWEDYYRUXALJBSYUXMUWNQWGUFMAYHOQRNYVSDTTQSCXIOKYFNXSPEIHE
