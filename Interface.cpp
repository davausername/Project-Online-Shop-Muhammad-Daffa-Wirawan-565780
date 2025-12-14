#include <iostream>
#include "Header/System.h"
#include "BuyingSystem/ProductDataBase.h"
#include "BuyingSystem/Products.h"
#include "Header/Account.h"

bool UserInfo::isLoggedIn = false;
std::string UserInfo::currentUser = "";

using namespace std;


void Sys::navBar(){
    cout << endl << "(Homepage)\t" << "|---1. Browse Products---|\t\t" << "|2. Order|\t" << "|3. Cart|\t" << "|4. Account|" << endl;
    cout << "------------------------------------------------------------------0.exit------------" << endl;
}

bool menuM (char menuM) {
    ProductDatabase db;
    switch (menuM) {
        case 'A': {
            Sys::clear();
            cout << "Green Tech" << endl;
            Product().showCategory(db.getCategory("Green Tech"));
            return true;
        }
        case 'B': {
            Sys::clear();
            cout << "Drones" << endl;
            Product().showCategory(db.getCategory("Drones"));
            return true;
        }
        case 'C': {
            Sys::clear();
            cout << "Books" << endl;
            Product().showCategory(db.getCategory("Books"));
            return true;
        }
        case 'D': {
            Sys::clear();
            cout << "Classy Laptops" << endl;
            Product().showCategory(db.getCategory("Classy Laptops"));
            return true;
        }
        case 'E': {
            Sys::clear();
            cout << "Appliances" << endl;
            Product().showCategory(db.getCategory("Appliances"));
            return true;
        }
        case 'P': {
            cout << "Track Your Expenses" << endl;
            Sys::clear();
            UserInfo::UserExpenses();
            return true;
        }
    }
    return false;
}

void Sys::menu() {
    
    navBar();

    // loggedin
    if (UserInfo::IsLoggedIn())
        cout << "Welcome, " << UserInfo::CurrentUser() << "!\n";
    else
        cout << "[Login]\n" << endl;

    cout << "Category:\n" << "A. Green Tech\t" << "B. Drones\t" << "C. Books\t" << "D. Classy Laptops\t" << "E. Appliances\t" << endl << endl;
    
    cout << "     ----------     P. Track Your Expenses     ----------     " << endl << endl;

    while (true)
    {
        char menu;
        cout << "Enter the following key to continue: ";
        cin >> menu;
        menu = toupper(menu);

        bool handled = false;

        handled |= switchMenu(menu);
        handled |= menuM(menu);

        if(!handled)
            cout << "Please Choose the given keys!";
    }
}