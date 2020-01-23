// -*- C++ -*-
/* 
 * File:   static_matrix_stride_iterator.hpp
 * Author: feng
 *
 * Created on October 9, 2009, 4:43 PM
 */

#ifndef _STATIC_MATRIX_STRIDE_ITERATOR_HPP_INCLUDED_SFDOIN3498YH4LKUHJAFDS98V98Y
#define	_STATIC_MATRIX_STRIDE_ITERATOR_HPP_INCLUDED_SFDOIN3498YH4LKUHJAFDS98V98Y 

#include <cstddef>
#include <iterator>

namespace device 
{


template< typename Iterator_Type, std::size_t Step >
class static_matrix_stride_iterator
{
public:
    typedef typename std::iterator_traits<Iterator_Type>::value_type value_type;
    typedef typename std::iterator_traits<Iterator_Type>::reference reference;
    typedef typename std::iterator_traits<Iterator_Type>::difference_type difference_type;
    typedef typename std::iterator_traits<Iterator_Type>::pointer pointer;
    typedef std::random_access_iterator_tag iterator_category;
    typedef static_matrix_stride_iterator self_type;

    static_matrix_stride_iterator() : iterator_(0){ }

    static_matrix_stride_iterator(const self_type& s) : iterator_(s.iterator_){ }

    explicit static_matrix_stride_iterator(const Iterator_Type& it) : iterator_(it){ }

    self_type & operator++()
    {
        iterator_ += Step;
        return *this;
    }

    const self_type operator ++ ( int )
    {
        const self_type ans(*this);
        operator ++();
        return ans;
    }

    self_type & operator+=(const difference_type dt)
    {
        iterator_ += dt*Step;
        return *this;
    }

    friend const self_type operator + ( const self_type& lhs, const difference_type rhs )
    {
        self_type ans( lhs );
        ans += rhs;
        return ans;
    }

    friend const self_type operator + ( const difference_type lhs, const self_type& rhs )
    {
        return rhs + lhs;
    }

    self_type & operator--()
    {
        iterator_ -= Step;
        return *this;
    }

    const self_type operator -- ( int )
    {
        const self_type ans(*this);
        operator --();
        return ans;
    }

    self_type & operator-=(const difference_type dt)
    {
        iterator_ -= dt*Step;
        return *this;
    }

    friend const self_type operator - ( const self_type& lhs, const difference_type rhs )
    {
        self_type ans(lhs);
        ans -= rhs;
        return ans;
    }

    reference operator[](const difference_type dt)
    {
        return iterator_[dt * Step];
    }

    //const reference operator[](const difference_type dt) const
    value_type operator[](const difference_type dt) const
    {
        return iterator_[dt * Step];
    }

    reference operator*()
    {
        return *iterator_;
    }

    //const reference operator*() const
    value_type operator*() const
    {
        return *iterator_;
    }

    friend bool operator ==(const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ == rhs.iterator_;
    }

    friend bool operator !=(const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ != rhs.iterator_;
    }

    friend bool operator<(const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ < rhs.iterator_;
    }

    friend difference_type operator - (const self_type& lhs, const self_type& rhs)
    {
        return (lhs.iterator_ - rhs.iterator_) / Step;
    }

private:
    Iterator_Type iterator_;
}; //static_matrix_Stride_Iterator

}//namespace device 


#endif//_STATIC_MATRIX_STRIDE_ITERATOR_HPP_INCLUDED_SFDOIN3498YH4LKUHJAFDS98V98Y 

