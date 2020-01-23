#ifndef _COPY_N_HPP_INCLUDED_SDIOASDFKJ39HUAFILSDJHAKFDSL49UHIAFJKLDSNMVB9834UHI
#define _COPY_N_HPP_INCLUDED_SDIOASDFKJ39HUAFILSDJHAKFDSL49UHIAFJKLDSNMVB9834UHI

#include <device/config/threads_per_block.hpp>
#include <device/iterator.hpp>
#include <device/typedef.hpp>

namespace device
{

    namespace copy_impl_safdinasfijn4eoiubnasflkjnsafdiuhb4ejafbfdiuhf
    {
        template< typename InputIterator, typename Distance, typename OutputIterator >
        __global__
        void __copy_n( InputIterator input_first, const Distance n, OutputIterator output_first )
        {
            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            for ( device::size_t i = index; i < n; i += blockDim.x * gridDim.x )
                *( output_first + i ) = *( input_first + i );
        }

        template< typename InputIterator, typename Distance, typename OutputIterator >
        void _copy_n( InputIterator input_first, const Distance n, OutputIterator output_first, device::random_access_iterator_tag, device::random_access_iterator_tag )
        {
            // threads per block
            const device::size_t threads = device::threads_per_block::value;
            // blocks per grid
            const device::size_t blocks   = ( n + threads - 1 ) / threads;
            __copy_n <<< blocks, threads>>>( input_first, n, output_first );
        }
    }//namespace copy_impl_safdinasfijn4eoiubnasflkjnsafdiuhb4ejafbfdiuhf

    template< typename InputIterator, typename Distance, typename OutputIterator >
    OutputIterator copy_n( InputIterator input_first, const Distance n, OutputIterator output_first )
    {
        using namespace copy_impl_safdinasfijn4eoiubnasflkjnsafdiuhb4ejafbfdiuhf;
        typedef typename device::iterator_traits<InputIterator>::iterator_category iterator_category_1;
        typedef typename device::iterator_traits<OutputIterator>::iterator_category iterator_category_2;
        _copy_n( input_first, n, output_first, iterator_category_1(), iterator_category_2() );
        return output_first;
    }

}//namespace device

#endif//_COPY_N_HPP_INCLUDED_SDIOASDFKJ39HUAFILSDJHAKFDSL49UHIAFJKLDSNMVB9834UHI

