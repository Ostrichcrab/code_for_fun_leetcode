#include "common/struct.h"
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_map>
using namespace std;
typedef long long LL;
const int INF = 1e9;

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

    // 83
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curNode = head;
        if (head == nullptr) return nullptr;
        while(curNode->next != nullptr){
            if (curNode->next->val == curNode->val) curNode->next = curNode->next->next;
            else  curNode = curNode->next;
        }
        return head;
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

    // 1578 dp
    int minCost(string s, vector<int>& cost) {
        int n = cost.size();
        vector<vector<int>> f(n, vector<int>(27, INF));
        f[0][s[0] - 'a'] = 0, f[0][26] = cost[0];
        for (int i = 1; i < n; i++){
            for (int j = 0; j < 27; j++) f[i][j] = f[i - 1][j] + cost[i];
            int j = s[i] - 'a';
            for (int k = 0; k < 27; k++)
                if (k != j)
                    f[i][j] = min(f[i][j], f[i -1][k]);
        }
        int res = INF;
        for (int i = 0; i < 27; i++) res = min(res, f[n - 1][i]);
        return res;
    }

    // 1582 暴力遍历+一点点剪枝
    int numSpecial(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int ans = 0;
        for(int i = 0; i < n; i++){ 
            for(int j = 0; j < m; j++){
                if(mat[i][j] == 0) continue;
                int flag = 0;
                for(int k = 0; k < n; k++){
                    if(k==i) continue;
                    if(mat[k][j] == 1){
                        flag=1;break;
                        }
                }
                for(int k = 0; k < m; k++){
                    if(k==j) continue;
                    if(mat[i][k] == 1){
                        flag=1;break;
                        }
                }
                if(!flag) ans++;
            }
        }
        return ans;
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

void test_83(){
    Solution m_solution;
    ListNode head = ListNode(1);
    ListNode node = ListNode(1);
    ListNode node2 = ListNode(3);
    ListNode node3 = ListNode(3);
    head.next = &node;
    head.next->next = &node2;
    head.next->next->next = &node3;
    ListNode* ans = m_solution.deleteDuplicates(&head);
    while(ans->next != nullptr){
        cout<<ans->val<<" ";
        ans = ans->next;
    }
    cout<<ans->val;
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

void test_1578(){
    Solution m_solution;
    string s = "aabaa";
    vector<int> cost = {1,2,3,4,1};
    int ans = m_solution.minCost(s, cost);
    cout<<ans<<endl;
}

void test_1582(){
    Solution m_solution;
    vector<vector<int>> mat = {{1,0,0},{0,1,0},{1,0,0}};
    int ans = m_solution.numSpecial(mat);
    cout<<ans<<endl;
}

int main(){
    cout<<"hello leetcode"<<endl;
    // test_66();
    // test_67();
    // test_83();
    // test_1576();
    // test_1577();
    // test_1578();
    test_1582();
    return 0;
}