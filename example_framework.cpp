#include "example_framework.h"
#include <rados/librados.hpp>

const char *ExampleClass::WORD_PROC_CLASS = "word_proc";
const char *ExampleClass::WORD_COUNT_METHOD = "word_count";

int ExampleClass::init(){
    char cluster_name[] = "ceph";
    char user_name[] = "client.admin";
    uint64_t flags = 0;
    int ret = cluster.init2(user_name, cluster_name, flags);
    if (ret < 0) {
        cerr << "Couldn't read the Ceph configuration file! error " << ret << std::endl;
        return EXIT_FAILURE;
    } else {
        cout << "Read the Ceph configuration file." << std::endl;
    }
    const char *pool_name = "data";

    // init io context
    ret = cluster.ioctx_create(pool_name, io_ctx);
    if (ret < 0) {
        std::cerr << "Couldn't set up ioctx! error " << ret << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Created an ioctx for the pool." << std::endl;
    }
    return EXIT_SUCCESS;
}

char* ExampleClass::readStuff(const string& oid, int partition){
    librados::bufferlist bl;
    int ret = io_ctx.read(oid, bl, 100, partition * 100);
    if (ret < 0) {
        std::cerr << "Couldn't read object! error " << ret << std::endl;
        return NULL;
    } else {
        std::cout << "Read new object" << oid << std::endl;
    }
    return bl.c_str();
}

int ExampleClass::writeStuff(const string& oid, string data){
    librados::bufferlist bl;
    bl.append(data);
    cout << "1_1" << std::endl;
    int ret = io_ctx.write_full("obj_id", bl);
    cout << "1_2" << std::endl;
    if (ret < 0) {
        std::cerr << "Couldn't write object! error " << ret << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Wrote new object" << oid << std::endl;
    }
    return EXIT_SUCCESS;
}

const char* ExampleClass::checkSize(string oid){
    char const *SIZE_BIG = "big";
    char const *SIZE_SMALL = "small";
    librados::bufferlist outbl;
    librados::bufferlist bl;
    bl.append("params");
    int ret = io_ctx.exec(oid,WORD_PROC_CLASS, WORD_COUNT_METHOD, bl, outbl);
    if (ret < 0) {
        std::cerr << "Couldn't exec! error " << ret << std::endl;
        return NULL;
    } else {
        std::cout << "Exec function" << oid << std::endl;
    }
    std::string::size_type sz;   // alias of size_t
    int count = std::stoi (outbl.c_str(),&sz);
    std::cout << "Count: " << count << std::endl;
    if (count < 100) {
        return SIZE_SMALL;
    }
    return SIZE_BIG;
}