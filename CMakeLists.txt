# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MallSystem VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 检查是否启用 AFL
option(ENABLE_AFL "Enable AFL++ fuzzing" OFF)
if(ENABLE_AFL)
    set(CMAKE_C_COMPILER afl-gcc)
    set(CMAKE_CXX_COMPILER afl-g++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address,undefined")
    message(STATUS "Building with AFL++ support")
endif()

# 收集所有源文件
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

# 检查main.cpp是否存在
if(EXISTS "${CMAKE_SOURCE_DIR}/src/main.cpp")
    list(APPEND SRC_FILES src/main.cpp)
endif()

# 创建主可执行文件
if(EXISTS "${CMAKE_SOURCE_DIR}/src/main.cpp")
    add_executable(mall_system ${SRC_FILES})
    set_target_properties(mall_system PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()

# 创建模糊测试可执行文件
# 注意：模糊测试不应该包含 main.cpp
set(FUZZ_SRC_FILES ${SRC_FILES})
if(EXISTS "${CMAKE_SOURCE_DIR}/src/main.cpp")
    list(REMOVE_ITEM FUZZ_SRC_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")
endif()

# 添加模糊测试目标
add_executable(fuzz_simple fuzz_tests/fuzz_simple.cpp ${FUZZ_SRC_FILES})
set_target_properties(fuzz_simple PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 如果有其他模糊测试，也可以添加
if(EXISTS "${CMAKE_SOURCE_DIR}/fuzz_tests/fuzz_order.cpp")
    add_executable(fuzz_order fuzz_tests/fuzz_order.cpp ${FUZZ_SRC_FILES})
    set_target_properties(fuzz_order PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

# 如果启用了GTest，添加单元测试
find_package(GTest QUIET)
if(GTEST_FOUND)
    message(STATUS "GTest found, building unit tests")
    
    # 创建单元测试可执行文件
    add_executable(unit_tests ${FUZZ_SRC_FILES} tests/Gtest_OrderItem.cpp tests/Gtest_message.cpp)
    target_link_libraries(unit_tests GTest::gtest GTest::gtest_main pthread)
    set_target_properties(unit_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    
    # 创建集成测试可执行文件
    add_executable(integration_tests ${FUZZ_SRC_FILES} 
        tests/Gtest_OrderItem.cpp 
        tests/Gtest_message.cpp
        tests/IntegrationTest_OrderManagement.cpp
        tests/IntegrationTest_ChatSystem.cpp
    )
    target_link_libraries(integration_tests GTest::gtest GTest::gtest_main pthread)
    set_target_properties(integration_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()

message(STATUS "Build configuration complete")