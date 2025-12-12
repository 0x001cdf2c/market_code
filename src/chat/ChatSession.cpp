#include "chat/ChatSession.h"
#include "chat/Message.h"
#include "user/User.h"
#include <iostream>
#include <sstream>
#include <algorithm>
ChatSession::ChatSession(const std::vector<std::shared_ptr<User>>& users)
    : participants(users), startTime(Date::now()) {
    // 生成会话ID
    std::stringstream ss;
    ss << "CHAT_" << std::hash<std::string>{}(startTime.toString());
    for (const auto& user : users) {
        ss << "_" << user->getUserId();
    }
    sessionId = ss.str();
    
    std::cout << "创建聊天会话: " << sessionId << std::endl;
}

void ChatSession::sendMessage(const std::string& content, std::shared_ptr<User> sender) {
    auto message = std::make_shared<Message>(content, sender);
    messages.push_back(message);
    
    std::cout << "用户 " << sender->getUserId() << " 发送消息: " << content << std::endl;
}

void ChatSession::sendProductCard(const std::string& productId) {
    std::string productCard = "[商品卡片] ID: " + productId;
    // 在实际应用中，这里会查询商品信息并生成富文本卡片
    std::cout << "发送商品卡片: " << productCard << std::endl;
    
    // 创建一个系统消息表示商品卡片
    // auto systemUser = std::make_shared<User>("system", "system", "SYSTEM");
    // sendMessage(productCard, systemUser);
}

void ChatSession::addParticipant(std::shared_ptr<User> user) {
    participants.push_back(user);
    std::cout << "添加参与者: " << user->getUserId() << std::endl;
}

void ChatSession::removeParticipant(std::shared_ptr<User> user) {
    participants.erase(
        std::remove_if(participants.begin(), participants.end(),
                      [&](const std::shared_ptr<User>& u) { return u->getUserId() == user->getUserId(); }),
        participants.end()
    );
    std::cout << "移除参与者: " << user->getUserId() << std::endl;
}

std::vector<std::shared_ptr<Message>> ChatSession::getMessageHistory() const {
    return messages;
}