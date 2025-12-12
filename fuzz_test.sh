#!/bin/bash
echo "=== 修复版 AFL++ 模糊测试构建 ==="

cd ~/MallSystem

# 检查 fuzz_target.cpp 是否存在
if [ ! -f "fuzz_target.cpp" ]; then
    echo "❌ 错误: fuzz_target.cpp 不存在，请先创建该文件"
    exit 1
fi

# 清理并创建目录
rm -rf fuzz_build
mkdir -p fuzz_build
cd fuzz_build

echo "收集源文件..."
# 找到所有源文件
find ../src -name "*.cpp" | while read src_file; do
    echo "找到: $src_file"
done

# 使用更简单的方法编译所有文件
echo "编译所有源文件..."
afl-g++ -std=c++11 -I../include -g -O1 \
    ../fuzz_target.cpp \
    ../src/common/Date.cpp \
    ../src/user/User.cpp \
    ../src/user/Customer.cpp \
    ../src/user/Merchant.cpp \
    ../src/user/Admin.cpp \
    ../src/chat/Message.cpp \
    ../src/chat/ChatSession.cpp \
    ../src/order/OrderItem.cpp \
    ../src/order/Order.cpp \
    ../src/payment/Payment.cpp \
    ../src/product/Product.cpp \
    ../src/product/ProductCategory.cpp \
    -o fuzzer

# 验证构建
if [ -f "fuzzer" ]; then
    echo "✅ 模糊测试目标构建成功!"
    echo "文件大小: $(stat -c%s fuzzer) 字节"
    
    # 测试构建
    echo "测试构建..."
    echo "test" > test_input.txt
    ./fuzzer test_input.txt
    TEST_RESULT=$?
    rm test_input.txt
    
    if [ $TEST_RESULT -eq 0 ]; then
        echo "✅ 测试通过"
    else
        echo "⚠️ 测试返回非零码: $TEST_RESULT"
    fi
else
    echo "❌ 构建失败"
    exit 1
fi