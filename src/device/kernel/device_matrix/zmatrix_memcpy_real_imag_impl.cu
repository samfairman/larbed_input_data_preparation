#include <f/device/assert/cuda_assert.hpp>
#include <f/device/assert/kernel_assert.hpp>

#include <cuda_runtime.h>

void __global__ 
zmatrix_memcpy_real_imag_kernel( double2* device_data, double* device_real, double* device_imag, unsigned long length )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;

    if ( tx < length )
    {
        (*(device_data+tx)).x = (*(device_real+tx));
        (*(device_data+tx)).y = (*(device_imag+tx));
    }
}

void zmatrix_memcpy_real_imag_impl( double2* device_data, const double* host_real, const double* host_imag, unsigned long length )
{
    double* device_real;
    double* device_imag;

    const unsigned long size_to_malloc = length * sizeof( double );
    cuda_assert( cudaMalloc( (void**)&device_real, size_to_malloc ) );
    cuda_assert( cudaMalloc( (void**)&device_imag, size_to_malloc ) );

    cuda_assert( cudaMemcpy( device_real, host_real, size_to_malloc, cudaMemcpyHostToDevice) );
    cuda_assert( cudaMemcpy( device_imag, host_imag, size_to_malloc, cudaMemcpyHostToDevice) );

    const unsigned long grids = ( length + 1023 ) >> 10;

    kernel_assert( ( zmatrix_memcpy_real_imag_kernel<<< grids, 1024>>>( device_data, device_real, device_imag, length ) ) );

    cuda_assert( cudaFree( device_real ) );
    cuda_assert( cudaFree( device_imag ) );
}

