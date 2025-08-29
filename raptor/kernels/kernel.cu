#include "kernel.cuh"
#include <iostream>
#include "raptor/core/matrix.hpp"
#include <cusparse.h>
namespace raptor

{
#define CHECK_KERNEL()                                                         \
    {                                                                          \
        cudaError_t status = cudaGetLastError();                               \
        if (status != cudaSuccess)                                             \
        {                                                                      \
            printf("Kernel launch failed at line %d with error: %s (%d)\n",    \
                   __LINE__, cudaGetErrorString(status), status);              \
            return EXIT_FAILURE;                                               \
        }                                                                      \
        status = cudaDeviceSynchronize();                                      \
        if (status != cudaSuccess)                                             \
        {                                                                      \
            printf("Kernel execution failed at line %d with error: %s (%d)\n", \
                   __LINE__, cudaGetErrorString(status), status);              \
            return EXIT_FAILURE;                                               \
        }                                                                      \
    }

#define CHECK_CUDA(func)                                               \
    {                                                                  \
        cudaError_t status = (func);                                   \
        if (status != cudaSuccess)                                     \
        {                                                              \
            printf("CUDA API failed at line %d with error: %s (%d)\n", \
                   __LINE__, cudaGetErrorString(status), status);      \
            exit(EXIT_FAILURE);                                        \
        }                                                              \
    }

#define CHECK_CUSPARSE(func)                                               \
    {                                                                      \
        cusparseStatus_t status = (func);                                  \
        if (status != CUSPARSE_STATUS_SUCCESS)                             \
        {                                                                  \
            printf("CUSPARSE API failed at line %d with error: %s (%d)\n", \
                   __LINE__, cusparseGetErrorString(status), status);      \
            exit(EXIT_FAILURE);                                            \
        }                                                                  \
    }
    __global__ void hello_cuda()
    {
        printf("Hello from GPU!\n");
    }

    void print_vector(const double *hB, int num_elements)
    {
        std::cout << "[";
        for (int i = 0; i < num_elements; ++i)
        {
            std::cout << hB[i];
            if (i != num_elements - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    void fill_vector()
    {
    }

    int *spmv_gpu(const CSRMatrix *A, const double *x, double *b)
    {

        double alpha = 1.0f;
        double beta = 0.0f;
        int A_num_rows = A->n_rows;
        int A_num_cols = A->n_cols;
        int A_nnz = A->vals.size();

        const int *hA_rows = A->idx1.data();
        const int *hA_columns = A->idx2.data();
        const double *hA_values = A->vals.data();

        const double *hX = x;
        // double *hB = b;
        // b = (double *)malloc(A_num_rows * sizeof(double));
        // memset(b, 0, A_num_rows * sizeof(double));

        //--------------------------------------------------//
        // Device memory management
        int *dA_rows,
            *dA_columns;
        double *dA_values, *dX, *dB;

        if(unified_m==1){
            CHECK_CUDA(cudaMallocManaged((void **)&dA_rows,
                                (A_num_rows + 1) * sizeof(int)));
            CHECK_CUDA(cudaMallocManaged((void **)&dA_columns, A_nnz * sizeof(int)));
            CHECK_CUDA(cudaMallocManaged((void **)&dA_values, A_nnz * sizeof(double)));
            CHECK_CUDA(cudaMallocManaged((void **)&dX, A_num_cols * sizeof(double)));
            CHECK_CUDA(cudaMallocManaged((void **)&dB, A_num_rows * sizeof(double)));
        }else{

        CHECK_CUDA(cudaMalloc((void **)&dA_rows,
                              (A_num_rows + 1) * sizeof(int)));
        CHECK_CUDA(cudaMalloc((void **)&dA_columns, A_nnz * sizeof(int)));
        CHECK_CUDA(cudaMalloc((void **)&dA_values, A_nnz * sizeof(double)));
        CHECK_CUDA(cudaMalloc((void **)&dX, A_num_cols * sizeof(double)));
        CHECK_CUDA(cudaMalloc((void **)&dB, A_num_rows * sizeof(double)));
        CHECK_CUDA(cudaMemcpy(dA_rows, hA_rows,
                              (A_num_rows + 1) * sizeof(int),
                              cudaMemcpyHostToDevice));
        CHECK_CUDA(cudaMemcpy(dA_columns, hA_columns, A_nnz * sizeof(int),
                              cudaMemcpyHostToDevice));
        CHECK_CUDA(cudaMemcpy(dA_values, hA_values, A_nnz * sizeof(double),
                              cudaMemcpyHostToDevice));
        CHECK_CUDA(cudaMemcpy(dX, hX, A_num_cols * sizeof(double),
                              cudaMemcpyHostToDevice));
        CHECK_CUDA(cudaMemcpy(dB, b, A_num_rows * sizeof(double),
                              cudaMemcpyHostToDevice));
        }
        // //-----------------------------------------------------  CUSPARSE APIs

        cusparseHandle_t handle = NULL;
        cusparseSpMatDescr_t matA;
        cusparseDnVecDescr_t vecX, vecB;
        void *dBuffer = NULL;
        size_t bufferSize = 0;
        CHECK_CUSPARSE(cusparseCreate(&handle));
        // Create sparse matrix A in COO format
        CHECK_CUSPARSE(cusparseCreateCsr(&matA, A_num_rows, A_num_cols, A_nnz,
                                         dA_rows, dA_columns, dA_values,
                                         CUSPARSE_INDEX_32I, CUSPARSE_INDEX_32I,
                                         CUSPARSE_INDEX_BASE_ZERO, CUDA_R_64F));
        // Create dense vector B
        CHECK_CUSPARSE(cusparseCreateDnVec(&vecX, A_num_cols, dX, CUDA_R_64F));
        // Create dense vector C or result
        CHECK_CUSPARSE(cusparseCreateDnVec(&vecB, A_num_rows, dB, CUDA_R_64F));
        // allocate an external buffer if needed
        CHECK_CUSPARSE(cusparseSpMV_bufferSize(
            handle, CUSPARSE_OPERATION_NON_TRANSPOSE,
            &alpha, matA, vecX, &beta, vecB, CUDA_R_64F,
            CUSPARSE_SPMV_ALG_DEFAULT, &bufferSize));
        CHECK_CUDA(cudaMalloc(&dBuffer, bufferSize));

        // execute SpMV
        CHECK_CUSPARSE(cusparseSpMV(handle, CUSPARSE_OPERATION_NON_TRANSPOSE,
                                    &alpha, matA, vecX, &beta, vecB, CUDA_R_64F,
                                    CUSPARSE_SPMV_ALG_DEFAULT, dBuffer));
        CHECK_CUDA(cudaDeviceSynchronize());
        //  destroy matrix/vector descriptors
        CHECK_CUSPARSE(cusparseDestroySpMat(matA));
        CHECK_CUSPARSE(cusparseDestroyDnVec(vecX));
        CHECK_CUSPARSE(cusparseDestroyDnVec(vecB));
        CHECK_CUSPARSE(cusparseDestroy(handle));

        CHECK_CUDA(cudaMemcpy(b, dB, A_num_rows * sizeof(double),
                              cudaMemcpyDeviceToHost));
        // std::cout << "GPU soln" << std::endl;
        // print_vector(hB, A->n_rows);
        // std::cout << "GPU soln ends" << std::endl;

        //  print_vector(hB, A_num_rows);
        //   hello_cuda<<<1, 1>>>();
        //   cudaDeviceSynchronize();
        cudaFree(dA_rows);
        cudaFree(dA_columns);
        cudaFree(dA_values);
        cudaFree(dX);
        cudaFree(dB);
        cudaFree(dBuffer);
        return 0;
    }

}
