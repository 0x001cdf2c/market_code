#include "user/User.h"
#include <algorithm>

User::User(const std::string& phone, const std::string& pwd, const std::string& type)
    : phoneNumber(phone), password(pwd), userType(type), registrationDate(Date::now()) {
    // 简单ID生成逻辑
    userId = "USER_" + std::to_string(std::hash<std::string>{}(phone + type));
}

bool User::login(const std::string& inputPassword) {
    return password == inputPassword;
}

void User::logout() {
    // 清理登录状态
    // 实际项目中这里会有更复杂的逻辑
}

void User::updateProfile(const std::string& newPhone, const std::string& newPassword) {
    if (!newPhone.empty()) {
        phoneNumber = newPhone;
    }
    if (!newPassword.empty()) {
        password = newPassword;
    }
}