#ifndef SZ3_WRAPPER_HPP
#define SZ3_WRAPPER_HPP
#include <vector>

namespace raptor
{
    template <typename T>
    char *compress_data(T *uncompressedData, size_t size, size_t cmpSize);
    template <typename T>
    void *decompress_data(T *uncompressedData, size_t size, size_t cmpSize,char *cmpData, T *dec_data_p);
}

#endif
