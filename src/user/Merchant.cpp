#include "user/Merchant.h"
#include "product/Product.h"
#include <iostream>

Merchant::Merchant(const std::string& phone, const std::string& pwd,
                   const std::string& shopName, const std::string& license)
    : User(phone, pwd, "MERCHANT"), shopName(shopName), 
      shopRating(0.0f), businessLicense(license) {}

void Merchant::publishProduct(std::shared_ptr<Product> product) {
    publishedProducts.push_back(product);
    std::cout << "商户 " << shopName << " 发布了商品: " << product->getProductName() << std::endl;
}

void Merchant::manageOrders() {
    std::cout << "管理订单功能" << std::endl;
}

void Merchant::viewSalesReport() const {
    std::cout << "=== 销售报告 ===" << std::endl;
    std::cout << "店铺: " << shopName << std::endl;
    std::cout << "评分: " << shopRating << std::endl;
    std::cout << "商品数量: " << publishedProducts.size() << std::endl;
}

void Merchant::updateShopRating(float newRating) {
    shopRating = newRating;
}