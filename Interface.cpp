#include <iostream>
#include "Header/System.h"
#include "BuyingSystem/ProductDataBase.h"
#include "BuyingSystem/Products.h"
#include "Header/Account.h"

bool isLoggedIn = false;     // actual storage
std::string currentUser = "";

using namespace std;


void navBar(){
    cout << endl << "(Shop)\t" << "|---1. See Products---|\t\t" << "|2. Order|\t" << "|3. Cart|\t" << "|4. Account|" << endl;
    cout << "------------------------------------------------------------------0.exit------------" << endl;
}

bool menuM (char menuM) {
    switch (menuM){
        case 'A': {
            cout << "Green Tech" << endl;
            clear();
            GreenTech gt;
            showCategory(gt.items);
            return true;
        }
        case 'B': {
            cout << "Drones" << endl;
            clear();
            Drones dr;
            showCategory(dr.items);
            return true;
        }
        case 'C': {
            cout << "Books" << endl;
            clear();
            Books bk;
            showCategory(bk.items);
            return true;
        }
        case 'D': {
            cout << "Classy Laptops" << endl;
            clear();
            ClassyLaptops cl;
            showCategory(cl.items);
            return true;
        }
        case 'E': {
            cout << "Appliances" << endl;
            clear();
            Appliances ap;
            showCategory(ap.items);
            return true;
        }
        case 'P': {
            cout << "Track Your Expenses" << endl;
            clear();
            UserExpenses();
            return true;
        }
    }
    return false;
}

void menu() {
    
    navBar();

    // loggedin
    if (isLoggedIn)
        cout << "Welcome, " << currentUser << "!\n";
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