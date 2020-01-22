#include <f/device/assert/cuda_assert.hpp>

#include <cuda.h>
#include <cuda_runtime.h>
#include <cuComplex.h>

#include <cassert>

struct cuda_pattern;

cuda_pattern* make_cuda_pattern( unsigned long n, unsigned long ug_size );
void release_cuda_pattern( cuda_pattern* cp );
void cuda_pattern_register_entry( cuda_pattern* cp, unsigned long index, unsigned long dim, unsigned long* ar, double* diag, double* intensity );
void cuda_pattern_update_ug_thickness( cuda_pattern* cp, double* p );
double cuda_pattern_make_residual( cuda_pattern* cp );
double cuda_pattern_make_residual( cuda_pattern* cp );

//device
struct individual_pattern
{
    //all gpu
    unsigned long dim;
    double* ug_thickness; //ug_size * 2 + 1
    unsigned long* ar;
    double* diag;
    double* I_exp;
    double* I_sim;
    double2* A;
    double2* S;
    double2* S0;
    double2* S1;
    double2* S2;
    double2* S3;
    double2* S4;
    double2* S5;
    double2* S6;
    double2* S7;
    double2* S8;
    double2* S9;
    double2* S10;
};

//host
struct pattern_on_gpu
{
    int gpu_id;
    int pattern_id_start;
    int pattern_id_end;
    individual_pattern* ip; //cpu -- > gpu ...

    double* ug_thickness; //gpu
};

//host
struct cuda_pattern
{
    unsigned long total_ug_size; //--> count as complex type
    unsigned long total_cuda_pattern;
    int total_gpu;
    pattern_on_gpu* pog; //cpu
};

void cuda_pattern_update_ug_thickness( cuda_pattern* cp, double* p )
{
    //copy to gpu
    for ( int index = 0; index != (*cp).total_gpu; ++index )
    {
        //!!GPU CODE
        cuda_assert( cudaSetDevice(index) );
        cuda_assert( cudaMemcpy( ((*cp).pog)[index].ug_thickness, p, sizeof(unsigned long)*dim*dim, cudaMemcpyHostToDevice ) );

    }
}

void release_cuda_pattern( cuda_pattern* cp )
{
    for ( int index = 0; index != (*cp).total_gpu; ++index )
    {
        pattern_on_gpu* the_pog = (*cp).pog + index; 
        
        //switch to gpu
        //!!GPU CODE
        cuda_assert( cudaSetDevice((*the_pog).gpu_id) );
        cuda_assert( cudaFree( (*the_pog).ug_thickness ) );
        (*the_pog).ug_thickness = 0;

        int const total_individual_pattern = (*the_pog).pattern_id_end - (*the_pog).pattern_id.start;

        for ( int jndex = 0; jndex != total_individual_pattern; ++jndex )
        {
            individual_pattern* the_individual_pattern = (*the_pog).ip + jndex;

            //cuda_assert( cudaFree( (*the_individual_pattern).ug_thickness ) );
            cuda_assert( cudaFree( (*the_individual_pattern).ar ) );
            cuda_assert( cudaFree( (*the_individual_pattern).diag ) );
            cuda_assert( cudaFree( (*the_individual_pattern).I_exp ) );
            cuda_assert( cudaFree( (*the_individual_pattern).I_sim ) );
            cuda_assert( cudaFree( (*the_individual_pattern).A ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S0 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S1 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S2 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S3 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S4 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S5 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S6 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S7 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S8 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S9 ) );
            cuda_assert( cudaFree( (*the_individual_pattern).S10 ) );

            //(*the_individual_pattern).ug_thickness = 0;
            (*the_individual_pattern).ar = 0;
            (*the_individual_pattern).diag = 0;
            (*the_individual_pattern).I_exp = 0;
            (*the_individual_pattern).I_sim = 0;
            (*the_individual_pattern).A = 0;
            (*the_individual_pattern).S = 0;
            (*the_individual_pattern).S0 = 0;
            (*the_individual_pattern).S1 = 0;
            (*the_individual_pattern).S2 = 0;
            (*the_individual_pattern).S3 = 0;
            (*the_individual_pattern).S4 = 0;
            (*the_individual_pattern).S5 = 0;
            (*the_individual_pattern).S6 = 0;
            (*the_individual_pattern).S7 = 0;
            (*the_individual_pattern).S8 = 0;
            (*the_individual_pattern).S9 = 0;
            (*the_individual_pattern).S10 = 0;
        }

        delete[] (*the_pog).ip;
    }

    delete[] (*cp).pog;
    (*cp).pog = 0;

    delete cp;
    cp = 0;
}

void cuda_pattern_register_entry( cuda_pattern* cp, unsigned long index, unsigned long dim, unsigned long* ar, double* diag, double* intensity )
{
    //find coresponding individual_pattern
    int gpu_index = 0;
    for ( gpu_index = 0; gpu_index != (*cp).total_gpu; ++gpu_index )
        if ( index < ((*cp).pog)[gpu_index].pattern_id_end ) 
            break;

    pattern_on_gpu* the_pog = (*cp).pog + gpu_index;
    int const pattern_index = index - (*the_pog).pattern_id_start;
    individual_pattern* the_individual_pattern = (*the_pog).ip + pattern_index;

    //!!GPU CODE

    //switch to the current gpu
    cuda_assert( cudaSetDevice(gpu_index) );

    //allocate memory
    //cuda_assert( cudaMalloc( &( (*the_individual_pattern).ug_thickness ), sizeof(double) * ( (*cp).total_ug_size * 2 + 1 ) ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).ar ), sizeof(unsigned long) * dim * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).diag ), sizeof(double) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).I_exp ), sizeof(double) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).I_sim ), sizeof(double) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).A ), sizeof(double) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S0 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S1 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S2 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S3 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S4 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S5 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S6 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S7 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S8 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S9 ), sizeof(double2) * dim ) );
    cuda_assert( cudaMalloc( &( (*the_individual_pattern).S10 ), sizeof(double2) * dim ) );

    //copy ar
    cuda_assert( cudaMemcpy( (*the_individual_pattern).ar, ar, sizeof(unsigned long)*dim*dim, cudaMemcpyHostToDevice ) );
    //copy diag
    cuda_assert( cudaMemcpy( (*the_individual_pattern).diag, diag, sizeof(double)*dim, cudaMemcpyHostToDevice ) );
    //copy intensity
    cuda_assert( cudaMemcpy( (*the_individual_pattern).I_exp, intensity, sizeof(double)*dim, cudaMemcpyHostToDevice ) );
}

cuda_pattern* make_cuda_pattern( unsigned long n, unsigned long ug_size; )
{
    int total_gpus_avaliable = 0;
    cuda_assert( cudaGetDeviceCount(&total_gpus_avaliable) );
    assert( total_gpus_avaliable > 0 );
    int const patterns_per_gpu = ( n + total_gpus_avaliable - 1 ) / total_gpus_avaliable;
    int const patterns_on_last_gpu = n - patterns_per_gpu * ( total_gpus_avaliable - 1 );

    //cuda_pattern
    cuda_pattern* cp = new cuda_pattern;
    (*cp).total_ug_size = ug_size;
    (*cp).total_gpu = total_gpus_avaliable;
    (*cp).total_cuda_pattern = n;
    (*cp).pog = new pattern_on_gpu[total_gpus_avaliable];
    
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
    }
    
    if ( patterns_on_last_gpu > 0 ) //the last gpu
    {
        int const index = total_gpus_avaliable - 1;
        ((*cp).pog)[index].gpu_id = index;
        ((*cp).pog)[index].pattern_id_start = index * pattern_on_gpu;
        ((*cp).pog)[index].pattern_id_end = ( index + 1 ) * pattern_on_gpu;
        ((*cp).pog)[index].ip = new individual_pattern[patterns_per_gpu];

        //!!GPU CODE
        cuda_assert( cudaSetDevice(index) );
        cuda_assert( cudaMalloc( &( ((*cp).pog)[index].ug_thickness ), sizeof(double) * ( (*cp).total_ug_size * 2 + 1 ) ) );
    }
    
    //individual_pattern


    retun cp;
}

