#include "order/OrderItem.h"
#include <sstream>
#include <stdexcept>

OrderItem::OrderItem(const std::string& prodId, const std::string& prodName, int qty, double price)
    : productId(prodId), productName(prodName), quantity(qty), unitPrice(price) {
    
    if (quantity <= 0) {
        throw std::invalid_argument("数量必须大于0");
    }
    if (unitPrice < 0) {
        throw std::invalid_argument("单价不能为负数");
    }
    
    // 生成订单项ID
    std::stringstream ss;
    ss << "ORDER_ITEM_" << std::hash<std::string>{}(productId + std::to_string(quantity));
    itemId = ss.str();
}

void OrderItem::updateQuantity(int newQuantity) {
    if (newQuantity <= 0) {
        throw std::invalid_argument("数量必须大于0");
    }
    quantity = newQuantity;
}

void OrderItem::updatePrice(double newPrice) {
    if (newPrice < 0) {
        throw std::invalid_argument("单价不能为负数");
    }
    unitPrice = newPrice;
}