#include "exampe_framework.h"

int ExampleClass::write_stuff(std::string name, librados::bufferlist bl){
    std::cout << "Writing new object " << name << "." << std::endl;
    int ret = io_ctx.write_full(name, bl);
    if (ret < 0) {
        std::cerr << "Couldn't write object! error " << ret << std::endl;
        return -1;
    } else {
        std::cout << "Wrote new object " << name << " of size of " << ret << "." << std::endl;
        return 1;
    }
}