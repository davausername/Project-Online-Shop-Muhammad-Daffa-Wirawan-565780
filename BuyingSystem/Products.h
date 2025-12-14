#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
using namespace std;

class Product {
public:
    string name;
    string description;
    double price;

public:
    void showProduct(const Product& p);
    void showCategory(const vector<Product>& items);
    void runStore();
    void viewCart();

    void AddProductToUserCart(const std::string& username, const std::string& productName);
    void buyProduct(const std::string& username, const double& productPrice);
    double getProductPrice(const string& productName);
    void clearCart(const string& username);
};

#endif