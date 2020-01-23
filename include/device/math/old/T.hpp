#ifndef
#define

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct _fun_name;

    template<> struct _fun_name<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type()( const value_type x ) const
        {
            return ::_fun_namef(x);
        }
    };//struct _fun_name<float>

    template<> struct _fun_name<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type()( const value_type x ) const
        {
            return ::_fun_name(x);
        }
    };//struct _fun_name<double>

    template< typename Type >
    struct _fun_name< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct _fun_name<complex<...> >

}//namespace device

#endif//
