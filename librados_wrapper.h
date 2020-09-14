//
// Created by esmaeil on 9/13/20.
//

#ifndef RADOS_MOCK_LIBRADOS_WRAPPER_H
#define RADOS_MOCK_LIBRADOS_WRAPPER_H

#include <iostream>
#include "librados_interface.h"
#include <rados/librados.hpp>

using namespace std;

class RadosWrapper: public RadosInterface{
public:
    int init2(const char * const name, const char * const clustername, uint64_t flags) override {
        return this->cluster.init2(name, clustername, flags);
    }

    int ioctx_create(const char *name, IoCtxInterface &pioctx) override{
        return this->cluster.ioctx_create(name, pioctx.getIoCtx());
    }

    librados::Rados& getCluster(){
        return this->cluster;
    }
private:
    librados::Rados& cluster;
};

class IoCtxWrapper: public IoCtxInterface{
public:
    int write_full(const std::string& oid, librados::bufferlist& bl) override{
        return this->ioCtx.write_full(oid,bl);
    }

    int read(const std::string& oid, librados::bufferlist& bl, size_t len, uint64_t off) override{
        return this->ioCtx.read(oid, bl, len, off);
    }

    int exec(const std::string& oid, const char *cls, const char *method, librados::bufferlist& inbl, librados::bufferlist& outbl) override{
        return this->ioCtx.exec(oid, cls, method, inbl, outbl);
    }

    librados::IoCtx& getIoCtx(){
        return this->ioCtx;
    }
private:
    librados::IoCtx& ioCtx;
};

#endif //RADOS_MOCK_LIBRADOS_WRAPPER_H
