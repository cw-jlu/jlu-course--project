#ifndef Useful_Tools
#define Useful_Tools
#include <string>
#include <cctype>      
#include <iostream>
#include <conio.h>     
#include <chrono>
#include <thread>
#include <vector>
#include <initializer_list>

namespace {
    char getKey() { return static_cast<char>(_getch()); }
}
/*这个文件里面放一些纯工具函数.*/
int readIntOnly(const std::string& prompt);
long long readLongLongOnly(const std::string& prompt);
bool ifphonenumberlegal(long long phonenumeber);
void coutline();

void delaycout(const std::string& str);
void delaycoutline();
void clearScreen();

void standardcout(std::initializer_list<std::string> texts, int howmanyspace);
#endif