//
// Created by esmaeil on 9/10/20.
//
#ifndef RADOS_MOCK_EXAMPLE_FRAMEWORK_H
#define RADOS_MOCK_EXAMPLE_FRAMEWORK_H

#include <iostream>
#include "librados_interface.h"
#include "librados_wrapper.h"
#include <rados/librados.hpp>

using namespace std;

class ExampleClass {
public:
    ExampleClass(RadosInterface &_cluster, IoCtxInterface &ioCtx) : cluster(_cluster), io_ctx(ioCtx) {}
    int init();
    char* readStuff(const string& oid, int partition);
    int writeStuff(const string& oid, string data);
    const char* checkSize(string oid);
    static const char *WORD_PROC_CLASS;
    static const char *WORD_COUNT_METHOD;

private:
    RadosInterface &cluster;
    IoCtxInterface &io_ctx;
};

#endif //RADOS_MOCK_EXAMPLE_FRAMEWORK_H