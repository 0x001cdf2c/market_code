#include <gtest/gtest.h>
#include "chat/Message.h"
#include "user/User.h"

class MessageTest : public ::testing::Test {
protected:
    void SetUp() override {
        sender = std::make_shared<User>("13800138000", "password123", "CUSTOMER");
        message = std::make_shared<Message>("Hello, this is a test message!", sender);
    }
    
    std::shared_ptr<User> sender;
    std::shared_ptr<Message> message;
};

//测试用例1: 正常创建消息
TEST_F(MessageTest, CreateMessageSuccessfully) {
    EXPECT_NO_THROW({
        Message msg("Test message", sender);
    });
    
    EXPECT_EQ(message->getContent(), "Hello, this is a test message!");
    EXPECT_EQ(message->getSender(), sender);
}

//测试用例2: 消息历史格式正确
TEST_F(MessageTest, MessageHistoryFormatCorrect) {
    std::string history = message->getMessageHistory();
    
    //检查是否包含时间戳格式
    EXPECT_TRUE(history.find("]") != std::string::npos);
    EXPECT_TRUE(history.find(sender->getUserId()) != std::string::npos);
    EXPECT_TRUE(history.find("Hello, this is a test message!") != std::string::npos);
}

//测试用例3: 检查消息来源用户
TEST_F(MessageTest, CheckMessageFromUser) {
    EXPECT_TRUE(message->isFromUser(sender->getUserId()));
    
    std::shared_ptr<User> otherUser = std::make_shared<User>("13900139000", "password", "CUSTOMER");
    EXPECT_FALSE(message->isFromUser(otherUser->getUserId()));
}

//测试用例4: 包含关键字搜索（区分大小写）
TEST_F(MessageTest, ContainsKeywordCaseSensitive) {
    // 默认实现是不区分大小写的，但测试区分大小写的场景
    auto caseSensitiveMessage = std::make_shared<Message>("Hello TEST Message", sender);
    
    EXPECT_TRUE(caseSensitiveMessage->containsKeyword("test")); // 小写搜索
    EXPECT_TRUE(caseSensitiveMessage->containsKeyword("TEST")); // 大写搜索
    EXPECT_TRUE(caseSensitiveMessage->containsKeyword("Test")); // 混合大小写
}

//测试用例5: 不包含关键字
TEST_F(MessageTest, DoesNotContainKeyword) {
    EXPECT_FALSE(message->containsKeyword("nonexistent"));
    EXPECT_FALSE(message->containsKeyword("Goodbye"));
}

//测试用例6: 空关键字搜索
TEST_F(MessageTest, EmptyKeywordSearch) {
    EXPECT_TRUE(message->containsKeyword("")); // 空字符串应该匹配所有消息
}

//测试用例7: 关键字在消息开头
TEST_F(MessageTest, KeywordAtBeginning) {
    auto msg = std::make_shared<Message>("Hello world test message", sender);
    EXPECT_TRUE(msg->containsKeyword("Hello"));
}

//测试用例8: 关键字在消息中间
TEST_F(MessageTest, KeywordInMiddle) {
    auto msg = std::make_shared<Message>("This is a test message", sender);
    EXPECT_TRUE(msg->containsKeyword("test"));
}

//测试用例9: 关键字在消息结尾
TEST_F(MessageTest, KeywordAtEnd) {
    auto msg = std::make_shared<Message>("This is a test", sender);
    EXPECT_TRUE(msg->containsKeyword("test"));
}

//测试用例10: 特殊字符关键字搜索
TEST_F(MessageTest, SpecialCharactersKeyword) {
    auto specialMessage = std::make_shared<Message>("Price: $100.50, Discount: 15%", sender);
    
    EXPECT_TRUE(specialMessage->containsKeyword("$100.50"));
    EXPECT_TRUE(specialMessage->containsKeyword("15%"));
}

//测试用例11: 长消息关键字搜索
TEST_F(MessageTest, LongMessageKeywordSearch) {
    std::string longContent = "This is a very long message that contains multiple keywords "
                             "for testing purposes. We need to ensure that the keyword "
                             "search functionality works correctly even with lengthy text.";
    
    auto longMessage = std::make_shared<Message>(longContent, sender);
    
    EXPECT_TRUE(longMessage->containsKeyword("keywords"));
    EXPECT_TRUE(longMessage->containsKeyword("lengthy"));
    EXPECT_FALSE(longMessage->containsKeyword("nonexistentword"));
}