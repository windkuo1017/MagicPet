#include "FunctionsAndConsts.h"

// 實際定義並初始化陣列
int exps[6] = {0, 220, 450, 700, 1000, 1500};
float maxHPs[6] = {60, 70, 84, 106, 130, 160};
int attackPowers[6] = {20, 22, 26, 34, 44, 54};
int defensePowers[6] = {6, 8, 12, 18, 26, 36};
int speeds[6] = {30, 35, 42, 54, 64, 78};
float escapeRate[6] = {0.1, 0.2, 0.35, 0.5, 0.65, 0.8};

// 1206修改
string types[5] = {"gold","wood","water","fire","mud"};




// 函數定義
int getRandomNum(int min, int max) {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr))); // 使用時間初始化生成器
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

void sleep(double seconds) {
    // 將秒數轉換為毫秒
    int milliseconds = static_cast<int>(seconds * 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::string strLower(const std::string& input) {
    std::string result = input; // 複製原字串，避免修改原字串
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// 在函數定義中移除預設參數
string formatMsg(const string& message, const string& colorCode, bool bold) {
    string style = bold ? "1;" : "";
    return "\033[" + style + colorCode + "m" + message + "\033[0m";
}