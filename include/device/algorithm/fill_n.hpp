#ifndef _FILL_N_HPP_INCLUDED_9834DFSJKVKNSD98HVJAHSDIUHFDS9UH4UI9HASFKJHSFKJHDFFDD
#define _FILL_N_HPP_INCLUDED_9834DFSJKVKNSD98HVJAHSDIUHFDS9UH4UI9HASFKJHSFKJHDFFDD

#include <device/config/threads_per_block.hpp>
#include <device/typedef.hpp>
#include <device/iterator.hpp>

namespace device
{
    namespace fill_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde
    {
        template< typename OutputIterator, typename Distance, typename Type >
        __global__
        void __fill_n( OutputIterator first, const Distance n, const Type v )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                *( first + i ) = v;
        }

        template< typename OutputIterator, typename Distance, typename Type >
        void _fill_n( OutputIterator first, const Distance n, const Type& v, device::random_access_iterator_tag )
        {
            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;
            __fill_n<<<blocks, threads>>>( first, n, v );
        }

    }//namespace fill_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde

    template< typename OutputIterator, typename Distance, typename Type >
    void fill_n( OutputIterator first, const Distance n, const Type& v )
    {
        using namespace fill_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde;
        typedef typename device::iterator_traits<OutputIterator>::iterator_category iterator_category;
        _fill_n( first, n, v, iterator_category() );
    }

}//namespace device

#endif//_FILL_N_HPP_INCLUDED_9834DFSJKVKNSD98HVJAHSDIUHFDS9UH4UI9HASFKJHSFKJHDFFDD 

