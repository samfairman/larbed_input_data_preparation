#include <f/device/device_assert/cuda_assert.hpp>
#include <f/device/device_assert/cublas_assert.hpp>
#include <f/device/device_assert/kernel_assert.hpp>

#include <cuda_runtime.h>

#include <cuComplex.h>
#include <math_functions.h>
#include <cmath>
/*
__global__
void
impl_rotation_diag( double lambda, double kx_scaler, double kx_offset, double ky_scaler, double ky_offset, double rotation, double* tilt, double* gvec, double* cuda_diag, unsigned long const tilt_size, unsigned long max_dim, double cos_rot, double sin_rot )
{
    unsigned long const index = blockDim.x * blockIdx.x + threadIdx.x;
    if ( index >= tilt_size ) return;
    double const theta_x = tilt[index+index];
    double const theta_y = tilt[index+index+1];
    double const tx = (1.0+kx_scaler*10.0) * theta_x + kx_offset;
    double const ty = (1.0+ky_scaler*10.0) * theta_y + ky_offset;
    double const kx_ = sin(tx) / lambda;
    double const ky_ = sin(ty) / lambda;
    double const kx = kx_ * cos_rot + ky_ * sin_rot;
    double const ky = - kx_ * sin_rot + ky_ * cos_rot;

    double gx = 0.0;
    double gy = 0.0;

    for ( unsigned long jndex = 0; jndex < max_dim; ++jndex )
    {
       gx = gvec[jndex+jndex];
       gy = gvec[jndex+jndex+1];
       cuda_diag[jndex*tilt_size+index] = - gx*gx - gy*gy - 2.0 * ( kx*gx + ky*gy );
    }
}
*/
__global__
void
impl_rotation_diag( double lambda, double kx_scaler, double kx_offset, double ky_scaler, double ky_offset, double rotation, double* tilt, double* gvec, double* cuda_diag, unsigned long const tilt_size, unsigned long max_dim, double cos_rot, double sin_rot )
{
    unsigned long const index = blockDim.x * blockIdx.x + threadIdx.x;
    if ( index >= tilt_size ) return;
    double const theta_x = tilt[index+index];
    double const theta_y = tilt[index+index+1];
    double const tx = (1.0+kx_scaler*10.0) * theta_x + kx_offset;
    double const ty = (1.0+ky_scaler*10.0) * theta_y + ky_offset;
    double const kx_ = sin(tx) / lambda;
    double const ky_ = sin(ty) / lambda;
    double const kx = kx_ * cos_rot + ky_ * sin_rot;
    double const ky = - kx_ * sin_rot + ky_ * cos_rot;

    double gx = 0.0;
    double gy = 0.0;

    for ( unsigned long jndex = 0; jndex < max_dim; ++jndex )
    {
       gx = gvec[jndex+jndex];
       gy = gvec[jndex+jndex+1];
       //cuda_diag[jndex*tilt_size+index] = - gx*gx - gy*gy - 2.0 * ( kx*gx + ky*gy );
       cuda_diag[index*max_dim+jndex] = - gx*gx - gy*gy - 2.0 * ( kx*gx + ky*gy );
    }
}

void make_rotation_diag( double lambda, double kx_scaler, double kx_offset, double ky_scaler, double ky_offset, double rotation, double* tilt, double* gvec, double* cuda_diag, unsigned long const tilt_size, unsigned long max_dim )
{
    unsigned long const threads = 64;
    unsigned long const grids = (tilt_size+threads-1)/threads;

	rotation = -1.88 * (1.0+rotation*10.0);
    double const cos_rot = std::cos( rotation );
    double const sin_rot = std::sin( rotation );

    kernel_assert( (impl_rotation_diag<<<grids,threads>>>( lambda, kx_scaler, kx_offset, ky_scaler, ky_offset, rotation, tilt, gvec, cuda_diag, tilt_size, max_dim, cos_rot, sin_rot )) );
    cuda_assert( cudaDeviceSynchronize() );
}

