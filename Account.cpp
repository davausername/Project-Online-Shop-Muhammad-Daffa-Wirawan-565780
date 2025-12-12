#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "Header/Account.h"
#include "Header/System.h"
using namespace std;

void UserInterraction(){

    UserInfo user;

    while (true){
        char accountAcces;
        cout << "===[M. Menu]===============[0. out]===" << endl;
        cout << "1. Sign Up\n2. Log In\n3. Account Details\n4. Remove Account" << endl;
        cout << "Enter Keyword Above: ";
        cin >> accountAcces;
        accountAcces = toupper(accountAcces);

        switch (accountAcces){
            case 'M':
                clear();
                menu();
                return;
            case '1':
                clear();
                user.SignUp();
                return;
            case '2':
                clear();
                user.LogIn();
                return;
            case '3':
                clear();
                user.AccoutDetails();
                return;
            case '4':
                clear();
                user.RemoveAccount();
                return;
            case '0':
                cout << "Bye, See ya!" << endl;
                exit(0);
            default:
                cout << "Please choose the followings" << endl;
                break;
        };
    };
}


void UserExpenses(){
    cout << "-----M.Menu----------------------------0.Exit()-----" << endl << endl;
    cout << "     === Track Your Total Expenses ===     " << endl << endl;

    if (isLoggedIn){
        cout << "Hi there, " << currentUser << endl;
        cout << "Here are your total expenses!" << endl << endl;
        fstream expenseFile;
        expenseFile.open("Header/users_data.txt", ios::app | ios::in);

        string line;
        double totalExpenses = 0.0;
        bool foundUser = false;

        while (getline(expenseFile, line)) {

            if (line.find("Username: " + currentUser) != string::npos) {
                foundUser = true;
                continue;
            }
            if (foundUser) {
                size_t pos = line.find("totalExpenses: ");
                if (pos != string::npos) {
                    totalExpenses = stod(line.substr(pos + 15));
                    break;
                }
            }
        }

        cout << "Total Expenses: $" << totalExpenses << endl << endl;
        expenseFile.close();
    } else {
        cout << "Please log in to view your expenses.\n\n";
    }

    char key;
    while (true) {
        cout << "Insert the following key to continue: ";
        cin >> key;
        if (key == 'M' || key == 'm') {
            clear();
            menu();
            return;
        } else if (key == '0') {
            cout << "See ya. Danke!" << endl;
            exit(0);
        } else {
            cout << "Invalid input. Please insert the following!" << endl;
        }
    }

}


void UserInfo::SignUp() {
    cout << "=== Sign Up ===" << endl;
    fstream users;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "First Name: ";
    getline(cin, FirstName);

    cout << "Last Name: ";
    getline(cin, LastName);

    // USERNAME CHECKING
    while (true) {
        cout << "Username: ";
        getline(cin, Username);

        if(Username.length() < 3) {
            cout << "Username must be at least 3 characters long." << endl;
            continue;
        } else if (Username.length() > 28){
            cout << "Username must be less than 28 characters long." << endl;
            continue;
        }

        bool exists = false;
        ifstream infile("Header/users_data.txt");

        string line;
        while (getline(infile, line)) {
            if (line.find("Username: " + Username) != string::npos) {
                exists = true;
                break;
            }
        }
        infile.close();

        if (exists) {
            cout << "Username already exists! Try another.\n";
        } else {
            break;
        }
    }

    // --- PASSWORD INPUT ---
    while (true)
    {
        cout << "Password: ";
        getline(cin, Password);

        if(Password.length() < 8) {
            cout << "Password must be at least 8 characters long." << endl;
            continue;
        } else if (Password.length() > 256){
            cout << "We only provide the maximum length of 256 characters for password." << endl;
            continue;
        } else {
            break;
        }
    }

    // SAVE DATA
    users.open("Header/users_data.txt", ios::app);
    if (users.is_open()) {
        users << "Username: " << Username << "\t";
        users << "Full Name: " << FirstName << " " << LastName << "\t";
        users << "Password: " << Password << endl;
        users << "Cart: " << endl;
        users << "totalItems: " << endl;
        users << "totalExpenses: " << endl << endl;

        cout << "Registration Successful!" << endl;
        users.close();
        isLoggedIn = true;
        currentUser = Username;
        menu();
    }
}

void UserInfo::LogIn() {
    while (true){
        cout << "=== Log In ===" << endl;
        string inputUser, inputPass;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Username: ";
        getline(cin, inputUser);

        cout << "Password: ";
        getline(cin, inputPass);

        ifstream infile("Header/users_data.txt");
        string line;
        bool found = false;

        while (getline(infile, line)) {
            if (line.find("Username: " + inputUser) != string::npos &&
                line.find("Password: " + inputPass) != string::npos) {
                found = true;
                break;
            }
        }

        infile.close();

        if (found) {
            isLoggedIn = true;
            cout << "Successfully Logged In, Thank You!" << endl;
            currentUser = inputUser;
            menu();
            return;
        } else {
            cout << "Invalid Username or Password!" << endl;
        }
    }
}

void UserInfo::RemoveAccount() {
    cout << "=== Remove Account ===" << endl;
    string usernameToDelete, passwordToDelete;
    cout << "Enter the username to delete: ";
    cin >> usernameToDelete;

    cout << "Enter password: ";
    cin >> passwordToDelete;

    ifstream input("Header/users_data.txt");
    ofstream temp("Header/temp.txt");

    bool found = false;
    bool skipBlock = false;

    string line;

    while (getline(input, line)) {

        if (line.find("Username: " + usernameToDelete) != string::npos &&
            line.find("Password: " + passwordToDelete) != string::npos) 
        {
            found = true;
            skipBlock = true;
            continue;
        }

        if (skipBlock) {
            // stop skipping at the next Username: line
            if (line.rfind("Username:", 0) == 0) { 
                skipBlock = false;
                temp << line << "\n";
            }
            continue;
        }

        temp << line << "\n";
    }

    input.close();
    temp.close();

    remove("Header/users_data.txt");
    rename("Header/temp.txt", "Header/users_data.txt");

    if (found){
        cout << "Account deleted successfully.\n";
        menu();
    } else {
        cout << "Username not found.\n";
        menu();
    }
}

void UserInfo::AccoutDetails(){
    cout << "=== Account Details ===" << endl;
    string inputUser, inputPass;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Username: ";
    getline(cin, inputUser);

    cout << "Password: ";
    getline(cin, inputPass);

    ifstream infile("Header/users_data.txt");
    string userDetails;
    int totalItems = 0;

    string line;
    bool found = false;

    while (getline(infile, line)) {
        if (line.find("Username: " + inputUser) != string::npos &&
            line.find("Password: " + inputPass) != string::npos) {
            found = true;
            userDetails = line;

            while (getline(infile, line)) {
            if (line.find("totalItems:") != string::npos) {
                string num = line.substr(line.find(":") + 1);
                totalItems = stoi(num);
                break;
            }
        }

            break;
        }
    }

    infile.close();

    if (found) {
        cout << "Account Details:\n" << userDetails << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Buying Record: " << totalItems << " items purchased." << endl << endl;
    } else {
        cout << "Invalid Username or Password!" << endl;
    }
}