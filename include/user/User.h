#ifndef USER_H
#define USER_H

#include "common/Date.h"
#include <string>
#include <memory>

class User {
protected:
    std::string userId;
    std::string phoneNumber;
    std::string password;
    std::string userType;
    Date registrationDate;

public:
    User(const std::string& phone, const std::string& pwd, const std::string& type);
    virtual ~User() = default;
    
    // 虚函数
    virtual bool login(const std::string& inputPassword);
    virtual void logout();
    virtual void updateProfile(const std::string& newPhone, const std::string& newPassword);
    
    // Getter方法
    std::string getUserId() const { return userId; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getUserType() const { return userType; }
    Date getRegistrationDate() const { return registrationDate; }
};

#endif