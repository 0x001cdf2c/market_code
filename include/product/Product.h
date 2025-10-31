#ifndef PRODUCT_H
#define PRODUCT_H

#include "common/Date.h"
#include <string>
#include <vector>
#include <memory>

class ProductCategory;

class Product {
private:
    std::string productId;
    std::string productName;
    std::string description;
    double price;
    std::string category;
    std::vector<std::string> images;
    std::string status;
    std::shared_ptr<ProductCategory> productCategory;

public:
    Product(const std::string& name, const std::string& desc, 
            double price, const std::string& category);
    
    void updateInfo(const std::string& newName, const std::string& newDesc, double newPrice);
    void changeStatus(const std::string& newStatus);
    void addImage(const std::string& imageUrl);
    
    // Getter方法
    std::string getProductId() const { return productId; }
    std::string getProductName() const { return productName; }
    double getPrice() const { return price; }
    std::string getStatus() const { return status; }
};

#endif