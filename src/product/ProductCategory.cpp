#include "product/ProductCategory.h"
#include "product/Product.h"
#include <algorithm>
#include <sstream>

ProductCategory::ProductCategory(const std::string& name, const std::string& parent)
    : categoryName(name), parentCategory(parent) {
    
    // 生成分类ID
    std::stringstream ss;
    ss << "CATEGORY_" << std::hash<std::string>{}(categoryName + parentCategory);
    categoryId = ss.str();
}

void ProductCategory::addSubCategory(std::shared_ptr<ProductCategory> subCategory) {
    subCategories.push_back(subCategory);
}

void ProductCategory::addProduct(std::shared_ptr<Product> product) {
    products.push_back(product);
}

void ProductCategory::removeProduct(const std::string& productId) {
    products.erase(
        std::remove_if(products.begin(), products.end(),
                      [&](const std::shared_ptr<Product>& product) {
                          return product->getProductId() == productId;
                      }),
        products.end()
    );
}

std::vector<std::shared_ptr<Product>> ProductCategory::getProducts() const {
    return products;
}

std::vector<std::shared_ptr<ProductCategory>> ProductCategory::getSubCategories() const {
    return subCategories;
}

bool ProductCategory::hasSubCategories() const {
    return !subCategories.empty();
}

int ProductCategory::getProductCount() const {
    return products.size();
}