#ifndef _VECTOR_HPP_INCLUDED_SFDPOIJH398YASFDKJVKJBNA789Y3JKBASFDBV897Y43JKHFDU7
#define _VECTOR_HPP_INCLUDED_SFDPOIJH398YASFDKJVKJBNA789Y3JKBASFDBV897Y43JKHFDU7

#include <device/typedef.hpp>
#include <device/allocator.hpp>
#include <device/algorithm.hpp>
#include <device/functional.hpp>
#include <device/utility/assert.hpp>
#include <device/iterator/reverse_iterator.hpp>
#include <device/complex.hpp>
#include <device/math.hpp>

namespace device
{

template< typename Type, class Allocator = device::allocator<Type> >
class vector
{

public:
    typedef Type                                                        value_type;
    typedef vector                                                      self_type;
    typedef value_type*                                                 iterator;
    typedef const value_type*                                           const_iterator;
    
    typedef Allocator                                                   storage_type;
    typedef device::size_t                                              size_type;
    typedef device::ptrdiff_t                                           difference_type;

    typedef typename Allocator::pointer                                 pointer;
    typedef typename Allocator::const_pointer                           const_pointer;
    typedef device::reverse_iterator<iterator>                          reverse_iterator;
    typedef device::reverse_iterator<const_iterator>                    const_reverse_iterator;

public:
    
    explicit vector( const size_type s = 0 ) 
    : size_(s), data_(storage_type(s)) 
    {}
    
    explicit vector( const size_type s, const value_type& v ) 
    : size_(s), data_(storage_type(s)) 
    { 
        device::fill( begin(), end(), v ); 
    }
    
    ~vector() { }
    
    vector(const self_type& rhs)
    {
        operator=(rhs);
    }
    
    self_type & operator=(const self_type& rhs)
    {
        do_copy(rhs);
        return *this;
    }
    
    template<typename T, typename A>
    vector(const vector<T,A>& rhs)
    {
        operator=(rhs);
    }
    
    template<typename T, typename A>
    self_type & operator=(const vector<T,A>& rhs)
    {
        do_copy(rhs);
        return *this;
    }

    template< typename Itor >
    vector( Itor first, Itor last )
    :   size_(device::distance(first, last)), data_(storage_type(size_)) 
    {
        device::copy( first, last, begin() ); 
    }

public:
    self_type& operator = ( const value_type & v )
    {
        device::fill( begin(), end(), v );
        return *this;
    }

private:
    
    template<typename T, typename A>
    void do_copy(const vector<T,A>& rhs)
    {
        data_.assign(rhs.begin(), rhs.end());
        size_ = rhs.size();
    }

public:
    
    size_type size() const
    {
        return size_;
    }

public:
    self_type& resize( const size_type new_size )
    {
        if ( size() == new_size )
            return *this;

        //not of same size
        self_type other( new_size );
        swap( other );

        return *this;
    }

    self_type& resize( const size_type new_size, const value_type& v = value_type(0) )
    {
        if ( size() == new_size )
        {
            device::fill( begin(), end(), v );
            return *this;
        }

        //if not of same size
        self_type other( new_size, v );
        swap( other );
        return *this;
    }

public:
    
    iterator begin()
    {
        return data_.begin();
    }

    
    iterator end()
    {
        return data_.end();
    }

    
    const_iterator begin() const
    {
        return data_.begin();
    }

    
    const_iterator end() const
    {
        return data_.end();
    }

    
    const_iterator cbegin() const
    {
        return data_.begin();
    }

    
    const_iterator cend() const
    {
        return data_.end();
    }

public:
    
    reverse_iterator rbegin()
    {
        return reverse_iterator( end() );
    }

    
    reverse_iterator rend()
    {
        return reverse_iterator( begin() );
    }

    
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator( end() );
    }

    
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator( begin() );
    }

    
    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator( end() );
    }

    
    const_reverse_iterator crend() const
    {
        return const_reverse_iterator( begin() );
    }

public:
    const self_type operator-() const
    {
        self_type ans(*this);
        device::transform(ans.begin(), ans.end(), ans.begin(), device::negate<value_type>());
        return ans;
    }

    const self_type operator+() const
    {
        self_type ans(*this);
        return ans;
    }

public:
    self_type & operator += (const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::plus<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator + ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs.size() );
        device::transform( lhs.begin(), lhs.end(), ans.begin(), device::bind2nd( device::plus<value_type>(), rhs ) );
        return ans;
    }

    friend const self_type operator + ( const value_type& lhs, self_type& rhs )
    {
        return rhs + lhs;
    }

    self_type & operator += (const self_type& rhs)
    {
        assert( size() == rhs.size() );
        device::transform(begin(), end(), rhs.begin(), begin(), device::plus<value_type>());
        return *this;
    }

    friend const self_type operator + ( const self_type& lhs, const self_type& rhs )
    {
        assert( lhs.size() == rhs.size() );
        self_type ans( lhs.size() );
        device::transform( lhs.begin(), lhs.end(), rhs.begin(), ans.begin(), device::plus<value_type>() );
        return ans;
    }

    self_type & operator -= (const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::minus<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator - ( const self_type& lhs, const value_type& rhs )
    {
        return lhs + ( -rhs );
    }

    friend const self_type operator - ( const value_type& lhs, const self_type& rhs )
    {
        self_type ans( rhs.size() );
        device::transform( rhs.begin(), rhs.end(), ans.begin(), device::bind1st(device::minus<value_type>(), lhs) );
        return ans;
    }

    self_type & operator -=(const self_type& rhs)
    {
        assert( size() == rhs.size() );
        device::transform(begin(), end(), rhs.begin(), begin(), device::minus<value_type>());
        return *this;
    }

    friend const self_type operator - ( const self_type& lhs, const self_type& rhs )
    {
        assert( lhs.size() == rhs.size() );
        self_type ans( lhs.size() );
        device::transform( lhs.begin(), lhs.end(), rhs.begin(), ans.begin(), device::minus<value_type>() );
        return ans;
    }

    self_type & operator *=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::multiplies<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator * ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs.size() );
        device::transform( lhs.begin(), lhs.end(), ans.begin(), device::bind1st( device::multiplies<value_type>(), rhs ) );
        return ans;
    }

    friend const self_type operator * ( const value_type& lhs, const self_type& rhs )
    {
        return rhs * lhs;
    }

    self_type & operator /=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::divides<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator / ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs.size() );
        device::transform( lhs.begin(), lhs.end(), ans.begin(), device::bind2nd( device::divides<value_type>(), rhs ) );
        return ans;
    }

public:
    
    pointer data()
    {
        return data_.data();
    }

    
    const_pointer data() const 
    {
        return data_.data();
    }

public:
    template <typename Function>
    self_type const apply( const Function& f ) const 
    {
        self_type ans( size() );

        device::transform( begin(), end(), ans.begin(), f );

        return ans;
    }

public:
    void swap( self_type& other )
    {
        device::swap( size_, other.size_ );
        data_.swap( other.data_ );
    }

public:
    typename device::complex_value_type<value_type>::value_type
    norm() const;

private:

    size_type size_;
    storage_type data_;
};//vector

}//namespace device


#include <device/vector/norm.tcc>
#include <device/vector/matrix_vector_multiply.tcc>


#endif//_VECTOR_HPP_INCLUDED_SFDPOIJH398YASFDKJVKJBNA789Y3JKBASFDBV897Y43JKHFDU7

