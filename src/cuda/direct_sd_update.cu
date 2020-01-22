#include <cuda_runtime.h>
#include <cuda.h>
#include <cuComplex.h>
#include <math_functions.h>

typedef unsigned long   size_type;
typedef size_type*      size_pointer_type;
typedef double          value_type;
typedef value_type*     value_pointer_type;
typedef cuDoubleComplex complex_type;
typedef complex_type*   complex_pointer_type;

// aa = a * a
void __global__ zgemm_aa( complex_pointer_type __restrict__ a, complex_pointer_type __restrict__ aa, size_type n )
{
}

void __global__ zgemm_a_b_c( complex_pointer_type __restrict__ a, complex_pointer_type __restrict__ b, complex_pointer_type __restrict__ c, size_type n )
{
}

void __global__
direct_sd_update_(  size_type                                  align_dim_,
                    size_type                                  ug_size_,
                    size_pointer_type             __restrict__ dim_cache_, 
                    complex_pointer_type          __restrict__ ug_cache_,  
                    complex_pointer_type          __restrict__ S_cache_,
                    complex_pointer_type          __restrict__ diag_cache_,
                    value_pointer_type            __restrict__ I_new_cache_,
                    value_pointer_type            __restrict__ I_ori_cache_,
                    size_pointer_type             __restrict__ ar_cache_,
                    complex_pointer_type          __restrict__ A_cache_,
                    complex_pointer_type          __restrict__ a_cache_,
                    complex_pointer_type          __restrict__ aa_cache_,
                    complex_pointer_type          __restrict__ aaa_cache_,
                    complex_pointer_type          __restrict__ PP_cache_,
                    complex_pointer_type          __restrict__ PQ_cache_,
                    complex_pointer_type          __restrict__ PR_cache_,
                    complex_pointer_type          __restrict__ PS_cache_,
                    value_pointer_type            __restrict__ residual_
                )
{
    size_type const block_index   = blockIdx.x;
    size_type const thread_index  = threadIdx.x;
    size_type const total_task    = align_dim_ >> 5; //threads per block is set to 32 
    size_type const task_begin    = thread_index * total_task;
    size_type const task_end      = task_begin + total_task;
    size_type const real_dim      = dim_cache_[block_index];

    size_type const matrix_offset = block_index * align_dim_ * align_dim_;
    size_type const array_offset  = block_index * align_dim_;

    complex_pointer_type A        = A_cache_ + matrix_offset;
    complex_pointer_type S        = S_cache_ + matrix_offset;
    complex_pointer_type diag     = diag_cache_ + array_offset;
    value_pointer_type I_new      = I_new_cache_ + array_offset;
    value_pointer_type I_ori      = I_ori_cache_ + array_offset;
    size_pointer_type ar          = ar_cache_ + matrix_offset;
    complex_pointer_type a        = a_cache_ + matrix_offset;
    complex_pointer_type aa       = aa_cache_ + matrix_offset;
    complex_pointer_type aaa      = aaa_cache_ + matrix_offset;
    complex_pointer_type PP       = PP_cache_ + matrix_offset;
    complex_pointer_type PQ       = PQ_cache_ + matrix_offset;
    complex_pointer_type PR       = PR_cache_ + matrix_offset;
    complex_pointer_type PS       = PS_cache_ + matrix_offset;

    //update A in col major -- TODO in row major -- also calc norm_1
    size_type square_times = 0;
    value_type scaler = 1.0;

    {
        //load ug to shared memory
        __shared__ complex_type ug[ug_size_ + 1];
        {
            size_type const task_per_thread = (ug_size_ + 31) >> 5; //32 threads
            size_type const start = thread_index * task_per_thread;
            size_type const end   = start + task_per_thread;

            for ( size_type index = start; index != end; ++index ) //not need to check memory boundary
                ug[index] = ug_cache_[index];

            __syncthreads();
        }

        //construct A, reduce norm2 to shared memory
        __shared__ value_type norm_1[ align_dim_ ];
        for ( size_type col = task_begin; col != task_end; ++col )
        {
            norm_1[col] = 0.0;
            for ( size_type row = 0; row != align_dim_; ++row )
            {
                size_type const align_offset = row * align_dim_ + col;
                size_type const real_offset  = row * real_dim + col;
                complex_type const the_element = ug[ar[real_offset]]; //slow
                A[align_offset] = the_element;

                norm_1[col] += hypot( cuReal( the_element ) , cuImag( the_element ) );
            }

            size_type const align_offset = row * align_dim_ + col;
            complex_type const the_element = diag[col]
            A[align_offset] = the_element; 

            norm_1[col] += hypot( cuReal( the_element ) , cuImag( the_element ) );

            //reduce to the first element in norm_1
            norm_1[task_begin] = fmax( norm_1[task_begin], norm_1[col] );
        }
        __syncthreads();

        if ( 0 == thread_index )
            for ( size_type index = task_per_thread; index != align_dim_; index += task_per_thread )
                norm_1[0] = fmax( norm_1[0], norm_1[index] );

        __syncthreads();

        value_type the_norm_1 = sqrt( norm_1[0] );
        value_type ratio = 5.371920351148152 / the_norm_1;
        square_times =  ratio < 1.0 ? 0 : (size_type)( ceil( log2( ratio ) ) );
        scaler = ratio < 1.0 ? (value_type)(1 << s) : 1.0;
    }

    //scale A to a
    {
        for ( size_type col = task_begin; col != task_end; ++col )
            for ( size_type row = 0; row != align_dim_; ++row )
            {
                size_type const offset = row * align_dim_ + col;
                a[offset] = A[offset] / scaler;
            }
        __syncthreads();
    }

    //calc aa
    {
        size_type const grids = ( align_dim_ + 31 ) >> 5;
        dim3 const blocks{ 16, 16 };
        if ( 0 == thread_index )
            zgemm_aa<<< grids, blocks >>>( a, aa, align_dim_ );
        __syncthreads();
    }

    //calc aaa
    {
        size_type const grids = ( align_dim_ + 31 ) >> 5;
        dim3 const blocks{ 16, 16 };
        if ( 0 == thread_index )
            zgemm_a_b_c<<< grids, blocks >>>( a, aa, aaa, align_dim_ );
        __syncthreads();
    }

    //calc PP



    //calc PQ

    //calc PR

    //calc PS

    //calc PP PQ PR PS


    //scale back

    //update I new

    //make diff

}

void direct_sd_update(  size_type tilt_size_,
                        size_type align_dim_, 
                        size_type ug_size_,
                        size_pointer_type dim_cache_,
                        complex_pointer_type ug_cache_,
                        complex_pointer_type S_cache_,
                        complex_pointer_type diag_cache_,
                        value_pointer_type I_new_cache_,
                        value_pointer_type I_ori_cache_,
                        size_pointer_type ar_cache_,
                        complex_pointer_type A_cache_,
                        complex_pointer_type a_cache_,
                        complex_pointer_type aa_cache_,
                        complex_pointer_type aaa_cache_,
                        complex_pointer_type PP_cache_,
                        complex_pointer_type PQ_cache_,
                        complex_pointer_type PR_cache_,
                        complex_pointer_type PS_cache_,
                        value_pointer_type residual_
                    )
{
        unsigned long const block_size = tilt_size_;
        unsigned long const thread_size = 16;

        direce_sd_update_<<<block_size, thread_size>>>( align_dim_, ug_size_, dim_cache_, ug_cache_, S_cache_, diag_cache_, I_new_cache_, I_ori_cache_, ar_cache_, A_cache_, a_cache_, aa_cache_, aaa_cache_, PP_cache_, PQ_cache_, PR_cache_, PS_cache_, residual_);
}

