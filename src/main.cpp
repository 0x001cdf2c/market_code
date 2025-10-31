#include <iostream>
#include <memory>
#include "user/Customer.h"
#include "user/Merchant.h"
#include "user/Admin.h"
#include "product/Product.h"
#include "order/Order.h"
#include "order/OrderItem.h"
#include "payment/Payment.h"

int main() {
    // 创建用户
    auto customer = std::make_shared<Customer>("13800138000", "password123");
    auto merchant = std::make_shared<Merchant>("13900139000", "merchant123", 
                                              "优质数码店", "LICENSE123");
    
    // 创建商品
    auto product = std::make_shared<Product>("iPhone 15", "最新款苹果手机", 5999.0, "数码");
    
    // 商户发布商品
    merchant->publishProduct(product);
    
    // 创建订单
    auto order = std::make_shared<Order>();
    auto orderItem = std::make_shared<OrderItem>(product->getProductId(), 1, product->getPrice());
    order->addItem(orderItem);
    
    // 处理支付
    auto payment = std::make_shared<Payment>(order->getTotalAmount());
    payment->processPayment();
    
    // 更新订单状态
    order->updateStatus("COMPLETED");
    
    // 客户查看购买历史
    customer->viewPurchaseHistory();
    
    std::cout << "系统演示完成!" << std::endl;
    
    return 0;
}