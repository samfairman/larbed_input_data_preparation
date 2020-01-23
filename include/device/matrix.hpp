#ifndef _MATRIX_IMPL_HPP_INCLUDED_DSFOINASKJL4U83IASFKLDJBASIOUB4EIUYBFAKJBIUHFE
#define _MATRIX_IMPL_HPP_INCLUDED_DSFOINASKJL4U83IASFKLDJBASIOUB4EIUYBFAKJBIUHFE 

#include <device/typedef.hpp>
#include <device/allocator.hpp>
#include <device/matrix/matrix_stride_iterator.hpp>
#include <device/matrix/matrix_multiply_kernel.hpp>
#include <device/algorithm.hpp>
#include <device/numeric/accumulate.hpp>
#include <device/functional.hpp>
#include <device/utility/assert.hpp>
#include <device/math/inverse.hpp>
#include <device/matrix/static_matrix.hpp>
#include <device/utility/device_to_host.hpp>
#include <device/utility/host_to_device.hpp>

namespace device
{

template< typename Type, class Allocator = device::allocator<Type> >
class matrix
{

public:
    typedef Type                                                        value_type;
    typedef matrix                                                      self_type;
    typedef value_type*                                                 iterator;
    typedef const value_type*                                           const_iterator;
    
    typedef Allocator                                                   storage_type;
    typedef device::size_t                                              size_type;
    typedef device::ptrdiff_t                                           difference_type;

    typedef typename Allocator::pointer                                 pointer;
    typedef typename Allocator::const_pointer                           const_pointer;

    //stride iterators
    typedef matrix_stride_iterator<value_type*>                         stride_iterator;
    typedef matrix_stride_iterator<value_type*>                         row_type;
    typedef matrix_stride_iterator<const value_type*>                   const_row_type;
    typedef matrix_stride_iterator<value_type*>                         col_type;
    typedef matrix_stride_iterator<const value_type*>                   const_col_type;
    typedef matrix_stride_iterator<value_type*>                         diag_type;
    typedef matrix_stride_iterator<const value_type*>                   const_diag_type;
    typedef matrix_stride_iterator<value_type*>                         anti_diag_type;
    typedef matrix_stride_iterator<const value_type*>                   const_anti_diag_type;
    typedef device::reverse_iterator<iterator>                          reverse_iterator;
    typedef device::reverse_iterator<const_iterator>                    const_reverse_iterator;
    typedef device::reverse_iterator<stride_iterator>                   reverse_stride_iterator;
    typedef device::reverse_iterator<row_type>                          reverse_row_type;
    typedef device::reverse_iterator<const_row_type>                    const_reverse_row_type;
    typedef device::reverse_iterator<col_type>                          reverse_col_type;
    typedef device::reverse_iterator<const_col_type>                    const_reverse_col_type;
    typedef device::reverse_iterator<diag_type>                         reverse_upper_diag_type;
    typedef device::reverse_iterator<const_diag_type>                   const_reverse_upper_diag_type;
    typedef device::reverse_iterator<diag_type>                         reverse_lower_diag_type;
    typedef device::reverse_iterator<const_diag_type>                   const_reverse_lower_diag_type;
    typedef device::reverse_iterator<diag_type>                         reverse_diag_type;
    typedef device::reverse_iterator<const_diag_type>                   const_reverse_diag_type;
    typedef device::reverse_iterator<anti_diag_type>                    reverse_anti_diag_type;
    typedef device::reverse_iterator<const_anti_diag_type>              const_reverse_anti_diag_type;

public:
    
    explicit matrix( const size_type r, const size_type c ) 
    : row_(r), col_(c), data_(storage_type(r*c)) { }
    
    explicit matrix( const size_type r, const size_type c, const value_type& v ) 
    : row_(r), col_(c), data_(storage_type(r*c)) 
    { 
        device::fill( begin(), end(), v ); 
    }
    
    explicit matrix( const size_type n ) : row_(n), col_(n), data_(storage_type(n*n)) {}
    
    ~matrix() { }
    
    matrix(const self_type& rhs)
    {
        operator=(rhs);
    }
    
    self_type & operator=(const self_type& rhs)
    {
        do_copy(rhs);
        return *this;
    }
    
    template<typename T, typename A>
    matrix(const matrix<T,A>& rhs)
    {
        operator=(rhs);
    }
    
    template<typename T, typename A>
    self_type & operator=(const matrix<T,A>& rhs)
    {
        do_copy(rhs);
        return *this;
    }

public:
    self_type& operator = ( const value_type & v )
    {
        device::fill( begin(), end(), v );
        return *this;
    }

public:
    matrix( const self_type& other, const size_type r0, const size_type r1, const size_type c0, const size_type c1 )
        : row_( r1-r0 ), col_( c1-c0 ), data_( storage_type((r1-r0)*(c1-c0)) ) 
    {
        assert( r0 < r1 );
        assert( c0 < c1 );

        for ( size_type i = r0; i != r1; ++i )
            device::copy( other.row_begin(i)+c0, other.row_begin(i)+c1, row_begin(i-r0) );
    }

public:
    
    template< typename Itor >
    matrix( const size_type r, const size_type c, Itor first, Itor last )
    :   row_(r), col_(c), data_(storage_type(r*c)) 
    {
        device::copy( first, last, begin() ); 
    }

private:
    
    template<typename T, typename A>
    void do_copy(const matrix<T,A>& rhs)
    {
        row_ = rhs.row();
        col_ = rhs.col();
        data_.assign(rhs.begin(), rhs.end());
    }

public:
    
    size_type row() const
    {
        return row_;
    }

    
    size_type rows() const
    {
        return row();
    }

    
    size_type size1() const
    {
        return row();
    }

    
    size_type col() const
    {
        return col_;
    }

    size_type cols() const
    {
        return col();
    }

    size_type size2() const
    {
        return col();
    }

    size_type size() const
    {
        return data_.size();
    }

public:
    self_type& resize( const size_type new_row, const size_type new_col )
    {
        //if of same size
        if ( row_ * col_  == new_row * new_col ) 
        {
            row_ = new_row;
            col_ = new_col;
            return *this;
        }

        //not of same size
        self_type other( new_row, new_col );
        swap( other );

        return *this;
    }

    self_type& resize( const size_type new_row, const size_type new_col, const value_type& v )
    {
        //if of same size
        if ( row_ * col_ == new_row * new_col )
        {
            row_ = new_row;
            col_ = new_col;
            device::fill( begin(), end(), v );
            return *this;
        }

        //if not of same size
        self_type other( new_row, new_col, v );
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
    
    row_type row_begin(const size_type index = 0)
    {
        return row_type(begin() + index * col(), 1);
    }

    
    row_type row_end(const size_type index = 0)
    {
        return row_begin(index) + col();
    }

    
    const_row_type row_begin(const size_type index = 0) const
    {
        return const_row_type(begin() + index * col(), 1);
    }

    
    const_row_type row_end(const size_type index = 0) const
    {
        return row_begin(index) + col();
    }

    
    const_row_type row_cbegin(const size_type index = 0) const
    {
        return const_row_type(begin() + index * col(), 1);
    }

    
    const_row_type row_cend(const size_type index = 0) const
    {
        return row_begin(index) + col();
    }

public:
    
    reverse_row_type row_rbegin( const size_type index = 0 )
    {
        return reverse_row_type( row_end( index ) );
    }

    
    reverse_row_type row_rend( const size_type index = 0 )
    {
        return reverse_row_type( row_begin( index ) );
    }

    
    const_reverse_row_type row_rbegin( const size_type index = 0 ) const
    {
        return const_reverse_row_type( row_end( index ) );
    }

    
    const_reverse_row_type row_rend( const size_type index = 0 ) const
    {
        return const_reverse_row_type( row_begin( index ) );
    }

    
    const_reverse_row_type row_crbegin( const size_type index = 0 ) const
    {
        return const_reverse_row_type( row_end( index ) );
    }

    
    const_reverse_row_type row_crend( const size_type index = 0 ) const
    {
        return const_reverse_row_type( row_begin( index ) );
    }

public:
    
    col_type col_begin(const size_type index)
    {
        return col_type(begin() + index, col());
    }

    
    col_type col_end(const size_type index)
    {
        return col_begin(index) + row();
    }

    
    const_col_type col_begin(const size_type index) const
    {
        return const_col_type(begin() + index, col());
    }

    
    const_col_type col_end(const size_type index) const
    {
        return col_begin(index) + row();
    }

    
    const_col_type col_cbegin(const size_type index) const
    {
        return const_col_type(begin() + index, col());
    }

    
    const_col_type col_cend(const size_type index) const
    {
        return col_begin(index) + row();
    }

public:
    
    reverse_col_type col_rbegin( const size_type index = 0 )
    {
        return reverse_col_type( col_end( index ) );
    }

    
    reverse_col_type col_rend( const size_type index = 0 )
    {
        return reverse_col_type( col_begin( index ) );
    }

    
    const_reverse_col_type col_rbegin( const size_type index = 0 ) const
    {
        return const_reverse_col_type( col_end( index ) );
    }

    
    const_reverse_col_type col_rend( const size_type index = 0 ) const
    {
        return const_reverse_col_type( col_begin( index ) );
    }

    
    const_reverse_col_type col_crbegin( const size_type index = 0 ) const
    {
        return const_reverse_col_type( col_end( index ) );
    }

    
    const_reverse_col_type col_crend( const size_type index = 0 ) const
    {
        return const_reverse_col_type( col_begin( index ) );
    }

public:
    
    diag_type upper_diag_begin(const size_type index)
    {
        return diag_type(begin() + index, col() + 1);
    }

    
    diag_type upper_diag_end(const size_type index)
    {
        size_type depth = col() - index;
        if (row() < depth)
            depth = row();
        return upper_diag_begin(index) + depth;
    }

    
    const_diag_type upper_diag_begin(const size_type index) const
    {
        return const_diag_type(begin() + index, col() + 1);
    }

    
    const_diag_type upper_diag_end(const size_type index) const 
    {
        size_type depth = col() - index;
        if (row() < depth)
            depth = row();
        return upper_diag_begin(index) + depth;
    }

    
    const_diag_type upper_diag_cbegin(const size_type index) const
    {
        return const_diag_type(cbegin() + index, col() + 1);
    }

    
    const_diag_type upper_diag_cend(const size_type index) const 
    {
        size_type depth = col() - index;
        if (row() < depth)
            depth = row();
        return upper_diag_cbegin(index) + depth;
    }

public:
    
    reverse_upper_diag_type upper_diag_rbegin( const size_type index = 0 )
    {
        return reverse_upper_diag_type( upper_diag_end( index ) );
    }

    
    reverse_upper_diag_type upper_diag_rend( const size_type index = 0 )
    {
        return reverse_upper_diag_type( upper_diag_begin( index ) );
    }

    
    const_reverse_upper_diag_type upper_diag_rbegin( const size_type index = 0 ) const
    {
        return const_reverse_upper_diag_type( upper_diag_end( index ) );
    }

    
    const_reverse_upper_diag_type upper_diag_rend( const size_type index = 0 ) const
    {
        return const_reverse_upper_diag_type( upper_diag_begin( index ) );
    }

    
    const_reverse_upper_diag_type upper_diag_crbegin( const size_type index = 0 ) const
    {
        return const_reverse_upper_diag_type( upper_diag_end( index ) );
    }

    
    const_reverse_upper_diag_type upper_diag_crend( const size_type index = 0 ) const
    {
        return const_reverse_upper_diag_type( upper_diag_begin( index ) );
    }

public:
    
    diag_type lower_diag_begin(const size_type index)
    {
        return diag_type(begin() + index * col(), col() + 1);
    }

    
    diag_type lower_diag_end(const size_type index)
    {
        size_type depth = row() - index;
        if (col() < depth)
            depth = col();
        return lower_diag_begin(index) + depth;
    }

    
    const_diag_type lower_diag_begin(const size_type index) const
    {
        return const_diag_type(begin() + index * col(), col() + 1);
    }

    
    const_diag_type lower_diag_end(const size_type index) const
    {
        size_type depth = row() - index;
        if (col() < depth)
            depth = col();
        return lower_diag_begin(index) + depth;
    }

    
    const_diag_type lower_diag_cbegin(const size_type index) const
    {
        return const_diag_type(begin() + index * col(), col() + 1);
    }

    
    const_diag_type lower_diag_cend(const size_type index) const
    {
        size_type depth = row() - index;
        if (col() < depth)
            depth = col();
        return lower_diag_begin(index) + depth;
    }

public:
    
    reverse_lower_diag_type lower_diag_rbegin( const size_type index = 0 )
    {
        return reverse_lower_diag_type( lower_diag_end( index ) );
    }

    
    reverse_lower_diag_type lower_diag_rend( const size_type index = 0 )
    {
        return reverse_lower_diag_type( lower_diag_begin( index ) );
    }

    
    const_reverse_lower_diag_type lower_diag_rbegin( const size_type index = 0 ) const
    {
        return const_reverse_lower_diag_type( lower_diag_end( index ) );
    }

    
    const_reverse_lower_diag_type lower_diag_rend( const size_type index = 0 ) const
    {
        return const_reverse_lower_diag_type( lower_diag_begin( index ) );
    }

    
    const_reverse_lower_diag_type lower_diag_crbegin( const size_type index = 0 ) const
    {
        return const_reverse_lower_diag_type( lower_diag_end( index ) );
    }

    
    const_reverse_lower_diag_type lower_diag_crend( const size_type index = 0 ) const
    {
        return const_reverse_lower_diag_type( lower_diag_begin( index ) );
    }

public:
    
    diag_type diag_begin( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_diag_begin( index );
        return lower_diag_begin( -index );
    }
    
    
    diag_type diag_end( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_diag_end( index );
        return lower_diag_end( -index );
    }

    
    const_diag_type diag_begin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_begin( index );
        return lower_diag_begin( -index );
    }
    
    
    const_diag_type diag_end( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_end( index );
        return lower_diag_end( -index );
    }

    
    const_diag_type diag_cbegin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_cbegin( index );
        return lower_diag_cbegin( -index );
    }
    
    
    const_diag_type diag_cend( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_cend( index );
        return lower_diag_cend( -index );
    }

public:
    
    reverse_diag_type diag_rbegin( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_diag_rbegin( index );
        return lower_diag_rbegin( -index );
    }
    
    
    reverse_diag_type diag_rend( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_diag_rend( index );
        return lower_diag_rend( -index );
    }

    
    const_reverse_diag_type diag_rbegin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_rbegin( index );
        return lower_diag_rbegin( -index );
    }
    
    
    const_reverse_diag_type diag_rend( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_rend( index );
        return lower_diag_rend( -index );
    }

    
    const_reverse_diag_type diag_crbegin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_crbegin( index );
        return lower_diag_crbegin( -index );
    }
    
    
    const_reverse_diag_type diag_crend( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_diag_crend( index );
        return lower_diag_crend( -index );
    }

public:
    
    anti_diag_type upper_anti_diag_begin( const size_type index = 0 ) 
    {
        return anti_diag_type( begin() + col() - index - 1, col() - 1);
    }

    
    anti_diag_type upper_anti_diag_end( const size_type index = 0 ) 
    {
        size_type depth = col() - index;
        if ( row() < depth )
            depth = row();
        return upper_anti_diag_begin(index) + depth;
    }

    
    const_anti_diag_type upper_anti_diag_begin( const size_type index = 0 )  const
    {
        return const_anti_diag_type( begin() + col() - index - 1, col() - 1);
    }

    
    const_anti_diag_type upper_anti_diag_end( const size_type index = 0 )  const
    {
        size_type depth = col() - index;
        if ( row() < depth )
            depth = row();
        return upper_anti_diag_begin(index) + depth;
    }

    
    const_anti_diag_type upper_anti_diag_cbegin( const size_type index = 0 )  const
    {
        return upper_anti_diag_begin(index);
    }

    
    const_anti_diag_type upper_anti_diag_cend( const size_type index = 0 )  const
    {
        return upper_anti_diag_end(index);
    }

public:
    
    reverse_anti_diag_type upper_anti_diag_rbegin( const size_type index = 0 ) 
    {
        return reverse_anti_diag_type(upper_anti_diag_end(index));
    }

    
    reverse_anti_diag_type upper_anti_diag_rend( const size_type index = 0 ) 
    {
        return reverse_anti_diag_type(upper_anti_diag_begin(index));
    }

    
    const_reverse_anti_diag_type upper_anti_diag_rbegin( const size_type index = 0 )  const
    {
        return const_reverse_anti_diag_type(upper_anti_diag_end(index));
    }

    
    const_reverse_anti_diag_type upper_anti_diag_rend( const size_type index = 0 )  const
    {
        return const_reverse_anti_diag_type(upper_anti_diag_begin(index));
    }

    
    const_reverse_anti_diag_type upper_anti_diag_crbegin( const size_type index = 0 )  const
    {
        return upper_anti_diag_rbegin(index);
    }

    
    const_reverse_anti_diag_type upper_anti_diag_crend( const size_type index = 0 )  const
    {
        return upper_anti_diag_rend(index);
    }

public:
    
    anti_diag_type lower_anti_diag_begin( const size_type index = 0 ) 
    {
        return anti_diag_type( begin()+(col()*(index+1))-1, col() - 1 );
    }

    
    anti_diag_type lower_anti_diag_end( const size_type index = 0 ) 
    {
        size_type depth = row() - index;
        if ( col() < depth )
            depth = col();
        return lower_anti_diag_begin(index) + depth;
    }

    
    const_anti_diag_type lower_anti_diag_begin( const size_type index = 0 )  const
    {
        return const_anti_diag_type( begin()+(col()*(index+1))-1, col() - 1 );
    }

    
    const_anti_diag_type lower_anti_diag_end( const size_type index = 0 )  const
    {
        size_type depth = row() - index;
        if ( col() < depth )
            depth = col();
        return lower_anti_diag_begin(index) + depth;
    }

    
    const_anti_diag_type lower_anti_diag_cbegin( const size_type index = 0 )  const
    {
        return lower_anti_diag_begin(index);
    }

    
    const_anti_diag_type lower_anti_diag_cend( const size_type index = 0 )  const
    {
        return lower_anti_diag_end(index);
    }

public:
    
    reverse_anti_diag_type lower_anti_diag_rbegin( const size_type index = 0 ) 
    {
        return reverse_anti_diag_type(lower_anti_diag_end(index));
    }

    
    reverse_anti_diag_type lower_anti_diag_rend( const size_type index = 0 ) 
    {
        return reverse_anti_diag_type(lower_anti_diag_begin(index));
    }

    
    const_reverse_anti_diag_type lower_anti_diag_rbegin( const size_type index = 0 )  const
    {
        return const_reverse_anti_diag_type(lower_anti_diag_end(index));
    }

    
    const_reverse_anti_diag_type lower_anti_diag_rend( const size_type index = 0 )  const
    {
        return const_reverse_anti_diag_type(lower_anti_diag_begin(index));
    }

    
    const_reverse_anti_diag_type lower_anti_diag_crbegin( const size_type index = 0 )  const
    {
        return lower_anti_diag_rbegin(index);
    }

    
    const_reverse_anti_diag_type lower_anti_diag_crend( const size_type index = 0 )  const
    {
        return lower_anti_diag_rend(index);
    }

public:
    
    anti_diag_type anti_diag_begin( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_anti_diag_begin( index );
        return lower_anti_diag_begin( -index );
    }
    
    
    anti_diag_type anti_diag_end( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_anti_diag_end( index );
        return lower_anti_diag_end( -index );
    }

    
    const_anti_diag_type anti_diag_begin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_begin( index );
        return lower_anti_diag_begin( -index );
    }
    
    
    const_anti_diag_type anti_diag_end( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_end( index );
        return lower_anti_diag_end( -index );
    }

    
    const_anti_diag_type anti_diag_cbegin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_cbegin( index );
        return lower_anti_diag_cbegin( -index );
    }
    
    
    const_anti_diag_type anti_diag_cend( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_cend( index );
        return lower_anti_diag_cend( -index );
    }

public:
    
    reverse_anti_diag_type anti_diag_rbegin( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_anti_diag_rbegin( index );
        return lower_anti_diag_rbegin( -index );
    }
    
    
    reverse_anti_diag_type anti_diag_rend( const difference_type index = 0 )
    {
        if ( index > 0 ) return upper_anti_diag_rend( index );
        return lower_anti_diag_rend( -index );
    }

    
    const_reverse_anti_diag_type anti_diag_rbegin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_rbegin( index );
        return lower_anti_diag_rbegin( -index );
    }
    
    
    const_reverse_anti_diag_type anti_diag_rend( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_rend( index );
        return lower_anti_diag_rend( -index );
    }

    
    const_reverse_anti_diag_type anti_diag_crbegin( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_crbegin( index );
        return lower_anti_diag_crbegin( -index );
    }
    
    
    const_reverse_anti_diag_type anti_diag_crend( const difference_type index = 0 ) const
    {
        if ( index > 0 ) return upper_anti_diag_crend( index );
        return lower_anti_diag_crend( -index );
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
    self_type & operator +=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::plus<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator + ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs.row(), lhs.col() );
        device::transform(lhs.begin(), lhs.end(), ans.begin(), device::bind2nd(device::plus<value_type>(), rhs));
        return ans;
    }

    friend const self_type operator + ( const value_type& lhs, const self_type& rhs )
    {
        return rhs + lhs;
    }

    self_type & operator +=(const self_type& rhs)
    {
        device::transform(begin(), end(), rhs.begin(), begin(), device::plus<value_type>());
        return *this;
    }

    friend const self_type operator + ( const self_type& lhs, const self_type& rhs )
    {
        assert( lhs.row() == rhs.row() );
        assert( lhs.col() == rhs.col() );
        self_type ans( lhs.row(), lhs.col() );
        device::transform( lhs.begin(), lhs.end(), rhs.begin(), ans.begin(), device::plus<value_type>() );
        return ans;
    }

    self_type& operator -=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::minus<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator - ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs.row(), lhs.col() );
        device::transform( lhs.begin(), lhs.end(), ans.begin(), device::bind2nd(device::minus<value_type>(), rhs) );
        return ans;
    }

    friend const self_type operator - ( const value_type& lhs, const self_type& rhs )
    {
        self_type ans( rhs.row(), rhs.col() );
        device::transform( rhs.begin(), rhs.end(), ans.begin(), device::bind1st(device::minus<value_type>(), lhs) );
        return ans;
    }

    self_type& operator -=(const self_type& rhs)
    {
        device::transform(begin(), end(), rhs.begin(), begin(), device::minus<value_type>());
        return *this;
    }

    friend const self_type operator - ( const self_type& lhs, const self_type& rhs )
    {
        assert( lhs.row() == rhs.row() );
        assert( lhs.col() == rhs.col() );
        self_type ans( lhs.row(), lhs.col() );
        device::transform( lhs.begin(), lhs.end(), rhs.begin(), ans.begin(), device::minus<value_type>() );
        return ans;
    }

    self_type& operator *=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::multiplies<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator * ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs.row(), lhs.col() ); 
        device::transform(lhs.begin(), lhs.end(), ans.begin(), device::bind2nd(device::multiplies<value_type>(), rhs));
        return ans;
    }

    friend const self_type operator * ( const value_type& lhs, const self_type& rhs )
    {
        return rhs * lhs;
    }

    self_type& operator *= ( const self_type& other )
    {
        assert( col() == other.row() );
        self_type ans( row(), other.col() );
        matrix_multiply( ans.begin(), cbegin(), other.cbegin(), row(), col(), other.col() );
        swap( ans );
        return *this;
    }

    friend const self_type operator * ( const self_type& lhs, const self_type& rhs )
    {
        assert( lhs.col() == rhs.row() );
        self_type ans( lhs.row(), rhs.col() );
        matrix_multiply( ans.begin(), lhs.begin(), rhs.begin(), lhs.row(), lhs.col(), rhs.col() );
        return ans;
    }

    self_type& operator /=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::divides<value_type>(), rhs));
        return *this;
    }

    friend const self_type operator / ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs.row(), lhs.col() );
        device::transform(lhs.begin(), lhs.end(), ans.begin(), device::bind2nd(device::divides<value_type>(), rhs));
        return ans;
    }

    self_type& operator /=(const self_type& rhs)
    {
        (*this) *= rhs.inverse();
        return *this;
    }

    friend const self_type operator / ( const self_type& lhs, const self_type& rhs )
    {
        return lhs * rhs.inverse();
    }

public:
   const self_type inverse() const 
   {
       assert( row() == col() );
       assert( !!size() );

       const size_type s = size();

        if ( row() == 1 ) 
            return apply( device::inverse<value_type>() );
#if 0

        if ( row()  == 1 )
            return static_matrix_1_inverse();

        if ( row()  == 2 )
            return static_matrix_2_inverse();

        if ( row()  == 3 )
            return static_matrix_3_inverse();

        if ( row()  == 4 )
            return static_matrix_4_inverse();

        if ( row()  == 5 )
            return static_matrix_5_inverse();

        if ( row()  == 6 )
            return static_matrix_6_inverse();

        if ( row()  == 7 )
            return static_matrix_7_inverse();

        if ( row()  == 8 )
            return static_matrix_8_inverse();

        if ( row()  == 9 )
            return static_matrix_9_inverse();

        if ( row()  == 10 )
            return static_matrix_10_inverse();

        if ( row()  == 11 )
            return static_matrix_11_inverse();

        if ( row()  == 12 )
            return static_matrix_12_inverse();

        if ( row()  == 13 )
            return static_matrix_13_inverse();

        if ( row()  == 14 )
            return static_matrix_14_inverse();

        if ( row()  == 15 )
            return static_matrix_15_inverse();

        if ( row()  == 16 )
            return static_matrix_16_inverse();

        if ( row()  == 17 )
            return static_matrix_17_inverse();

        if ( row()  == 18 )
            return static_matrix_18_inverse();

        if ( row()  == 19 )
            return static_matrix_19_inverse();

        if ( row()  == 20 )
            return static_matrix_20_inverse();

        if ( row()  == 21 )
            return static_matrix_21_inverse();

        if ( row()  == 22 )
            return static_matrix_22_inverse();

        if ( row()  == 23 )
            return static_matrix_23_inverse();

        if ( row()  == 24 )
            return static_matrix_24_inverse();

        if ( row()  == 25 )
            return static_matrix_25_inverse();

        if ( row()  == 26 )
            return static_matrix_26_inverse();

        if ( row()  == 27 )
            return static_matrix_27_inverse();

        if ( row()  == 28 )
            return static_matrix_28_inverse();

        if ( row()  == 29 )
            return static_matrix_29_inverse();

        if ( row()  == 30 )
            return static_matrix_30_inverse();

        if ( row()  == 31 )
            return static_matrix_31_inverse();

        if ( row()  == 32 )
            return static_matrix_32_inverse();

        if ( row()  == 33 )
            return static_matrix_33_inverse();

        if ( row()  == 34 )
            return static_matrix_34_inverse();

        if ( row()  == 35 )
            return static_matrix_35_inverse();

        if ( row()  == 36 )
            return static_matrix_36_inverse();

        if ( row()  == 37 )
            return static_matrix_37_inverse();

        if ( row()  == 38 )
            return static_matrix_38_inverse();

        if ( row()  == 39 )
            return static_matrix_39_inverse();

        if ( row()  == 40 )
            return static_matrix_40_inverse();

        if ( row()  == 41 )
            return static_matrix_41_inverse();

        if ( row()  == 42 )
            return static_matrix_42_inverse();

        if ( row()  == 43 )
            return static_matrix_43_inverse();

        if ( row()  == 44 )
            return static_matrix_44_inverse();

        if ( row()  == 45 )
            return static_matrix_45_inverse();

        if ( row()  == 46 )
            return static_matrix_46_inverse();

        if ( row()  == 47 )
            return static_matrix_47_inverse();

        if ( row()  == 48 )
            return static_matrix_48_inverse();

        if ( row()  == 49 )
            return static_matrix_49_inverse();

        if ( row()  == 50 )
            return static_matrix_50_inverse();

        if ( row()  == 51 )
            return static_matrix_51_inverse();

        if ( row()  == 52 )
            return static_matrix_52_inverse();

        if ( row()  == 53 )
            return static_matrix_53_inverse();

        if ( row()  == 54 )
            return static_matrix_54_inverse();

        if ( row()  == 55 )
            return static_matrix_55_inverse();

        if ( row()  == 56 )
            return static_matrix_56_inverse();

        if ( row()  == 57 )
            return static_matrix_57_inverse();

        if ( row()  == 58 )
            return static_matrix_58_inverse();

        if ( row()  == 59 )
            return static_matrix_59_inverse();

        if ( row()  == 60 )
            return static_matrix_60_inverse();

        if ( row()  == 61 )
            return static_matrix_61_inverse();

        if ( row()  == 62 )
            return static_matrix_62_inverse();

        if ( row()  == 63 )
            return static_matrix_63_inverse();

        if ( row()  == 64 )
            return static_matrix_64_inverse();

        if ( row()  == 65 )
            return static_matrix_65_inverse();

        if ( row()  == 66 )
            return static_matrix_66_inverse();

        if ( row()  == 67 )
            return static_matrix_67_inverse();

        if ( row()  == 68 )
            return static_matrix_68_inverse();

        if ( row()  == 69 )
            return static_matrix_69_inverse();

        if ( row()  == 70 )
            return static_matrix_70_inverse();

        if ( row()  == 71 )
            return static_matrix_71_inverse();

        if ( row()  == 72 )
            return static_matrix_72_inverse();

        if ( row()  == 73 )
            return static_matrix_73_inverse();

        if ( row()  == 74 )
            return static_matrix_74_inverse();

        if ( row()  == 75 )
            return static_matrix_75_inverse();

        if ( row()  == 76 )
            return static_matrix_76_inverse();

        if ( row()  == 77 )
            return static_matrix_77_inverse();

        if ( row()  == 78 )
            return static_matrix_78_inverse();

        if ( row()  == 79 )
            return static_matrix_79_inverse();

        if ( row()  == 80 )
            return static_matrix_80_inverse();

        if ( row()  == 81 )
            return static_matrix_81_inverse();

        if ( row()  == 82 )
            return static_matrix_82_inverse();

        if ( row()  == 83 )
            return static_matrix_83_inverse();

        if ( row()  == 84 )
            return static_matrix_84_inverse();

        if ( row()  == 85 )
            return static_matrix_85_inverse();

        if ( row()  == 86 )
            return static_matrix_86_inverse();

        if ( row()  == 87 )
            return static_matrix_87_inverse();

        if ( row()  == 88 )
            return static_matrix_88_inverse();

        if ( row()  == 89 )
            return static_matrix_89_inverse();

        if ( row()  == 90 )
            return static_matrix_90_inverse();

        if ( row()  == 91 )
            return static_matrix_91_inverse();

        if ( row()  == 92 )
            return static_matrix_92_inverse();

        if ( row()  == 93 )
            return static_matrix_93_inverse();

        if ( row()  == 94 )
            return static_matrix_94_inverse();

        if ( row()  == 95 )
            return static_matrix_95_inverse();

        if ( row()  == 96 )
            return static_matrix_96_inverse();

        if ( row()  == 97 )
            return static_matrix_97_inverse();

        if ( row()  == 98 )
            return static_matrix_98_inverse();

        if ( row()  == 99 )
            return static_matrix_99_inverse();

        if ( row()  == 100 )
            return static_matrix_100_inverse();

        if ( row()  == 101 )
            return static_matrix_101_inverse();

        if ( row()  == 102 )
            return static_matrix_102_inverse();

        if ( row()  == 103 )
            return static_matrix_103_inverse();

        if ( row()  == 104 )
            return static_matrix_104_inverse();

        if ( row()  == 105 )
            return static_matrix_105_inverse();

        if ( row()  == 106 )
            return static_matrix_106_inverse();

        if ( row()  == 107 )
            return static_matrix_107_inverse();

        if ( row()  == 108 )
            return static_matrix_108_inverse();

        if ( row()  == 109 )
            return static_matrix_109_inverse();

        if ( row()  == 110 )
            return static_matrix_110_inverse();

        if ( row()  == 111 )
            return static_matrix_111_inverse();

        if ( row()  == 112 )
            return static_matrix_112_inverse();

        if ( row()  == 113 )
            return static_matrix_113_inverse();

        if ( row()  == 114 )
            return static_matrix_114_inverse();

        if ( row()  == 115 )
            return static_matrix_115_inverse();

        if ( row()  == 116 )
            return static_matrix_116_inverse();

        if ( row()  == 117 )
            return static_matrix_117_inverse();

        if ( row()  == 118 )
            return static_matrix_118_inverse();

        if ( row()  == 119 )
            return static_matrix_119_inverse();

        if ( row()  == 120 )
            return static_matrix_120_inverse();

        if ( row()  == 121 )
            return static_matrix_121_inverse();

        if ( row()  == 122 )
            return static_matrix_122_inverse();

        if ( row()  == 123 )
            return static_matrix_123_inverse();

        if ( row()  == 124 )
            return static_matrix_124_inverse();

        if ( row()  == 125 )
            return static_matrix_125_inverse();

        if ( row()  == 126 )
            return static_matrix_126_inverse();

        if ( row()  == 127 )
            return static_matrix_127_inverse();

        if ( row()  == 128 )
            return static_matrix_128_inverse();
#endif

        #if 0
        #endif

        if ( row() & 1 ) return direct_inverse();

       return strassen_inverse();
   }

private:
#if 0
   const self_type static_matrix_1_inverse() const
   {
        device::static_matrix<value_type, 1, 1> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 1, 1>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_2_inverse() const
   {
        device::static_matrix<value_type, 2, 2> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 2, 2>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_3_inverse() const
   {
        device::static_matrix<value_type, 3, 3> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 3, 3>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_4_inverse() const
   {
        device::static_matrix<value_type, 4, 4> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 4, 4>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_5_inverse() const
   {
        device::static_matrix<value_type, 5, 5> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 5, 5>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_6_inverse() const
   {
        device::static_matrix<value_type, 6, 6> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 6, 6>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_7_inverse() const
   {
        device::static_matrix<value_type, 7, 7> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 7, 7>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_8_inverse() const
   {
        device::static_matrix<value_type, 8, 8> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 8, 8>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_9_inverse() const
   {
        device::static_matrix<value_type, 9, 9> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 9, 9>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_10_inverse() const
   {
        device::static_matrix<value_type, 10, 10> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 10, 10>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_11_inverse() const
   {
        device::static_matrix<value_type, 11, 11> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 11, 11>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_12_inverse() const
   {
        device::static_matrix<value_type, 12, 12> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 12, 12>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_13_inverse() const
   {
        device::static_matrix<value_type, 13, 13> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 13, 13>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_14_inverse() const
   {
        device::static_matrix<value_type, 14, 14> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 14, 14>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_15_inverse() const
   {
        device::static_matrix<value_type, 15, 15> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 15, 15>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_16_inverse() const
   {
        device::static_matrix<value_type, 16, 16> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 16, 16>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_17_inverse() const
   {
        device::static_matrix<value_type, 17, 17> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 17, 17>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_18_inverse() const
   {
        device::static_matrix<value_type, 18, 18> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 18, 18>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_19_inverse() const
   {
        device::static_matrix<value_type, 19, 19> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 19, 19>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_20_inverse() const
   {
        device::static_matrix<value_type, 20, 20> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 20, 20>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_21_inverse() const
   {
        device::static_matrix<value_type, 21, 21> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 21, 21>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_22_inverse() const
   {
        device::static_matrix<value_type, 22, 22> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 22, 22>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_23_inverse() const
   {
        device::static_matrix<value_type, 23, 23> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 23, 23>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_24_inverse() const
   {
        device::static_matrix<value_type, 24, 24> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 24, 24>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_25_inverse() const
   {
        device::static_matrix<value_type, 25, 25> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 25, 25>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_26_inverse() const
   {
        device::static_matrix<value_type, 26, 26> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 26, 26>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_27_inverse() const
   {
        device::static_matrix<value_type, 27, 27> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 27, 27>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_28_inverse() const
   {
        device::static_matrix<value_type, 28, 28> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 28, 28>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_29_inverse() const
   {
        device::static_matrix<value_type, 29, 29> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 29, 29>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_30_inverse() const
   {
        device::static_matrix<value_type, 30, 30> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 30, 30>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_31_inverse() const
   {
        device::static_matrix<value_type, 31, 31> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 31, 31>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_32_inverse() const
   {
        device::static_matrix<value_type, 32, 32> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 32, 32>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_33_inverse() const
   {
        device::static_matrix<value_type, 33, 33> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 33, 33>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_34_inverse() const
   {
        device::static_matrix<value_type, 34, 34> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 34, 34>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_35_inverse() const
   {
        device::static_matrix<value_type, 35, 35> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 35, 35>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_36_inverse() const
   {
        device::static_matrix<value_type, 36, 36> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 36, 36>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_37_inverse() const
   {
        device::static_matrix<value_type, 37, 37> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 37, 37>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_38_inverse() const
   {
        device::static_matrix<value_type, 38, 38> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 38, 38>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_39_inverse() const
   {
        device::static_matrix<value_type, 39, 39> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 39, 39>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_40_inverse() const
   {
        device::static_matrix<value_type, 40, 40> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 40, 40>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_41_inverse() const
   {
        device::static_matrix<value_type, 41, 41> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 41, 41>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_42_inverse() const
   {
        device::static_matrix<value_type, 42, 42> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 42, 42>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_43_inverse() const
   {
        device::static_matrix<value_type, 43, 43> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 43, 43>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_44_inverse() const
   {
        device::static_matrix<value_type, 44, 44> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 44, 44>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_45_inverse() const
   {
        device::static_matrix<value_type, 45, 45> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 45, 45>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_46_inverse() const
   {
        device::static_matrix<value_type, 46, 46> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 46, 46>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_47_inverse() const
   {
        device::static_matrix<value_type, 47, 47> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 47, 47>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_48_inverse() const
   {
        device::static_matrix<value_type, 48, 48> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 48, 48>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_49_inverse() const
   {
        device::static_matrix<value_type, 49, 49> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 49, 49>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_50_inverse() const
   {
        device::static_matrix<value_type, 50, 50> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 50, 50>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_51_inverse() const
   {
        device::static_matrix<value_type, 51, 51> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 51, 51>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_52_inverse() const
   {
        device::static_matrix<value_type, 52, 52> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 52, 52>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_53_inverse() const
   {
        device::static_matrix<value_type, 53, 53> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 53, 53>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_54_inverse() const
   {
        device::static_matrix<value_type, 54, 54> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 54, 54>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_55_inverse() const
   {
        device::static_matrix<value_type, 55, 55> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 55, 55>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_56_inverse() const
   {
        device::static_matrix<value_type, 56, 56> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 56, 56>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_57_inverse() const
   {
        device::static_matrix<value_type, 57, 57> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 57, 57>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_58_inverse() const
   {
        device::static_matrix<value_type, 58, 58> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 58, 58>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_59_inverse() const
   {
        device::static_matrix<value_type, 59, 59> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 59, 59>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_60_inverse() const
   {
        device::static_matrix<value_type, 60, 60> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 60, 60>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_61_inverse() const
   {
        device::static_matrix<value_type, 61, 61> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 61, 61>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_62_inverse() const
   {
        device::static_matrix<value_type, 62, 62> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 62, 62>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_63_inverse() const
   {
        device::static_matrix<value_type, 63, 63> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 63, 63>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_64_inverse() const
   {
        device::static_matrix<value_type, 64, 64> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 64, 64>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_65_inverse() const
   {
        device::static_matrix<value_type, 65, 65> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 65, 65>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_66_inverse() const
   {
        device::static_matrix<value_type, 66, 66> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 66, 66>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   cnst device::static_matrix<value_type, 26, 26>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_27_inverse() const
   {
        device::static_matrix<value_type, 27, 27> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 27, 27>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_28_inverse() const
   {
        device::static_matrix<value_type, 28, 28> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 28, 28>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_29_inverse() const
   {
        devicow(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_70_inverse() const
   {
        device::static_matrix<value_type, 70, 70> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 70, 70>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_71_inverse() const
   {
        device::static_matrix<value_type, 71, 71> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 71, 71>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_72_inverse() const
   {
        device::static_matrix<value_type, 72, 72> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 72, 72>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_73_inverse() const
   {
        device::static_matrix<value_type, 73, 73> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 73, 73>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_74_inverse() const
   {
        device::static_matrix<value_type, 74, 74> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 74, 74>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_75_inverse() const
   {
        device::static_matrix<value_type, 75, 75> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 75, 75>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_76_inverse() const
   {
        device::static_matrix<value_type, 76, 76> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 76, 76>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_77_inverse() const
   {
        device::static_matrix<value_type, 77, 77> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 77, 77>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_78_inverse() const
   {
        device::static_matrix<value_type, 78, 78> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 78, 78>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_79_inverse() const
   {
        device::static_matrix<value_type, 79, 79> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 79, 79>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_80_inverse() const
   {
        device::static_matrix<value_type, 80, 80> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 80, 80>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_81_inverse() const
   {
        device::static_matrix<value_type, 81, 81> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 81, 81>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_82_inverse() const
   {
        device::static_matrix<value_type, 82, 82> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 82, 82>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_83_inverse() const
   {
        device::static_matrix<value_type, 83, 83> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 83, 83>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_84_inverse() const
   {
        device::static_matrix<value_type, 84, 84> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 84, 84>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_85_inverse() const
   {
        device::static_matrix<value_type, 85, 85> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 85, 85>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_86_inverse() const
   {
        device::static_matrix<value_type, 86, 86> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 86, 86>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_87_inverse() const
   {
        device::static_matrix<value_type, 87, 87> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 87, 87>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_88_inverse() const
   {
        device::static_matrix<value_type, 88, 88> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 88, 88>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_89_inverse() const
   {
        device::static_matrix<value_type, 89, 89> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 89, 89>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_90_inverse() const
   {
        device::static_matrix<value_type, 90, 90> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 90, 90>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_91_inverse() const
   {
        device::static_matrix<value_type, 91, 91> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 91, 91>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_92_inverse() const
   {
        device::static_matrix<value_type, 92, 92> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 92, 92>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_93_inverse() const
   {
        device::static_matrix<value_type, 93, 93> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 93, 93>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_94_inverse() const
   {
        device::static_matrix<value_type, 94, 94> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 94, 94>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_95_inverse() const
   {
        device::static_matrix<value_type, 95, 95> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 95, 95>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_96_inverse() const
   {
        device::static_matrix<value_type, 96, 96> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 96, 96>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_97_inverse() const
   {
        device::static_matrix<value_type, 97, 97> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 97, 97>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_98_inverse() const
   {
        device::static_matrix<value_type, 98, 98> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 98, 98>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_99_inverse() const
   {
        device::static_matrix<value_type, 99, 99> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 99, 99>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_100_inverse() const
   {
        device::static_matrix<value_type, 100, 100> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 100, 100>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_101_inverse() const
   {
        device::static_matrix<value_type, 101, 101> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 101, 101>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_102_inverse() const
   {
        device::static_matrix<value_type, 102, 102> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 102, 102>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_103_inverse() const
   {
        device::static_matrix<value_type, 103, 103> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 103, 103>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_104_inverse() const
   {
        device::static_matrix<value_type, 104, 104> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 104, 104>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_105_inverse() const
   {
        device::static_matrix<value_type, 105, 105> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 105, 105>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_106_inverse() const
   {
        device::static_matrix<value_type, 106, 106> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 106, 106>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_107_inverse() const
   {
        device::static_matrix<value_type, 107, 107> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 107, 107>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_108_inverse() const
   {
        device::static_matrix<value_type, 108, 108> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 108, 108>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_109_inverse() const
   {
        device::static_matrix<value_type, 109, 109> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 109, 109>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_110_inverse() const
   {
        device::static_matrix<value_type, 110, 110> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 110, 110>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_111_inverse() const
   {
        device::static_matrix<value_type, 111, 111> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 111, 111>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_112_inverse() const
   {
        device::static_matrix<value_type, 112, 112> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 112, 112>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_113_inverse() const
   {
        device::static_matrix<value_type, 113, 113> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 113, 113>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_114_inverse() const
   {
        device::static_matrix<value_type, 114, 114> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 114, 114>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_115_inverse() const
   {
        device::static_matrix<value_type, 115, 115> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 115, 115>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_116_inverse() const
   {
        device::static_matrix<value_type, 116, 116> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 116, 116>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_117_inverse() const
   {
        device::static_matrix<value_type, 117, 117> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 117, 117>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_118_inverse() const
   {
        device::static_matrix<value_type, 118, 118> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 118, 118>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_119_inverse() const
   {
        device::static_matrix<value_type, 119, 119> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 119, 119>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_120_inverse() const
   {
        device::static_matrix<value_type, 120, 120> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 120, 120>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_121_inverse() const
   {
        device::static_matrix<value_type, 121, 121> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 121, 121>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_122_inverse() const
   {
        device::static_matrix<value_type, 122, 122> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 122, 122>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_123_inverse() const
   {
        device::static_matrix<value_type, 123, 123> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 123, 123>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_124_inverse() const
   {
        device::static_matrix<value_type, 124, 124> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 124, 124>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_125_inverse() const
   {
        device::static_matrix<value_type, 125, 125> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 125, 125>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_126_inverse() const
   {
        device::static_matrix<value_type, 126, 126> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 126, 126>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_127_inverse() const
   {
        device::static_matrix<value_type, 127, 127> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 127, 127>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }

   const self_type static_matrix_128_inverse() const
   {
        device::static_matrix<value_type, 128, 128> sm;
        device::device_to_host( begin(), end(), sm.begin() );
        const device::static_matrix<value_type, 128, 128>&s = sm.inverse();
        self_type ans(row(), col() );
        device::host_to_device( s.begin(), s.end(), ans.begin() );
        return  ans;
   }
#endif

private:
   const self_type direct_inverse() const 
   {
        const size_type m = row() >> 1;
        const size_type n = row();

        const self_type P( *this, 0, m, 0, m ); const self_type Q( *this, 0, m, m, n );
        const self_type R( *this, m, n, 0, m ); const self_type S( *this, m, n, m, n );

        const self_type& s = S.inverse();
        const self_type& Qs = Q * s;
        const self_type& sR = s * R;
        const self_type& QsR = Q * sR;
        const self_type& L = P - QsR;
        const self_type& P_ = L.inverse();  
        const self_type& Q_ = -P_ * Qs;
        const self_type& R_ = -sR * P_;
        const self_type& S_ = s - R_ * Qs;

        return ( P_ || Q_ ) && ( R_ || S_ );
   }

   const self_type strassen_inverse() const 
   {
        const size_type n = row();
        const size_type n_2 = n >> 1;

        const self_type a_11( *this, 0, n_2, 0, n_2 ); const self_type a_12( *this, 0, n_2, n_2, n );
        const self_type a_21( *this, n_2, n, 0, n_2 ); const self_type a_22( *this, n_2, n, n_2, n );

        const self_type& R1     = a_11.inverse();
        const self_type& R2     = a_21 * R1;
        const self_type& R3     = R1 * a_12;
        const self_type& R4     = a_21 * R3;
        const self_type& R5     = R4 - a_22;
        const self_type& R6     = R5.inverse(); 
        const self_type& c_12   = R3 * R6;
        const self_type& c_21   = R6 * R2;
        const self_type& R7     = R3 * c_21;
        const self_type& c_11   = R1 - R7;
        const self_type& c_22   = -R6;

        return (c_11 || c_12) && (c_21 || c_22);
   }

public:
    friend const self_type operator || ( const self_type& lhs, const self_type& rhs )
    {
       assert( lhs.row() == rhs.row() );

        const size_type row = lhs.row();
        const size_type col = lhs.col() + rhs.col();

        self_type ans( row, col );

        for ( size_type i = 0; i < row; ++i )
        {   
            device::copy( lhs.row_begin(i), lhs.row_end(i), ans.row_begin(i));
            device::copy( rhs.row_begin(i), rhs.row_end(i), ans.row_begin(i)+lhs.col() );
        }   

        return ans; 
    }

    friend const self_type operator && ( const self_type& lhs, const self_type& rhs )
    {
       assert( lhs.col() == rhs.col() );

        const size_type row = lhs.row() + rhs.row();
        const size_type col = lhs.col();

        self_type ans( row, col );

        for ( size_type i = 0; i < col; ++i )
        {
            device::copy( lhs.col_begin(i), lhs.col_end(i), ans.col_begin(i));
            device::copy( rhs.col_begin(i), rhs.col_end(i), ans.col_begin(i)+lhs.row() );
        }

        return ans; 
    }

public:
    const value_type tr() const 
    {
        return device::accumulate( diag_begin(), diag_end(), value_type() );
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
        self_type ans( row(), col() );

        device::transform( begin(), end(), ans.begin(), f );

        return ans;
    }

public:
    void swap( self_type& other )
    {
        device::swap( row_, other.row_ );
        device::swap( col_, other.col_ );
        data_.swap( other.data_ );
    }

private:

    size_type row_;
    size_type col_;
    storage_type data_;
};//struct matrix

}//namespace device

#endif//_MATRIX_IMPL_HPP_INCLUDED_DSFOINASKJL4U83IASFKLDJBASIOUB4EIUYBFAKJBIUHFE
