#include <iostream>
#include "payment.h"
#include "../Header/System.h"
using std::cout;
using std::cin;
using std::endl;

void PaymentMethod::paymentMethod() {
    cout << "====M.Menu==== Choose your payment method:====0.Out====" << endl;
    cout << "1. Credit Card\n2. Debit Card\n3. PayPal\n4. Wise" << endl;

    while (true) {
        char choice;
        cout << "Select a payment option: ";
        cin >> choice;

        PaymentMethod pm;
        pm.setPaymentChoice(choice);
        if (choice == '0') {
            cout << "See you, Danke." << endl;
            exit(0);
            return;
        } else if (choice == '1' || choice == '2' || choice == '3' || choice == '4') {
            cout << "You selected option " << choice << "." << endl;
            paymentProcessing();
            return;
        } else if (choice == 'M' || choice == 'm') {
            Sys::menu();
            return;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    
}

void PaymentMethod::paymentProcessing() {
    cout << "Processing payment..." << endl;
    cout << "Payment successful!" << endl;
}