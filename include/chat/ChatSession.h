#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "common/Date.h"
#include <vector>
#include <memory>
#include <string>

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
    void addParticipant(std::shared_ptr<User> user);
    void removeParticipant(std::shared_ptr<User> user);
    std::vector<std::shared_ptr<Message>> getMessageHistory() const;
    
    std::string getSessionId() const { return sessionId; }
    Date getStartTime() const { return startTime; }
    size_t getParticipantCount() const { return participants.size(); }
    size_t getMessageCount() const { return messages.size(); }
};

#endif