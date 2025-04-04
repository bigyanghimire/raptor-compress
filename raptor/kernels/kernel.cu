#include "kernel.cuh"
#include <iostream>
namespace raptor

{
    __global__ void hello_cuda()
    {
        printf("Hello from GPU!\n");
    }

    int wrap_test_print()
    {
        hello_cuda<<<1, 1>>>();
        cudaDeviceSynchronize();
        return 0;
    }

}
