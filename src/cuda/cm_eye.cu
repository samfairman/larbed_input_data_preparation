#include <cuda_runtime.h>

void __global__
cm_eye_impl( float2* v, unsigned long n )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;
    
    if ( tx < n )
        v[ tx * (n+1) ].x = 1.0;
}

void cm_eye( float2* v, unsigned long n )
{
    const unsigned long grids = ( n + 1023 ) >> 10;
    cm_eye_impl<<<grids, 1024>>>( v, n );    
}

void __global__
d_cm_eye_impl( double2* v, unsigned long n )
{
    const unsigned long tx = threadIdx.x + blockIdx.x * 1024;
    
    if ( tx < n )
        v[ tx * (n+1) ].x = 1.0;
}

void cm_eye( double2* v, unsigned long n )
{
    const unsigned long grids = ( n + 1023 ) >> 10;
    d_cm_eye_impl<<<grids, 1024>>>( v, n );    
}
