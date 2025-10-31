cmake_minimum_required(VERSION 3.10)
project(MallSystem)

set(CMAKE_CXX_STANDARD 11)

# 包含目录
include_directories(include)

# 源文件分组
set(USER_SOURCES
    src/user/User.cpp
    src/user/Customer.cpp
    src/user/Merchant.cpp
    src/user/Admin.cpp
)

set(PRODUCT_SOURCES
    src/product/Product.cpp
    src/product/ProductCategory.cpp
)

set(ORDER_SOURCES
    src/order/Order.cpp
    src/order/OrderItem.cpp
)

set(PAYMENT_SOURCES
    src/payment/Payment.cpp
)

set(CHAT_SOURCES
    src/chat/ChatSession.cpp
    src/chat/Message.cpp
)

set(COMMON_SOURCES
    src/common/Date.cpp
)

# 可执行文件
add_executable(MallSystem
    src/main.cpp
    ${USER_SOURCES}
    ${PRODUCT_SOURCES}
    ${ORDER_SOURCES}
    ${PAYMENT_SOURCES}
    ${CHAT_SOURCES}
    ${COMMON_SOURCES}
)

# 设置编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(MallSystem PRIVATE -Wall -Wextra -O2)
endif()

# 注释掉测试目标，因为我们还没有实现测试文件
# add_executable(TestMallSystem tests/test_main.cpp ${USER_SOURCES} ${COMMON_SOURCES})