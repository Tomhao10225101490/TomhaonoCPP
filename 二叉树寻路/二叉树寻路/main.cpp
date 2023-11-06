//
//  main.cpp
//  二叉树寻路
//
//  Created by TOM钟浩 on 2023/6/20.
//

#include <iostream>
#include <stack>
using namespace std;
int main(int argc, const char * argv[]) {
    int num;
    cin>>num;
    int len = 0;
    int ttt = num;
    while(ttt){
        len++;
        ttt /= 2;
    }
    vector<int> sta;
    sta.push_back(num);
    int i = 0;
    while(len-i > 0){
            int temp = pow(2, len-i) + pow(2,len-i-1)-1;
            int ans = temp - num;
            num = ans/2;
        if(num){
            sta.push_back(num);
        }
            i++;
    }
    for(int i = sta.size()-1; i>=0 ;i--){
        cout<<sta[i]<<' ';
    }
    return 0;
}
