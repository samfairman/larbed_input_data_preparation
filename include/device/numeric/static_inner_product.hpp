#ifndef _STATIC_INNER_PRODUCT_HPP_INCLUDED_SDFOPINASFLDKJSADFOKJNADSFKLJFDSJFDAJ
#define _STATIC_INNER_PRODUCT_HPP_INCLUDED_SDFOPINASFLDKJSADFOKJNADSFKLJFDSJFDAJ

#include <device/typedef.hpp>

namespace device
{

    namespace static_inner_product_private_dsfopinsdflkjnsadfljnfefdefds
    {
    template< device::size_t N >
    struct _static_inner_product
    {
        template< typename T>
        __device__
        T operator()( T* a_first, T* b_first, T init ) const 
        {
            return _static_inner_product<N-1>()( a_first+1, b_first+1, init + (*a_first)*(*b_first) );
        }
    };

    template<>
    struct _static_inner_product<0>
    {
        template< typename T>
        __device__
        T operator()( T*, T*, T init ) const 
        {
            return init;
        }
    };
    }//namespace static_inner_product_private_dsfopinsdflkjnsadfljnfefdefds

    template< device::size_t N, typename T >
    __device__
    T static_inner_product( T* a_first, T* b_first, T init )
    {
        using namespace static_inner_product_private_dsfopinsdflkjnsadfljnfefdefds;
        return _static_inner_product<N>()( a_first, b_first, init );
    }

}//namespace device

#endif//_STATIC_INNER_PRODUCT_HPP_INCLUDED_SDFOPINASFLDKJSADFOKJNADSFKLJFDSJFDAJ

