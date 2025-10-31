#ifndef MESSAGE_H
#define MESSAGE_H

#include "common/Date.h"
#include <string>
#include <memory>

class User;

class Message {
private:
    std::string messageId;
    std::string content;
    Date timestamp;
    std::shared_ptr<User> sender;
    std::string messageType; // TEXT, IMAGE, PRODUCT_CARD, etc.

public:
    Message(const std::string& content, std::shared_ptr<User> sender, 
            const std::string& type = "TEXT");
    
    std::string getMessageHistory() const;
    bool isFromUser(const std::string& userId) const;
    bool containsKeyword(const std::string& keyword) const;
    
    std::string getMessageId() const { return messageId; }
    std::string getContent() const { return content; }
    Date getTimestamp() const { return timestamp; }
    std::shared_ptr<User> getSender() const { return sender; }
    std::string getMessageType() const { return messageType; }
};

#endif