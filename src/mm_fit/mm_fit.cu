#include <cstdio>

__global__ void update_device_data_kernel( unsigned long size, unsigned long order, unsigned long* A, unsigned long* B, unsigned long* C, double* residual, double* x )
{
    unsigned long const index = blockDim.x * blockIdx.x + threadIdx.x;
    if ( index >= size ) return;

    unsigned long* a = A + index * 4;
    unsigned long* b = B + index * 4;
    unsigned long* c = C + index * 4;
    double* alpha = x;
    double* beta = x + 4 * order;
    double* gamma = beta + 4 * order;

    double const weigh = c[0] + c[1] + c[2] + c[3] + 1.0;

#if 0
    printf( "size = %ld\n", size );
    printf( "order = %ld\n", order );
    printf( "index = %ld\n", index );
    printf( "weigh = %lf\n", weigh );

    printf( "a[0] = %ld\n", a[0] );
    printf( "a[1] = %ld\n", a[1] );
    printf( "a[2] = %ld\n", a[2] );
    printf( "a[3] = %ld\n", a[3] );

    printf( "b[0] = %ld\n", b[0] );
    printf( "b[1] = %ld\n", b[1] );
    printf( "b[2] = %ld\n", b[2] );
    printf( "b[3] = %ld\n", b[3] );

    printf( "c[0] = %ld\n", c[0] );
    printf( "c[1] = %ld\n", c[1] );
    printf( "c[2] = %ld\n", c[2] );
    printf( "c[3] = %ld\n", c[3] );
#endif
    double ss[6];
    double cc[4];

    for ( unsigned long jndex = 0; jndex < order; ++jndex )
    {
        unsigned long const offset = jndex * 4;
        double* alpha_ = alpha + offset;
        double* beta_ = beta + offset;
        ss[jndex] = 1.0*a[0]*alpha_[0] + a[1]*alpha_[1] + a[2]*alpha_[2] + a[3]*alpha_[3];
        ss[jndex] *= 1.0*b[0]*beta_[0] + b[1]*beta_[1] + b[2]*beta_[2] + b[3]*beta_[3];
#if 0
        printf( "ss[%ld/%ld] = %lf\n", jndex, order, ss[jndex] );
#endif
    }


    cc[0] = -1.0 * c[0]; cc[1] = -1.0 * c[1]; cc[2] = -1.0 * c[2]; cc[3] = -1.0 * c[3];

#if 0
    printf( "cc[0] = %lf\n", cc[0] );
    printf( "cc[1] = %lf\n", cc[1] );
    printf( "cc[2] = %lf\n", cc[2] );
    printf( "cc[3] = %lf\n", cc[3] );
    printf( "\n" );
#endif

    for ( unsigned long kndex = 0; kndex != order; ++kndex )
    {
#if 0
        double cc0 = gamma[kndex] * ss[kndex];
        double cc1 = gamma[kndex+order] * ss[kndex];
        double cc2 = gamma[kndex+order+order] * ss[kndex];
        double cc3 = gamma[kndex+order+order+order] * ss[kndex];
        printf( "kndex %ld\n", kndex );
        printf( "cc0 = %lf\n", cc0 );
        printf( "cc1 = %lf\n", cc1 );
        printf( "cc2 = %lf\n", cc2 );
        printf( "cc3 = %lf\n", cc3 );
        printf( "\n" );
#endif
        cc[0] += gamma[kndex] * ss[kndex];
        cc[1] += gamma[kndex+order] * ss[kndex];
        cc[2] += gamma[kndex+order+order] * ss[kndex];
        cc[3] += gamma[kndex+order+order+order] * ss[kndex];
    }
#if 0
    printf( "cc[0] = %lf\n", cc[0] );
    printf( "cc[1] = %lf\n", cc[1] );
    printf( "cc[2] = %lf\n", cc[2] );
    printf( "cc[3] = %lf\n", cc[3] );
#endif

    residual[index] = ( cc[0] + cc[1] + cc[2] + cc[3] ) / weigh;

}

void update_device_data( unsigned long size, unsigned long order, unsigned long* A, unsigned long* B, unsigned long* C, double* residual, double* x )
{
    update_device_data_kernel<<<1, size>>>( size, order, A, B, C, residual, x );
    cudaDeviceSynchronize();
}
