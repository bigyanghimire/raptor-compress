#include <SZ3/api/sz.hpp>   // <-- include SZ3 only in .cpp!
#include "sz3_wrapper.hpp"
#include <iostream>
namespace SZ3Wrapper {

 void compress_data(){
    std::vector<size_t> dims({100, 200, 300});
    SZ3::Config conf({dims[0], dims[1], dims[2]});
    conf.cmprAlgo = ALGO_INTERP_LORENZO;
    conf.errorBoundMode = EB_ABS; // refer to def.hpp for all supported error bound mode
    conf.absErrorBound = 1E-3; // absolute error bound 1e-3
    std::cout<<"Compression called"<<std::endl;
 }

}
