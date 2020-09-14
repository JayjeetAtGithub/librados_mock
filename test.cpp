//
// Created by esmaeil on 9/9/20.
//
#include <iostream>
#include <rados/librados.hpp>
#include "example_framework.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockRados: public RadosInterface{
public:
    MOCK_METHOD3(init2, int(const char * const name, const char * const clustername, uint64_t flags));
    MOCK_METHOD2(ioctx_create, int(const char *name, IoCtxInterface &pioctx));
};

class MockIoCtx: public IoCtxInterface{
public:
    MOCK_METHOD2(write_full, int(const string& oid, librados::bufferlist& bl));
    MOCK_METHOD4(read, int(const std::string& oid, librados::bufferlist& bl, size_t len, uint64_t off));
    MOCK_METHOD5(exec, int(const std::string& oid, const char *cls, const char *method, librados::bufferlist& inbl, librados::bufferlist& outbl));
};

TEST(MyTest, Test1){
    // mocks init
    MockRados mockRados;
    MockIoCtx mockIoCtx;
    ExampleClass example(mockRados, mockIoCtx);

    EXPECT_CALL(mockRados, init2(testing::_, testing::_, testing::_))
            .WillOnce(testing::Return(0));

    EXPECT_CALL(mockRados, ioctx_create(testing::_,testing::_))
        .WillOnce(testing::Return(0));

    EXPECT_CALL(mockIoCtx, write_full(testing::_, testing::_))
            .WillOnce(testing::Return(12));

    librados::bufferlist readMsg;
    readMsg.append("Hello");
    EXPECT_CALL(mockIoCtx, read("obj_id", testing::_, testing::_, 0))
            .WillOnce(DoAll(testing::SetArgReferee<1>(readMsg), testing::Return(0)));

    librados::bufferlist res;
    res.append("25");
    EXPECT_CALL(mockIoCtx, exec("obj_id", ExampleClass::WORD_PROC_CLASS, ExampleClass::WORD_COUNT_METHOD, testing::_, testing::_))
            .WillOnce(DoAll(testing::SetArgReferee<4>(res), testing::Return(0)));

    // test
    int ret;
    ret = example.init();
    ASSERT_EQ(ret, EXIT_SUCCESS);

    cout << "1" << std::endl;

    ret = example.writeStuff("obj_id", "data bllahh bllahh ...");
    ASSERT_EQ(ret, EXIT_SUCCESS);

    cout << "2" << std::endl;

    const char* result = example.readStuff("obj_id", 0);
    cout << result << std::endl;
    ASSERT_STREQ(result, readMsg.c_str());

    const char* size = example.checkSize("obj_id");
    ASSERT_STREQ(size, "small");
}

int main(int argc, char **argv) {

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
