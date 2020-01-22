#include <cuda_runtime.h>
#include <cuComplex.h>
#include <f/device/assert/kernel_assert.hpp>

//
// P = alpha_0 P0 + alpha_1 P1 + alpha_2 P2 + alpha_3 P3
//
void __global__
zmatrix_poly4_eval_kernel(unsigned long n, double2* P, double alpha_0, double2* P0, double alpha_1, double2* P1, double alpha_2, double2* P2, double alpha_3, double2* P3 )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;
    if ( tx < n )
    {
        (*(P+tx)).x = alpha_0 * ((*(P0+tx)).x) + alpha_1 * ((*(P1+tx)).x) + alpha_2 * ((*(P2+tx)).x) + alpha_3 * ((*(P3+tx)).x);
        (*(P+tx)).y = alpha_0 * ((*(P0+tx)).y) + alpha_1 * ((*(P1+tx)).y) + alpha_2 * ((*(P2+tx)).y) + alpha_3 * ((*(P3+tx)).y);
    }
}

void zmatrix_poly4_eval( unsigned long n, double2* P, double alpha_0, double2* P0, double alpha_1, double2* P1, double alpha_2, double2* P2, double alpha_3, double2* P3 )
{
    const unsigned long grids = ( n + 1023 ) >> 10;
    kernel_assert( ( zmatrix_poly4_eval_kernel<<<grids, 1024>>>( n, P, alpha_0, P0, alpha_1, P1, alpha_2, P2, alpha_3, P3 ) ) );
}

//
// P = P0 + alpha_1 P1 + alpha_2 P2 + alpha_3 P3
//
void __global__
zmatrix_poly4_eval_kernel(unsigned long n, double2* P, double2* P0, double alpha_1, double2* P1, double alpha_2, double2* P2, double alpha_3, double2* P3 )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;
    if ( tx < n )
    {
        (*(P+tx)).x =  ((*(P0+tx)).x) + alpha_1 * ((*(P1+tx)).x) + alpha_2 * ((*(P2+tx)).x) + alpha_3 * ((*(P3+tx)).x);
        (*(P+tx)).y =  ((*(P0+tx)).y) + alpha_1 * ((*(P1+tx)).y) + alpha_2 * ((*(P2+tx)).y) + alpha_3 * ((*(P3+tx)).y);
    }
}

void zmatrix_poly4_eval( unsigned long n, double2* P, double2* P0, double alpha_1, double2* P1, double alpha_2, double2* P2, double alpha_3, double2* P3 )
{
    const unsigned long grids = ( n + 1023 ) >> 10;
    kernel_assert( ( zmatrix_poly4_eval_kernel<<<grids, 1024>>>( n, P, P0, alpha_1, P1, alpha_2, P2, alpha_3, P3 ) ) );
}



void __global__
zmatrix_poly4_eval_kernel( unsigned long n, double2* P, double2* P0, double alpha_1_r, double alpha_1_i, double2* P1, double alpha_2_r, double alpha_2_i, double2* P2, double alpha_3_r, double alpha_3_i, double2* P3 )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;
    if ( tx < n )
    {
        (*(P+tx)) = cuCadd( cuCadd( (*(P0+tx)),
                                    cuCmul( make_cuDoubleComplex( alpha_1_r, alpha_1_i ), (*(P1+tx)) )
                                  ),
                            cuCadd( cuCmul( make_cuDoubleComplex( alpha_2_r, alpha_2_i ), (*(P2+tx)) ),
                                    cuCmul( make_cuDoubleComplex( alpha_3_r, alpha_3_i ), (*(P3+tx)) )
                                  )
                         );
    }
}

void zmatrix_poly4_eval( unsigned long n, double2* P, double2* P0, double alpha_1_r, double alpha_1_i, double2* P1, double alpha_2_r, double alpha_2_i, double2* P2, double alpha_3_r, double alpha_3_i, double2* P3 )
{
    const unsigned long grids = ( n + 1023 ) >> 10;
    kernel_assert( ( zmatrix_poly4_eval_kernel<<<grids, 1024>>>( n, P, P0, alpha_1_r, alpha_1_i, P1, alpha_2_r, alpha_2_i, P2, alpha_3_r, alpha_3_i, P3 ) ) );
}


/*
void __global__
zmatrix_poly4_eval_kernel(unsigned long n, double2* P, double2 alpha_0, double2* P0, double2 alpha_1, double2* P1, double2 alpha_2, double2* P2, double2 alpha_3, double2* P3 )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 256;
    if ( tx < n )
        (*(P+tx)) = cuAdd( cuAdd( cuMul( alpha_0, *(P0+tx) ), cuMul( alpha_1, *(P1+tx) ) ), cuAdd( cuMul( alpha_2, *(P2+tx) ), cuMul( alpha_3, *(P3+tx) ) ) );
}

void zmatrix_poly4_eval( unsigned long n, double2* P, double2 alpha_0, double2* P0, double2 alpha_1, double2* P1, double2 alpha_2, double2* P2, double2 alpha_3, double2* P3 )
{
    const unsigned long grids = ( n + 255 ) >> 8;
    kernel_assert( ( zmatrix_poly4_eval_kernel<<<grids, 256>>>( n, P, alpha_0, P0, alpha_1, P1, alpha_2, P2, alpha_3, P3 ) ) );
}
*/
