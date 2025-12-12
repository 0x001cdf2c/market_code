#include <gtest/gtest.h>
#include "order/OrderItem.h"
#include <stdexcept>

class OrderItemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建正常的订单项用于测试
        normalItem = std::make_shared<OrderItem>("P001", "iPhone 15", 2, 5999.99);
    }
    
    std::shared_ptr<OrderItem> normalItem;
};

//测试用例1: 正常创建订单项
TEST_F(OrderItemTest, CreateValidOrderItem) {
    EXPECT_NO_THROW({
        OrderItem item("P001", "iPhone 15", 1, 5999.99);
    });
    
    EXPECT_EQ(normalItem->getProductId(), "P001");
    EXPECT_EQ(normalItem->getProductName(), "iPhone 15");
    EXPECT_EQ(normalItem->getQuantity(), 2);
    EXPECT_DOUBLE_EQ(normalItem->getUnitPrice(), 5999.99);
}

//测试用例2: 数量为0时抛出异常
TEST_F(OrderItemTest, CreateWithZeroQuantityThrowsException) {
    EXPECT_THROW({
        OrderItem item("P001", "iPhone 15", 0, 5999.99);
    }, std::invalid_argument);
}

//测试用例3: 数量为负数时抛出异常
TEST_F(OrderItemTest, CreateWithNegativeQuantityThrowsException) {
    EXPECT_THROW({
        OrderItem item("P001", "iPhone 15", -1, 5999.99);
    }, std::invalid_argument);
}

//测试用例4: 单价为负数时抛出异常
TEST_F(OrderItemTest, CreateWithNegativePriceThrowsException) {
    EXPECT_THROW({
        OrderItem item("P001", "iPhone 15", 1, -100.0);
    }, std::invalid_argument);
}

//测试用例5: 计算小计正确性
TEST_F(OrderItemTest, CalculateSubtotalCorrectly) {
    double expectedSubtotal = 2 * 5999.99;
    EXPECT_DOUBLE_EQ(normalItem->calculateSubtotal(), expectedSubtotal);
}

//测试用例6: 正常更新数量
TEST_F(OrderItemTest, UpdateQuantityValid) {
    EXPECT_NO_THROW({
        normalItem->updateQuantity(5);
    });
    EXPECT_EQ(normalItem->getQuantity(), 5);
}

//测试用例7: 更新数量为0时抛出异常
TEST_F(OrderItemTest, UpdateQuantityToZeroThrowsException) {
    EXPECT_THROW({
        normalItem->updateQuantity(0);
    }, std::invalid_argument);
}

//测试用例8: 更新数量为负数时抛出异常
TEST_F(OrderItemTest, UpdateQuantityToNegativeThrowsException) {
    EXPECT_THROW({
        normalItem->updateQuantity(-5);
    }, std::invalid_argument);
}

//测试用例9: 正常更新单价
TEST_F(OrderItemTest, UpdatePriceValid) {
    EXPECT_NO_THROW({
        normalItem->updatePrice(5499.99);
    });
    EXPECT_DOUBLE_EQ(normalItem->getUnitPrice(), 5499.99);
}

//测试用例10: 更新单价为负数时抛出异常
TEST_F(OrderItemTest, UpdatePriceToNegativeThrowsException) {
    EXPECT_THROW({
        normalItem->updatePrice(-100.0);
    }, std::invalid_argument);
}

//测试用例11: 更新后小计重新计算
TEST_F(OrderItemTest, SubtotalRecalculatedAfterUpdates) {
    normalItem->updateQuantity(3);
    normalItem->updatePrice(5499.99);
    
    double expectedSubtotal = 3 * 5499.99;
    EXPECT_DOUBLE_EQ(normalItem->calculateSubtotal(), expectedSubtotal);
}

//测试用例12: 订单项ID生成唯一性
TEST_F(OrderItemTest, ItemIdGenerationUnique) {
    OrderItem item1("P001", "iPhone 15", 1, 5999.99);
    OrderItem item2("P001", "iPhone 15", 2, 5999.99); //相同商品不同数量
    OrderItem item3("P002", "MacBook Pro", 1, 12999.99); //不同商品
    
    EXPECT_NE(item1.getItemId(), item2.getItemId());
    EXPECT_NE(item1.getItemId(), item3.getItemId());
    EXPECT_NE(item2.getItemId(), item3.getItemId());
}