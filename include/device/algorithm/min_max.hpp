#ifndef _MIN_MAX_HPP_INCLUDED_DSFPOINASLDKJ3OUASFDLKJAS48UEHAFKJHB4389FH89UFKJFD
#define _MIN_MAX_HPP_INCLUDED_DSFPOINASLDKJ3OUASFDLKJAS48UEHAFKJHB4389FH89UFKJFD

namespace device
{
    template<typename T>
    __host__ __device__
    T const min( const T& lhs, const T& rhs )
    {
        return lhs > rhs ? rhs : lhs;
    }

    template<typename T>
    __host__ __device__
    T const max( const T& lhs, const T& rhs )
    {
        return lhs > rhs ? lhs : rhs;
    }
}//namespace device

#endif//_MIN_MAX_HPP_INCLUDED_DSFPOINASLDKJ3OUASFDLKJAS48UEHAFKJHB4389FH89UFKJFD

