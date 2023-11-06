//
//  main.cpp
//  5.三数之和
//
//  Created by TOM钟浩 on 2023/5/27.
//

#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int len = (int)nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        for(int i=0; i<len; ++i){
            if(nums[i] > 0)break;
            int l=i+1, r=len-1;
            while(l<r){
                if(nums[l]+nums[r] == -nums[i]){
                    ans.push_back({nums[i], nums[l], nums[r]});
                    ++l;--r;
                    while(l<r && nums[l]==nums[l-1])++l;
                    while(l<r && nums[r]==nums[r+1])--r;
                }
                else if(nums[l]+nums[r] > -nums[i]){
                    --r;
                }
                else{
                    ++l;
                }
            }
            while(i+1<len && nums[i+1]==nums[i])++i;
        }
        
        return ans;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
