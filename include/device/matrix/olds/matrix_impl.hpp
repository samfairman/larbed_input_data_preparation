#ifndef _MATRIX_IMPL_HPP_INCLUDED_DSFOINASKJL4U83IASFKLDJBASIOUB4EIUYBFAKJBIUHFE
#define _MATRIX_IMPL_HPP_INCLUDED_DSFOINASKJL4U83IASFKLDJBASIOUB4EIUYBFAKJBIUHFE 

#include <device/typedef.hpp>
#include <device/matrix/matrix_allocator.hpp>
#include <device/matrix/matrix_range_iterator.hpp>
#include <device/matrix/matrix_stride_iterator.hpp>
#include <device/matrix/matrix_multiply_kernel.hpp>
#include <device/matrix/misc.hpp>
#include <device/matrix/numeric/math/inverse.hpp>
#include <device/algorithm.hpp>
#include <device/functional.hpp>
#include <device/utility/assert.hpp>

// blas macro and heads

// cublas macro and heads

// culablas macro and heads

/*
#include <fstream>
#include <functional>
#include <iosfwd>
#include <iterator>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <valarray>
#include <vector>
*/

namespace device
{

template< typename Type, class Allocator = device::matrix_allocator<Type> >
class matrix
{

public:
    typedef Type                                                        value_type;
    typedef matrix                                                      self_type;
    typedef value_type*                                                 iterator;
    typedef const value_type*                                           const_iterator;
    
    typedef matrix_buffer<value_type, Default, Allocator>               storage_type;
    typedef device::size_t                                              size_type;
    typedef device::ptrdiff_t                                           difference_type;
    typedef range                                                       range_type;

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

    //range iterators
    typedef matrix_range_iterator<row_type>                             row_range_type;
    typedef matrix_range_iterator<const_row_type>                       const_row_range_type;
    typedef matrix_range_iterator<col_type>                             col_range_type;
    typedef matrix_range_iterator<const_col_type>                       const_col_range_type;
    typedef device::reverse_iterator<row_range_type>                    reverse_row_range_type;
    typedef device::reverse_iterator<const_row_range_type>              const_reverse_row_range_type;
    typedef device::reverse_iterator<col_range_type>                    reverse_col_range_type;
    typedef device::reverse_iterator<const_col_range_type>              const_reverse_col_range_type;

public:
    
    explicit matrix( const size_type r = 0, const size_type c = 0, const value_type& v = value_type() ) 
    : row_(r), col_(c), data_(storage_type(r*c)) 
    { 
        device::fill( begin(), end(), v ); 
    }

    
    explicit matrix( const size_type n ) 
    : row_(n), col_(n), data_(storage_type(n*n)) 
    {}

    
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

    
    template<typename T, size_type D, typename A>
    matrix(const matrix<T,D,A>& rhs)
    {
        operator=(rhs);
    }

    
    template<typename T, size_type D, typename A>
    self_type & operator=(const matrix<T,D,A>& rhs)
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
    
    template< typename T, size_type D, typename A >
    matrix( const matrix<T,D,A>& other, const range_type& rr, const range_type& rc )
        :   row_( rr.second - rr.first ), col_( rc.second - rc.first ), data_(storage_type((rr.second-rr.first)*(rc.second-rc.first))) 
    {
        clone( other, rr.first, rr.second, rc.first, rc.second );
    }

    
    template< typename T, size_type D, typename A >
    matrix( const matrix<T,D,A>& other, size_type const r0, size_type r1, size_type const c0, size_type const c1 )
        :   row_( r1-r0 ), col_( c1-c0 ), data_(storage_type((r1-r0)*(c1-c0))) 
    {
        clone( other, r0, r1, c0, c1 );
    }

public:
    
    template< typename T, size_type D, typename A >
    self_type& clone( const matrix<T,D,A>& other, size_type const r0, size_type const r1, size_type const c0, size_type const c1 )
    {
        assert( r1 > r0 );
        assert( c1 > c0 );

        resize( r1-r0, c1-c0 );
        
        //TODO: parallel here
        for ( size_type i = r0; i != r1; ++i )
            device::copy( other.row_begin(i)+c0, other.row_begin(i)+c1, row_begin(i-r0) );
        
        return *this;
    }

public:
    bool save_as( const char* const file_name ) const
    {
        std::ofstream ofs( file_name );
        if ( !ofs ) return false;
        ofs.precision(16);
        ofs << *this;
        ofs.close();
        return true;
    }

    bool save_as( const std::string& file_name ) const 
    {
        return save_as( file_name.c_str() );
    }

    bool save_to( const char* const file_name ) const 
    {
        return save_as( file_name );
    }

    bool save_to( const std::string& file_name ) const 
    {
        return save_as( file_name.c_str() );
    }

    bool save( const char* const file_name ) const 
    {
        return save_as( file_name );
    }

    bool save( const std::string& file_name ) const 
    {
        return save_as( file_name.c_str() );
    }

public:
    
    template< typename Itor >
    matrix( const size_type r, const size_type c, Itor first, Itor last )
    :   row_(r), col_(c), data_(storage_type(r*c)) 
    {
        device::copy( first, last, begin() ); 
    }

private:
    
    template<typename T, size_type D, typename A>
    void do_copy(const matrix<T,D,A>& rhs)
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

    self_type& resize( const size_type new_row, const size_type new_col, const value_type& v = value_type(0) )
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
    
    row_type operator[](const size_type index)
    {
        return row_begin(index);
    }

    
    const_row_type operator[](const size_type index) const
    {
        return row_begin(index);
    }

public:
    
    value_type& operator()( const size_type r = 0, const size_type c = 0 )
    {
        return *(row_begin(r)+c);
    }

    
    value_type operator()( const size_type r = 0, const size_type c = 0 ) const 
    {
        return *(row_cbegin(r)+c);
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

    const self_type operator~() const
    {
        return transpose();
    }

    const self_type operator!() const
    {
        return inverse();
    }

public:
    self_type & operator +=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::plus<value_type>(), rhs));
        return *this;
    }

    self_type & operator +=(const self_type& rhs)
    {
        device::transform(begin(), end(), rhs.begin(), begin(), device::plus<value_type>());
        return *this;
    }

    self_type & operator -=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::minus<value_type>(), rhs));
        return *this;
    }

    self_type & operator -=(const self_type& rhs)
    {
        device::transform(begin(), end(), rhs.begin(), begin(), device::minus<value_type>());
        return *this;
    }

    self_type & operator *=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::multiplies<value_type>(), rhs));
        return *this;
    }

public:
    self_type& operator *= ( const self_type& other )
    {
        //
        assert( col() == other.row() );
        self_type ans( row(), other.col() );
        matrix_multiply( ans.begin(), cbegin(), other.cbegin(), row(), col(), other.col() );
        swap( ans );
        return ans;
    }

    self_type & operator /=(const value_type& rhs)
    {
        device::transform(begin(), end(), begin(), device::bind2nd(device::divides<value_type>(), rhs));
        return *this;
    }

    self_type & operator /=(const self_type& rhs)
    {
        return operator*=(!rhs);
    }

    template<typename T_>
    self_type & operator /= ( const T_& rhs )
    {
        device::transform( begin(), end(), begin(), device::bind2nd(device::divides<value_type>(), rhs) );
        return *this;
    }

    public:
    const self_type transpose() const
    {
        //TODO parallel here
        self_type ans(col(), row());

        for (size_type i = 0; i < col(); ++i)
            device::copy(col_begin(i), col_end(i), ans.row_begin(i));

        return ans;
    }

    public:
    const self_type inverse() const
    {
        //TODO: use LU or svd algorithm to solve this problem
        assert( row() == col() && size() != 0 );

        if (1 == size())
        {
            device::transform( begin(), end(), begin(), device::inverse() );
            return ans;
        }

        if ( row() & 1 )
            return direct_inverse();

        return strassen_inverse();
    }

    private:
    //
    //A=[P Q] 
    //  [R S]
    //where P is m*m, Q is m*n, R is n*m and S is n*n
    //
    //suppose the inverse is 
    //A'=[P' Q'] 
    //   [R' S']
    //then we could get :
    //  P' = (P-Q*S^{-1}*R)^{-1}
    //  Q' = -(P-Q*S^{-1}*R)^{-1} * (Q*S^{-1})
    //  R' = -(S^{-1}*R) * (P-Q*S^{-1}*R)^{-1}
    //  S' = S^{-1} + (S^{-1}*R) * (P-Q*S^{-1}*R)^{-1} * (Q*S^{-1})
    //or short terms: 
    // a) s[n,n] = S^{-1}
    // b) p[m,m] = P^{-1}
    // c) Qs[m,n]= Q*s
    // d) sR[n,m]= s*R
    // e) QsR[m,m]= Q*sR
    // f) L[m,m] = P-QsR
    // g) P'[m,m] = L^{-1}
    // h) Q'[m,n] = -P'*Qs
    // i) R'[n,m] = -sR*P'
    // j) S'[n,n] = s + sR * P' * Qs
    //
    const self_type direct_inverse() const
    {
        const size_type m = row() >> 1;
        const size_type n = row();

        const self_type P( *this, 0, m, 0, m ); const self_type Q( *this, 0, m, m, n );
        const self_type R( *this, m, n, 0, m ); const self_type S( *this, m, n, m, n );

        // a)
        const self_type& s = S.inverse();
        // b)
        //const self_type& p = P.inverse();
        // c)
        const self_type& Qs = Q * s;
        // d)
        const self_type& sR = s * R;
        // e)
        const self_type& QsR = Q * sR;
        // f)
        const self_type& L = P - QsR;
        // g)
        const self_type& P_ = L.inverse();
        // h)
        const self_type& Q_ = -P_ * Qs;
        // i)
        const self_type& R_ = -sR * P_;
        // j)
        const self_type& S_ = s - R_ * Qs;

        return ( P_ || Q_ ) &&
               ( R_ || S_ );
    }

    // A:   suppose the matrices (a_11 a_12, a_21 a_22) and (c_11 c_12, c_21 c_22) are inverses of each other.
    //      the c's can be obtained by following operations:
    //  1       R1 = inverse(a_11)
    //  2       R2 = a_21 * R1
    //  3       R3 = R1 * a_12
    //  4       R4 = a_21 * R3
    //  5       R5 = R4 - a_22
    //  6       R6 = inverse(R5)
    //  7       c_12 = R3*R6
    //  8       c_21 = R6*R2
    //  9       R7 = R3*c_21
    //  10      c_11 = R1-R7
    //  11      c_22 = -R6
    // B:   merge   c_11 c_12
    //              c_21 c_22
    //      to generate the reverse matrix.
    const self_type strassen_inverse() const
    {
        const size_type n = row();
        const size_type n_2 = n >> 1;

        //A
        const self_type a_11( *this, range_type(0, n_2), range_type(0, n_2) ); const self_type a_12( *this, range_type(0, n_2), range_type(n_2, n) );
        const self_type a_21( *this, range_type(n_2, n), range_type(0, n_2) ); const self_type a_22( *this, range_type(n_2, n), range_type(n_2, n) );
        
        //1
        const self_type& R1 = a_11.inverse();
        //2
        const self_type& R2 = a_21 * R1;
        //3
        const self_type& R3 = R1 * a_12;
        //4
        const self_type& R4 = a_21 * R3;
        //5
        const self_type& R5 = R4 - a_22;
        //6
        const self_type& R6 = R5.inverse();
        //7
        const self_type& c_12 = R3 * R6;
        //8
        const self_type& c_21 = R6 * R2;
        //9
        const self_type& R7 = R3 * c_21;
        //10
        const self_type& c_11 = R1 - R7;
        //11
        const self_type& c_22 = -R6;
        //B
        return (c_11 || c_12) && 
               (c_21 || c_22);
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
};

template<typename T, std::size_t D, typename A>
std::ostream & operator <<(std::ostream& lhs, const matrix<T, D, A>& rhs)
{
    typedef typename matrix<T>::size_type size_type;
    typedef typename matrix<T>::value_type value_type;

    //allocate memory
    //copy from device to host
    //output host

    for (size_type i = 0; i < rhs.row(); ++i)
    {
        std::copy(rhs.row_begin(i), rhs.row_end(i), std::ostream_iterator<value_type > (lhs, " \t "));
        lhs << "\n";
    }

    return lhs;
} 

}//namespace device

#endif//_MATRIX_IMPL_HPP_INCLUDED_DSFOINASKJL4U83IASFKLDJBASIOUB4EIUYBFAKJBIUHFE

