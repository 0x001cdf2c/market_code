#include "order/Order.h"
#include "order/OrderItem.h"
#include "payment/Payment.h"
#include <iostream>

Order::Order() : orderDate(Date::now()), totalAmount(0.0), status("PENDING") {
    orderId = "ORDER_" + std::to_string(std::hash<std::string>{}(orderDate.toString()));
}

double Order::calculateTotal() {
    totalAmount = 0.0;
    for (const auto& item : items) {
        totalAmount += item->calculateSubtotal();
    }
    return totalAmount;
}

void Order::updateStatus(const std::string& newStatus) {
    status = newStatus;
    std::cout << "订单 " << orderId << " 状态更新为: " << newStatus << std::endl;
}

void Order::generateInvoice() const {
    std::cout << "=== 发票 ===" << std::endl;
    std::cout << "订单ID: " << orderId << std::endl;
    std::cout << "总金额: " << totalAmount << std::endl;
    std::cout << "日期: " << orderDate.toString() << std::endl;
}

void Order::addItem(std::shared_ptr<OrderItem> item) {
    items.push_back(item);
    calculateTotal();
}