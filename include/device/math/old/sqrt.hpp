#ifndef _SQRT_HPP_INCLUDED_DSPOINASFLKDJN39HUASFLKJH498HAFKLJHFDS9H498HASDF4ERRE
#define _SQRT_HPP_INCLUDED_DSPOINASFLKDJN39HUASFLKJH498HAFKLJHFDS9H498HASDF4ERRE

#include <device/complex.hpp>
#include <device/math/copysign.hpp>
#include <device/math/rsqrt.hpp> 

namespace device
{

    template<typename Type>
    struct sqrt;

    template<>
    struct sqrt<float>
    {
        typedef float value_type;
        __host__ __device__
        value_type operator () ( const value_type x ) const 
        {
            return value_type(1) / device::rsqrt<value_type>()(x);
        }
    };

    template<>
    struct sqrt<double>
    {
        typedef double value_type;
        __host__ __device__
        value_type operator () ( const value_type x ) const 
        {
            return value_type(1) / device::rsqrt<value_type>()(x);
        }
    };

    template<>
    struct sqrt<device::complex<float> >
    {
        typedef device::complex<float> value_type;

        __host__ __device__
        value_type operator()( const value_type& c ) const 
        {
            float const x   = c.real();
            float const y   = c.imag();
            float const r   = device::sqrt<float>()( x*x + y*y );
            float const r_  = device::sqrt<float>()( (r + x) / float(2) );
            float const i_  = device::sqrt<float>()( (r - x) / float(2) );

            return device::complex<float>( r_, device::copysign<float>()( i_, y ) );
        }
    };

    template<>
    struct sqrt<device::complex<double> >
    {
        typedef device::complex<double> value_type;

        __host__ __device__
        value_type operator()( const value_type& c ) const 
        {
            double const x   = c.real();
            double const y   = c.imag();
            double const r   = device::sqrt<double>()( x*x + y*y );
            double const r_  = device::sqrt<double>()( (r + x) / double(2) );
            double const i_  = device::sqrt<double>()( (r - x) / double(2) );

            return device::complex<double>( r_, device::copysign<double>()( i_, y ) );
        }
    };

}//namespace device

#endif//_SQRT_HPP_INCLUDED_DSPOINASFLKDJN39HUASFLKJH498HAFKLJHFDS9H498HASDF4ERRE

