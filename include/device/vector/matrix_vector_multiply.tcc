#ifndef _MATRIX_VECTOR_MULTIPLY_TCC_INCLUDED_SFPOINSAFLKJAFSDPOIJ4POIHSFDLKJSAFD
#define _MATRIX_VECTOR_MULTIPLY_TCC_INCLUDED_SFPOINSAFLKJAFSDPOIJ4POIHSFDLKJSAFD

#include <device/vector.hpp>
#include <device/matrix.hpp>
#include <device/iterator.hpp>
#include <device/numeric/inner_product.hpp>
#include <device/typedef.hpp>

namespace device
{

#if 0
namespace mvm_private
{
    //Not efficient
    //TODO: optimization
    template< typename Iterator1, typename Iterator2, typename Iterator3, typename Distance >
    __global__ // y = Ax
    void __gemv( Iterator1 A_first, Iterator2 x_first, Iterator3 y_first, Distance A_row, Distance A_col )
    {
        typedef typename device::iterator_traits<Iterator1>::value_type value_type;

        const device::size_t index = blockDim.x * blockIdx.x + threadIdx.x;

        if ( index >= A_row ) return;

        Iterator1 row_begin = A_first + A_col * index;
        Iterator1 row_end = row_begin + col;

        *(y_first+index) = device::kernel_inner_product( row_begin, row_end, x_first, value_type(0) );
    }

}//namespace mvm_private 

    template<typename T>
    void gemv( const device::matrix<T>& A, const device::vector<T>& x, device::vector<T>& y )
    {
        assert( A.col() == x.size() );
        y.resize( A.row() );

        const device::size_t threads = device::threads_per_block::value;
        const device::size_t blocks = (A.row()+threads-1)/threads;

        mvm_private::__gemv<<<blocks, threads>>>( A.begin(), x.begin(), y.begin(), A.row(), A.col() );
    }

    template<typename T, typename A1, typename A2>
    const device::vector<T,A2> operator * ( const device::matrix<T,A1>& A, const device::vector<T,A2>& x )
    {
        device::vector<T,A2> y( A.row() );
        gemv( A, x, y );
        return y;
    }
#endif
}


#endif//_MATRIX_VECTOR_MULTIPLY_TCC_INCLUDED_SFPOINSAFLKJAFSDPOIJ4POIHSFDLKJSAFD

