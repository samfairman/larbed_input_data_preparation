#ifndef _DYNAMIC_MATRIX_STRIDE_ITERATOR_HPP_INCLUDED_3948HSALFKJN498HSAFLKJNV98Y
#define	_DYNAMIC_MATRIX_STRIDE_ITERATOR_HPP_INCLUDED_3948HSALFKJN498HSAFLKJNV98Y

#include <device/iterator.hpp>
#include <algorithm>

namespace device
{

/*
 *		Stride iterator is an iterator adaptor that takes a random access iterator range and provides
 *		a random access iterator on it goes through a stride (a sequence of iterator n steps apart),
 *		which is useful when striding a matrix column or diagonal.
 */
template< typename Iterator_Type >
class matrix_stride_iterator
{
public:
    typedef typename device::iterator_traits<Iterator_Type>::value_type 				value_type;
    typedef typename device::iterator_traits<Iterator_Type>::reference 				    reference;
    typedef typename device::iterator_traits<Iterator_Type>::difference_type 			difference_type;
    typedef typename device::iterator_traits<Iterator_Type>::pointer 					pointer;
    typedef typename device::iterator_traits<Iterator_Type>::iterator_category          iterator_category;
    typedef matrix_stride_iterator 			        								    self_type;

    __host__ __device__
    matrix_stride_iterator() : iterator_(0), step_(1) { }

    __host__ __device__
    matrix_stride_iterator(const Iterator_Type& it, const difference_type& dt) : iterator_(it), step_(dt) { }

    __host__ __device__
    matrix_stride_iterator(const self_type& other): iterator_(other.iterator_), step_(other.step_) {}

    __host__ __device__
    self_type& operator = (const self_type& other)
    {
        iterator_ = other.iterator_;
        step_ = other.step_;
        return *this;
    }

    __host__ __device__
    self_type& operator++()
    {
        iterator_ += step_;
        return *this;
    }

    __host__ __device__
	const self_type operator ++(int)
	{
		const self_type ans(*this);
		operator++();
		return ans;
	}

    __host__ __device__
    self_type& operator+=(const difference_type dt)
    {
        iterator_ += dt*step_;
        return *this;
    }

    __host__ __device__
	friend const self_type operator + ( const self_type& lhs, const difference_type rhs )
	{
		self_type ans(lhs);
		ans += rhs;
		return ans;
	}

    __host__ __device__
	friend const self_type operator + ( const difference_type lhs, const self_type& rhs )
	{
		return rhs + lhs;
	}

    self_type& operator--() 
    {
        iterator_ -= step_;
        return *this;
    }

    __host__ __device__
	const self_type operator -- ( int )
	{
		self_type ans(*this);
		operator--();
		return ans;
	}

    __host__ __device__
    self_type& operator-=(const difference_type dt)
    {
        iterator_ -= dt*step_;
        return *this;
    }

    __host__ __device__
	friend const self_type operator - ( const self_type& lhs, const difference_type rhs )
	{
		self_type ans(lhs);
		ans -= rhs;
		return ans;
	}

    __host__ __device__
    reference operator[](const difference_type dt)
    {
        return iterator_[dt * step_];
    }

    __host__ __device__
    const reference operator[](const difference_type dt) const
    {
        return iterator_[dt * step_];
    }

    __host__ __device__
    reference operator*()
    {
        return *iterator_;
    }

    __host__ __device__
    const reference operator*() const
    {
        return *iterator_;
    }

    __host__ __device__
    friend bool operator == (const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ == rhs.iterator_;
    }

    __host__ __device__
    friend bool operator != (const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ != rhs.iterator_;
    }

    __host__ __device__
    friend bool operator < (const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ < rhs.iterator_;
    }

    __host__ __device__
    friend bool operator <= (const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ <= rhs.iterator_;
    }

    __host__ __device__
    friend bool operator > (const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ > rhs.iterator_;
    }

    __host__ __device__
    friend bool operator >= (const self_type& lhs, const self_type& rhs)
    {
        return lhs.iterator_ >= rhs.iterator_;
    }

    __host__ __device__
    friend difference_type operator - (const self_type& lhs, const self_type& rhs)
    {
        return (lhs.iterator_ - rhs.iterator_) / lhs.step_;
    }

    __host__ __device__
	difference_type step() const
	{
		return step_;
	}

    __host__ __device__
	void reset_step( const difference_type step )
	{
		step_ = step;
	}

    __host__ __device__
	void step( const difference_type step )
	{
		step_ = step;
	}

private:
	// iterator stored
	Iterator_Type iterator_;
	// stride step
    difference_type step_;

}; //matrix_stride_iterator

}//namespace device

#endif//_DYNAMIC_MATRIX_STRIDE_ITERATOR_HPP_INCLUDED_3948HSALFKJN498HSAFLKJNV98Y

