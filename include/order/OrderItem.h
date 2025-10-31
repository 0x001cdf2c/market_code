#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <string>

class OrderItem {
private:
    std::string itemId;
    int quantity;
    double unitPrice;
    std::string productId;
    std::string productName;

public:
    OrderItem(const std::string& prodId, const std::string& prodName, int qty, double price);
    
    double calculateSubtotal() const { return quantity * unitPrice; }
    void updateQuantity(int newQuantity);
    void updatePrice(double newPrice);
    
    std::string getItemId() const { return itemId; }
    int getQuantity() const { return quantity; }
    double getUnitPrice() const { return unitPrice; }
    std::string getProductId() const { return productId; }
    std::string getProductName() const { return productName; }
};

#endif