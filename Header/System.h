#pragma once
extern bool inProcess;

class Sys {
public:
    static void menu();
    static void navBar();
    static void clear();   
    static void deliveryProcess();
    static bool switchMenu(char theMenu);
};