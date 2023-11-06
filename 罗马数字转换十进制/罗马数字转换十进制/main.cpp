//
//  main.cpp
//  罗马数字转换十进制
//
//  Created by TOM钟浩 on 2023/5/27.
//


#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        if(s.find("IV") != string::npos)
        s.replace(s.find("IV"),2,"1");
        if(s.find("IX") != string::npos)
        s.replace(s.find("IX"),2,"2");
        if(s.find("XL") != string::npos)
        s.replace(s.find("XL"),2,"3");
        if(s.find("XC") != string::npos)
        s.replace(s.find("XC"),2,"4");
        if(s.find("CD") != string::npos)
        s.replace(s.find("CD"),2,"5");
        if(s.find("CM") != string::npos)
        s.replace(s.find("CM"),2,"6");
           for(int i = 0; i<s.length();i++){
           if(s[i]=='I') res += 1;
           if(s[i]=='V') res += 5;
           if(s[i]=='X') res += 10;
           if(s[i]=='L') res += 50;
           if(s[i]=='C') res += 100;
           if(s[i]=='D') res += 500;
           if(s[i]=='M') res += 1000;
           if(s[i]=='1') res += 4;
           if(s[i]=='2') res += 9;
           if(s[i]=='3') res += 40;
           if(s[i]=='4') res += 90;
           if(s[i]=='5') res += 400;
           if(s[i]=='6') res += 900;
           }
        return res;
    }
};

int main(int argc, const char * argv[]) {
    string str;
    cin>>str;
    Solution so;
    cout<<so.romanToInt(str)<<endl;
    return 0;
}
