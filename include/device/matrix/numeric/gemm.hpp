#ifndef _GEMM_HPP_INCLUDED_H489AFKJ478FSADJKJKVN9487YDFKJVNBKR98E7YKJDFH4897YFEF
#define _GEMM_HPP_INCLUDED_H489AFKJ478FSADJKJKVN9487YDFKJVNBKR98E7YKJDFH4897YFEF

#include <device/matrix.hpp>
#include <device/matrix/matrix_multiply_kernel.hpp>
#include <device/utility/assert.hpp>

namespace device
{

    // M = A * B
    template<typename T1, typename T2, typename T3>
    void gemm( matrix<T1>& M, const matrix<T2>& A, const matrix<T3>& B )
    {
        const device::size_t A_row = A.row();
        const device::size_t A_col = A.col();
        const device::size_t B_row = B.row();
        const device::size_t B_col = B.col();

        assert( A_col == B_row );

        M.resize( A_row, B_col );
        matrix_multiply( M.begin(), A.cbegin(), B.cbegin(), A_row, A_col, B_col );
    }

}//namespace device

#endif//_GEMM_HPP_INCLUDED_H489AFKJ478FSADJKJKVN9487YDFKJVNBKR98E7YKJDFH4897YFEF

