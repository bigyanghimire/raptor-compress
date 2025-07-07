#include <SZ3/api/sz.hpp> // <-- include SZ3 only in .cpp!
#include "sz3_wrapper.hpp"
#include <iostream>
namespace raptor
{
    template <typename T>
    char *compress_data(T *uncompressedData, size_t size)
    {
        SZ3::Config conf({size});
        conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = 1e-3;
        size_t cmpSize;
        char *cmpData = SZ_compress(conf, uncompressedData, cmpSize);
        return cmpData;
    }

    template <typename T>
    void *decompress_data( T *uncompressedData, size_t size, char *cmpData, T *dec_data_p)
    {
           SZ3::Config conf({size});
        conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = 1e-3;
        SZ_decompress(conf, cmpData, cmpData.size(), dec_data_p);
        // return cmpData;
    }

    template char *compress_data<float>(float *data, size_t size);
    template char *compress_data<double>(double *data, size_t size);
    template char *compress_data<int>(int *data, size_t size);

    template char *decompress_data<float>(float *data, size_t size);
    template char *decompress_data<double>(double *data, size_t size);
    template char *decompress_data<int>(int *data, size_t size);

}
