#include <iostream>
#include <string>
#include <vector>
using namespace std;

int getNum(char c) {
    switch (c) {
        case 'a': return 1;
        case 'b': return 2;
        case 'c': return 3;
        case 'd': return 4;
        default: return 0;
    }
}

char getChar(int num) {
    while (num > 4) {
        num -= 4;
    }
    switch (num) {
        case 1: return 'a';
        case 2: return 'b';
        case 3: return 'c';
        case 4: return 'd';
        default: return ' ';
    }
}

string mergeString(const string& str) {
    vector<int> nums;
    for (char c : str) {
        nums.push_back(getNum(c));
    }
    bool merged = true;
    while (merged) {
        merged = false;
        int minSum = 10;
        int mergeIdx = -1;
        for (int i = 0; i < nums.size() - 1; i++) {
            int sum = nums[i] + nums[i + 1];
            if (sum <= minSum) {
                minSum = sum;
                mergeIdx = i;
            }
        }
        if (mergeIdx != -1) {
            int num = minSum % 4;
            if (num == 0) {
                num = 4;
            }
            nums[mergeIdx] = num;
            nums.erase(nums.begin() + mergeIdx + 1);
            merged = true;
        }
    }
    string result;
    for (int num : nums) {
        result += getChar(num);
    }
    return result;
}

int main() {
    string str = "cc";
    cout << mergeString(str) << endl; // 输出：a
    return 0;
}
