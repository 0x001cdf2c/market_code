#include "payment/Payment.h"
#include <iostream>

Payment::Payment(double amount) : amount(amount), paymentDate(Date::now()), status("PENDING") {
    paymentId = "PAY_" + std::to_string(std::hash<std::string>{}(paymentDate.toString()));
}

bool Payment::processPayment() {
    // 模拟支付处理
    std::cout << "处理支付: " << amount << "元" << std::endl;
    status = "COMPLETED";
    return true;
}

bool Payment::refund() {
    std::cout << "退款处理: " << amount << "元" << std::endl;
    status = "REFUNDED";
    return true;
}