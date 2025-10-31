#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <vector>
#include <memory>

// 前向声明
class Order;

class Customer : public User {
private:
    std::string customerLevel;
    int membershipPoints;
    std::vector<std::shared_ptr<Order>> purchaseHistory;

public:
    Customer(const std::string& phone, const std::string& pwd);
    
    void viewPurchaseHistory() const;
    void addToCart(const std::string& productId, int quantity);
    void upgradeLevel();
    void addPoints(int points);
    
    std::string getCustomerLevel() const { return customerLevel; }
    int getMembershipPoints() const { return membershipPoints; }
};

#endif