#include <string>
#include <vector>
#include <algorithm>
using std::min;
using std::vector;
using std::string;

class Solution {
public:
    int expand(const string& s, int left, int right) {
        // 计算臂长
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return (right - left - 2) / 2;
    }

    string longestPalindrome(string s) {
        //字符扩充 "ab" -> "#a#b#"
        int start = 0, end = -1;
        string t = "#";
        for (char c: s) {
            t += c;
            t += '#';
        }
        t += '#';
        s = t;

        // 臂长dp数组,记录字符串对应i位置的臂长
        vector<int> arm_len;
        // 当前回文中心以及对应的最右端
        int right = -1, j = -1;
        for (int i = 0; i < s.size(); ++i) {
            int cur_arm_len;
            //  如果当前位置小于等于最右端
            if (right >= i) {
                // i 关于j的对称点
                int i_sym = j * 2 - i;
                // 显然,如果对称点的臂长小于i到最右端的距离,那么 i点的臂长至少也是对称点的臂长
                // 如果对称点的臂长大于i到最右端的距离,那么i点的臂长至少是i到最右端的距离
                // 证明:
                //     center 是对称点, 那么关于center对称的所有点都应该是相等的
                //     i_sym 是对称点,那么关于i_sym对称的所有点也都是相等的
                //     对于当前位置i来说, 显然以i为对称点的区间和它关于center对称的区间是严格相等的
                //     那么至少在i_sym区间与center区间相交的部分, i区间对应对称的部分也应该是相等的
                //     因此只需在此基础上扩展即可
                int min_arm_len = min(arm_len[i_sym], right - i);
                // 中心扩散
                cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
            } else {
                // 当前位置大于最右端, 那么它是没有对应对称点的
                cur_arm_len = expand(s, i, i);
            }
            arm_len.push_back(cur_arm_len);
            // 当前位置的对应的最右端大于目前最右端的话,就更新最右端的值和中心点的值
            if (i + cur_arm_len > right) {
                j = i;
                right = i + cur_arm_len;
            }
            // 这里是计算最大回文串的长度
            if (cur_arm_len * 2 + 1 > end - start) {
                start = i - cur_arm_len;
                end = i + cur_arm_len;
            }
        }

        string ans;
        for (int i = start; i <= end; ++i) {
            if (s[i] != '#') {
                ans += s[i];
            }
        }
        return ans;
    }
};