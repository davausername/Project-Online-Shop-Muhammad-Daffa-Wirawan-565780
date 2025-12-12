#include <iostream>
#include <cstdlib>
#include "Header/System.h"
#include "BuyingSystem/Products.h"
#include "Header/Account.h"
using namespace std;


void clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool switchMenu(char theMenu){
    switch (theMenu)
    {
    case '0':
        clear();
        cout << "\nSee Ya, Danke" << endl;
        exit(0);
        return true;
    case '1':
        clear();
        runStore();
        return true;
    case '2':
        clear();
        deliveryProcess();
        return true;
    case '3':
        clear();
        cout << "Cart" << endl;
        viewCart();
        return true;
    case '4':
        clear();
        UserInterraction();
        return true;
    }
    return false;
}