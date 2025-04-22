#include <iostream>
#include <vector>
#include "nccl.h"
#include "cuda_runtime.h"

#include <mpi.h>
void nccl_allgather_int(int local_value, std::vector<int> &result,
                        ncclComm_t comm, cudaStream_t stream, int nRanks);
ncclComm_t init_nccl_comm(MPI_Comm mpi_comm, int myRank, int nRanks);
void setup_cuda(int localRank, cudaStream_t *stream);
void cleanup_nccl(cudaStream_t stream, ncclComm_t comm);