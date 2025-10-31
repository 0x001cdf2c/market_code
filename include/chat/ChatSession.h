#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "common/Date.h"
#include <vector>
#include <memory>

class User;
class Message;

class ChatSession {
private:
    std::string sessionId;
    std::vector<std::shared_ptr<User>> participants;
    Date startTime;
    std::vector<std::shared_ptr<Message>> messages;

public:
    ChatSession(const std::vector<std::shared_ptr<User>>& users);
    
    void sendMessage(const std::string& content, std::shared_ptr<User> sender);
    void sendProductCard(const std::string& productId);
    
    std::string getSessionId() const { return sessionId; }
};

#endif