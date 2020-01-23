#ifndef _ITERATOR_TRAITS_HPP_INCLUDED_DFSAOISFALIU498AFKJH4KJAFKJBVIAHJFD84UHAFI
#define _ITERATOR_TRAITS_HPP_INCLUDED_DFSAOISFALIU498AFKJH4KJAFKJBVIAHJFD84UHAFI

#include <device/typedef.hpp>

namespace device
{
    struct input_iterator_tag {};

    struct output_iterator_tag {};

    struct forward_iterator_tag : public input_iterator_tag {};

    struct bidirectional_iterator_tag : public forward_iterator_tag {};

    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<typename Category, typename Type, typename Distance = device::ptrdiff_t, typename Pointer = Type *, typename Reference = Type&>
    struct iterator
    {
        typedef Category        iterator_category;
        typedef Type            value_type;
        typedef Distance        difference_type;
        typedef Pointer         pointer;
        typedef Reference       reference;
    };

    template<typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    template<typename Type>
    struct iterator_traits<Type *>
    {
        typedef random_access_iterator_tag      iterator_category;
        typedef Type                            value_type;
        typedef device::ptrdiff_t               difference_type;
        typedef Type                           *pointer;
        typedef Type&                           reference;
    };

    template<typename Type>
    struct iterator_traits<const Type *>
    {
        typedef random_access_iterator_tag      iterator_category;
        typedef Type                            value_type;
        typedef device::ptrdiff_t               difference_type;
        typedef const Type                     *pointer;
        typedef const Type&                     reference;
    };


    namespace distance_impl_dsopainsdofuin4kljanfsoiun4kajhfb84huafkjb
    {

        template<typename InputIterator>
        inline typename iterator_traits<InputIterator>::difference_type
        __distance( InputIterator first, InputIterator last, input_iterator_tag )
        {
            if ( first == last )
                return 0;
            //compiler will optimize here
            return 1 + __distance( ++first, last, input_iterator_tag() );
        }

        template<typename RandomAccessIterator>
        inline typename iterator_traits<RandomAccessIterator>::difference_type
        __distance( RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag )
        {
            return last - first;
        }

    }//namespace distance_impl_dsopainsdofuin4kljanfsoiun4kajhfb84huafkjb

    template<typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance( InputIterator first, InputIterator last )
    {
        using namespace distance_impl_dsopainsdofuin4kljanfsoiun4kajhfb84huafkjb;
        typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
        return __distance( first, last, iterator_category() );
    }

    namespace advance_impl_siopn34987huafkjhaslkfjn4euoinasfkj48unfaif
    {

        template<typename InputIterator, typename Distance>
        inline void
        __advance( InputIterator& i, Distance n, device::input_iterator_tag )
        {
            while ( n-- )
                ++i;
        }

        template<typename _BidirectionalIterator, typename Distance>
        inline void __advance( _BidirectionalIterator& i, Distance n, device::bidirectional_iterator_tag )
        {
            if ( n > 0 )
                while ( n-- )
                    ++i;
            else
                while ( n++ )
                    --i;
        }

        template<typename RandomAccessIterator, typename Distance>
        inline void __advance( RandomAccessIterator& i, Distance n, device::random_access_iterator_tag )
        {
            i += n;
        }
    }//namespace advance_impl_siopn34987huafkjhaslkfjn4euoinasfkj48unfaif

    template<typename InputIterator, typename Distance>
    inline void advance( InputIterator& i, Distance n )
    {
        using namespace advance_impl_siopn34987huafkjhaslkfjn4euoinasfkj48unfaif;
        typename device::iterator_traits<InputIterator>::difference_type d = n;
        typedef typename device::iterator_traits<InputIterator>::iterator_category iterator_category;
        __advance( i, d, iterator_category() );
    }

}//namespace device

#endif//_ITERATOR_TRAITS_HPP_INCLUDED_DFSAOISFALIU498AFKJH4KJAFKJBVIAHJFD84UHAFI

