#ifndef _MATRIX_TCC_INCLUDED_SOIJS98Y34ALKFUHDSAKJFDSHADFUH34UIHAFKJVS8YH4IAHUFS
#define _MATRIX_TCC_INCLUDED_SOIJS98Y34ALKFUHDSAKJFDSHADFUH34UIHAFKJVS8YH4IAHUFS

#include <cuda_runtime_api.h>

#include <device/algorithm/copy.hpp>
#include <device/algorithm/fill.hpp>
#include <device/algorithm/transform.hpp>
#include <device/functional/negate.hpp>
#include <device/utility/assert.hpp>
#include <device/utility/cuda_assert.hpp>
#include <device/matrix/matrix_multiply_kernel.hpp>

namespace device
{
    template<typename T>
    matrix<T>::matrix( const self_type& other )
    {
        row_ = other.row_;
        col_ = other.col_;
        const size_type byte_size = row_ * col_ * sizeof(value_type);
        cuda_assert( cudaMalloc( reinterpret_cast<void**>(data_), byte_size ) );
        device::copy( other.cbegin(), other.cend(), begin() );
    }

    template<typename T>
    matrix<T>::matrix( const size_type row, const size_type col )
    : row_(row), col_(col)
    {
        const size_type byte_size = row_ * col_ * sizeof(value_type);
        cuda_assert( cudaMalloc( reinterpret_cast<void**>(data_), byte_size ) );
    }

    template<typename T>
    matrix<T>::matrix( const size_type row, const size_type col, const value_type& v )
    : row_(row), col_(col)
    {
        const size_type byte_size = row_ * col_ * sizeof(value_type);
        cuda_assert( cudaMalloc( reinterpret_cast<void**>(data_), byte_size ) );
        device::fill( begin(), end(), v );
    }

    template<typename T>
    matrix<T>::self_type& matrix<T>::operator = matrix( const self_type& other ) 
    {
        if ( size() != other.size() )
        {
            //deallocate
            cuda_assert( cudaFree( data_ ) );
            //allocate
            const size_type byte_size = other.row_ * other.col_ * sizeof(value_type);
            cuda_assert( cudaMalloc( reinterpret_cast<void**>(data_), byte_size ) );
        }
        //change row and col now, as matrix can of different dims(row and col) but same size
        row_ = other.row_;
        col_ = other.col_;
        device::copy( begin(), end(), other.begin() );
        return *this; 
    }

    template<typename T>
        template<typename U>
    matrix<T>::self_type& matrix<T>::operator = ( const U& v )
    {
        device::fill( begin(), end(), v );
    }

    template<typename T>
    matrix<T>::~matrix()
    {
        cuMemFree( data_ );
        data_ = 0;
        row_ = 0;
        col_ = 0;
    }
    
    template<typename T>
    const matrix<T>::self_type matrix<T>::operator + () const
    {
        const self_type ans(*this);
        return ans;
    }
    
    template<typename T>
    const matrix<T>::self_type matrix<T>::operator - () const
    {
        self_type ans(row(), col());
        device::transform( cbegin(), cend(), ans.begin(), device::negate<value_type>() );
        return ans;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator += ( const value_type& v) const
    {
        device::transform( begin(), end(), begin(), device::bind2nd( device::plus<value_type>(), v ) );
        return *this;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator -= ( const value_type& v) const
    {
        device::transform( begin(), end(), begin(), device::bind2nd( device::minus<value_type>(), v ) );
        return *this;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator *= ( const value_type& v) const
    {
        device::transform( begin(), end(), begin(), device::bind2nd( device::multiplies<value_type>(), v ) );
        return *this;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator /= ( const value_type& v) const
    {
        device::transform( begin(), end(), begin(), device::bind2nd( device::divides<value_type>(), v ) );
        return *this;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator += ( const self_type& other) const
    {
        assert( row() == other.row() );
        assert( col() == other.col() );
        device::transform( begin(), end(), other.begin(), begin(), device::plus<value_type>() );
        return *this;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator -= ( const self_type& other) const
    {
        assert( row() == other.row() );
        assert( col() == other.col() );
        device::transform( begin(), end(), other.begin(), begin(), device::minus<value_type>() );
        return *this;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator *= ( const self_type& other) const
    {
        assert( col() == other.row() );
        self_type ans( row(), other.col() );
        matrix_multiply( ans.begin(), cbegin(), other.cbegin(), row(), col(), other.col() );
        swap( ans );
        return *this;
    }
    
    template<typename T>
    matrix<T>::self_type& matrix<T>::operator /= ( const self_type& other) const
    {
        assert( col() == other.row() );
        assert( other.row() == other.col() );
        //to be implemented
    }
    
    template<typename T>
    void swap( self_type& other)
    {
        row_^=other.row_; other.row_^=row_; row_^=other.row_;
        col_^=other.col_; other.col_^=col_; col_^=other.col_;
        const pointer tmp=data_; data_=other.data_; other.data_=tmp;
    }

}//namespace device

#endif//_MATRIX_TCC_INCLUDED_SOIJS98Y34ALKFUHDSAKJFDSHADFUH34UIHAFKJVS8YH4IAHUFS

