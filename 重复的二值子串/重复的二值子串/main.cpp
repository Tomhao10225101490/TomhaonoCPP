#include <iostream>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

class point{
    public:
         point();
     string strr;
     int count;
};
point::point(){
strr  = "";
count = 1;
}

bool cmp(point x, point y) {
    return x.strr > y.strr;
}
int main(){
    string str;
    cin>>str;
    int len = (int)str.length();
    vector<point> a;
    set<point> b;
    for(int i = 0; i<len-9; i++){
        for(int j = i; j <len-9 ;j++){
            a[i].strr += str[j];
        }
    }
    for(int i = 0; i < len-10; i++){
        for(int j = i+1 ;j < len-9 ;j++){
            if(a[i].strr == a[j].strr)
            b.insert(a[i]);
        }
    }
    sort(b.begin(),b.end(),cmp);
//    for(auto it: b){
//        cout<<it.strr<<endl;
//    }
        return 0;
}
