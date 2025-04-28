#ifndef KERNELS_HPP
#define KERNELS_HPP
#include "raptor/core/matrix.hpp"
#include <stdio.h>
#include "kernel.cuh"
namespace raptor
{

    int *spmv_gpu(const CSRMatrix *A, const double *x, double *b);
}
#endif
