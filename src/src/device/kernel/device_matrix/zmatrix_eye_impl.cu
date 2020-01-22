#include <cuda_runtime.h>

#include <f/device/assert/kernel_assert.hpp>

/*
void __global__
zmatrix_eye_kernel( double2* data, unsigned long const n )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;

    if ( tx < n )
        (*(data+tx*n+tx)).x = 1.0;
}

void zmatrix_eye_impl( double2* data, unsigned long const n )
{
    const unsigned long grids = ( n + 1023 ) >> 10;

    kernel_assert( (zmatrix_eye_kernel<<<grids, 1024>>>( data, n ) ) );
}
*/

void __global__
zmatrix_eye_kernel( double2* data, unsigned long const n, double val )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;

    if ( tx < n )
        (*(data+tx*n+tx)).x = val;
}

void zmatrix_eye_impl( double2* data, unsigned long const n, double val )
{
    const unsigned long grids = ( n + 1023 ) >> 10;

    kernel_assert( (zmatrix_eye_kernel<<<grids, 1024>>>( data, n, val ) ) );
}

void zmatrix_eye_impl( double2* data, unsigned long const n )
{
    zmatrix_eye_impl( data, n, 1.0 );
}

void __global__
zmatrix_eye_kernel( double2* data, unsigned long const n, double real, double imag )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;

    if ( tx < n )
    {
        (*(data+tx*n+tx)).x = real;
        (*(data+tx*n+tx)).x = imag;
    }
}

void zmatrix_eye_impl( double2* data, unsigned long const n, double real, double imag )
{
    const unsigned long grids = ( n + 1023 ) >> 10;

    kernel_assert( (zmatrix_eye_kernel<<<grids, 1024>>>( data, n, real, imag ) ) );
}

