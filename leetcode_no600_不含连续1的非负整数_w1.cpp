/* ------------------------------------------------------------------|
给定一个正整数 n，找出小于或等于 n 的非负整数中，其二进制表示不包含 连续的1 的个数。

示例 1:

输入: 5
输出: 5
解释:
下面是带有相应二进制表示的非负整数<= 5：
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
其中，只有整数3违反规则（有两个连续的1），其他5个满足规则。
说明: 1 <= n <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	双指针法
*
*	执行用时：8 ms, 在所有 C++ 提交中击败了26.81%的用户
*	内存消耗：7.7 MB, 在所有 C++ 提交中击败了13.77%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int findIntegers(int num) {
    vector<int> nums;
    while (num) {
        nums.push_back(num % 2);
        num /= 2;
    }

    vector<vector<int>> dp(nums.size(), vector<int>(2));
    dp[0][0] = 1;
    dp[0][1] = 1;
    for (int i = 1; i < nums.size(); i++) {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
    }

    int res = 0;
    int last = 0;
    for (int i = nums.size() - 1; i >= 0; i--) {
        int x = nums[i];
        //在每一位都为1时，记录下该位为0开头的所有的数的总数
        //  比如 ：1XXX时，读取dp[3][0]，将所有0XXX的情况算入总数
        //  *11XX时，读取dp[2][0]，将10XX的情况算入总数，直接break退出循环，表示已经将所有的数找完了
        //  101X时，该位为1，读取dp[1][0]，将100X的情况算入总数
        //  1010时，本来该不操作的，但是又没有提前break，说明当前这个数符合要求，res要+1
        if (x) {
            res += dp[i][0];
            if (x && last) {
                break;
            }
        }
        last = x;
        if (!i) {
            res++;
        }
    }
    return res;
}

int main() {
    int num = 12;
    int res = findIntegers(num);
}