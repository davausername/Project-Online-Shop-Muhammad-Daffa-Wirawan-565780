#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <atomic>
#include "Header/System.h"
using namespace std;
bool inProcess = false;

atomic<int> currentNumber(0);

void backgroundTask() {
    inProcess = false;
    for (int i = 0; i <= 100; i+=10) {
        currentNumber = i;

        cout << "\033[s";

        cout << "\033[1;1H";
        cout << "\033[2K";
        cout << "Processing: " << currentNumber << "%" << flush;
        if (currentNumber == 20) {
            cout << "\nYour Stuff is About to be Delivered!" << endl;
        } else if (currentNumber == 40) {
            cout << "\nWe're Shipping Your Stuff!          " << endl;
        } else if (currentNumber == 50) {
            cout << "\nYour Stuff is on the Way!           " << endl;
        } else if (currentNumber == 100) {
            cout << "\nYour Stuff has been Delivered! Thank You!" << endl;
        }

        cout << "\033[u" << flush;

        this_thread::sleep_for(chrono::seconds(2));
    }
}

void deliveryProcess() {
    cout << "\033[2J";

    cout << "\033[3;1H";

    if (inProcess == true){
        thread worker(backgroundTask);
        worker.detach();  // keep it running in the background
    } else {
        cout << "No active delivery processes." << endl;
    }


    string name;
    while (true) {
        cout << "Insert 'M' to go back to menu: ";
        cin >> name;
        if (name == "M" || name == "m") {
            clear();
            menu();
            return;
        } else {
            cout << "Invalid input. Please insert the following!" << endl;
        }
    }
}