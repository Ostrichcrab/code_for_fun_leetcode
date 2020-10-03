#include "common/struct.h"
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_map>
#include<limits.h>
using namespace std;
typedef long long LL;
const int INF = 1e9;
const int N = 1001;
const int MOD = 1e9 + 7;
// pirme minSpanTree
int mpt[N][N]; // 原图对应矩阵
int dis[N]; // 最近的距离
int cls[N]; // 最近点编号

class Solution {
    public: Solution(){}

    // 57
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        bool has_in = false;
        for(auto item : intervals){
            if (item[1] < newInterval[0]) ans.push_back(item);
            else if (item[0] > newInterval[1]){
                if(!has_in) {
                    ans.push_back(newInterval);
                    has_in = true;
                }
                ans.push_back(item);
            } 
            else{
                newInterval[0] = min(item[0], newInterval[0]);
                newInterval[1] = max(item[1], newInterval[1]);
            }
        }
        if (!has_in){
            ans.push_back(newInterval);
        }  
        return ans;
    }

    // 63
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        if (m == 0) return 0;
        int n = obstacleGrid[0].size();
        if (n == 0) return 0;
        LL dp[101][101] = {0};
        dp[0][0] = 1 - obstacleGrid[0][0];
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(obstacleGrid[i][j] == 1) dp[i][j] = 0;
                else{
                    if(i > 0) dp[i][j] += dp[i-1][j];
                    if(j > 0) dp[i][j] += dp[i][j-1];
                }
            }
        }
        return dp[m-1][n-1];
    }

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

    // 73
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.empty()) return ;
        int n = matrix.size();
        int m = matrix[0].size();
        int col0 = 1, row0 = 1;
        for(int i = 0; i < n; i++)
            if(!matrix[i][0]) col0 = 0;
        for(int j = 0; j < m; j++)
            if(!matrix[0][j]) row0 = 0;
        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                if(!matrix[i][j]){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for(int i = 1; i < n; i++){
            if(!matrix[i][0]){
                for(int j = 1; j < m; j++){
                    matrix[i][j] = 0;
                }
            }
        }
        for(int i = 1; i < m; i++){
            if(!matrix[0][i]){
                for(int j = 1; j < n; j++){
                    matrix[j][i] = 0;
                }
            }
        }
        if(!col0){
            for(int i = 0; i < n; i++){
                matrix[i][0] = 0;
            }
        }
        if(!row0){
            for(int i = 0; i < m; i++){
                matrix[0][i] = 0;
            }
        }
    }

    // 74
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if(!n) return false;
         int m = matrix[0].size();
        if(!m) return false;
        int l = 0, r = m * n - 1;
        while(l < r){
            int mid = (l + r) / 2;
            if(matrix[mid/m][mid%m] >= target) r = mid;
            else l = mid + 1;
        }
        return matrix[r/m][r%m] == target;
    }

    // 81
    bool search(vector<int>& nums, int target) {
        for(auto item : nums){
            if(item == target){
                return true;
            }
        }
        return false;
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

    // 86
    ListNode* partition(ListNode* head, int x) {
        ListNode *before = new ListNode(0);
        ListNode *after = new ListNode(0);
        ListNode *pa = before;
        ListNode *pb = after;
        for(ListNode *p = head; p; p = p->next){
            if (p->val < x){
                pa->next = p;
                pa = pa->next;
            }
            if (p->val >= x){
                pb->next = p;
                pb = pb->next;
            }
        }
        pa->next = after->next;
        pb->next = nullptr;
        return before->next;
    }

    // 118
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        if(!numRows) return ans;
        ans.push_back(vector<int> (1,1));
        for(int i = 1; i < numRows; i++){
            vector<int> &last = ans.back();
            vector<int> tmp;
            tmp.push_back(1);
            for(int j = 0; j + 1 < last.size(); j++){
                tmp.push_back(last[j] + last[j + 1]);
            }
            tmp.push_back(1);
            ans.push_back(tmp);
        }
        return ans;
    }

    // 119
    vector<int> getRow(int rowIndex) {
        vector<int> last(rowIndex + 1), now(rowIndex + 1);
        last[0] = 1;
        for(int i = 0; i < rowIndex; i++){
            now[0] = 1;
            for(int j = 0; j + 1 <= i; j++){
                now[j + 1] = last[j] + last[j + 1];
            }
            now[i + 1] = last[i];
            last = now;
        }
        return last;
    }

    // 120 
    int minimumTotal(vector<vector<int>>& triangle) {
        for(int i = triangle.size() - 2; i >= 0; i--){
            for(int j = 0; j < i + 1; j++ ){
                triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }

    // 152 除去0以外，子串随着长度，其乘积绝对值递增。
    int maxProduct(vector<int>& nums) {
        int pos = 0, neg = 0;
        int res =  INT_MIN;
        for(auto x : nums){
            if(x > 0){
                if (pos > 0){
                    pos *= x;
                }
                else{
                    pos = x;
                }
                neg *= x;
            }
            else if(x < 0){
                int ng = neg;
                if(pos > 0){
                    neg = pos * x;
                }
                else{
                    neg = x;
                }
                pos = ng * x;
            }
            else{
                pos = neg = 0;
            }
            res = max(res, x);
            if(pos != 0) res = max(res, pos);
        }
        return res;
    }

    // 167
    vector<int> twoSum(vector<int>& numbers, int target) {
        for(int i = 0, j = numbers.size()-1; i < j; i++){
            while (numbers[i] + numbers[j] > target) j--;
            if(numbers[i] + numbers[j] == target){
                vector<int> res;
                res.push_back(i + 1), res.push_back(j + 1);
                return res;
            }
        }
        return {};
    }

    // 169
    int majorityElement(vector<int>& nums) {
        int cnt = 0, candidate;
        for(int i = 0; i < nums.size(); i++){
            if (cnt == 0) candidate = nums[i];
            if(candidate == nums[i]) cnt++;
            else cnt--;
        }
        return candidate;
    }

    // 1573 组合数学 插板法
    int numWays(string s) {
        int n = s.size(), ones = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1') ones++;
        }
        if (ones%3 != 0) return 0;
        if (ones == 0) return (LL)(n-1)*(n-2)/2%MOD;
        int cnt = 0, l1 = 0, l2 = 0;
        ones /= 3;
        for(int i = 0; i < n; i++){
            if(s[i] == '1') cnt++;
            if(cnt == ones) l1++;
            if(cnt == 2 * ones) l2++;
        }
        return (LL)l1*l2%MOD;
    }

    // 1574 前缀、后缀、滑动窗口
     int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int j = n - 1;
        // 处理后缀
        while (j > 0 && arr[j - 1] <= arr[j]) j--;
        int ans = n - j;
        // 遍历前缀终点
        for (int i = 0; i < n; i++){
            if (i && arr[i] < arr[i - 1]) break;
            while (j <= i || (j < n && arr[i] > arr[j])) j++;
            ans = max(ans, i + n - j + 1);
        }
        return n - ans;
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

    // 1584 prime minSpanTree
     int prime(int s, int n ){
        int ans = 0;
        for(int j = 1; j <= n; j++){
            cls[j] = s;
            dis[j] = mpt[s][j];
        }
        dis[s] = -1;
        for(int i = 1; i < n; i++){
            int Min = INF, k;
            for(int j = 1; j <= n; j++)
                if(dis[j]!=-1 && dis[j]<Min){
                    Min = dis[k=j];
                }
                ans += dis[k];
                dis[k] = -1;
                for(int j = 1; j <= n; j++)
                    if(dis[j]!=-1 && mpt[k][j] < dis[j]){
                        dis[j] = mpt[k][j];
                        cls[j] = k;
                    }
        }
        return ans;
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        for( int i = 0; i < n; i++)
            for(int j = 0; j < n; j++){
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                mpt[i+1][j+1] = mpt[j+1][i+1] = abs(x1 - x2) + abs(y1 - y2);
            }
        int ans = prime(1, n);
        return ans;
    }
};

void test_57(){
    Solution m_solution;
    vector<vector<int>> intervals = {{1,3}, {6,9}};
    vector<int> newInterval = {2,5};
    vector<vector<int>> ans = m_solution.insert(intervals, newInterval);
    for(int i = 0; i < ans.size(); i++){
        cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
    }
}

void test_63(){
    Solution m_solution;
    // vector<vector<int> > obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    vector<vector<int> > obstacleGrid = {{0,0,0}};
    int ans = m_solution.uniquePathsWithObstacles(obstacleGrid);
    cout<<ans<<endl;
}

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

void test_73(){
    Solution m_solution;
    vector<vector<int>> matrix = {{1,1,1},{1,0,1},{1,1,1}};
    m_solution.setZeroes(matrix);
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            cout<<matrix[i][j];
        }
        cout<<endl;
    }
}

void test_74(){
    Solution m_solution;
    vector<vector<int>> matrix = {{1,3,5},{6,7,9},{11,13,16}};
    bool ans = m_solution.searchMatrix(matrix, 33);
    cout<<ans;
}

void test_81(){
    Solution m_solution;
    vector<int> nums = {2,5,6,0,0,1,2};
    bool ans = m_solution.search(nums, 22);
    cout<<ans;
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

void test_86(){
    Solution m_solution;
    ListNode *head = new ListNode(0);
    ListNode *t = head;
    t->next = new ListNode(1); t = t->next;
    t->next = new ListNode(4); t = t->next;
    t->next = new ListNode(3); t = t->next;
    t->next = new ListNode(2); t = t->next;
    t->next = new ListNode(5); t = t->next;
    t->next = new ListNode(2); t = t->next;
    ListNode *ans = m_solution.partition(head->next, 3);
    while(ans->next != nullptr){
        cout<<ans->val<<" ";
        ans = ans->next;
    }
    cout<<ans->val;
}

void test_118(){
    Solution m_solution;
    vector<vector<int>> ans = m_solution.generate(5);
    for(int i = 0; i < ans.size(); i++){
        for(int j = 0; j < ans[i].size(); j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
}

void test_119(){
    Solution m_solution;
    vector<int> ans = m_solution.getRow(4);
    for(int i = 0; i < ans.size(); i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}

void test_120(){
    Solution m_solution;
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
    int ans = m_solution.minimumTotal(triangle);
    cout<<ans;
}

void test_152(){
    Solution m_solution;
    // vector<int> nums = {2,3,-1,4};
    vector<int> nums = {1,2,-1,-2,2,1,-2,1,4,-5,4};
    int ans = m_solution.maxProduct(nums);
    cout<<ans;
}

void test_167(){
    Solution m_solution;
    vector<int> numbers = {2,7,11,15};
    vector<int> ans = m_solution.twoSum(numbers, 29);
    for(auto i : ans){
        cout<<i<<" ";
    }
}

void test_169(){
    Solution m_sulution;
    vector<int> nums = {2,2,1,1,1,2,2};
    int ans = m_sulution.majorityElement(nums);
    cout<<ans;
}

void test_1573(){
    Solution m_solution;
    string s = "10101";
    int ans = m_solution.numWays(s);
    cout<<ans<<endl;
}

void test_1574(){
    Solution m_solution;
    vector<int> arr = {1,2,3,10,4,2,3,5};
    int ans = m_solution.findLengthOfShortestSubarray(arr);
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

void test_1584(){
    Solution m_solution;
    vector<vector<int>> points = {{3,12},{-2,5},{-4,1}};
    int ans = m_solution.minCostConnectPoints(points);
    cout<<ans<<endl;
}

int main(){
    cout<<"hello leetcode"<<endl;
    // test_57();
    // test_63();
    // test_66();
    // test_67();
    // test_73();
    // test_74();
    // test_81();
    // test_83();
    // test_86();
    // test_118();
    // test_119();
    // test_120();
    // test_152();
    // test_167();
    test_169();
    // test_1573();
    // test_1574();
    // test_1576();
    // test_1577();
    // test_1578();
    // test_1582();
    // test_1584();
    return 0;
}