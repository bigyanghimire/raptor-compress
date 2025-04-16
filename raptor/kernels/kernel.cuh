#ifndef KERNELS_HPP
#define KERNELS_HPP
#include "raptor/core/matrix.hpp"
#include <stdio.h>
#include "kernel.cuh"
namespace raptor
{
    double *spmv_gpu(const CSRMatrix *A, const double *x);
    int *spmv_gpu2(const CSRMatrix *A, const double *x, double *b);
}
#endif
