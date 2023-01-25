/**
 * Programare dinamica
 *
 * Folosim o matrice numita dp care va avea mapate pe linii literele primului text si pe coloana literele celui de-al doilea text.
 * La intersectia lor vom avea lcs intre subsirurile respective (spre jos si spre dreapta).
 * Facem recursiv pana acoperim sirurile si returnam lcs.
 *
 * Complexitate: O(n*m)
 *
 * Leetcode: https://leetcode.com/problems/longest-common-subsequence/submissions/874277603/
 *
 * Surse de inspiratie:
 * https://www.youtube.com/watch?v=Ua0GhsJSlWM
 * https://leetcode.com/problems/longest-common-subsequence/solutions/2914722/c-dynamic-programming-memoization-tabulation-with-space-optimization-easy-to-understand/
 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findSub(string &text1, string &text2, int i, int j, vector<vector<int>> &dp) {
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (text1[i] == text2[j]) {
            dp[i][j] = 1 + findSub(text1, text2, i - 1, j - 1, dp);
            return dp[i][j];
        }

        dp[i][j] = max(findSub(text1, text2, i - 1, j, dp), findSub(text1, text2, i, j - 1, dp));
        return dp[i][j];
    }

    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), -1));
        return findSub(text1, text2, text1.size() - 1, text2.size() - 1, dp);
    }
};

int main() {

    Solution *sol = new Solution();

    string text1 = "abcde";
    string text2 = "ace";

    cout << sol->longestCommonSubsequence(text1, text2);

    return 0;
}