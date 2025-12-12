// tests/IntegrationTest_ChatSystem.cpp
#include <gtest/gtest.h>
#include "chat/ChatSession.h"
#include "chat/Message.h"
#include "user/Customer.h"
#include "user/Merchant.h"
#include "user/Admin.h"

class ChatSystemIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建不同类型的用户
        customer = std::make_shared<Customer>("13800138000", "password123");
        merchant = std::make_shared<Merchant>("13900139000", "password123", 
                                            "Apple Store", "LICENSE123");
        admin = std::make_shared<Admin>("13700137000", "password123", "NORMAL");
        
        // 创建用户列表
        users.push_back(customer);
        users.push_back(merchant);
    }
    
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Merchant> merchant;
    std::shared_ptr<Admin> admin;
    std::vector<std::shared_ptr<User>> users;
};

// 测试用例1: 完整聊天会话流程
TEST_F(ChatSystemIntegrationTest, CompleteChatSessionFlow) {
    // 1. 创建聊天会话 - 显式创建vector
    std::vector<std::shared_ptr<User>> participants = {customer, merchant};
    auto chatSession = std::make_shared<ChatSession>(participants);
    
    EXPECT_FALSE(chatSession->getSessionId().empty());
    
    // 2. 发送消息
    chatSession->sendMessage("你好，我想咨询商品信息", customer);
    chatSession->sendMessage("您好，请问有什么可以帮助您的？", merchant);
    
    // 3. 验证消息历史
    auto messageHistory = chatSession->getMessageHistory();
    EXPECT_EQ(messageHistory.size(), 2);
    
    // 4. 验证消息内容
    EXPECT_TRUE(messageHistory[0]->isFromUser(customer->getUserId()));
    EXPECT_TRUE(messageHistory[1]->isFromUser(merchant->getUserId()));
}


// 测试用例3: 商品卡片发送集成
TEST_F(ChatSystemIntegrationTest, ProductCardIntegration) {
    std::vector<std::shared_ptr<User>> participants = {customer, merchant};
    auto chatSession = std::make_shared<ChatSession>(participants);
    
    // 发送普通消息
    chatSession->sendMessage("请查看这个商品", merchant);
    
    // 发送商品卡片（系统消息）
    EXPECT_NO_THROW({
        chatSession->sendProductCard("P001");
    });
    
    // 验证会话中有相应记录
    auto messages = chatSession->getMessageHistory();
    EXPECT_GE(messages.size(), 1);
}

// 测试用例4: 多用户角色消息交互
TEST_F(ChatSystemIntegrationTest, MultiUserRoleInteraction) {
    // 添加管理员到参与者列表
    std::vector<std::shared_ptr<User>> participants = {customer, merchant, admin};
    auto chatSession = std::make_shared<ChatSession>(participants);
    
    // 各角色发送消息
    chatSession->sendMessage("客户咨询问题", customer);
    chatSession->sendMessage("商户回复", merchant);
    chatSession->sendMessage("管理员监控对话", admin);
    
    auto messages = chatSession->getMessageHistory();
    EXPECT_EQ(messages.size(), 3);
    
    // 验证消息来源多样性
    bool hasCustomerMsg = false, hasMerchantMsg = false, hasAdminMsg = false;
    for (const auto& msg : messages) {
        if (msg->isFromUser(customer->getUserId())) hasCustomerMsg = true;
        if (msg->isFromUser(merchant->getUserId())) hasMerchantMsg = true;
        if (msg->isFromUser(admin->getUserId())) hasAdminMsg = true;
    }
    
    EXPECT_TRUE(hasCustomerMsg);
    EXPECT_TRUE(hasMerchantMsg);
    EXPECT_TRUE(hasAdminMsg);
}

// 测试用例5: 消息搜索和过滤集成
TEST_F(ChatSystemIntegrationTest, MessageSearchAndFilterIntegration) {
    std::vector<std::shared_ptr<User>> participants = {customer, merchant};
    auto chatSession = std::make_shared<ChatSession>(participants);
    
    // 发送多种消息
    chatSession->sendMessage("请问iPhone 15有货吗？", customer);
    chatSession->sendMessage("iPhone 15有现货，价格5999元", merchant);
    chatSession->sendMessage("AirPods有优惠吗？", customer);
    chatSession->sendMessage("AirPods现在特价1299元", merchant);
    
    auto messages = chatSession->getMessageHistory();
    
    // 测试关键字搜索
    int iphoneMessages = 0;
    for (const auto& msg : messages) {
        if (msg->containsKeyword("iPhone") || msg->containsKeyword("iphone")) {
            iphoneMessages++;
        }
    }
    EXPECT_GE(iphoneMessages, 1);
    
    // 测试价格相关消息
    int priceMessages = 0;
    for (const auto& msg : messages) {
        if (msg->containsKeyword("5999") || msg->containsKeyword("1299")) {
            priceMessages++;
        }
    }
    EXPECT_GE(priceMessages, 1);
}