#ifndef MERCHANT_H
#define MERCHANT_H

#include "User.h"
#include <vector>
#include <string>

class Product;

class Merchant : public User {
private:
    std::string shopName;
    float shopRating;
    std::string businessLicense;
    std::vector<std::shared_ptr<Product>> publishedProducts;

public:
    Merchant(const std::string& phone, const std::string& pwd, 
             const std::string& shopName, const std::string& license);
    
    void publishProduct(std::shared_ptr<Product> product);
    void manageOrders();
    void viewSalesReport() const;
    void updateShopRating(float newRating);
    
    std::string getShopName() const { return shopName; }
    float getShopRating() const { return shopRating; }
};

#endif