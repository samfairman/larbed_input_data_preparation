#ifndef _INVERSE_HPP_INCLUDED_FIONASFKLNJ3IOUANFKLJSDNOSPIAFDJSFD9OJAFDOIJFFEFA1
#define _INVERSE_HPP_INCLUDED_FIONASFKLNJ3IOUANFKLJSDNOSPIAFDJSFD9OJAFDOIJFFEFA1

#include <device/complex.hpp>
#include <device/math/sqrt.hpp>

namespace device
{
    template<typename Type>
    struct inverse
    {
        typedef Type value_type;
        
        __host__ __device__
        value_type operator()( const value_type& x ) const
        {
            return value_type(1) / x;
        }
    
    };//struct inverse

    template<typename Type>
    struct inverse<device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __host__ __device__
        value_type operator()( const value_type& c ) const 
        {
            return value_type(c.real(), -c.imag()) / ( c.real()*c.real()+c.imag()*c.imag() );
        }
    };//struct inverse<complex<...>>

}//namespace devic3

#endif//_INVERSE_HPP_INCLUDED_FIONASFKLNJ3IOUANFKLJSDNOSPIAFDJSFD9OJAFDOIJFFEFA1

