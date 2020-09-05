#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

class Solution {
    public: Solution(){}
    // 66
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> ans(n+1);
        int flag = 0;
        for(int i = 0; i < n; i++){
           int now = digits[n-i-1] + flag;
           if (!i) now++;
           ans[n-i] = now % 10;
           flag = now / 10;
        }
        if(flag){
            ans[0] = 1;
        }else{
            ans.erase(ans.begin());
        }
        return ans;
    }
};

int main(){
    cout<<"hello leetcode"<<endl;
    Solution m_solution;
    vector<int> digits = {9,9};
    vector<int> ans = m_solution.plusOne(digits);
    for(int i = 0; i <ans.size(); i++){
        cout<<ans[i];
    }
    return 0;
}