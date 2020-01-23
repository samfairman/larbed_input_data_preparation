#ifndef _NORM_TCC_INCLUDED_DSOINSADKLJ498YAFLKJH398YHASFIKH4398YHAF8943YFUIOH938
#define _NORM_TCC_INCLUDED_DSOINSADKLJ498YAFLKJH398YHASFIKH4398YHAF8943YFUIOH938

#include <device/complex.hpp>
#include <device/config/threads_per_block.hpp>
#include <device/math/abs.hpp>
#include <device/typedef.hpp>
#include <device/vector.hpp>
#include <device/iterator.hpp>
#include <device/numeric/accumulate.hpp>

namespace device
{
    template<typename Iterator>
    typename device::complex_value_type< typename device::iterator_traits<Iterator>::value_type >::value_type
    norm( Iterator first, Iterator last )
    {
        typedef typename device::iterator_traits<Iterator>::value_type value_type;
        typedef typename device::complex_value_type< value_type >::value_type real_type;
        const device::size_t n = device::distance( first, last );
        device::vector<real_type> a(n);
        device::transform( first, last, a.begin(), device::abs<value_type>() );
        return device::accumulate( a.begin(), a.end(), real_type(0) );
    }

    template<typename T, typename A>
    typename device::complex_value_type<T>::value_type device::vector<T,A>::norm() const
    {
        return device::norm( begin(), end() );
    }

}

#endif//_NORM_TCC_INCLUDED_DSOINSADKLJ498YAFLKJH398YHASFIKH4398YHAF8943YFUIOH938

