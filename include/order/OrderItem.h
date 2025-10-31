#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <string>

class OrderItem {
private:
    std::string itemId;
    int quantity;
    double unitPrice;
    std::string productId;

public:
    OrderItem(const std::string& prodId, int qty, double price);
    
    double calculateSubtotal() const { return quantity * unitPrice; }
    
    std::string getItemId() const { return itemId; }
    int getQuantity() const { return quantity; }
    double getUnitPrice() const { return unitPrice; }
};

#endif