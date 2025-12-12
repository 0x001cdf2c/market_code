# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MallSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 包含目录
include_directories(include)

# 源文件（不包含 main.cpp）
set(SRC_FILES
    src/common/Date.cpp
    src/user/User.cpp
    src/user/Customer.cpp
    src/user/Merchant.cpp
    src/user/Admin.cpp
    src/chat/Message.cpp
    src/chat/ChatSession.cpp
    src/order/OrderItem.cpp
    src/order/Order.cpp
    src/payment/Payment.cpp
    src/product/Product.cpp
    src/product/ProductCategory.cpp
)

# 测试文件
set(TEST_FILES
    tests/Gtest_OrderItem.cpp
    tests/Gtest_message.cpp
    tests/IntegrationTest_OrderManagement.cpp
    tests/IntegrationTest_ChatSystem.cpp
)

# 主程序（单独编译）
if(EXISTS "src/main.cpp")
    add_executable(mall_system src/main.cpp ${SRC_FILES})
    set_target_properties(mall_system PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    message(STATUS "创建主程序: mall_system")
endif()

# 单元测试（确保不包含 main.cpp）
add_executable(unit_tests ${SRC_FILES} tests/Gtest_OrderItem.cpp tests/Gtest_message.cpp)
set_target_properties(unit_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 集成测试（确保不包含 main.cpp）
add_executable(integration_tests ${SRC_FILES} ${TEST_FILES})
set_target_properties(integration_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 链接库
target_link_libraries(unit_tests gtest gtest_main pthread)
target_link_libraries(integration_tests gtest gtest_main pthread)

message(STATUS "构建配置完成")