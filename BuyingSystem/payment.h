#pragma once
#include <string>
using namespace std;

class PaymentMethod {
public:
    char paymentChoice;

public:
    void paymentMethod();
    void paymentProcessing();

    void setPaymentChoice(char choice) {
        paymentChoice = choice;
    }
};