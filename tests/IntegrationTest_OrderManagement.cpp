// tests/IntegrationTest_OrderManagement.cpp
#include <gtest/gtest.h>
#include "order/Order.h"
#include "order/OrderItem.h"
#include "payment/Payment.h"
#include "user/Customer.h"

class OrderManagementIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建测试客户
        customer = std::make_shared<Customer>("13800138000", "password123");
        
        // 创建订单
        order = std::make_shared<Order>();
        
        // 创建订单项
        item1 = std::make_shared<OrderItem>("P001", "iPhone 15", 2, 5999.99);
        item2 = std::make_shared<OrderItem>("P002", "AirPods", 1, 1299.99);
    }
    
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Order> order;
    std::shared_ptr<OrderItem> item1, item2;
};

// 测试用例1: 完整订单创建流程
TEST_F(OrderManagementIntegrationTest, CompleteOrderCreationFlow) {
    // 1. 添加订单项到订单
    order->addItem(item1);
    order->addItem(item2);
    
    // 2. 计算总金额
    double total = order->calculateTotal();
    double expectedTotal = (2 * 5999.99) + (1 * 1299.99);
    EXPECT_DOUBLE_EQ(total, expectedTotal);
    
    // 3. 创建支付
    auto payment = std::make_shared<Payment>(total);
    EXPECT_EQ(payment->getAmount(), total);
    EXPECT_EQ(payment->getStatus(), "PENDING");
    
    // 4. 处理支付
    bool paymentResult = payment->processPayment();
    EXPECT_TRUE(paymentResult);
    EXPECT_EQ(payment->getStatus(), "COMPLETED");
    
    // 5. 更新订单状态
    order->updateStatus("PAID");
    
    // 验证完整流程
    EXPECT_EQ(order->getStatus(), "PAID");
    EXPECT_DOUBLE_EQ(order->getTotalAmount(), expectedTotal);
}

// 测试用例2: 订单项更新影响订单总额
TEST_F(OrderManagementIntegrationTest, OrderItemUpdateAffectsOrderTotal) {
    // 初始添加商品
    order->addItem(item1);
    double initialTotal = order->calculateTotal();
    EXPECT_DOUBLE_EQ(initialTotal, 2 * 5999.99);
    
    // 更新订单项数量
    item1->updateQuantity(3);
    order->calculateTotal(); // 重新计算
    
    double updatedTotal = order->getTotalAmount();
    EXPECT_DOUBLE_EQ(updatedTotal, 3 * 5999.99);
    EXPECT_NE(initialTotal, updatedTotal);
}

// 测试用例3: 支付失败场景
TEST_F(OrderManagementIntegrationTest, PaymentFailureScenario) {
    order->addItem(item1);
    double total = order->calculateTotal();
    
    auto payment = std::make_shared<Payment>(total);
    
    // 模拟支付失败（在实际系统中可能有更复杂的逻辑）
    // 这里我们测试状态回滚
    order->updateStatus("PAYMENT_FAILED");
    EXPECT_EQ(order->getStatus(), "PAYMENT_FAILED");
    
    // 支付状态应保持PENDING或失败状态
    EXPECT_NE(payment->getStatus(), "COMPLETED");
}

// 测试用例4: 订单发票生成
TEST_F(OrderManagementIntegrationTest, OrderInvoiceGeneration) {
    order->addItem(item1);
    order->addItem(item2);
    order->calculateTotal();
    
    // 测试发票生成不抛出异常
    EXPECT_NO_THROW({
        order->generateInvoice();
    });
    
    // 验证订单信息完整
    EXPECT_FALSE(order->getOrderId().empty());
    EXPECT_GT(order->getTotalAmount(), 0);
}

// 测试用例5: 退款流程集成
TEST_F(OrderManagementIntegrationTest, RefundProcessIntegration) {
    order->addItem(item1);
    double total = order->calculateTotal();
    
    auto payment = std::make_shared<Payment>(total);
    payment->processPayment();
    
    // 执行退款
    bool refundResult = payment->refund();
    EXPECT_TRUE(refundResult);
    EXPECT_EQ(payment->getStatus(), "REFUNDED");
    
    // 订单状态应相应更新
    order->updateStatus("REFUNDED");
    EXPECT_EQ(order->getStatus(), "REFUNDED");
}