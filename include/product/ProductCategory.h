#ifndef PRODUCT_CATEGORY_H
#define PRODUCT_CATEGORY_H

#include <string>
#include <vector>
#include <memory>

class Product;

class ProductCategory {
private:
    std::string categoryId;
    std::string categoryName;
    std::string parentCategory;
    std::vector<std::shared_ptr<ProductCategory>> subCategories;
    std::vector<std::shared_ptr<Product>> products;

public:
    ProductCategory(const std::string& name, const std::string& parent = "");
    
    void addSubCategory(std::shared_ptr<ProductCategory> subCategory);
    void addProduct(std::shared_ptr<Product> product);
    
    std::string getCategoryId() const { return categoryId; }
    std::string getCategoryName() const { return categoryName; }
};

#endif