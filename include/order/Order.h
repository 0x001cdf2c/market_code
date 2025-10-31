#ifndef ORDER_H
#define ORDER_H

#include "common/Date.h"
#include <string>
#include <vector>
#include <memory>

class OrderItem;
class Payment;

class Order {
private:
    std::string orderId;
    Date orderDate;
    double totalAmount;
    std::string status;
    std::string paymentMethod;
    std::vector<std::shared_ptr<OrderItem>> items;
    std::shared_ptr<Payment> payment;

public:
    Order();
    
    double calculateTotal();
    void updateStatus(const std::string& newStatus);
    void generateInvoice() const;
    void addItem(std::shared_ptr<OrderItem> item);
    
    std::string getOrderId() const { return orderId; }
    double getTotalAmount() const { return totalAmount; }
    std::string getStatus() const { return status; }
};

#endif