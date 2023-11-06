//
//  main.cpp
//  3.两数之和
//
//  Created by TOM钟浩 on 2023/5/27.
//

#include <iostream>
#include <map>
using namespace std;
// 可以用暴力， 但效率感人
//现在用hash
class Solution{
public:
    vector<int> teoSum(vector<int>& nums, int target){
        map<int, int> a;
        vector<int> b(2,-1); //用来承载结果，初始化为大小为2，值为 -1
        for(int i = 0 ;i < nums.size() ;i++){
            if(a.count(target-nums[i]) != 0){//找到了
                b[0] =  i;
                b[1] = a[target-nums[i]];
                break;
            }
            a[nums[i]] = i;
        }
        return b;
    }
};

