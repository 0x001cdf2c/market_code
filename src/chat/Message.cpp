#include "chat/Message.h"
#include "user/User.h"
#include <sstream>
#include <algorithm>

Message::Message(const std::string& content, std::shared_ptr<User> sender, 
                 const std::string& type)
    : content(content), sender(sender), messageType(type), timestamp(Date::now()) {
    // 生成消息ID
    std::stringstream ss;
    ss << "MSG_" << std::hash<std::string>{}(timestamp.toString() + content);
    messageId = ss.str();
}

std::string Message::getMessageHistory() const {
    std::stringstream ss;
    ss << "[" << timestamp.toString() << "] " 
       << sender->getUserId() << ": " << content;
    return ss.str();
}

bool Message::isFromUser(const std::string& userId) const {
    return sender->getUserId() == userId;
}

bool Message::containsKeyword(const std::string& keyword) const {
    std::string lowerContent = content;
    std::string lowerKeyword = keyword;
    
    // 转换为小写进行不区分大小写的搜索
    std::transform(lowerContent.begin(), lowerContent.end(), lowerContent.begin(), ::tolower);
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
    
    return lowerContent.find(lowerKeyword) != std::string::npos;
}