#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <thread>
#include <chrono>
#include <map>
#include <sstream>

#include "../Header/Account.h"
#include "ProductDataBase.h"
#include "Products.h"
#include "../Header/System.h"
#include "payment.h"

using namespace std;

vector<Product> cart;

void Product::showProduct(const Product& p) {
    Sys::clear();
    cout << "\n========== PRODUCT DETAILS ==========\n";
    cout << "Product: " << p.name << "\n";
    cout << "Description: " << p.description << "\n";
    cout << "Price: $" << p.price << "\n\n";

    cout << "1. Add to Cart\n";
    cout << "2. Buy Now ($)\n";
    cout << "0. Back\n";
    cout << "Choice: ";

    char choice;
    while (true){
        cin >> choice;
        cin.ignore();
        if (choice == '1') {
            if (UserInfo::IsLoggedIn()) {
                cart.push_back(p);
                cout << "\nAdded " << p.name << " to cart!\n";
                // processing
                AddProductToUserCart(UserInfo::CurrentUser(), p.name);
            } else {
                cout << "You're not logged in. Please log in to save your cart.\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        } else if (choice == '2') {
            if (UserInfo::IsLoggedIn()) {
                PaymentMethod pm;
                pm.paymentMethod();
                cout << "Thank you, we deliver your order soon!" << endl;
                buyProduct(UserInfo::CurrentUser(), p.price);
                std::this_thread::sleep_for(std::chrono::seconds(1));

                inProcess = true;
                Sys::deliveryProcess();
            } else {
                cout << "You're not logged in. Please log in to proceed with the purchase.\n";
                this_thread::sleep_for(chrono::seconds(1));
                return;
            }
            break;
        } else if (choice == '0') {
            Sys::clear();
            return;
        } else {
            cout << "Invalid choice. Please try again: ";
        }
    }
}

void Product::showCategory(const vector<Product>& items) {
    Sys::clear();
    while (true) {
        cout << "\n--- Select a product ---\n";

        for (int i = 0; i < items.size(); i++)
            cout << i + 1 << ". " << items[i].name << endl;

        cout << "0. Back\n";

        cout << "Choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) {Sys::clear(); runStore();}
        if (choice > 0 && choice <= items.size())
            showProduct(items[choice - 1]);
    }
};

void Product::viewCart() {
    Sys::clear();
    cout << "-----M.Menu----------------------------0.Exit()-----" << endl << endl;
    cout << "========== CART ==========" << endl;
    double total = 0;

    if(UserInfo::IsLoggedIn()) {
        cout << "Hi, " << UserInfo::CurrentUser() << "\n\n";
        ifstream infile("Header/users_data.txt");
        string line;
        string userCart;
        bool found = false;
        while (getline(infile, line)) {
            if (line.find("Username: " + UserInfo::CurrentUser()) != string::npos) {
                found = true;
                while (getline(infile, line)) {
                    if (line.find("Cart:") != string::npos) {
                        userCart = line.substr(line.find("Cart:") + 6);
                        break;
                    }
                }
                break;
            }
        }
        infile.close();
        if (found && !userCart.empty()) {
            cout << "+++++ Your Cart +++++" << endl;
            string item;
            stringstream ss(userCart);

            while (getline(ss, item, ',')) {

                if (!item.empty() && item[0] == ' ')
                    item.erase(0, 1);

                double price = getProductPrice(item);

                if (price != -1) {
                    cout << item << " - $" << price << endl;
                    total += price;
                } else {
                    cout << item << " - (Price not found)" << endl;
                }
            }
            cout << "-------------------------------------------" << endl;
            cout << "Total Price: $" << total << endl;
            cout << "-------------------------------------------" << endl;
            cout << "2. Checkout\n\n";
        } else {
            cout << "Sorry, We can't find your data!" << endl;
        }

    } else {
        cout << "You're not logged in. Please log in to view your cart.\n\n";
    }


    char key;
    while (true) {
        cout << "Insert the following key to continue: ";
        cin >> key;
        if (key == 'M' || key == 'm') {
            Sys::clear();
            Sys::menu();
            return;
        } else if (key == '0') {
            cout << "See ya. Danke!" << endl;
            exit(0);
        } else if (key == '2') {
            if (UserInfo::IsLoggedIn()) {
                PaymentMethod pm;
                pm.paymentMethod();
                cout << "Thank you, we deliver your order soon!" << endl;
                double totalPrice;;
                totalPrice = total;
                buyProduct(UserInfo::CurrentUser(), totalPrice);
                std::this_thread::sleep_for(std::chrono::seconds(1));

                inProcess = true;
                clearCart(UserInfo::CurrentUser());
                Sys::deliveryProcess();
            } else {
                cout << "You're not logged in. Please log in to proceed with the purchase.\n";
                this_thread::sleep_for(chrono::seconds(1));
                return;
            }

        } else {
            cout << "Invalid input. Please insert the following!" << endl;
        }
    }
}


void Product::runStore() {
    Sys::clear();
    while (true) {
        cout << "--[-M. Menu-]\t=== WELCOME TO THE STORE ===\t[+ C. Cart +]--" << endl;
        cout << "-----------------------------------------0. Exit------------" << endl;
        cout << "1. GreenTech\n";
        cout << "2. Drones\n";
        cout << "3. Books\n";
        cout << "4. Classy Laptops\n";
        cout << "5. Appliances\n";
        cout << "6. German Cars\n";
        cout << "7. German Tech\n";
        cout << "8. German Books\n";
        cout << "9. German Appliances\n";
        cout << "Choice: ";

        char catChoice;
        cin >> catChoice;
        catChoice = toupper(catChoice);
        cin.ignore();

        if (catChoice == '0') {
            cout << "Thanks for visiting the store!\n";
            exit(0);
        }

        ProductDatabase db;
        switch (catChoice) {
            case 'M':
                Sys::clear();
                Sys::menu();
                break;
        case '1': {
            Sys::clear();
            showCategory(db.getCategory("Green Tech"));
            break;
        }
        case '2': {
            Sys::clear();
            showCategory(db.getCategory("Drones"));
            break;
        }
        case '3': {
            Sys::clear();
            showCategory(db.getCategory("Books"));
            break;
        }
        case '4': {
            Sys::clear();
            showCategory(db.getCategory("Classy Laptops"));
            break;
        }
        case '5': {
            Sys::clear();
            showCategory(db.getCategory("Appliances"));
            break;
        }
        case '6': {
            Sys::clear();
            showCategory(db.getCategory("German Cars"));
            break;
        }
        case '7': {
            Sys::clear();
            showCategory(db.getCategory("German Tech"));
            break;
        }
        case '8': {
            Sys::clear();
            showCategory(db.getCategory("German Books"));
            break;
        }
        case '9': {
            Sys::clear();
            showCategory(db.getCategory("German Appliances"));
            break;
        }
            case 'C':
                Sys::clear();
                viewCart();
                break;
            case '0':
                Sys::clear();
                cout << "Thanks for visiting the store!\n";
                exit(0);
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}



double Product::getProductPrice(const string& productName) {
    ProductDatabase db;

    for (const auto& categoryName : db.getCategoryNames()) {
        const vector<Product>& products = db.getCategory(categoryName);

        for (const auto& p : products) {
            if (p.name == productName) {
                return p.price;
            }
        }
    }

    return -1.0; // not found
}


void Product::clearCart(const string& username) {
    ifstream infile("Header/users_data.txt");
    if (!infile.is_open()) {
        cout << "Error opening users_data.txt" << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool foundUser = false;

    while (getline(infile, line)) {
        if (line.find("Username: " + username) != string::npos) {
            foundUser = true;
            lines.push_back(line);
            // Look for the next "Cart:" line
            if (getline(infile, line)) {
                if (line.find("Cart:") != string::npos) {
                    lines.push_back("Cart: ");
                    continue;
                }
            }
        }
        lines.push_back(line);
    }
    infile.close();

    ofstream outfile("Header/users_data.txt", ios::trunc);

    for (auto& l : lines) {
        outfile << l << endl;
    }
    outfile.close();
}