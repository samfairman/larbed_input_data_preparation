#ifndef _REVERSE_ITERATOR_HPP_INCLUDED_SDFPOIN4HU9FDSLKJASDFIUH4O8HUSFADKJHSBAFD
#define _REVERSE_ITERATOR_HPP_INCLUDED_SDFPOIN4HU9FDSLKJASDFIUH4O8HUSFADKJHSBAFD

#include <device/iterator/iterator_traits.hpp>

namespace device
{

    template<typename Iterator>
    struct reverse_iterator: public iterator < typename iterator_traits<Iterator>::iterator_category,
                                               typename iterator_traits<Iterator>::value_type,
                                               typename iterator_traits<Iterator>::difference_type,
                                               typename iterator_traits<Iterator>::pointer,
                                               typename iterator_traits<Iterator>::reference 
                                             >
    {
        protected:
            Iterator the_iterator_;

        public:
            typedef iterator_traits<Iterator>                       traits_type;
            typedef Iterator                                        iterator_type;
            typedef typename traits_type::difference_type           difference_type;
            typedef typename traits_type::pointer                   pointer;
            typedef typename traits_type::reference                 reference;
            typedef reverse_iterator                                self_type;

            reverse_iterator() : the_iterator_() { }

            explicit reverse_iterator( iterator_type value ) : the_iterator_( value ) { }

            reverse_iterator( const self_type& value ) : the_iterator_( value.the_iterator_ ) { }

            template<typename Iter>
            reverse_iterator( const reverse_iterator<Iter>& value ) : the_iterator_( value.base() ) { }

            const iterator_type base() const
            {
                return the_iterator_;
            }

            
            reference operator*() const
            {
                Iterator tmp = the_iterator_;
                return *--tmp;
            }

            
            pointer operator->() const
            {
                return &( operator*() );
            }

            
            self_type& operator++()
            {
                --the_iterator_;
                return *this;
            }

            
            const self_type operator++( int )
            {
                self_type tmp = *this;
                --the_iterator_;
                return tmp;
            }

            
            self_type& operator--()
            {
                ++the_iterator_;
                return *this;
            }

            
            const self_type operator--( int )
            {
                self_type tmp = *this;
                ++the_iterator_;
                return tmp;
            }

            
            const self_type operator+( difference_type diff ) const
            {
                return self_type( the_iterator_ - diff );
            }

            
            self_type& operator+=( difference_type diff )
            {
                the_iterator_ -= diff;
                return *this;
            }

            
            const self_type operator-( difference_type diff ) const
            {
                return self_type( the_iterator_ + diff );
            }

            
            self_type& operator-=( difference_type diff )
            {
                the_iterator_ += diff;
                return *this;
            }

            
            reference operator[]( difference_type diff ) const
            {
                return *( *this + diff );
            }

    };//struct reverse_iterator 

    template<typename Iterator>
    inline bool operator==( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    {
        return lhs.base() == rhs.base();
    }

    template<typename Iterator>
    inline bool operator<( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    {
        return rhs.base() < lhs.base();
    }

    template<typename Iterator>
    inline bool operator!=( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    {
        return !( lhs == rhs );
    }

    template<typename Iterator>
    inline bool operator>( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    {
        return rhs < lhs;
    }

    template<typename Iterator>
    inline bool operator<=( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    {
        return !( rhs < lhs );
    }

    template<typename Iterator>
    inline bool operator>=( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    {
        return !( lhs < rhs );
    }

    template<typename Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    {
        return rhs.base() - lhs.base();
    }

    template<typename Iterator>
    inline reverse_iterator<Iterator>
    operator+( typename reverse_iterator<Iterator>::difference_type diff, const reverse_iterator<Iterator>& rhs )
    {
        return reverse_iterator<Iterator>( rhs.base() - diff );
    }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator==( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs )
    {
        return lhs.base() == rhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline bool operator<( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs )
    {
        return rhs.base() < lhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline bool operator!=( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs )
    {
        return !( lhs == rhs );
    }

    template<typename IteratorL, typename IteratorR>
    inline bool operator>( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs )
    {
        return rhs < lhs;
    }

    template<typename IteratorL, typename IteratorR>
    inline bool operator<=( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs )
    {
        return !( rhs < lhs );
    }

    template<typename IteratorL, typename IteratorR>
    inline bool operator>=( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs )
    {
        return !( lhs < rhs );
    }

    template<typename IteratorL, typename IteratorR>
    inline typename reverse_iterator<IteratorL>::difference_type
    operator-( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs )
    {
        return rhs.base() - lhs.base();
    }

}//namespace device

#endif//_REVERSE_ITERATOR_HPP_INCLUDED_SDFPOIN4HU9FDSLKJASDFIUH4O8HUSFADKJHSBAFD

