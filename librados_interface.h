//
// Created by esmaeil on 9/13/20.
//

#ifndef RADOS_MOCK_LIBRADOS_INTERFACE_H
#define RADOS_MOCK_LIBRADOS_INTERFACE_H

#include <iostream>
#include <rados/librados.hpp>

class IoCtxInterface;

class RadosInterface{
public:
    virtual int init2(const char * const name, const char * const clustername, uint64_t flags) = 0;
    virtual int ioctx_create(const char *name, IoCtxInterface &pioctx) = 0;
    librados::Rados& getCluster();
};

class IoCtxInterface{
public:
    virtual int write_full(const std::string& oid, librados::bufferlist& bl) = 0;
    virtual int read(const std::string& oid, librados::bufferlist& bl, size_t len, uint64_t off) = 0;
    virtual int exec(const std::string& oid, const char *cls, const char *method, librados::bufferlist& inbl, librados::bufferlist& outbl) = 0;
    librados::IoCtx& getIoCtx();
};

#endif //RADOS_MOCK_LIBRADOS_INTERFACE_H
