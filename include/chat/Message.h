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

public:
    Message(const std::string& content, std::shared_ptr<User> sender);
    
    std::string getMessageHistory() const;
    
    std::string getMessageId() const { return messageId; }
    std::string getContent() const { return content; }
    Date getTimestamp() const { return timestamp; }
};

#endif