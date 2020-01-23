#ifndef _FILL_HPP_INCLUDED_SFOPIAHJSFD9O84Y98AHFUSKASJHFD498Y7HAFKSDLHVKJBV8UH74
#define _FILL_HPP_INCLUDED_SFOPIAHJSFD9O84Y98AHFUSKASJHFD498Y7HAFKSDLHVKJBV8UH74

#include <device/algorithm/fill_n.hpp>
#include <device/iterator.hpp>

namespace device
{

    template< typename OutputIterator, typename Type >
    void fill( OutputIterator first, OutputIterator last, const Type& v )
    {
        device::fill_n( first, device::distance(first, last), v );
    }

}//namespace device

#endif//_FILL_HPP_INCLUDED_SFOPIAHJSFD9O84Y98AHFUSKASJHFD498Y7HAFKSDLHVKJBV8UH74

