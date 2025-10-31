#include "user/Admin.h"
#include "user/Merchant.h"
#include "user/User.h"
#include <iostream>
#include <algorithm>

Admin::Admin(const std::string& phone, const std::string& pwd, const std::string& level)
    : User(phone, pwd, "ADMIN"), adminLevel(level) {
    
    // 根据管理员级别设置基础权限
    if (adminLevel == "SUPER") {
        permissions = {"USER_MANAGEMENT", "SHOP_MANAGEMENT", "SYSTEM_CONFIG", "DATA_ANALYSIS"};
    } else if (adminLevel == "NORMAL") {
        permissions = {"USER_MANAGEMENT", "SHOP_MANAGEMENT"};
    } else {
        permissions = {"DATA_VIEW"};
    }
}

void Admin::manageUsers() {
    std::cout << "管理员 " << userId << " 正在管理用户..." << std::endl;
}

void Admin::viewSystemReports() const {
    std::cout << "=== 系统报告 ===" << std::endl;
    std::cout << "管理员级别: " << adminLevel << std::endl;
    std::cout << "权限数量: " << permissions.size() << std::endl;
    std::cout << "管理的店铺数量: " << managedShops.size() << std::endl;
}

void Admin::manageShops() {
    std::cout << "管理员 " << userId << " 正在管理店铺..." << std::endl;
    for (const auto& shop : managedShops) {
        std::cout << "管理店铺: " << shop->getShopName() << std::endl;
    }
}

void Admin::addPermission(const std::string& permission) {
    if (std::find(permissions.begin(), permissions.end(), permission) == permissions.end()) {
        permissions.push_back(permission);
        std::cout << "添加权限: " << permission << std::endl;
    }
}

bool Admin::hasPermission(const std::string& permission) const {
    return std::find(permissions.begin(), permissions.end(), permission) != permissions.end();
}

void Admin::suspendUser(const std::string& userId) {
    if (hasPermission("USER_MANAGEMENT")) {
        std::cout << "暂停用户: " << userId << std::endl;
    } else {
        std::cout << "权限不足，无法暂停用户" << std::endl;
    }
}

void Admin::activateUser(const std::string& userId) {
    if (hasPermission("USER_MANAGEMENT")) {
        std::cout << "激活用户: " << userId << std::endl;
    } else {
        std::cout << "权限不足，无法激活用户" << std::endl;
    }
}

void Admin::addManagedShop(std::shared_ptr<Merchant> shop) {
    managedShops.push_back(shop);
    std::cout << "添加管理店铺: " << shop->getShopName() << std::endl;
}

std::vector<std::string> Admin::generateSystemReport() const {
    std::vector<std::string> report;
    report.push_back("管理员ID: " + userId);
    report.push_back("级别: " + adminLevel);
    report.push_back("权限数量: " + std::to_string(permissions.size()));
    report.push_back("管理店铺数量: " + std::to_string(managedShops.size()));
    return report;
}