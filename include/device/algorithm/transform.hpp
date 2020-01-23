#ifndef _TRANSFORM_HPP_INCLUDED_SFODIPASLKJHSADFLKJH4O9HUAFLKJHSDIUHSOIFUH3498SF
#define _TRANSFORM_HPP_INCLUDED_SFODIPASLKJHSADFLKJH4O9HUAFLKJHSDIUHSOIFUH3498SF

#include <device/config/threads_per_block.hpp>
#include <device/iterator.hpp>
#include <device/typedef.hpp>

namespace device
{

    namespace transform_impl_dsfiounaslkjnsdoiun4ijafsoiu34haskfjbdsiu
    {

        template< typename InputIterator, typename Distance, typename OutputIterator, typename Device_Function >
        __global__
        void __transform_n( InputIterator in_first, const Distance n, OutputIterator out_first, Device_Function f )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                *( out_first + i ) = f( *( in_first + i ) );
        }

        template< typename InputIterator_1, typename Distance, typename InputIterator_2, typename OutputIterator, typename Device_Function >
        __global__
        void __transform_n( InputIterator_1 in_first_1, const Distance n, InputIterator_2 in_first_2, OutputIterator out_first, Device_Function f )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                *( out_first + i ) = f( *( in_first_1 + i ), *( in_first_2 + i ) );
        }

        template< typename InputIterator_1, typename Distance, typename InputIterator_2, typename InputIterator_3, typename OutputIterator, typename Device_Function >
        __global__
        void __transform_n( InputIterator_1 in_first_1, const Distance n, InputIterator_2 in_first_2, InputIterator_3 in_first_3, OutputIterator out_first, Device_Function f )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                *( out_first + i ) = f( *( in_first_1 + i ), *( in_first_2 + i ), *(in_first_3 + i ) );
        }

        template< typename InputIterator, typename Distance, typename OutputIterator, typename Device_Function >
        void _transform_n( InputIterator in_first, const Distance n, OutputIterator out_first, Device_Function f, device::random_access_iterator_tag, device::random_access_iterator_tag )
        {
            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;
            __transform_n<<<blocks, threads>>>( in_first, n, out_first, f );
        }

        template< typename InputIterator_1, typename  Distance, typename InputIterator_2, typename OutputIterator, typename Device_Function >
        void _transform_n( InputIterator_1 in_first_1, const Distance n, InputIterator_2 in_first_2, OutputIterator out_first, Device_Function f, device::random_access_iterator_tag, device::random_access_iterator_tag, device::random_access_iterator_tag )
        {
            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;
            __transform_n<<<blocks, threads>>>( in_first_1, n, in_first_2, out_first, f );
        }

        template< typename InputIterator_1, typename  Distance, typename InputIterator_2, typename InputIterator_3, typename OutputIterator, typename Device_Function >
        void _transform_n( InputIterator_1 in_first_1, const Distance n, InputIterator_2 in_first_2, InputIterator_3 in_first_3, OutputIterator out_first, Device_Function f, device::random_access_iterator_tag, device::random_access_iterator_tag, device::random_access_iterator_tag, device::random_access_iterator_tag )
        {
            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;
            __transform_n<<<blocks, threads>>>( in_first_1, n, in_first_2, in_first_3, out_first, f );
        }

    }//namespace transform_impl_dsfiounaslkjnsdoiun4ijafsoiu34haskfjbdsiu

    template< typename InputIterator, typename OutputIterator, typename Device_Function >
    void transform( InputIterator in_first, InputIterator in_last, OutputIterator out_first, Device_Function f )
    {
        using namespace transform_impl_dsfiounaslkjnsdoiun4ijafsoiu34haskfjbdsiu;
        typedef typename device::iterator_traits<InputIterator>::iterator_category iterator_category_1;
        typedef typename device::iterator_traits<OutputIterator>::iterator_category iterator_category_2;
        const device::ptrdiff_t n = device::distance( in_first, in_last );
        _transform_n( in_first, n, out_first, f, iterator_category_1(), iterator_category_2() );
    }

    template< typename InputIterator_1, typename InputIterator_2, typename OutputIterator, typename Device_Function >
    void transform( InputIterator_1 in_first_1, InputIterator_1 in_last_1, InputIterator_2 in_first_2, OutputIterator out_first, Device_Function f )
    {
        using namespace transform_impl_dsfiounaslkjnsdoiun4ijafsoiu34haskfjbdsiu;
        typedef typename device::iterator_traits<InputIterator_1>::iterator_category iterator_category_1;
        typedef typename device::iterator_traits<InputIterator_2>::iterator_category iterator_category_2;
        typedef typename device::iterator_traits<OutputIterator>::iterator_category iterator_category_3;
        const device::ptrdiff_t n = device::distance( in_first_1, in_last_1 );
        _transform_n( in_first_1, n, in_first_2, out_first, f, iterator_category_1(), iterator_category_2(), iterator_category_3() );
    }

    template< typename InputIterator_1, typename InputIterator_2, typename InputIterator_3, typename OutputIterator, typename Device_Function >
    void transform( InputIterator_1 in_first_1, InputIterator_1 in_last_1, InputIterator_2 in_first_2, InputIterator_3 in_first_3, OutputIterator out_first, Device_Function f )
    {
        using namespace transform_impl_dsfiounaslkjnsdoiun4ijafsoiu34haskfjbdsiu;
        typedef typename device::iterator_traits<InputIterator_1>::iterator_category iterator_category_1;
        typedef typename device::iterator_traits<InputIterator_2>::iterator_category iterator_category_2;
        typedef typename device::iterator_traits<InputIterator_3>::iterator_category iterator_category_3;
        typedef typename device::iterator_traits<OutputIterator>::iterator_category iterator_category_4;
        const device::ptrdiff_t n = device::distance( in_first_1, in_last_1 );
        _transform_n( in_first_1, n, in_first_2, in_first_3, out_first, f, iterator_category_1(), iterator_category_2(), iterator_category_3(), iterator_category_4() );
    }

}//namespace device

#endif//_TRANSFORM_HPP_INCLUDED_SFODIPASLKJHSADFLKJH4O9HUAFLKJHSDIUHSOIFUH3498SF

