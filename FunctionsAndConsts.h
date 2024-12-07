#ifndef FUNCTIONSANDCONSTS_H
#define FUNCTIONSANDCONSTS_H


#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <sstream>

using namespace std;

// 宣告陣列，讓其他檔案可以引用
extern int exps[6];
extern float maxHPs[6];
extern int attackPowers[6];
extern int defensePowers[6];
extern int speeds[6];
extern float escapeRate[6];
extern string types[5];

// 函數宣告
int getRandomNum(int min, int max);
void sleep(double seconds);
string strLower(const string& input);
string formatMsg(const string& message, const string& colorCode = "31", bool bold = true);



#endif
