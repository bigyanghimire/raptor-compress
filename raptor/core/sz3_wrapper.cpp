#include <SZ3/api/sz.hpp> // <-- include SZ3 only in .cpp!
#include <SZ3/api/impl/SZImpl.hpp>
#include "sz3_wrapper.hpp"
#include <iostream>
namespace raptor
{
    template <typename T>
    char *compress_data(T *uncompressedData, size_t size, size_t &cmpSize)
    {
        SZ3::Config conf({size});
        std::vector<char> cmpDatadum(conf.num);
        size_t cmpSizedum = cmpDatadum.size();
        std::cout << "COnf num is" << conf.num << std::endl;
        size_t bufferLen = SZ3::SZ_compress_size_bound<T>(conf);
        std::cout << "Bufferlens size" << bufferLen <<cmpSizedum<< std::endl;
        conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = 1e-3;
        char *cmpData = SZ_compress(conf, uncompressedData, cmpSize);
        return cmpData;
    }

    template <typename T>
    void decompress_data(T *uncompressedData, size_t size, size_t cmpSize, char *cmpData, T *dec_data_p)
    {
        SZ3::Config conf({size});
        conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = 1e-3;
        SZ_decompress(conf, cmpData, cmpSize, dec_data_p);
        // return cmpData;
    }

    template char *compress_data<float>(float *uncompressedData, size_t size, size_t &cmpSize);
    template char *compress_data<double>(double *uncompressedData, size_t size, size_t &cmpSize);
    template char *compress_data<int>(int *uncompressedData, size_t size, size_t &cmpSize);

    template void decompress_data<float>(float *uncompressedData, size_t size, size_t cmpSize, char *cmpData, float *dec_data_p);
    template void decompress_data<double>(double *uncompressedData, size_t size, size_t cmpSize, char *cmpData, double *dec_data_p);
    template void decompress_data<int>(int *uncompressedData, size_t size, size_t cmpSize, char *cmpData, int *dec_data_p);

}
