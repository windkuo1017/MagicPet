#include "FunctionsAndConsts.h"
#include <iostream>


// 實際定義並初始化陣列
int exps[6] = {0, 49, 450, 700, 1000, 1500};
float maxHPs[6] = {40, 70, 84, 106, 130, 160};
int attackPowers[6] = {20, 22, 26, 34, 44, 54};
int defensePowers[6] = {6, 8, 12, 18, 26, 36};
int speeds[6] = {30, 35, 42, 54, 64, 78};
float escapeRate[6] = {0.1, 0.2, 0.35, 0.5, 0.65, 0.8};

// 1206修改
string types[5] = {"gold","wood","water","fire","mud"};




// 函數定義
// int getRandomNum(int min, int max) {
//     // 初始化隨機數生成器，只需要在程式啟動時呼叫一次
//     static bool initialized = false;
//     if (!initialized) {
//         srand(static_cast<unsigned int>(time(nullptr))); // 使用時間初始化種子
//         initialized = true;
//     }

//     // 使用 rand() 生成隨機數並縮放至指定範圍
//     return min + rand() % (max - min + 1);
// }


std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

int getRandomNum(int min, int max) {

    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void sleep(double seconds) {
    // 將秒數轉換為毫秒
    int milliseconds = static_cast<int>(seconds * 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void alignTime(int times, double sec){
    for (size_t i = 0; i < times; i++)
    {
        sleep(sec);
        std::cout << endl;
    }
    
}

std::string strLower(const std::string& input) {
    std::string result = input; // 複製原字串，避免修改原字串
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


string formatMsg(const string& message, const string& colorCode, bool bold) {
    string style = bold ? "1;" : "";
    return "\033[" + style + colorCode + "m" + message + "\033[0m";
}