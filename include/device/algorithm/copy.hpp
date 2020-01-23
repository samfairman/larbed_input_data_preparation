#ifndef _COPY_HPP_INCLUDED_DSOIHASLKJHASFDKJHASDFKJHSDFIUH3KJHFSJHDFIUHASFDFDDSF
#define _COPY_HPP_INCLUDED_DSOIHASLKJHASFDKJHASDFKJHSDFIUH3KJHFSJHDFIUHASFDFDDSF

#include <device/algorithm/copy_n.hpp>
#include <device/iterator.hpp>

namespace device
{

    template< typename InputIterator, typename OutputIterator >
    OutputIterator copy( InputIterator input_first, InputIterator src_last, OutputIterator output_first )
    {
        return device::copy_n( input_first, device::distance(input_first, src_last), output_first );
    }

}//namespace device

#endif//_COPY_HPP_INCLUDED_DSOIHASLKJHASFDKJHASDFKJHSDFIUH3KJHFSJHDFIUHASFDFDDSF

