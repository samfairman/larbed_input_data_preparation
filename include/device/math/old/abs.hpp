#ifndef _ABS_HPP_INCLUDED_DSOPIJ498HASFLKJH4098YAHWFELKJH4987HASFKJ4987HAFLKJH98
#define _ABS_HPP_INCLUDED_DSOPIJ498HASFLKJH4098YAHWFELKJH4987HASFKJ4987HAFLKJH98

#include <device/complex.hpp>
#include <device/math/sqrt.hpp>

namespace device
{
    /*
    template<typename Type> __device__
    Type abs( const Type& x )
    {
        return x > Type(0) ? x : -x;
    }

    template<typename Type> __device__
    Type abs( const device::complex<Type>& c )
    {
        const Type r = device::sqrt( c.real()*c.real() + c.imag()*c.imag() );
    }
    */
    template<typename Type>
    struct abs
    {
        typedef Type value_type;
        
        __host__ __device__
        value_type operator()( const value_type& x ) const
        {
            return x > Type(0) ? x : -x;
        }
    
    };//struct abs

    template<typename Type>
    struct abs<device::complex<Type> >
    {
        typedef Type value_type;

        __host__ __device__
        value_type operator()( const device::complex<Type>& c ) const 
        {
            return device::sqrt<value_type>()( c.real()*c.real() + c.imag()*c.imag() );
        }
    };//struct abs<complex<...>>

}

#endif//_ABS_HPP_INCLUDED_DSOPIJ498HASFLKJH4098YAHWFELKJH4987HASFKJ4987HAFLKJH98

