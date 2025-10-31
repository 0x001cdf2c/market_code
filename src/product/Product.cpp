#include "product/Product.h"
#include <iostream>

Product::Product(const std::string& name, const std::string& desc, 
                 double price, const std::string& category)
    : productName(name), description(desc), price(price), 
      category(category), status("ACTIVE") {
    productId = "PROD_" + std::to_string(std::hash<std::string>{}(name + desc));
}

void Product::updateInfo(const std::string& newName, const std::string& newDesc, double newPrice) {
    if (!newName.empty()) productName = newName;
    if (!newDesc.empty()) description = newDesc;
    if (newPrice > 0) price = newPrice;
}

void Product::changeStatus(const std::string& newStatus) {
    status = newStatus;
    std::cout << "商品状态更新为: " << newStatus << std::endl;
}

void Product::addImage(const std::string& imageUrl) {
    images.push_back(imageUrl);
}