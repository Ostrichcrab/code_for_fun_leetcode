#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_map>
using namespace std;
typedef long long LL;

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

    // 67
    string addBinary(string a, string b) {
        string ans = "";
        int la = a.length();
        int lb = b.length();
        int len = max(la, lb);
        int flag = 0;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        for(int i = 0; i < len; i++){
            int ta, tb;
            if(i+1>la) ta = 0;
            else ta = a[i] - '0';
            if(i+1>lb) tb = 0;
            else tb = b[i] - '0';
            ans += ('0' + (ta + tb + flag) % 2);
            flag = (ta + tb + flag) / 2;
        }
        if (flag){
            ans += "1";
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    //  1576
    string modifyString(string s) {
        for (int i = 0; i < s.size(); i++){
            if (s[i] != '?')    continue;
            char c = 'a';
            while(i && s[i - 1] == c || i + 1 < s.size() && s[i + 1] == c) c++;
            s[i] = c;
        }
        return s;
    }

    // 1577
    int numTriplets_helper(vector<int>& a, vector<int>& b) {
        int res = 0;
        unordered_map<LL, int> hash;
        for (int x: a) hash[(LL)x * x] ++;
        for (int j = 0; j < b.size(); j++)
            for (int k = j + 1; k < b.size(); k++)
                res += hash[(LL)b[j] * b[k]];
        return res;
    }
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        return numTriplets_helper(nums1, nums2) + numTriplets_helper(nums2, nums1);
    }
};

void test_66(){
    Solution m_solution;
    vector<int> digits = {9,9};
    vector<int> ans = m_solution.plusOne(digits);
    for(int i = 0; i <ans.size(); i++){
        cout<<ans[i];
    }
}

void test_67(){
    Solution m_solution;
    string a = "100";
    string b = "110010";
    string ans = m_solution.addBinary(a,b);
    cout<<ans<<endl;
}

void test_1576(){
    Solution m_solution;
    string s = "??yw?ipkj?";
    string ans = m_solution.modifyString(s);
    cout<<ans<<endl;
}

void test_1577(){
    Solution m_solution;
    vector<int> nums1 = {1,1};
    vector<int> nums2 = {1,1,1};
    int ans = m_solution.numTriplets(nums1, nums2);
    cout<<ans<<endl;
}

int main(){
    cout<<"hello leetcode"<<endl;
    // test_66();
    // test_67();
    // test_1576();
    test_1577();
    return 0;
}