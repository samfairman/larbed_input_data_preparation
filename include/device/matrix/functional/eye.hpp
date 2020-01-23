#ifndef _EYE_HPP_INCLUDED_SPIOHSDF98Y4098YAHSFKLJV9408YAJKF498YUHAFDJKLSBNVFD98Y
#define _EYE_HPP_INCLUDED_SPIOHSDF98Y4098YAHSFKLJV9408YAJKF498YUHAFDJKLSBNVFD98Y

#include <device/typedef.hpp>
#include <device/matrix.hpp>
#include <device/allocator.hpp>
#include <device/algorithm/fill.hpp>

namespace device
{

    template<typename T >
    const device::matrix<T> eye( const device::size_t m, const device::size_t n, const T& v = T(1) )
    {
        device::matrix<T> ans( m, n );
        device::fill( ans.begin(), ans.end(), T() );
        device::fill( ans.diag_begin(), ans.diag_end(), v );
        return ans;
    }

    template<typename T >
    const device::matrix<T> eye( const device::size_t m, const T& v = T(1) )
    {
        return eye<T>( m, m, v );
    }

}//namespace device

#endif//_EYE_HPP_INCLUDED_SPIOHSDF98Y4098YAHSFKLJV9408YAJKF498YUHAFDJKLSBNVFD98Y

