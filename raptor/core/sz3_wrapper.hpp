#ifndef SZ3_WRAPPER_HPP
#define SZ3_WRAPPER_HPP
#include <vector>

namespace raptor
{
    template <typename T>
    struct CompressedResult
    {
        char *cmpData;
        size_t cmpSize;
        SZ3::Config conf;
    };

    template <typename T>
    CompressedResult<T> compress_data(T *data, size_t size);
    // template <typename T>
    // CompressedResult<T> decompress_data(T *data, size_t size);
}

#endif
