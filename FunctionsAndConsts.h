#ifndef FUNCTIONSANDCONSTS_H
#define FUNCTIONSANDCONSTS_H


#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <sstream>

using namespace std;

// �ŧi�}�C�A����L�ɮץi�H�ޥ�
extern int exps[6];
extern float maxHPs[6];
extern int attackPowers[6];
extern int defensePowers[6];
extern int speeds[6];
extern float escapeRate[6];
extern string types[5];

// ��ƫŧi
int getRandomNum(int min, int max);
void sleep(double seconds);
string strLower(const string& input);
string formatMsg(const string& message, const string& colorCode = "31", bool bold = true);



#endif
