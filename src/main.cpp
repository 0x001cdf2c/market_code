#include <iostream>
#include <memory>
#include "user/Customer.h"
#include "user/Merchant.h"
#include "user/Admin.h"
#include "product/Product.h"
#include "product/ProductCategory.h"
#include "order/Order.h"
#include "order/OrderItem.h"
#include "payment/Payment.h"
#include "chat/ChatSession.h"
#include "chat/Message.h"

int main() {
    std::cout << "=== 商场交易系统演示 ===" << std::endl;
    
    // 创建用户
    auto customer = std::make_shared<Customer>("13800138000", "password123");
    auto merchant = std::make_shared<Merchant>("13900139000", "merchant123", 
                                              "优质数码店", "LICENSE123");
    auto admin = std::make_shared<Admin>("18800188000", "admin123", "SUPER");
    
    // 创建商品分类
    auto electronicsCategory = std::make_shared<ProductCategory>("电子产品");
    auto phoneCategory = std::make_shared<ProductCategory>("手机", "电子产品");
    electronicsCategory->addSubCategory(phoneCategory);
    
    // 创建商品
    auto product = std::make_shared<Product>("iPhone 15", "最新款苹果手机", 5999.0, "手机");
    phoneCategory->addProduct(product);
    
    // 商户发布商品
    merchant->publishProduct(product);
    
    // 创建订单
    auto order = std::make_shared<Order>();
    auto orderItem = std::make_shared<OrderItem>(
        product->getProductId(), product->getProductName(), 1, product->getPrice()
    );
    order->addItem(orderItem);
    
    // 处理支付
    auto payment = std::make_shared<Payment>(order->getTotalAmount());
    payment->processPayment();
    
    // 更新订单状态
    order->updateStatus("COMPLETED");
    
    // 创建聊天会话
    std::vector<std::shared_ptr<User>> chatParticipants = {customer, merchant};
    auto chatSession = std::make_shared<ChatSession>(chatParticipants);
    
    // 发送消息
    chatSession->sendMessage("这个手机有现货吗？", customer);
    chatSession->sendMessage("有现货，今天可以发货", merchant);
    chatSession->sendProductCard(product->getProductId());
    
    // 管理员操作
    admin->addManagedShop(merchant);
    admin->viewSystemReports();
    admin->suspendUser("某个用户ID");
    
    // 客户查看购买历史
    customer->viewPurchaseHistory();
    
    // 显示聊天历史
    auto messages = chatSession->getMessageHistory();
    std::cout << "\n=== 聊天历史 ===" << std::endl;
    for (const auto& msg : messages) {
        std::cout << msg->getMessageHistory() << std::endl;
    }
    
    std::cout << "\n系统演示完成!" << std::endl;
    
    return 0;
}