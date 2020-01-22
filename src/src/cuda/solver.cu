#include <thrust/device_vector.h>
#include <cusp/array1d.h>

#include <cuda_runtime.h>
#include <cusparse.h>
#include <cusolver_common.h>
#include <cusolverSp.h>
#include <cuda_runtime_api.h>

#include <cassert>
#include <iostream>


void status_check( cusolverStatus_t status )
{
    if (status == CUSOLVER_STATUS_NOT_INITIALIZED)
    {
        assert( !"The cuSolver library was not initialized. This is usually caused by the lack of a prior call, an error in the CUDA Runtime API called by the cuSolver routine, or an error in the hardware setup. To correct: call cusolverCreate() prior to the function call; and check that the hardware, an appropriate version of the driver, and the cuSolver library are correctly installed." );
    }

    if (status == CUSOLVER_STATUS_ALLOC_FAILED )
        assert( !"Resource allocation failed inside the cuSolver library. This is usually caused by a cudaMalloc() failure. To correct: prior to the function call, deallocate previously allocated memory as much as possible. " );

    if (status == CUSOLVER_STATUS_INVALID_VALUE)
        assert( !"An unsupported value or parameter was passed to the function (a negative vector size, for example). To correct: ensure that all the parameters being passed have valid values. " );

    if (status == CUSOLVER_STATUS_ARCH_MISMATCH )
        assert( !"The function requires a feature absent from the device architecture; usually caused by the lack of support for atomic operations or double precision. To correct: compile and run the application on a device with compute capability 2.0 or above. " );

    if (status == CUSOLVER_STATUS_EXECUTION_FAILED )
        assert( !"The GPU program failed to execute. This is often caused by a launch failure of the kernel on the GPU, which can be caused by multiple reasons. To correct: check that the hardware, an appropriate version of the driver, and the cuSolver library are correctly installed. " );

    if (status == CUSOLVER_STATUS_INTERNAL_ERROR )
        assert( !"An internal cuSolver operation failed. This error is usually caused by a cudaMemcpyAsync() failure.  To correct: check that the hardware, an appropriate version of the driver, and the cuSolver library are correctly installed. Also, check that the memory passed as a parameter to the routine is not being deallocated prior to the routine’s completion. " );

    if (status == CUSOLVER_STATUS_MATRIX_TYPE_NOT_SUPPORTED )
        assert( !"The matrix type is not supported by this function. This is usually caused by passing an invalid matrix descriptor to the function. To correct: check that the fields in descrA were set correctly. " );
}


// link -lcusparse_static   -lculibos

float solve( int row, int col, int size, int* A_row, int* A_col, float* A_data, float* x, float* b )
{
    //copy everything to device
    thrust::device_vector<int> DA_row( A_row, A_row+row );
    thrust::device_vector<int> DA_col( A_col, A_col+col );
    thrust::device_vector<float> DA_data( A_data, A_data+size );
    thrust::device_vector<float> D_x( x, x+col );
    thrust::device_vector<float> D_b( b, b+row );

    float norm = 0.0f;

    //solve equation
    {
        cusolverSpHandle_t handle;
        cusolverStatus_t cusolver_status = cusolverSpCreate(&handle);
        status_check( cusolver_status );
        //assert (cusolver_status == CUSOLVER_STATUS_SUCCESS && "failed to initialize cusolver");

        cusparseMatDescr_t descrA;
        cusparseStatus_t cusparse_status = cusparse_status = cusparseCreateMatDescr(&descrA);
        assert(cusparse_status == CUSPARSE_STATUS_SUCCESS && "failed to create Matrix descriptor");

        cusparseSetMatType(descrA, CUSPARSE_MATRIX_TYPE_GENERAL);
        cusparseSetMatIndexBase(descrA, CUSPARSE_INDEX_BASE_ONE);

        float tol = 1.0e-7f;
        thrust::device_vector<int> D_p( row );
        int rankA = 0;

        std::cout << "solver: solver created." << std::endl;

        //convet COO matrix to CSR
        thrust::device_vector<int> DA_csr_row( row+1 );
        {
            cusparseHandle_t handle=0;
            cusparseStatus_t status= cusparseCreate(&handle);
            assert( status == CUSPARSE_STATUS_SUCCESS && "failed to initialize cusparse library" );

            cusparseStatus_t error = cusparseXcoo2csr( handle, DA_row.data().get(), size, row, DA_csr_row.data().get(), CUSPARSE_INDEX_BASE_ONE );
            assert( error == CUSPARSE_STATUS_SUCCESS && "failed to convert coo matrix to csr matrix" );

            status = cusparseDestroy(handle);
            assert( status == CUSPARSE_STATUS_SUCCESS && "failed to release cusparse library" );

            std::cout << "COO matrix -> CSR matrix finished." << std::endl;
        }

        // solving
        //              Ax = b
        for (;;)
        {
            std::cout << "Solving equation with tol " << tol << std::endl;

            cusolver_status = cusolverSpScsrlsqvqrHost(
                                                        //// Input
                                                        handle,                 // handle to the cuSolver library context
                                                        row,                    // number of rows
                                                        col,                    // number of columns
                                                        size,                   // number of non-zeros
                                                        descrA,                 // description of matrix
                                                        DA_data.data().get(),   // non-zero elements of the sparse matrix
                                                        DA_csr_row.data().get(),// row index of CSR matrix
                                                        DA_col.data().get(),    // column index of CSR matrix
                                                        D_b.data().get(),       // right handd data of b
                                                        tol,                    // tolerance to decide rank of A
                                                        //// Output
                                                        &rankA,                 // numerical rank of A
                                                        D_x.data().get(),       // solution of x
                                                        D_p.data().get(),       // permutation matrix
                                                        &norm                   // ||Ax-b||
                                                      );

            status_check( cusolver_status );

            tol *= 10.0f;

            if (cusolver_status == CUSOLVER_STATUS_SUCCESS )
                break;

            if ( tol > 1.0f )
                assert( !"Failed to optimize the LLSF problem." );
        }
    }

    //copy D_x to x
    thrust::copy( D_x.begin(), D_x.end(), x );

    return norm;
}





