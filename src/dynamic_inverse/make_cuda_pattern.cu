#include "cuda_pattern.h"

#include <f/device/assert/cuda_assert.hpp>

#include <cassert>

void make_individual_pattern( int gpu_id, individual_pattern* ip, unsigned long dim, unsigned long* ar, double* diag, double* intensity, double* ug_thickness )
{
    assert( gpu_id >= 0 );
    assert( (*ip).dim = 0 );
    assert( !(*ip).ug_thickness );
    assert( !(*ip).ar );
    assert( !(*ip).diag );
    assert( !(*ip).I_exp );
    assert( !(*ip).I_sim );
    assert( !(*ip).A );
    assert( !(*ip).S );
    assert( !(*ip).S0 );
    assert( !(*ip).S1 );
    assert( !(*ip).S2 );
    assert( !(*ip).S3 );
    assert( !(*ip).S4 );
    assert( !(*ip).S5 );
    assert( !(*ip).S6 );
    assert( !(*ip).S7 );
    assert( !(*ip).S9 );
    assert( !(*ip).S10 );
    assert( ip );
    assert( dim );
    assert( ar );
    assert( diag );
    assert( intensity );
    assert( ug_thickness );

    (*ip).ug_thickness = ug_thickness;
    (*ip).dim = dim;

    cuda_assert( cudaSetDevice(gpu_index) );

    cuda_assert( cudaMalloc( &( (*ip).ar ), sizeof(unsigned long) * dim * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).diag ), sizeof(double) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).I_exp ), sizeof(double) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).I_sim ), sizeof(double) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).A ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S0 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S1 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S2 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S3 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S4 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S5 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S6 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S7 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S8 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S9 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*ip).S10 ), sizeof(double2) * dim ) );

    //copy ar
    cuda_assert( cudaMemcpy( (*ip).ar, ar, sizeof(unsigned long)*dim*dim, cudaMemcpyHostToDevice ) );
    //copy diag
    cuda_assert( cudaMemcpy( (*ip).diag, diag, sizeof(double)*dim, cudaMemcpyHostToDevice ) );
    //copy intensity
    cuda_assert( cudaMemcpy( (*ip).I_exp, intensity, sizeof(double)*dim, cudaMemcpyHostToDevice ) );
}

void make_individual_pattern( individual_pattern* ip )
{
    (*ip).dim = 0;
    (*ip).ug_thickness = 0;
    (*ip).ar = 0;
    (*ip).diag = 0;
    (*ip).I_exp = 0;
    (*ip).I_sim = 0;
    (*ip).A = 0;
    (*ip).S = 0;
    (*ip).S0 = 0;
    (*ip).S1 = 0;
    (*ip).S2 = 0;
    (*ip).S3 = 0;
    (*ip).S4 = 0;
    (*ip).S5 = 0;
    (*ip).S6 = 0;
    (*ip).S7 = 0;
    (*ip).S8 = 0;
    (*ip).S9 = 0;
    (*ip).S10 = 0;
}

void make_pattern_on_gpu( pattern_on_gpu* pog, int const gpu_id_, int const pattern_id_start_, int const pattern_id_end_  )
{
    assert( pog );
    assert( pattern_id_end_ > pattern_id_start_ );

    unsigned long const total_ip = pattern_id_end_ - pattern_id_start_;

    (*pog).gpu_id = gpu_id_;
    (*pog).pattern_id_start = pattern_id_start_;
    (*pog).pattern_id_end = pattern_id_end_;

    (*pog).ip = new individual_pattern[total_ip];
    for ( unsigned long index = 0; index != total_ip; ++index )
        make_individual_pattern( (*pog).ip + index );

    (*pog).ip_cpu = 0;
    (*pog).ug_thickness = 0;
}

/**
  * n           --      total_tilt
  * ug_size     --      reflections  
  */
cuda_pattern* make_cuda_pattern( unsigned long n, unsigned long ug_size; )
{
    assert( n );
    assert( ug_size );

    //alloc patterns on gpu
    int total_gpus_avaliable = 0;
    cuda_assert( cudaGetDeviceCount(&total_gpus_avaliable) );
    assert( total_gpus_avaliable > 0 );
    int const patterns_per_gpu = ( n + total_gpus_avaliable - 1 ) / total_gpus_avaliable;  // --> on first M-1 gpu
    int const patterns_on_last_gpu = n - patterns_per_gpu * ( total_gpus_avaliable - 1 );  // --> on last gpu

    //cuda_pattern
    cuda_pattern* cp = new cuda_pattern;
    (*cp).total_ug_size = ug_size;
    (*cp).total_cuda_pattern = n;
    (*cp).total_gpu = total_gpus_avaliable;
    (*cp).pog = new pattern_on_gpu[total_gpus_avaliable];

    for ( int index = 0; index != total_gpus_avaliable; ++index )
    {
        int const start_pattern = index * patterns_per_gpu;
        int const end_pattern = start_pattern+patterns_per_gpu > n ? n : start_pattern+patterns_per_gpu;

        make_pattern_on_gpu( (*cp).pog+index, index, start_pattern, end_pattern );
    }

    return cp;

/*
    
    //pattern on gpu
    for ( int index = 0; index != total_gpus_avaliable - 1; ++index ) //will skip if only one gpu
    {
        ((*cp).pog)[index].gpu_id = index;
        ((*cp).pog)[index].pattern_id_start = index * pattern_on_gpu;
        ((*cp).pog)[index].pattern_id_end = ( index + 1 ) * pattern_on_gpu;
        ((*cp).pog)[index].ip = new individual_pattern[patterns_per_gpu];


        //!!GPU CODE
        cuda_assert( cudaSetDevice(index) );
        cuda_assert( cudaMalloc( &( ((*cp).pog)[index].ug_thickness ), sizeof(double) * ( (*cp).total_ug_size * 2 + 1 ) ) );

        for ( unsigned long jndex = 0; jndex != patterns_per_gpu; ++jndex )
            (((*cp).pog)[index].ip)[jndex] = ((*cp).pog)[index].ug_thickness;

        //ip_gpu set to null
        ((*cp).pog)[index].ip_gpu = 0;
    }
    
    if ( patterns_on_last_gpu > 0 ) //the last gpu
    {
        int const index = total_gpus_avaliable - 1;
        ((*cp).pog)[index].gpu_id = index;
        ((*cp).pog)[index].pattern_id_start = index * pattern_on_gpu;
        ((*cp).pog)[index].pattern_id_end = ( index + 1 ) * pattern_on_gpu;
        ((*cp).pog)[index].ip = new individual_pattern[patterns_on_last_gpu];

        //!!GPU CODE
        cuda_assert( cudaSetDevice(index) );
        cuda_assert( cudaMalloc( &( ((*cp).pog)[index].ug_thickness ), sizeof(double) * ( (*cp).total_ug_size * 2 + 1 ) ) );

        for ( unsigned long jndex = 0; jndex != patterns_on_last_gpu; ++jndex )
            (((*cp).pog)[index].ip)[jndex] = ((*cp).pog)[index].ug_thickness;

        //ip_gpu set to null
        ((*cp).pog)[index].ip_gpu = 0;
    }

    retun cp;
*/
}

