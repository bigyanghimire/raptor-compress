#include "nccl.h"
#include "cuda_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "nccl_types.h"

#define MPICHECK(cmd)                                \
    do                                               \
    {                                                \
        int e = cmd;                                 \
        if (e != MPI_SUCCESS)                        \
        {                                            \
            printf("Failed: MPI error %s:%d '%d'\n", \
                   __FILE__, __LINE__, e);           \
            exit(EXIT_FAILURE);                      \
        }                                            \
    } while (0)

#define CUDACHECK(cmd)                                         \
    do                                                         \
    {                                                          \
        cudaError_t e = cmd;                                   \
        if (e != cudaSuccess)                                  \
        {                                                      \
            printf("Failed: Cuda error %s:%d '%s'\n",          \
                   __FILE__, __LINE__, cudaGetErrorString(e)); \
            exit(EXIT_FAILURE);                                \
        }                                                      \
    } while (0)

#define NCCLCHECK(cmd)                                         \
    do                                                         \
    {                                                          \
        ncclResult_t r = cmd;                                  \
        if (r != ncclSuccess)                                  \
        {                                                      \
            printf("Failed, NCCL error %s:%d '%s'\n",          \
                   __FILE__, __LINE__, ncclGetErrorString(r)); \
            exit(EXIT_FAILURE);                                \
        }                                                      \
    } while (0)

ncclComm_t init_nccl_comm(MPI_Comm mpi_comm, int myRank, int nRanks)
{
    ncclUniqueId id;
    ncclComm_t comm;

    if (myRank == 0)
        NCCLCHECK(ncclGetUniqueId(&id));

    MPICHECK(MPI_Bcast((void *)&id, sizeof(id), MPI_BYTE, 0, mpi_comm));
    NCCLCHECK(ncclCommInitRank(&comm, nRanks, id, myRank));

    return comm;
}

void nccl_allgather_int(int local_value, std::vector<int> &result,
                        ncclComm_t comm, cudaStream_t stream, int nRanks)
{
    int *d_sendbuff;
    int *d_recvbuff;

    CUDACHECK(cudaMalloc(&d_sendbuff, sizeof(int)));
    CUDACHECK(cudaMalloc(&d_recvbuff, sizeof(int) * nRanks));
    CUDACHECK(cudaMemcpy(d_sendbuff, &local_value, sizeof(int), cudaMemcpyHostToDevice));

    NCCLCHECK(ncclAllGather((const void *)d_sendbuff, (void *)d_recvbuff, 1, ncclInt, comm, stream));
    CUDACHECK(cudaStreamSynchronize(stream));

    result.resize(nRanks);
    CUDACHECK(cudaMemcpy(result.data(), d_recvbuff, sizeof(int) * nRanks, cudaMemcpyDeviceToHost));

    CUDACHECK(cudaFree(d_sendbuff));
    CUDACHECK(cudaFree(d_recvbuff));
}
void setup_cuda(int localRank, cudaStream_t *stream)
{
    CUDACHECK(cudaSetDevice(localRank));
    CUDACHECK(cudaStreamCreate(stream));
}
void cleanup_nccl(cudaStream_t stream, ncclComm_t comm)
{
    CUDACHECK(cudaStreamDestroy(stream));
    NCCLCHECK(ncclCommDestroy(comm));
}