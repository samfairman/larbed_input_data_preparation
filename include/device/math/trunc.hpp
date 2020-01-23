#ifndef UGCXJNRBEWURATOUUUXVJFDKBUPMWVCMYYYMCLQQUWGUIXICHXJOPEUIHDXWLGKNBWLELQLRN
#define UGCXJNRBEWURATOUUUXVJFDKBUPMWVCMYYYMCLQQUWGUIXICHXJOPEUIHDXWLGKNBWLELQLRN

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct trunc;

    template<> struct trunc<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::truncf(x);
        }
    };//struct trunc<float>

    template<> struct trunc<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::trunc(x);
        }
    };//struct trunc<double>

    template< typename Type >
    struct trunc< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct trunc<complex<...> >

}//namespace device

#endif//UGCXJNRBEWURATOUUUXVJFDKBUPMWVCMYYYMCLQQUWGUIXICHXJOPEUIHDXWLGKNBWLELQLRN
