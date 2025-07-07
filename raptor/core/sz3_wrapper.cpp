#include <SZ3/api/sz.hpp> // <-- include SZ3 only in .cpp!
#include "sz3_wrapper.hpp"
#include <iostream>
namespace raptor
{
    template <typename T>
    CompressedResult<T> compress_data(T *data, size_t size)
    {
        SZ3::Config conf({size});
        conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = 1e-3;
        size_t cmpSize;
        char *cmpData = SZ_compress(conf, data, cmpSize);
        return {cmpData, cmpSize, conf};
    }
    
    // template <typename T>
    // void *decompress_data(SZ3::Config conf, char *cmpData, T *dec_data_p)
    // {
    //     size_t cmpSize;
    //     SZ_decompress(conf, cmpData, cmpSize, dec_data_p);
    //     // return cmpData;
    // }

    template CompressedResult<float> compress_data<float>(float *data, size_t size);
    template CompressedResult<double> compress_data<double>(double *data, size_t size);
    template CompressedResult<int> compress_data<int>(int *data, size_t size);

}
