//
// Created by esmaeil on 9/10/20.
//

#ifndef RADOS_MOCK_EXAMPE_FRAMEWORK_H
#define RADOS_MOCK_EXAMPE_FRAMEWORK_H
#include <iostream>
#include <rados/librados.hpp>

class ExampleClass {
    librados::IoCtx& io_ctx;
public:
    explicit ExampleClass(librados::IoCtx& _io_ctx) : io_ctx(_io_ctx){}
    int write_stuff(std::string name, librados::bufferlist bl);
};

#endif //RADOS_MOCK_EXAMPE_FRAMEWORK_H
