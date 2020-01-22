#include "./cuda_include.h"

void set_device( int id )
{
    int current_id;
    cuda_assert( cudaGetDevice( &current_id ) );
    if ( current_id != id )
        cuda_assert( cudaSetDevice( id ) );
}

void cuda_allocate( void** p, unsigned long n )
{
    cuda_assert( cudaMalloc( p, n ) );
    cuda_assert( cudaMemset( *p, 0, n ) );
}

void cuda_deallocate( void* p )
{
    cuda_assert( cudaFree( p ) );
}

void cuda_memcopy_host_to_device( const void* src, unsigned long n, void* dst )
{
    cuda_assert( cudaMemcpy( dst, src, n, cudaMemcpyHostToDevice  ) );
}

void cuda_memcopy_device_to_host( const void* src, unsigned long n, void* dst )
{
    cuda_assert( cudaMemcpy( dst, src, n, cudaMemcpyDeviceToHost  ) );
}

double dot( double* x_begin, double* x_end, double* y_begin )
{
    cublasHandle_t handle;
    cublas_assert( cublasCreate(&handle) );
    unsigned long n = x_end - x_begin;
    double ans;
    cublas_assert( cublasDdot( handle, n, x_begin, 1, y_begin, 1, &ans ) );
    cublas_assert( cublasDestroy(handle) );
    return ans;
}

