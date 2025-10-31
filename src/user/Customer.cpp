#include "user/Customer.h"
#include "order/Order.h"
#include <iostream>

Customer::Customer(const std::string& phone, const std::string& pwd)
    : User(phone, pwd, "CUSTOMER"), customerLevel("BRONZE"), membershipPoints(0) {}

void Customer::viewPurchaseHistory() const {
    std::cout << "=== 购买历史 ===" << std::endl;
    for (const auto& order : purchaseHistory) {
        std::cout << "订单ID: " << order->getOrderId() 
                  << ", 金额: " << order->getTotalAmount() << std::endl;
    }
}

void Customer::addToCart(const std::string& productId, int quantity) {
    // 购物车添加逻辑
    std::cout << "添加商品 " << productId << " 数量 " << quantity << " 到购物车" << std::endl;
}

void Customer::upgradeLevel() {
    if (membershipPoints >= 1000) customerLevel = "GOLD";
    else if (membershipPoints >= 500) customerLevel = "SILVER";
}

void Customer::addPoints(int points) {
    membershipPoints += points;
    upgradeLevel();
}