#include <SZ3/api/sz.hpp> // <-- include SZ3 only in .cpp!
#include "sz3_wrapper.hpp"
#include <iostream>
namespace raptor
{

    // std::vector<uint8_t> compress_float_array(const float* data, size_t size) {
    //     SZ3::Config conf({size});
    //     conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
    //     conf.errorBoundMode = SZ3::EB_ABS;
    //     conf.absErrorBound = 1e-3;

    //     SZ3::SZ<float> compressor(conf, size);
    //     return compressor.compress(data);
    // }

    // std::vector<float> decompress_float_array(const uint8_t* compressed_data, size_t compressed_size) {
    //     SZ3::SZ<float> compressor;
    //     return compressor.decompress(compressed_data, compressed_size);
    // }

    template <class T>
    char *compress_data(T *data, size_t size)
    {
        SZ3::Config conf({size});
        conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = 1e-3;
        size_t cmpSize;
        char *cmpData = SZ_compress(conf, data, cmpSize);
        return cmpData;
    }
template char* compress_data<float>(float* data, size_t size);
template char* compress_data<double>(double* data, size_t size);
template char* compress_data<int>(int* data, size_t size);
    // template <class T>
    // void *decompress_data(SZ3::Config conf, char *cmpData, T *dec_data_p)
    // {
    //     size_t cmpSize;
    //     SZ_decompress(conf, cmpData, cmpSize, dec_data_p);
    //     // return cmpData;
    // }
    // int helloworld()
    // {
    //     return 0;
    // }

}
