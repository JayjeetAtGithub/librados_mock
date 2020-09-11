//
// Created by esmaeil on 9/9/20.
//
#include <iostream>
#include <rados/librados.hpp>
#include "exampe_framework.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockIoCtx: public librados::IoCtx{
public:
    MOCK_METHOD2(write_full, int (const std::string& oid, librados::bufferlist& bl));
};

TEST(MyTest, Test1){
    MockIoCtx ioCtx;
    ExampleClass example(ioCtx);
    librados::bufferlist bl;
    bl.append("Hello World!");
    EXPECT_CALL(ioCtx, write_full("obj_id", bl))
            .Times(1)
            .WillOnce(testing::Return(12));

//    int ret = ioCtx.write_full("obj_id", bl);
//    std::cout << "Wrote new object of size of " << ret << "." << std::endl;
    int ret = example.write_stuff("obj_id", bl);
    ASSERT_EQ(ret, 12);

}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
