#ifndef _FOR_EACH_HPP_INCLUDED_SDPOIJSADLFKJND9H43OHAFD093Y8AFLHADFDF984HFD938YH
#define _FOR_EACH_HPP_INCLUDED_SDPOIJSADLFKJND9H43OHAFD093Y8AFLHADFDF984HFD938YH

#include <device/algorithm/for_each_n.hpp>
#include <device/iterator.hpp>

namespace device
{

    template< typename Iterator, typename Function >
    void for_each( Iterator first, Iterator last, Function f )
    {
        device::for_each_n( first, device::distance(first, last), f );
    }

    template< typename Iterator1, typename Iterator2, typename Function >
    void for_each( Iterator1 first1, Iterator1 last1, Iterator2 first2,  Function f )
    {
        device::for_each_n( first1, first2, device::distance(first1, last1), f );
    }

    template< typename Iterator1, typename Iterator2, typename Iterator3, typename Function >
    void for_each( Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator3 first3,  Function f )
    {
        device::for_each_n( first1, first2, first3, device::distance(first1, last1), f );
    }

}//namespace device

#endif//_FOR_EACH_HPP_INCLUDED_SDPOIJSADLFKJND9H43OHAFD093Y8AFLHADFDF984HFD938YH

