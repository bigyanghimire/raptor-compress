#include <SZ3/api/sz.hpp> // <-- include SZ3 only in .cpp!
#include <SZ3/api/impl/SZImpl.hpp>
#include "sz3_wrapper.hpp"
#include "mpi_types.hpp"
#include <iostream>
namespace raptor
{
    template <typename T>
    char *compress_data(T *uncompressedData, size_t size, size_t &cmpSize)
    {
        SZ3::Config conf({size});
        std::vector<char> cmpDatadum(conf.num);
        size_t cmpSizedum = cmpDatadum.size();
        // conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = ext_solve_tol;
        std::cout<<"Error bound is"<<conf.absErrorBound<<std:endl;
        assert(conf.num == size); 
        char *cmpData = SZ_compress(conf, uncompressedData, cmpSize);
        return cmpData;
    }

    template <typename T>
    T* decompress_data(size_t size, size_t cmpSize, char *cmpData)
    {
        SZ3::Config conf({size});
        // conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = ext_solve_tol;
        // SZ_decompress(conf, cmpData, cmpSize, dec_data_p);
        return SZ_decompress<T>(conf, cmpData, cmpSize);
        // return cmpData;
    }

    template char *compress_data<float>(float *uncompressedData, size_t size, size_t &cmpSize);
    template char *compress_data<double>(double *uncompressedData, size_t size, size_t &cmpSize);
    template char *compress_data<int>(int *uncompressedData, size_t size, size_t &cmpSize);
    template char *compress_data<unsigned long>(unsigned long *uncompressedData, size_t size, size_t &cmpSize);

    template float *decompress_data<float>( size_t size, size_t cmpSize, char *cmpData );
    template double *decompress_data<double>( size_t size, size_t cmpSize, char *cmpData );
    template int *decompress_data<int>( size_t size, size_t cmpSize, char *cmpData);

}
