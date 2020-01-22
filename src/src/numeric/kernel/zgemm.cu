#include <cuComplex.h>

//cuDoubleComplex

//C = alpha * A * B + beta * c

__device__ __inline__ cuDoubleComplex 
dc_multiply( cuDoubleComplex x, cuDoubleComplex y )
{
    double const a = x.x;
    double const b = x.x;
    double const c = y.x;
    double const d = y.y;
    //double const ac = a * c;
    double const ac = __dmul_rz( a, c );
    //double const bd = b * d;
    double const bd = __dmul_rz( b, d );
    //double const ab_cd = ( a + b ) * ( c + d );
    double const ab_cd = __dmul_rz ( __dadd_rz( a, b ) * __dadd_rz( c, d ) );

    //double real = ac - bd;
    double const real = __dsub_rz( ac, bd );
    //double imag = ab_cd - ac - bd;
    //double const imag = __dsub_rz( ab_cd, __dmul_rz( ac, bd ) );
    double const imag = __dsub_rz( ab_cd, __dmul_rz( ac, bd ) );
    return make_cuDoubleComplex( real, imag );
}

__global__ void
zgemm( const cuDoubleComplex* __restrict__ A, const cuDoubleComplex* __restrict__ B, cuDoubleComplex* __restrict__ C, const cuDoubleComplex* __restrict__ alpha, const cuComplex* __restrict__ beta, int const dim )
{
    cuDoubleComplex CValue = make_cuDoubleComplex( 0.0, 0.0 );

    int const bidx = blockIdx.x;
    int const bidy = blockIdx.y;
    int const tidx = threadIdx.x;
    int const tidy = threadIdx.y;

    int const row = ( bidx << 4 ) + tidx;
    int const col = ( bidy << 4 ) + tidy;

    __shared__ cuDoubleComplex As[16][17];
    __shared__ cuDoubleComplex Bs[16][17];

    int const aligned_blocks = dim >> 4;
    int const rest_elems = dim - aligned_blocks << 4;

    for ( int block_index = 0; block_index != aligned_blocks; ++block_index )
    {

    }

    for ( int k = 0; k < ( 16 + dim - 1 ) / 16; k++ )
    {
        if ( k * 16 + threadIdx.x < dim && row < dim )
            As[threadIdx.y][threadIdx.x] = A[row * dim + k * 16 + threadIdx.x];
        else
            As[threadIdx.y][threadIdx.x] = 0.0;

        if ( k * 16 + threadIdx.y < Brows && col < dim )
            Bs[threadIdx.y][threadIdx.x] = B[( k * 16 + threadIdx.y ) * dim + col];
        else
            Bs[threadIdx.y][threadIdx.x] = 0.0;

        __syncthreads();

        for ( int n = 0; n < 16; ++n )
            //CValue += cuCml( As[threadIdx.y][n], Bs[n][threadIdx.x] );
            CValue += dc_multiply( As[threadIdx.y][n], Bs[n][threadIdx.x] );

        __syncthreads();
    }

    if ( row < dim && col < dim )
        C[( ( blockIdx.y * blockDim.y + threadIdx.y )*dim ) + ( blockIdx.x * blockDim.x ) + threadIdx.x] = CValue;

}
