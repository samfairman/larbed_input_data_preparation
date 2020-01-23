#ifndef _STATIC_MATRIX_N_N_HPP_INCLUDED_SDPOINSAFDLKJN4E9UAHFLKJH498YHAFUH4389H 
#define _STATIC_MATRIX_N_N_HPP_INCLUDED_SDPOINSAFDLKJN4E9UAHFLKJH498YHAFUH4389H 

#include <device/matrix/static_matrix/static_matrix_m_n.hpp>
#include <device/matrix/static_matrix/static_matrix_1_1.hpp>
#include <device/typedef.hpp>
#include <device/matrix/static_matrix/static_matrix_buffer.hpp>
#include <device/matrix/static_matrix/static_matrix_stride_iterator.hpp>

#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <iostream>

namespace device
{

template<typename Type, device::size_t Dim>
class static_matrix<Type, Dim, Dim>
{
public:

    typedef Type                                                        value_type;
    typedef static_matrix                                               self_type;
    typedef value_type*                                                 iterator;
    typedef const value_type*                                           const_iterator;
    typedef value_type*                                                 row_type;
    typedef const value_type*                                           const_row_type;
    typedef static_matrix_stride_iterator<value_type*, Dim>               col_type;
    typedef static_matrix_stride_iterator<const value_type*, Dim>         const_col_type;
    typedef static_matrix_stride_iterator<value_type*, Dim+1>             diag_type;
    typedef static_matrix_stride_iterator<const value_type*, Dim+1>       const_diag_type;
    typedef static_matrix_buffer<value_type, Dim*Dim>                       storage_type;
    typedef device::size_t                                              size_type;

    typedef std::reverse_iterator<iterator>                             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>                       const_reverse_iterator;

    typedef std::reverse_iterator<row_type>                             reverse_row_type;
    typedef std::reverse_iterator<const_row_type>                       const_reverse_row_type;
    
    typedef std::reverse_iterator<col_type>                             reverse_col_type;
    typedef std::reverse_iterator<const_col_type>                       const_reverse_col_type;
    
    typedef std::reverse_iterator<diag_type>                            reverse_upper_diag_type;
    typedef std::reverse_iterator<const_diag_type>                      const_reverse_upper_diag_type;
    
    typedef std::reverse_iterator<diag_type>                            reverse_lower_diag_type;
    typedef std::reverse_iterator<const_diag_type>                      const_reverse_lower_diag_type;
    
    typedef std::reverse_iterator<diag_type>                            reverse_diag_type;
    typedef std::reverse_iterator<const_diag_type>                      const_reverse_diag_type;

public:

    static_matrix() {}

    ~static_matrix() {}

    static_matrix( const value_type& v )
    {
        std::fill( begin(), end(), v );
    }

    template<typename U>
    static_matrix(const static_matrix<U, Dim, Dim>& rhs)
    {
        operator=<U>(rhs);
    }

    template<typename U>
    self_type &
    operator=(const static_matrix<U, Dim, Dim>& rhs)
    {
        do_copy<U>(rhs);
        return *this;
    }

    static_matrix(const self_type& rhs)
    {
        operator=(rhs);
    }

    self_type & 
    operator=(const self_type& rhs)
    {
        do_copy(rhs);
        return *this;
    }

private:

    template<typename U>
    void do_copy(const static_matrix<U, Dim, Dim>& rhs)
    {
        std::copy(rhs.begin(), rhs.end(), begin());
    }

    void do_copy(const self_type& rhs)
    {
        data_ = rhs.data_;
    }

public:

    size_type row()const
    {
        return Dim;
    }

    size_type col()const
    {
        return Dim;
    }

    size_type size()const
    {
        return Dim*Dim;
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

public:

    row_type row_begin(const size_type index = 0)
    {
        return begin() + index * Dim;
    }

    row_type row_end(const size_type index = 0)
    {
        return row_begin(index) + Dim;
    }

    const_row_type row_begin(const size_type index = 0) const
    {
        return begin() + index * Dim;
    }

    const_row_type row_end(const size_type index = 0) const
    {
        return row_begin(index) + Dim;
    }

public:

    col_type col_begin(const size_type index = 0)
    {
        return col_type(begin() + index);
    }

    col_type col_end(const size_type index = 0)
    {
        return col_begin(index) + Dim;
    }

    const_col_type col_begin(const size_type index = 0 ) const
    {
        return const_col_type(begin() + index);
    }

    const_col_type col_end(const size_type index = 0 ) const
    {
        //return col_begin(index) + Dim;
        return col_begin(index) + Dim;
    }

public:

    diag_type upper_diag_begin(const size_type index = 0 )
    {
        return diag_type(begin() + index);
    }

    diag_type upper_diag_end(const size_type index = 0 )
    {
        size_type depth = Dim - index;
        if (Dim < depth)
            depth = Dim;
        return upper_diag_begin(index) + depth;
    }

    const_diag_type upper_diag_begin(const size_type index = 0 ) const
    {
        return const_diag_type(begin() + index);
    }

    const_diag_type upper_diag_end(const size_type index = 0 ) const
    {
        size_type depth = Dim - index;
        if (Dim < depth)
            depth = Dim;
        return upper_diag_begin(index) + depth;
    }

public:

    diag_type lower_diag_begin(const size_type index = 0 )
    {
        return diag_type(begin() + index * Dim);
    }

    diag_type lower_diag_end(const size_type index = 0 )
    {
        size_type depth = Dim - index;
        if (Dim < depth)
            depth = Dim;
        return lower_diag_begin(index) + depth;
    }

    const_diag_type lower_diag_begin(const size_type index = 0 ) const
    {
        return const_diag_type(begin() + index * Dim);
    }

    const_diag_type lower_diag_end(const size_type index = 0 ) const
    {
        size_type depth = Dim - index;
        if (Dim < depth)
            depth = Dim;
        return lower_diag_begin(index) + depth;
    }

public:

    diag_type diag_begin()
    {
        return lower_diag_begin(0);
    }

    diag_type diag_end()
    {
        return lower_diag_end(0);
    }

    const_diag_type diag_begin() const
    {
        return lower_diag_begin(0);
    }

    const_diag_type diag_end() const
    {
        return lower_diag_end(0);
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

public:
    reverse_diag_type diag_rbegin()
    {
        return reverse_diag_type( diag_end() );
    }

    reverse_diag_type diag_rend()
    {
        return reverse_diag_type( diag_begin() );
    }

    const_reverse_diag_type diag_rbegin() const
    {
        return const_reverse_diag_type( diag_end() );
    }

    const_reverse_diag_type diag_rend() const
    {
        return const_reverse_diag_type( diag_begin() );
    }

public:

    row_type operator[](const size_type index )
    {
        return row_begin(index);
    }

    const_row_type operator[](const size_type index ) const
    {
        return row_begin(index);
    }

public:
    const static_matrix<value_type, Dim, Dim> operator~() const
    {
        return transpose();
    }

public:

    const static_matrix<value_type, Dim, Dim>
    transpose() const
    {
        static_matrix<value_type, Dim, Dim> ans;

        for (size_type i = 0; i < Dim; ++i)
            std::copy(col_begin(i), col_end(i), ans.row_begin(i));

        return ans;
    }


public:

    friend bool operator == ( const self_type& lhs, const self_type& rhs ) 
    {
        return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
    }

    friend bool operator == ( const self_type& lhs, const value_type& rhs )
    {
        return  std::count( lhs.begin(), lhs.end(), rhs ) == lhs.size();
    }

    friend bool operator == ( const value_type& lhs, const self_type& rhs )
    {
        return rhs == lhs;
    }

    friend bool operator < ( const self_type& lhs, const self_type& rhs )
    {
        return std::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
    }

   friend bool operator < ( const self_type& lhs, const value_type& rhs )
   {
        return  std::count_if( lhs.begin(), lhs.end(), std::bind2nd(std::less<value_type>(), rhs) ) == lhs.size();
   }

   friend bool operator < ( const value_type& lhs, const self_type& rhs )
   {
        return  std::count_if( rhs.begin(), rhs.end(), std::bind1st(std::greater<value_type>(), lhs) ) == rhs.size();
   }

   friend bool operator > ( const self_type& lhs, const value_type& rhs ) 
   {
        return  std::count_if( lhs.begin(), lhs.end(), std::bind2nd(std::greater<value_type>(), rhs) ) == lhs.size();
   }

   friend bool operator > ( const self_type& lhs, const self_type& rhs )
   {
        return !( lhs == rhs ) && !( lhs < rhs ); 
   }

   friend bool operator > ( const value_type& lhs, const self_type& rhs )
   {
        return !( lhs == rhs ) && !( lhs < rhs ); 
   }

public:
   const self_type operator + () const
   {
       return *this;
   }

   const self_type operator - () const 
   {
       self_type ans(*this);
       std::transform( ans.begin(), ans.end(), ans.begin(), std::negate<value_type>() );
       return ans;
   }

public:
    self_type & operator +=(const value_type& rhs)
    {
        std::transform(begin(), end(), begin(), std::bind1st(std::plus<value_type > (), rhs));
        return *this;
    }

    friend const self_type operator + ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans(lhs);
        ans += rhs; 
        return ans;
    }

    friend const self_type operator + ( const value_type& lhs, const self_type& rhs )
    {
        return rhs + lhs;
    }

    self_type & operator += (const self_type& rhs)
    {
        std::transform(begin(), end(), rhs.begin(), begin(), std::plus<value_type > ());
        return *this;
    }

    friend const self_type operator + ( const self_type& lhs, const self_type& rhs )
    {
        self_type ans( lhs );
        ans += rhs;
        return ans;
    }

    self_type & operator -= (const value_type& rhs)
    {
        std::transform(begin(), end(), begin(), std::bind1st(std::minus<value_type > (), rhs));
        return *this;
    }

    friend const self_type operator - ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs );
        ans -= rhs;
        return ans;
    }

    friend const self_type operator - ( const value_type& lhs, const self_type& rhs )
    {
        return rhs - lhs;
    }

    self_type & operator -= (const self_type& rhs)
    {
        std::transform(begin(), end(), rhs.begin(), begin(), std::minus<value_type > ());
        return *this;
    }

    friend const self_type operator - ( const self_type& lhs, const self_type& rhs )
    {
        self_type ans( lhs );
        ans -= rhs;
        return ans;
    }

    self_type & operator *=(const value_type& rhs)
    {
        std::transform(begin(), end(), begin(), std::bind1st(std::multiplies<value_type > (), rhs));
        return *this;
    }

    friend const self_type operator * ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs );
        ans *= rhs;
        return ans;
    }

    friend const self_type operator * ( const value_type& lhs, const self_type& rhs )
    {
        return rhs * lhs;
    }

    self_type & operator /=(const value_type& rhs)
    {
        std::transform(begin(), end(), begin(), std::bind2nd(std::divides<value_type > (), rhs));
        return *this;
    }

    friend const self_type operator / ( const self_type& lhs, const value_type& rhs )
    {
        self_type ans( lhs );
        ans /= rhs;
        return ans;
    }

    const self_type inverse() const 
    {
        self_type ans;

        static_matrix<value_type, Dim/2, Dim/2> P; // m m
        static_matrix<value_type, Dim/2, Dim-Dim/2> Q; // m n
        static_matrix<value_type, Dim-Dim/2, Dim/2> R; // n m
        static_matrix<value_type, Dim-Dim/2, Dim-Dim/2> S; // n n

        for (size_type i=0; i<Dim/2; ++i)
        {
            std::copy(row_begin(i), row_begin(i) + Dim/2, P.row_begin(i));
            std::copy(row_begin(i)+Dim/2, row_end(i), Q.row_begin(i));
        }
        for (size_type i=Dim/2; i<Dim; ++i)
        {
            std::copy(row_begin(i), row_begin(i)+Dim/2, R.row_begin(i-Dim/2));
            std::copy(row_begin(i)+Dim/2, row_end(i), S.row_begin(i-Dim/2));
        }

        const static_matrix<value_type, Dim-Dim/2, Dim-Dim/2>& s = S.inverse();
        const static_matrix<value_type, Dim/2, Dim-Dim/2>& Qs = Q * s;
        const static_matrix<value_type, Dim-Dim/2, Dim/2>& sR = s * R;
        const static_matrix<value_type, Dim/2, Dim/2>& QsR = Q * sR;
        const static_matrix<value_type, Dim/2, Dim/2>& L = P - QsR;
        const static_matrix<value_type, Dim/2, Dim/2>& P_ = L.inverse();
        const static_matrix<value_type, Dim/2, Dim-Dim/2>& Q_ = -P_ * Qs;
        const static_matrix<value_type, Dim-Dim/2, Dim/2>& R_ = -sR * P_;
        const static_matrix<value_type, Dim-Dim/2, Dim-Dim/2>& S_ = s - R_ * Qs;

        for (size_type i = 0; i < Dim/2; ++i)
        {
            std::copy(P_.row_begin(i), P_.row_end(i), ans.row_begin(i));
            std::copy(Q_.row_begin(i), Q_.row_end(i), ans.row_begin(i) + Dim/2);
        }
        for (size_type i = 0; i < (Dim-Dim/2); ++i)
        {
            std::copy(R_.row_begin(i), R_.row_end(i), ans.row_begin(i + Dim/2));
            std::copy(S_.row_begin(i), S_.row_end(i), ans.row_begin(i + Dim/2) + Dim/2);
        }

        return ans;

    }

private:

    storage_type data_;
};//struct static_matrix

}//namespace device

#endif//_STATIC_MATRIX_N_N_HPP_INCLUDED_SDPOINSAFDLKJN4E9UAHFLKJH498YHAFUH4389H 

