#include <f/device/device_assert/cuda_assert.hpp>
#include <f/device/device_assert/cublas_assert.hpp>
#include <f/device/device_assert/kernel_assert.hpp>

#include <cuda_runtime.h>
#include <cublas_v2.h>

#include <cuComplex.h>
#include <math_functions.h>

__global__ void Dznrm2( unsigned long m, double2 *dA, double *dxnorm )// Dznrm2<<<1,128>>>(...)
{
    unsigned long i = threadIdx.x;

    __shared__ double x[128];

    double lsum = 0.0;

    for( unsigned long j = i; j < m; j += 128 ) 
    {
        double const re = dA[j].x;
        double const im = dA[j].y;
        lsum += re*re + im*im;
    }

    x[i] = lsum;

    __syncthreads();

    if ( i <   64 ) { x[i] += x[i+  64]; }  __syncthreads();
    if ( i <   32 ) { x[i] += x[i+  32]; }  __syncthreads();
    if ( i <   16 ) { x[i] += x[i+  16]; }  __syncthreads();
    if ( i <    8 ) { x[i] += x[i+   8]; }  __syncthreads();
    if ( i <    4 ) { x[i] += x[i+   4]; }  __syncthreads();
    if ( i <    2 ) { x[i] += x[i+   2]; }  __syncthreads();
    if ( i <    1 ) { x[i] += x[i+   1]; }  __syncthreads();

    if ( i == 0 ) *dxnorm = sqrt(x[0]);
}

__device__ void device_Dznrm2( unsigned long m, double2 *dA, double *dxnorm )
{
    double ans = 0.0;
    for ( unsigned long index = 0; index != m; ++index )
    {
        double const real = dA[index].x;
        double const imag = dA[index].y;
        ans += real*real + imag*imag;
    }

    dxnorm[0] = ans;
}

__global__ void Dasum( unsigned long m, double2 *dA, double *dxnorm )
{
    unsigned long i = threadIdx.x;

    __shared__ double x[128];

    double lsum = 0.0;

    for( unsigned long j = i; j < m; j += 128 ) 
    {
        double const re = dA[j].x;
        double const im = dA[j].y;
        lsum += sqrt(re*re + im*im);
    }

    x[i] = lsum;

    __syncthreads();

    if ( i <   64 ) { x[i] += x[i+  64]; }  __syncthreads();
    if ( i <   32 ) { x[i] += x[i+  32]; }  __syncthreads();
    if ( i <   16 ) { x[i] += x[i+  16]; }  __syncthreads();
    if ( i <    8 ) { x[i] += x[i+   8]; }  __syncthreads();
    if ( i <    4 ) { x[i] += x[i+   4]; }  __syncthreads();
    if ( i <    2 ) { x[i] += x[i+   2]; }  __syncthreads();
    if ( i <    1 ) { x[i] += x[i+   1]; }  __syncthreads();

    if ( i == 0 ) *dxnorm = x[0];
}

//should call with Zscale<<<1, 128>>>(...);
__global__ void Zscal( unsigned long m, double real, double2* dA )
{
    const int i = threadIdx.x;

    for( unsigned long j = i; j < m; j += 128 ) 
    {
        dA[j].x *= real;
        dA[j].y *= real;
    }
}

__device__ void device_Zscal( unsigned long m, double real, double2* dA )
{
    //for ( unsigned long index = 0; index != m; ++index ) <<-- WHY this one doesnot work????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    for ( unsigned long index = 0; index < m; ++index )
    {
        dA[index].x *= real;
        dA[index].y *= real;
    }
}

    //TODO: optimization
    __global__ //<<<((dim+15)/16,(dim+15)/16), (16,16)>>>
    void Zgemm( double2* P, double2* M, double2* N, unsigned long dim, double alpha )
    {
        typedef double              value_type;
        typedef double2             complex_type;
        typedef unsigned long       size_type;

        __shared__ value_type _M[16][17];
        __shared__ value_type _m[16][17];
        __shared__ value_type _N[16][17];
        __shared__ value_type _n[16][17];

        const size_type bx = blockIdx.x;
        const size_type by = blockIdx.y;
        const size_type tx = threadIdx.x;
        const size_type ty = threadIdx.y;
        const size_type row = by * 16 + ty;
        const size_type col = bx * 16 + tx;
        const size_type iter_n = (dim+15)/16;

        value_type R = 0.0;
        value_type I = 0.0;

        for ( size_type i = 0; i != iter_n; ++i )
        {
            if ( i * 16 + tx < dim && row < dim )
            {
                _M[ty][tx] = (*( M + row * dim + i * 16 + tx )).x;
                _m[ty][tx] = (*( M + row * dim + i * 16 + tx )).y;
            }
            else
            {
                _M[ty][tx] = 0.0;
                _m[ty][tx] = 0.0;
            }

            if ( i * 16 + ty < dim && col < dim )
            {
                _N[ty][tx] = (*( N + ( i * 16 + ty ) * dim + col )).x;
                _n[ty][tx] = (*( N + ( i * 16 + ty ) * dim + col )).y;
            }
            else
            {
                _N[ty][tx] = 0.0;
                _n[ty][tx] = 0.0;
            }

            __syncthreads();

            #pragma unroll
            for ( size_type j = 0; j != 16; ++j )
            {
                R += _M[ty][j] * _N[j][tx] - _m[ty][j] * _n[j][tx];
                I += _M[ty][j] * _n[j][tx] + _m[ty][j] * _N[j][tx];
            }
            __syncthreads();
        }

        if ( row < dim && col < dim )
        {
            (*( P + row * dim + col )).x = alpha * R;
            (*( P + row * dim + col )).y = alpha * I;
        }
    }

__global__ void //<<<1,128>>>
Zcopy( unsigned long dims, double2* src, double2* dst )
{
    unsigned long const i = threadIdx.x;

    for( unsigned long j = i; j < dims; j += 128 ) 
    {
        (*(dst+j)).x = (*(src+j)).x;
        (*(dst+j)).y = (*(src+j)).y;
    }
}

__device__ void
device_Zcopy( unsigned long dims, double2* src, double2* dst )
{
    for ( unsigned long index = 0; index < dims; ++index )
    {
        dst[index].x = src[index].x;
        dst[index].y = src[index].y;
    }
}

__global__ void//<<<1, 128>>>
Zaxpy( unsigned long dims, double real, double imag, double2* dst, double2* src ) // dst += (real,imag) * src
{
    unsigned long const i = threadIdx.x;
    double R = 0.0;
    double I = 0.0;

    for( unsigned long j = i; j < dims; j += 128 ) 
    {
        R = (*(src+j)).x;
        I = (*(src+j)).y;

        (*(dst+j)).x += real * R - imag * I;
        (*(dst+j)).y += real * I + imag * R;
    }
}

__device__ void//<<<1, 128>>>
device_Zaxpy( unsigned long dims, double real, double imag, double2* dst, double2* src ) // dst += (real,imag) * src
{
    for ( unsigned long index = 0; index < dims; ++index )
    {
        double const R = src[index].x;
        double const I = src[index].y;
        dst[index].x = real * R - imag * I;
        dst[index].y = real * I + imag * R;
    }
}
#if 0
__global__ void
compose_a( double* ug, unsigned long* ar, double* diag, double thickness, double2* a, unsigned long dim )
{
    int const row_index = threadIdx.x;

    for ( unsigned long col_index = 0; col_index != dim; ++col_index )
    {
        unsigned long a_offset = row_index * dim + col_index;
        unsigned long const ug_index = *(ar+a_offset);
        *(a+a_offset) = make_cuDoubleComplex( -thickness * (*(ug+ug_index+ug_index+1)), thickness *( *(ug+ug_index+ug_index)) );
    }

    *(a+row_index*dim+row_index) = make_cuDoubleComplex( 0.0, thickness *( *(diag+row_index) ) );
}
#endif
#if 0
__device__ void
device_compose_a( double* ug, unsigned long* ar, double* diag, double thickness, double2* a, unsigned long dim, double alpha, double beta, double gamma, double* beams )
{
    thickness *= 100.0;
    for ( unsigned long row_index = 0; row_index != dim; ++row_index )
    {
        for ( unsigned long col_index = 0; col_index != dim; ++col_index )
        {
            unsigned long a_offset = row_index * dim + col_index;
            unsigned long const ug_index = *(ar+a_offset);
            *(a+a_offset) = make_cuDoubleComplex( -thickness * (*(ug+ug_index+ug_index+1)), thickness *( *(ug+ug_index+ug_index)) );
        }
        unsigned long const beams_index = ar[row_index*dim];
        double const kx = beams[beams_index*10+1];
        double const ky = beams[beams_index*10+2];

        *(a+row_index*dim+row_index) = make_cuDoubleComplex( 0.0, thickness *( *(diag+row_index) + kx*alpha + ky*beta + gamma ) );
    }
}
#endif
__device__ void
device_compose_a( double* ug, unsigned long* ar, double* diag, double thickness, double2* a, unsigned long dim, double alpha, double beta, double* beams )
{
    thickness *= 100.0;
    for ( unsigned long row_index = 0; row_index != dim; ++row_index )
    {
        for ( unsigned long col_index = 0; col_index != dim; ++col_index )
        {
            unsigned long a_offset = row_index * dim + col_index;
            unsigned long const ug_index = *(ar+a_offset);
            *(a+a_offset) = make_cuDoubleComplex( -thickness * (*(ug+ug_index+ug_index+1)), thickness *( *(ug+ug_index+ug_index)) );
        }
        unsigned long const beams_index = ar[row_index*dim];
        double const kx = beams[beams_index*10+1];
        double const ky = beams[beams_index*10+2];

        *(a+row_index*dim+row_index) = make_cuDoubleComplex( 0.0, thickness * ( *(diag+row_index) + kx*alpha + ky*beta ) );
    }
}

//TODO: optimization
#if 0
Comment:
            When working with original global kernel 'extract_intensity_diff_with_offset_zigmoid', the generated residuals( all kinds ) are
            a little bit smaller(1.0e-6 order) than the new device routine 'device_extract_intensity_diff_with_offset_zigmoid'
#endif
__global__ void
extract_intensity_diff_with_offset_zigmoid( double2* s, double* I_exp, double* I_diff, double* I_zigmoid, unsigned long dim, unsigned long column_index, double ac_offset, double dc_offset, double c )
{
    int const I_offset = threadIdx.x;
    int const S_offset = column_index + threadIdx.x * dim;
    double const norm = cuCabs(*(s+S_offset));

    double const val = *(I_exp+I_offset);
    double const df = val - norm * norm * ac_offset - dc_offset;
    *(I_diff+I_offset) = df;
    *(I_zigmoid+I_offset) = df / ( 1.0 + exp( 12.56637061435917295384*c*val ) );
}

__device__ void
device_extract_intensity_diff_with_offset_zigmoid( double2* s, double* I_exp, double* I_diff, double* I_zigmoid, unsigned long dim, unsigned long column_index, double ac_offset, double dc_offset, double c )
{
    for ( unsigned long index = 0; index < dim; ++index )
    {
        unsigned long const I_offset = index;
        unsigned long const S_offset = column_index + index * dim;
        double const real = s[S_offset].x;
        double const imag = s[S_offset].y;
        double const norm = real*real + imag*imag;
        double const val  = I_exp[I_offset];
        double const df = val - norm * ac_offset - dc_offset;
        I_diff[I_offset] = df;
        I_zigmoid[I_offset] = df / ( 1.0 + exp( 12.56637061435917295384*c*val ) );
    }
}

//TODO: optimization
__global__ void
sum_diag( double2* a, unsigned long dim, double real, double imag )
{
    int const index = threadIdx.x;
    int const offset = index * dim + index;
    *(a+offset) = make_cuDoubleComplex( cuCreal(*(a+offset))+real, cuCimag(*(a+offset))+imag );
}

__device__ void
device_sum_diag( double2* a, unsigned long dim, double real, double imag )
{
    for ( unsigned long index = 0; index < dim; ++index )
    {
        unsigned long const offset = index * dim + index;
        a[offset].x += real;
        a[offset].y += imag;
    }
}

/*
 * Input/Output:
 *
 ** ug[M]
 *  ar[n][n]
 *  diag[n]         ==>>    I_diff[n]
 ** thickness
 *  dim -- n
 *  I_exp[n]
 ** column_index
 *
 *  cache:
 *  a_[n][n]    -- p2p3
 *  a^2_[n][n]  -- s
 *  a^3_[n][n]  -- s_
 *  P1[n][n]
 *  P2[n][n]
 *  P3[n][n]
 *
 * 1) compose A
 * 2) scale to A_
 * 3) compute A_^2 A_^3
 * 4) compute (P1) (P2) (P3)
 * 5) square back
 * 6) extract one column
 */
__global__ void
make_individual_pattern_intensity_diff( double* cuda_ug, unsigned long* cuda_ar, double* cuda_diag, double thickness, unsigned long* cuda_dim, double* cuda_I_exp, double* cuda_I_diff, unsigned long column_index, double2* cuda_cache, unsigned long max_dim, unsigned long tilt_size, double c, double * cuda_I_zigmoid, double* beams, double* kt_factor )
{
    unsigned long const tilt_index = blockDim.x * blockIdx.x + threadIdx.x;

    if ( tilt_index >= tilt_size ) return;

    unsigned long const dim = *(cuda_dim + tilt_index);
    double* ug = cuda_ug;
    unsigned long* ar = cuda_ar + tilt_index * max_dim * max_dim;
    double* diag = cuda_diag + tilt_index * max_dim;
    double* I_exp = cuda_I_exp + tilt_index * max_dim;
    double* I_diff = cuda_I_diff + tilt_index * max_dim;
    double* I_zigmoid = cuda_I_zigmoid + tilt_index * max_dim;
    double2* cache = cuda_cache + 6 * tilt_index * max_dim * max_dim;

    unsigned long dimdim = dim*dim;

    //cache should be of size 6*N^2
    double2* a_ = cache;
    double2* aa_ = a_ + dimdim;
    double2* aaa_ = aa_ + dimdim;
    double2* p1 = aaa_ + dimdim;
    double2* p2 = p1 + dimdim;
    double2* p3 = p2 + dimdim;

    //reuse memory in latter steps, when a_, aa_ and aaa_ are idle
    //double2* p2p3 = a_;
    double2* p2p3 = aaa_;
    double2* s = aa_;
    double2* s_ = aaa_;

    //1)
    //kernel_assert( (compose_a<<<1, dim>>>( ug, ar, diag, thickness, a_, dim )) );
    //cuda_assert( cudaDeviceSynchronize() );
    //device_compose_a( ug, ar, diag, thickness, a_, dim );

    //double const alpha = kt_factor[tilt_index*3];
    //double const beta = kt_factor[tilt_index*3+1];
    //double const gamma = kt_factor[tilt_index*3+2];
    //device_compose_a( ug, ar, diag, thickness, a_, dim, alpha, beta, gamma, beams );

    double const alpha = kt_factor[tilt_index*2];
    double const beta = kt_factor[tilt_index*2+1];
    device_compose_a( ug, ar, diag, thickness, a_, dim, alpha, beta, beams );

    //2)
    //TODO
    double* the_norm = (double*)aa_;
    //kernel_assert( (Dznrm2<<<1,128>>>( dimdim, a_, the_norm )) );
    ////kernel_assert( (Dasum<<<1,128>>>( dimdim, a_, the_norm )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Dznrm2( dimdim, a_, the_norm );

    //double const ratio = (*the_norm) * 53.71920351148152;
    double const ratio = (*the_norm) / 5.371920351148152;
    unsigned long const scaler = ratio < 1.0 ? 0 : ceil(log2(ratio));
    unsigned long const scaling_factor =  1 << scaler;
    double const scale = scaling_factor;
    //kernel_assert( (Zscal<<<1, 128>>>( dimdim, 1.0/scale, a_ )) );    //a_ /= scale
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zscal( dimdim, 1.0/scale, a_ );

    //3)
    dim3 const mm_grids( (dim+15)/16, (dim+15)/16 );
    dim3 const mm_threads( 16, 16 );
    kernel_assert( (Zgemm<<<mm_grids, mm_threads>>>( aa_, a_, a_, dim, 1.0 )) );
    cuda_assert( cudaDeviceSynchronize() );
    kernel_assert( (Zgemm<<<mm_grids, mm_threads>>>( aaa_, aa_, a_, dim, 1.0 )) );
    cuda_assert( cudaDeviceSynchronize() );

    //4)
    /*
     * Maple:
     *  Digits := 25
     *  evalf(solve(_Z^9+9*_Z^8+72*_Z^7+504*_Z^6+3024*_Z^5+15120*_Z^4+60480*_Z^3+181440*_Z^2+362880*_Z+362880 = 0))
     * Returns:
     *  2.697333461536989227389605+5.184162062649414177834087*I,     //c1
     *  -.3810698456631129990312942+4.384644533145397950369203*I,    //c2
     *  -2.110839800302654737498705+3.089910928725500922777702*I,    //c3
     *  -3.038648072936697089212469+1.586801195758838328803868*I,    //c4
     *  -3.333551485269048803294274,                                 //c5
     *  -3.038648072936697089212469-1.586801195758838328803868*I,    //c6
     *  -2.110839800302654737498705-3.089910928725500922777702*I,    //c7
     *  -.3810698456631129990312942-4.384644533145397950369203*I,    //c8
     *  2.697333461536989227389605-5.184162062649414177834087*I      //c9
     *
     *  expand((x-c1)*(x-c2)*(x-c3))  >> p1                                                                                                   (                     p1_c                             )
     *      x^3-.205423815571221490859606*x^2-(12.65871752452031305098099*I)*x^2-58.21460179641193947200471*x-(3.189848964212376356715960*I)*x-19.71085376106750328141397+94.20645646169128946503649*I
     *
     *  expand((x-c4)*(x-c5)*(x-c6))  >> p2   (         p2_c            )
     *      x^3+9.410847631142442981719212*x^2+39.17363072664900708597702-6.123261017392618755198919*10^(-24)*I+32.01029973951970099352671*x+(4.*10^(-24)*I)*x
     *
     *  expand((x-c7)*(x-c8)*(x-c9))  >> p3                                                                                                  (                         p3_c                         )
     *      x^3-.205423815571221490859601*x^2+(12.65871752452031305098099*I)*x^2-58.21460179641193947200470*x+(3.18984896421237635671600*I)*x-19.71085376106750328141404-94.20645646169128946503646*I
     *
     *  expand((x-c1)*(x-c2)*(x-c3)*(x-c4)*(x-c5)*(x-c6)*(x-c7)*(x-c8)*(x-c9))
     *      3.628800000000000000000003*10^5-1.365022562699469279472268*10^(-19)*I+3.628800000000000000000003*10^5*x+x^9+9.00000000000000000000000*x^8+72.00000000000000000000006*x^7+503.9999999999999999999995*x^6+3024.000000000000000000002*x^5+15120.00000000000000000000*x^4+60479.99999999999999999995*x^3+1.814400000000000000000001*10^5*x^2-(5.*10^(-22)*I)*x^6-(1.*10^(-20)*I)*x^4-(1.0*10^(-19)*I)*x^3+(2.*10^(-24)*I)*x^8-(3.0*10^(-19)*I)*x^2-(7.*10^(-21)*I)*x^5-(4.*10^(-19)*I)*x+(2.*10^(-23)*I)*x^7
     */
    //4 - p1)
    //kernel_assert( (Zcopy<<<1,128>>>( dimdim, aaa_, p1 )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zcopy( dimdim, aaa_, p1 );
    //kernel_assert( (Zaxpy<<<1,128>>>( dimdim, -0.205423815571221490859606, -12.65871752452031305098099, p1, aa_ )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zaxpy( dimdim, -0.205423815571221490859606, -12.65871752452031305098099, p1, aa_ );
    //kernel_assert( (Zaxpy<<<1,128>>>( dimdim, -58.21460179641193947200471, -3.189848964212376356715960, p1, a_ )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zaxpy( dimdim, -58.21460179641193947200471, -3.189848964212376356715960, p1, a_ );
    //kernel_assert( (sum_diag<<<1,dim>>>( p1, dim, -19.71085376106750328141397, 94.20645646169128946503649 )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_sum_diag( p1, dim, -19.71085376106750328141397, 94.20645646169128946503649 );

    //4 - p2)
    //kernel_assert( (Zcopy<<<1,128>>>( dimdim, aaa_, p2 )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zcopy( dimdim, aaa_, p2 );
    //kernel_assert( (Zaxpy<<<1,128>>>( dimdim, 9.410847631142442981719212, 0.0, p2, aa_ )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zaxpy( dimdim, 9.410847631142442981719212, 0.0, p2, aa_ );
    //kernel_assert( (Zaxpy<<<1,128>>>( dimdim, 32.01029973951970099352671, 0.0, p2, a_ )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zaxpy( dimdim, 32.01029973951970099352671, 0.0, p2, a_ );
    //kernel_assert( (sum_diag<<<1,dim>>>( p2, dim, 39.17363072664900708597702, 0.0  )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_sum_diag( p2, dim, 39.17363072664900708597702, 0.0 );

    //4 - p3)
    //kernel_assert( (Zcopy<<<1,128>>>( dimdim, aaa_, p3 )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zcopy( dimdim, aaa_, p3 );
    //kernel_assert( (Zaxpy<<<1,128>>>( dimdim, -0.205423815571221490859601, 12.65871752452031305098099, p3, aa_ )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zaxpy( dimdim, -0.205423815571221490859601, 12.65871752452031305098099, p3, aa_ );
    //kernel_assert( (Zaxpy<<<1,128>>>( dimdim, -58.21460179641193947200470, 3.18984896421237635671600, p3, a_ )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_Zaxpy( dimdim, -58.21460179641193947200470, 3.18984896421237635671600, p3, a_ );
    //kernel_assert( (sum_diag<<<1,dim>>>( p3, dim, -19.71085376106750328141404, -94.20645646169128946503646 )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_sum_diag( p3, dim, -19.71085376106750328141404, -94.20645646169128946503646 );

    //4 - s)
    kernel_assert( (Zgemm<<<mm_grids, mm_threads>>>( p2p3, p2, p3, dim, 0.0016600397351866578333 )) );
    cuda_assert( cudaDeviceSynchronize() );
    kernel_assert( (Zgemm<<<mm_grids, mm_threads>>>( s, p1, p2p3, dim, 0.0016600397351866578333 )) );
    cuda_assert( cudaDeviceSynchronize() );

    //5)
    if ( scaler != 0 )
    {
        for ( unsigned long index = 0; index != scaler; ++index )
        {
            kernel_assert( (Zgemm<<<mm_grids, mm_threads>>>( s_, s, s, dim, 1.0 )) );
            cuda_assert( cudaDeviceSynchronize() );
            double2* tmp = s_;
            s_ = s;
            s = tmp;
        }
    }

    //6)
    double const ac_offset = cuda_ug[0];
    double const dc_offset = cuda_ug[1];
    //kernel_assert( (extract_intensity_diff_with_offset_zigmoid<<<1,dim>>>( s, I_exp, I_diff, I_zigmoid, dim, column_index, ac_offset, dc_offset, c )) );
    //cuda_assert( cudaDeviceSynchronize() );
    device_extract_intensity_diff_with_offset_zigmoid( s, I_exp, I_diff, I_zigmoid, dim, column_index, ac_offset, dc_offset, c );
}

void make_pattern_intensity_diff( double* cuda_ug, unsigned long* cuda_ar, double* cuda_diag, double thickness, unsigned long* cuda_dim, double* cuda_I_exp, double* cuda_I_diff, unsigned long column_index, double2* cuda_cache, unsigned long tilt_size, unsigned long max_dim, double c, double* cuda_I_zigmoid, double* beams, double* kt_factor )
{
    //unsigned long const threads = 64;
    //unsigned long const threads = 128;
    unsigned long const threads = 256;
    unsigned long const grids = (tilt_size + threads - 1)/threads;

    kernel_assert( ( make_individual_pattern_intensity_diff<<<grids, threads>>>( cuda_ug, cuda_ar, cuda_diag, thickness, cuda_dim, cuda_I_exp, cuda_I_diff, column_index, cuda_cache, max_dim, tilt_size, c, cuda_I_zigmoid, beams, kt_factor ) ) );
    //cuda_assert( cudaDeviceSynchronize() );
}

