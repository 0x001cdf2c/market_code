#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <memory>

// 包含您的项目头文件
#include "order/Order.h"
#include "order/OrderItem.h"
#include "chat/Message.h"
#include "user/User.h"
#include "chat/ChatSession.h"
#include "payment/Payment.h"
#include "product/Product.h"

// 主函数 - AFL++ 文件输入模式
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    
    // 读取输入文件
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }
    
    // 读取文件内容
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    if (size == 0) {
        return 0;  // 空文件，跳过
    }
    
    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }
    
    std::string input(reinterpret_cast<char*>(buffer.data()), size);
    
    try {
        // ========== 测试 1: 订单项创建和边界测试 ==========
        if (size >= 4) {
            // 从输入数据中提取参数，测试各种边界情况
            std::string productId = "P" + input.substr(0, std::min(size_t(10), size));
            std::string productName = "Product" + input.substr(0, std::min(size_t(20), size));
            
            // 使用输入数据生成测试参数
            int quantity = 1;
            double price = 10.0;
            
            if (size > 0) {
                // 测试各种数量边界
                quantity = (static_cast<unsigned char>(buffer[0]) % 100);  // 0-99
                if (quantity == 0) quantity = 1;  // 避免0，除非我们想测试异常
            }
            
            if (size > 1) {
                // 测试各种价格边界
                price = static_cast<double>(static_cast<unsigned char>(buffer[1])) * 100.0;
                if (price < 0.01) price = 0.01;  // 最小价格
            }
            
            // 创建订单项 - 这里可能会抛出异常（如负数价格）
            auto orderItem = std::make_shared<OrderItem>(productId, productName, quantity, price);
            
            // 测试订单项功能
            double subtotal = orderItem->calculateSubtotal();
            
            // 测试更新功能 - 使用更多输入数据
            if (size > 2) {
                int newQuantity = (static_cast<unsigned char>(buffer[2]) % 50);
                double newPrice = static_cast<double>(static_cast<unsigned char>(buffer[3])) * 50.0;
                
                // 测试更新操作
                if (newQuantity > 0) {
                    orderItem->updateQuantity(newQuantity);
                }
                
                if (newPrice > 0) {
                    orderItem->updatePrice(newPrice);
                }
                
                // 重新计算小计
                orderItem->calculateSubtotal();
            }
            
            // 测试订单管理
            Order order;
            order.addItem(orderItem);
            double total = order.calculateTotal();
            
            // 测试订单状态更新
            if (size > 4) {
                std::string status = (buffer[4] % 2 == 0) ? "PAID" : "PENDING";
                order.updateStatus(status);
            }
        }
        
        // ========== 测试 2: 消息处理系统 ==========
        if (size >= 1) {
            // 创建测试用户
            auto user = std::make_shared<User>("test_user", "password", "CUSTOMER");
            
            // 测试各种消息长度
            std::string messageContent(input);
            if (messageContent.length() > 10000) {
                messageContent = messageContent.substr(0, 10000);  // 限制长度
            }
            
            auto message = std::make_shared<Message>(messageContent, user);
            
            // 测试消息功能
            std::string history = message->getMessageHistory();
            bool isFromUser = message->isFromUser("test_user");
            
            // 测试关键词搜索 - 使用输入数据作为关键词
            if (size >= 3) {
                std::string keyword = input.substr(0, std::min(size_t(50), size));
                bool contains = message->containsKeyword(keyword);
                
                // 测试空关键词和特殊字符
                message->containsKeyword("");
                message->containsKeyword("!@#$%");
            }
        }
        
        // ========== 测试 3: 聊天会话系统 ==========
        if (size >= 10) {
            // 创建多个用户
            auto customer = std::make_shared<User>("customer", "pass", "CUSTOMER");
            auto merchant = std::make_shared<User>("merchant", "pass", "MERCHANT");
            
            std::vector<std::shared_ptr<User>> participants = {customer, merchant};
            auto chatSession = std::make_shared<ChatSession>(participants);
            
            // 发送消息测试
            std::string messageText = input.substr(0, std::min(size_t(500), size));
            chatSession->sendMessage(messageText, customer);
            
            // 测试消息历史
            auto history = chatSession->getMessageHistory();
            
            // 测试动态参与者管理
            if (size > 20) {
                auto admin = std::make_shared<User>("admin", "pass", "ADMIN");
                chatSession->addParticipant(admin);
                
                // 发送更多消息
                chatSession->sendMessage("Admin joined", admin);
            }
            
            // 测试商品卡片功能
            if (size > 5) {
                std::string productId = "P" + input.substr(5, 3);
                chatSession->sendProductCard(productId);
            }
        }
        
        // ========== 测试 4: 支付系统 ==========
        if (size >= 2) {
            double amount = static_cast<double>(static_cast<unsigned char>(buffer[0])) * 10.0 + 
                           static_cast<double>(static_cast<unsigned char>(buffer[1]));
            
            if (amount > 0) {
                auto payment = std::make_shared<Payment>(amount);
                
                // 测试支付处理
                bool paymentResult = payment->processPayment();
                
                // 测试退款流程
                if (size > 10 && (buffer[2] % 2 == 0)) {
                    bool refundResult = payment->refund();
                }
            }
        }
        
        // ========== 测试 5: 商品管理系统 ==========
        if (size >= 5) {
            std::string productName = "Product" + input.substr(0, std::min(size_t(20), size));
            std::string description = "Description" + input.substr(0, std::min(size_t(100), size));
            double price = static_cast<double>(static_cast<unsigned char>(buffer[0])) * 100.0;
            std::string category = "Category" + input.substr(0, std::min(size_t(10), size));
            
            auto product = std::make_shared<Product>(productName, description, price, category);
            
            // 测试商品信息更新
            if (size > 15) {
                std::string newName = "Updated" + input.substr(10, std::min(size_t(15), size-10));
                std::string newDesc = "Updated" + input.substr(20, std::min(size_t(50), size-20));
                double newPrice = static_cast<double>(static_cast<unsigned char>(buffer[5])) * 50.0;
                
                product->updateInfo(newName, newDesc, newPrice);
            }
            
            // 测试商品状态管理
            if (size > 8) {
                std::string status = (buffer[6] % 2 == 0) ? "ACTIVE" : "INACTIVE";
                product->changeStatus(status);
            }
        }
        
        // ========== 测试 6: 边界和压力测试 ==========
        
        // 测试极长输入
        if (size > 1000) {
            std::string longString(size, 'A');  // 创建超长字符串
            // 注意：这里可能会暴露内存或性能问题
        }
        
        // 测试特殊字符和二进制数据
        if (size > 0) {
            // 检查是否包含大量空字节
            size_t nullCount = 0;
            for (size_t i = 0; i < size; ++i) {
                if (buffer[i] == 0) nullCount++;
            }
            
            // 如果大部分是空字节，测试边界情况
            if (nullCount > size / 2) {
                // 这种输入可能触发边界条件
            }
        }
        
        // 测试数字边界
        if (size >= 8) {
            // 尝试从输入中提取各种数字组合
            int32_t intValue = 0;
            double doubleValue = 0.0;
            
            // 使用前几个字节构造整数和浮点数
            memcpy(&intValue, buffer.data(), std::min(size_t(4), size));
            memcpy(&doubleValue, buffer.data(), std::min(size_t(8), size));
            
            // 这些值可能非常大或非常小，测试边界情况
        }
        
    } catch (const std::exception& e) {
        // 正常处理异常 - AFL++ 不会将其视为崩溃
        // 但会记录异常路径，有助于提高测试覆盖率
    } catch (...) {
        // 捕获所有其他异常
    }
    
    return 0;
}