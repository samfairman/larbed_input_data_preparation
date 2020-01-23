#ifndef _MISC_HPP_INCLUDED_SDP9JIASOI49UHASFDLKJSAFOIUN34IHABSFKSJDHBF847HUFASKJ
#define _MISC_HPP_INCLUDED_SDP9JIASOI49UHASFDLKJSAFOIUN34IHABSFKSJDHBF847HUFASKJ

#include <device/typedef.hpp>

namespace device
{
    template<typename T>
    struct remove_reference
    {
        typedef T result_type;
    };

    template<typename T>
    struct remove_reference<T&>
    {
        typedef T result_type;
    };

    template<typename T>
    struct remove_const
    {
        typedef T result_type;
    };

    template<typename T>
    struct remove_const<T const>
    {
        typedef T result_type;
    };

    struct range 
    {
        typedef range self_type;
        typedef device::size_t value_type;

        value_type first;
        value_type second;

        range( const value_type first_, const value_type second_ ) : first(first_), second(second_) {}
        range( const self_type& other ) : first(other.first), second(other.second) {}

        friend const self_type 
        operator + ( const self_type lhs, const device::size_t n )
        {
            return self_type( lhs.first+n, lhs.second+n );
        }
        friend const self_type 
        operator - ( const self_type lhs, const device::size_t n )
        {
            return self_type( lhs.first-n, lhs.second-n );
        }
    };//struct range

}//namespace device

#endif//_MISC_HPP_INCLUDED_SDP9JIASOI49UHASFDLKJSAFOIUN34IHABSFKSJDHBF847HUFASKJ

