#include <iostream>
#include <fstream>
#include <string>
#include "Products.h"
using namespace std;

void Product::AddProductToUserCart(const string& username, const string& productName) {
    ifstream input("Header/users_data.txt");
    ofstream temp("Header/temp.txt");

    if (!input || !temp) {
        cout << "Error opening user data file.\n";
        return;
    }

    string line;
    bool inTargetUser = false;

    while (getline(input, line)) {

        // Detect a new user
        if (line.rfind("Username:", 0) == 0) {
            if (line.find("Username: " + username) != string::npos) {
                inTargetUser = true;
            } else {
                inTargetUser = false;
            }
            temp << line << "\n";
            continue;
        }

        if (inTargetUser && line.rfind("Cart:", 0) == 0) {
            string cartData = line.substr(5); // after "Cart:"
            
            // trim
            while (!cartData.empty() && (cartData[0] == ' ' || cartData[0] == '\t'))
                cartData.erase(cartData.begin());

            // Append product
            if (cartData.empty()) {
                cartData = productName;
            } else {
                cartData += ", " + productName;
            }

            temp << "Cart: " << cartData << "\n";
            continue;
        }

        temp << line << "\n";
    }

    input.close();
    temp.close();

    remove("Header/users_data.txt");
    rename("Header/temp.txt", "Header/users_data.txt");

    cout << "Product saved to cart in file.\n";
}



void Product::buyProduct(const string& username, const double& productPrice) {
    ifstream input("Header/users_data.txt");
    ofstream temp("Header/temp.txt");

    if (!input || !temp) {
        cout << "Error opening user data file.\n";
        return;
    }

    string line;
    bool inTargetUser = false;

    while (getline(input, line)) {

        // Detect a new user section
        if (line.rfind("Username:", 0) == 0) {
            if (line.find("Username: " + username) != string::npos) {
                inTargetUser = true;
            } else {
                inTargetUser = false;
            }
            temp << line << "\n";
            continue;
        }

        if (inTargetUser && line.rfind("totalExpenses:", 0) == 0) {
            string value = line.substr(14);
            double cartData = 0;

            if (!value.empty()) {
                try {
                    cartData = stod(value);
                } catch (...) {
                    cartData = 0;
                }
            }

            cartData += productPrice;
            temp << "totalExpenses: " << cartData << "\n";
            continue;
        }

        if (inTargetUser && line.rfind("totalItems:", 0) == 0) {
            string value = line.substr(11);
            int items = 0;
            if (!value.empty()) {
                try {
                    items = stoi(value);
                } catch (...) {
                    items = 0;
                }
            }
            items += 1;
            temp << "totalItems: " << items << "\n";
            continue;
        }

        temp << line << "\n";
    }

    input.close();
    temp.close();

    remove("Header/users_data.txt");
    rename("Header/temp.txt", "Header/users_data.txt");

    cout << "Product saved to cart in file.\n";
}