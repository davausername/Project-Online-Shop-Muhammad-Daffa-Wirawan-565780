#pragma once

#include <iostream>
#include <string>
#include <limits>
using namespace std;

class UserInfo {
private:
    string FirstName, LastName, Username, Password;

    static bool isLoggedIn;
    static std::string currentUser;

public:
    void SignUp();
    void LogIn();
    void RemoveAccount();
    void AccountDetails();

    static void UserInterraction();
    static void UserExpenses();

    // checking
    static bool IsLoggedIn();
    static void SetLoggedIn(bool value);

    static const std::string& CurrentUser();
    static void SetCurrentUser(const std::string& user);

    bool usernamePasswordChecking(const string& inputUser, const string& inputPass);
};