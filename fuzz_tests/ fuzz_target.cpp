#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// 包含您的项目头文件
#include "order/Order.h"
#include "order/OrderItem.h"
#include "chat/Message.h"
#include "user/User.h"
#include <testkit.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;  // 空输入，跳过
    }
    
    try {
        // 将模糊数据转换为字符串
        std::string input(reinterpret_cast<const char*>(data), size);
        
        // ========== 测试 1: 订单项创建 ==========
        if (size >= 4) {
            // 提取测试数据
            std::string productId = "P" + input.substr(0, 3);
            std::string productName = "Product" + input.substr(0, 3);
            
            int quantity = 1;
            double price = 10.0;
            
            if (size > 0) {
                quantity = (static_cast<unsigned char>(data[0]) % 10) + 1;
            }
            
            if (size > 1) {
                price = static_cast<double>(static_cast<unsigned char>(data[1])) + 1.0;
            }
            
            // 创建订单项
            auto orderItem = std::make_shared<OrderItem>(productId, productName, quantity, price);
            
            // 测试订单项功能
            orderItem->calculateSubtotal();
            
            // 测试更新功能
            if (size > 2) {
                int newQuantity = (static_cast<unsigned char>(data[2]) % 10) + 1;
                double newPrice = static_cast<double>(static_cast<unsigned char>(data[3])) + 1.0;
                
                if (newQuantity > 0) {
                    orderItem->updateQuantity(newQuantity);
                }
                
                if (newPrice > 0) {
                    orderItem->updatePrice(newPrice);
                }
            }
        }
        
        // ========== 测试 2: 消息处理 ==========
        if (size >= 1) {
            // 创建用户
            auto user = std::make_shared<User>("test_user", "password", "CUSTOMER");
            
            // 创建消息
            std::string messageContent(input);
            if (messageContent.length() > 1000) {
                messageContent = messageContent.substr(0, 1000);
            }
            
            auto message = std::make_shared<Message>(messageContent, user);
            
            // 测试消息功能
            message->getMessageHistory();
            message->isFromUser("test_user");
            
            // 测试关键词搜索
            if (size >= 3) {
                std::string keyword = input.substr(0, std::min(size_t(10), size));
                message->containsKeyword(keyword);
            }
        }
        
        // ========== 测试 3: 边界条件 ==========
        // 制造一些已知的崩溃点用于验证
        std::string inputStr(input);
        
        if (inputStr.find("CRASH_ME") != std::string::npos) {
            // 制造一个崩溃
            volatile int* ptr = nullptr;
            *ptr = 42;  // 段错误
        }
        
        if (inputStr.find("ABORT_ME") != std::string::npos) {
            abort();  // 中止程序
        }
        
        if (inputStr.find("ASSERT_ME") != std::string::npos) {
            assert(false && "Assertion triggered by fuzzer");
        }
        
    } catch (const std::exception& e) {
        // 正常处理异常 - AFL++ 不会将其视为崩溃
    } catch (...) {
        // 捕获所有其他异常
    }
    
    return 0;
}