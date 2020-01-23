#ifndef _FOR_EACH_N_HPP_INCLUDED_SDFPI4908YAFSH498YASFDIUH498YAFIU43H9A8YF348YAF
#define _FOR_EACH_N_HPP_INCLUDED_SDFPI4908YAFSH498YASFDIUH498YAFIU43H9A8YF348YAF 

#include <device/config/threads_per_block.hpp>
#include <device/typedef.hpp>
#include <device/iterator.hpp>

namespace device
{
    namespace for_each_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde
    {
        template< typename Iterator, typename Distance, typename Function >
        __global__
        void __for_each_n( Iterator first, const Distance n, Function f )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            if ( index >= n ) return;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                f( *(first+i) );
        }

        template< typename Iterator1, typename Iterator2, typename Distance, typename Function >
        __global__
        void __for_each_n( Iterator1 first1, Iterator2 first2, const Distance n, Function f )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            if ( index >= n ) return;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                f( *(first1+i), *(first2+i) );
        }

        template< typename Iterator1, typename Iterator2, typename Iterator3, typename Distance, typename Function >
        __global__
        void __for_each_n( Iterator1 first1, Iterator2 first2, Iterator3 first3, const Distance n, Function f )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            if ( index >= n ) return;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                f( *(first1+i), *(first2+i), *(first3+i) );
        }

        template< typename Iterator, typename Distance, typename Function >
        void _for_each_n( Iterator first, const Distance n, Function f, device::random_access_iterator_tag )
        {
            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;
            __for_each_n<<<blocks, threads>>>( first, n, f );
        }

        template< typename Iterator1, typename Iterator2, typename Distance, typename Function >
        void _for_each_n( Iterator1 first1, Iterator2 first2, const Distance n, Function f, device::random_access_iterator_tag, device::random_access_iterator_tag )
        {
            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;
            __for_each_n<<<blocks, threads>>>( first1, first2, n, f );
        }

        template< typename Iterator1, typename Iterator2, typename Iterator3, typename Distance, typename Function >
        void _for_each_n( Iterator1 first1, Iterator2 first2, Iterator3 first3, const Distance n, Function f, device::random_access_iterator_tag, device::random_access_iterator_tag, device::random_access_iterator_tag )
        {
            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;
            __for_each_n<<<blocks, threads>>>( first1, first2, first3, n, f );
        }

    }//namespace for_each_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde

    template< typename Iterator, typename Distance, typename Function >
    Function for_each_n( Iterator first, const Distance n, Function f )
    {
        using namespace for_each_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde;
        typedef typename device::iterator_traits<Iterator>::iterator_category iterator_category;
        _for_each_n( first, n, f, iterator_category() );
        return f;
    }

    template< typename Iterator1, typename Iterator2, typename Distance, typename Function >
    Function for_each_n( Iterator1 first1, Iterator2 first2, const Distance n, Function f )
    {
        using namespace for_each_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde;
        typedef typename device::iterator_traits<Iterator1>::iterator_category iterator_category1;
        typedef typename device::iterator_traits<Iterator2>::iterator_category iterator_category2;
        _for_each_n( first1, first2, n, f, iterator_category1(), iterator_category2() );
        return f;
    }

    template< typename Iterator1, typename Iterator2, typename Iterator3, typename Distance, typename Function >
    Function for_each_n( Iterator1 first1, Iterator2 first2, Iterator3 first3, const Distance n, Function f )
    {
        using namespace for_each_n_impl_dsp9ij49uihasflkjasfdljkhasdfiuhfddskjhfsfde;
        typedef typename device::iterator_traits<Iterator1>::iterator_category iterator_category1;
        typedef typename device::iterator_traits<Iterator2>::iterator_category iterator_category2;
        typedef typename device::iterator_traits<Iterator3>::iterator_category iterator_category3;
        _for_each_n( first1, first2, first3, n, f, iterator_category1(), iterator_category2(), iterator_category3() );
        return f;
    }

}//namespace device

#endif//_FOR_EACH_N_HPP_INCLUDED_SDFPI4908YAFSH498YASFDIUH498YAFIU43H9A8YF348YAF 

