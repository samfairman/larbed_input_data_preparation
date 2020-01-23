#ifndef _NORM_HPP_INCLUDED_SDPOISAKLH49HAFDKLSDAHFIOUSDHLKJSFAH4EY89HASFILUH48YF
#define _NORM_HPP_INCLUDED_SDPOISAKLH49HAFDKLSDAHFIOUSDHLKJSFAH4EY89HASFILUH48YF

#if 0
namespace feng
{
    // return ||A|| _{inf}
    template< typename Matrix >
    typename Matrix::value_type 
    norm( const Matrix& A )
    {
        typedef typename Matrix::value_type value_type;

        std::vector<value_type> m( A.row() );

        for ( std::size_t i = 0; i != A.row(); ++i )
            m[i] = std::accumulate( A.row_cbegin(i), A.row_cend(i), value_type(0), []( value_type u, value_type v ) { return u + std::abs(v); } );

        return *(std::max_element( m.begin(), m.end() ));
    }

    template< typename Matrix >
    typename Matrix::value_type 
    norm( const Matrix& A, const std::size_t n )
    {
        typedef typename Matrix::value_type value_type;

        if ( 1 == n ) 
        {
            std::vector<value_type> m( A.col() );

            for ( std::size_t i = 0; i != A.col(); ++i )
                m[i] = std::accumulate( A.col_cbegin(i), A.col_cend(i), value_type(0), []( value_type u, value_type v ) { return u + std::abs(v); } );

            return *(std::max_element( m.begin(), m.end() ));
        }

        if ( 2 == n )
        {
            return std::sqrt(eigen_power_iteration( A ));
        }

        assert( !"norm:: other norm algorithm has not been implemented!" );

        return  value_type(0);
    }

    template< typename Matrix >
    typename Matrix::value_type 
    norm_1( const Matrix& A )
    {
        typedef typename Matrix::value_type value_type;
        std::vector<value_type> m( A.col() );

        for ( std::size_t i = 0; i != A.col(); ++i )
            m[i] = std::accumulate( A.col_cbegin(i), A.col_cend(i), value_type(0), []( value_type u, value_type v ) { return u + std::abs(v); } );

        return *(std::max_element( m.begin(), m.end() ));
    }

    template< typename T, std::size_t D, typename A_ >
    T
    norm_1( const matrix<std::complex<T>, D, A_>& A )
    {
        std::vector<T> m( A.col() );

        for ( std::size_t i = 0; i != A.col(); ++i )
            m[i] = std::accumulate( A.col_cbegin(i), A.col_cend(i), T(0), []( const T u, const std::complex<T>& v ) { return u + std::abs(v); } );

        return *(std::max_element( m.begin(), m.end() ));
    }

    template< typename Matrix >
    typename Matrix::value_type 
    norm_2( const Matrix& A )
    {
        return std::sqrt(eigen_power_iteration( A ));
    }

}//namespace feng

#endif

#include <device/matrix.hpp>
#include <device/math/abs.hpp>
#include <device/complex.hpp>
#include <device/algorithm/transform.hpp>
#include <device/config/threads_per_block.hpp>
#include <device/typedef.hpp>
#include <device/vector.hpp>
#include <device/numeric/accumulate.hpp>
#include <device/matrix/matrix_stride_iterator.hpp>
#include <device/utility/device_to_host.hpp>

namespace device
{

    namespace norm_private
    {
        template<typename T>
        struct extract_complex_value_type
        {
            typedef T value_type;
        };

        template<typename T>
        struct extract_complex_value_type<device::complex<T> >
        {
            typedef T value_type;
        };

        template<typename Iterator1, typename Iterator2, typename Distance>
        __global__
        void __col_accumulate( Iterator1 matrix_first, Iterator2 vector_first, Distance matrix_row, Distance matrix_col )
        {
            typedef typename device::iterator_traits<Iterator1>::value_type value_type;
            typedef device::matrix_stride_iterator<Iterator1> stride_iterator_type;

            const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;
            if ( index >= matrix_col ) return;

            stride_iterator_type col_first( matrix_first+index, matrix_col );
            stride_iterator_type col_end( col_first + matrix_row );

            *(vector_first+index) = kernel_accumulate( col_first, col_end, value_type(0) );            
        }

        template <class ForwardIterator>
        ForwardIterator host_max_element ( ForwardIterator first, ForwardIterator last )
        {
            if (first==last) return last;

            ForwardIterator largest = first;

            while (++first!=last)
                if (*largest<*first)   
                    largest=first;

            return largest;
        } 

    }//namespace norm_private

    template<typename T, typename A>
    const typename norm_private::extract_complex_value_type<T>::value_type
    col_norm( const device::matrix<T,A>& M )
    {
        typedef typename norm_private::extract_complex_value_type<T>::value_type real_type;
        real_type ans(0);

        const device::size_t n = M.col();

        if ( !!n )
        {
            device::matrix<real_type> m( M.row(), M.col() ); 
            device::transform( M.begin(), M.end(), m.begin(), device::abs<T>() );

            device::vector<real_type> v( n );

            const device::size_t threads = device::threads_per_block::value;
            const device::size_t blocks = ( n + threads - 1 ) / threads;

            norm_private::__col_accumulate<<<threads, blocks>>>( m.begin(), v.begin(), m.row(), m.col() );

            //host reduct, TODO optimization with large size in kernel
            real_type* arr = new real_type[n];
            device::device_to_host( v.begin(), v.end(), arr );
            ans = *norm_private::host_max_element( arr, arr+n );
            delete[] arr;
        } 

        return ans;
    }

}//namespace device

#endif//_NORM_HPP_INCLUDED_SDPOISAKLH49HAFDKLSDAHFIOUSDHLKJSFAH4EY89HASFILUH48YF 

