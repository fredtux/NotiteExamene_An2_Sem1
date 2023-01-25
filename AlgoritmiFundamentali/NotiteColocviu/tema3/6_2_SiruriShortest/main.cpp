/**
 * Programare dinamica
 *
 * Vom face o matrice de stringuri in care vom pune cuvintele formate pana in acel loc.
 * Metoda este asemanatoare cu problema anterioara, pe linii mapam un string, pe coloane altul.
 * Daca litera la care am ajuns este la fel, vom adauga de pe diagonala stanga-sus si vom concatena cu litera comuna.
 * Daca litera difera, vom copia sirul mai mare dintre cel aflat la stanga si cel aflat deasupra.
 * La sfarsit, daca mai raman litere le adaugam pe rand.
 *
 * Complexitate: O(n*m)
 *
 * Leetcode: https://leetcode.com/problems/shortest-common-supersequence/submissions/874296399/
 *
 * Sursa de inspiratie: https://leetcode.com/problems/shortest-common-supersequence/solutions/312710/c-python-find-the-lcs/
 */
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int i = 0;
        int j = 0;
        stringstream res("");
        string res2;
        int n = str1.size();
        int m = str2.size();
        vector<vector<string>> dp(n + 1, vector<string>(m+1,""));

        for(int i = 0; i < n; ++i){
            for(int j = 0; j< m; ++j){
                if(str1[i] == str2[j]){
                    dp[i + 1][j+1] = dp[i][j] + str1[i];
                } else{
                    if(dp[i+1][j].size() > dp[i][j+1].size()){
                        dp[i+1][j+1] = dp[i+1][j];
                    } else {
                        dp[i+1][j+1] = dp[i][j+1];
                    }
                }

            }
        }

        for(char c : dp[n][m]){
            while(str1[i] != c)
                res << str1[i++];
            while(str2[j] != c)
                res << str2[j++];

            res << c;
            ++i;
            ++j;
        }

        res << str1.substr(i) << str2.substr(j);
        res >> res2;
        return res2;
    }
};

int main() {
    Solution *sol = new Solution();

    string str1 = "abac";
    string str2 = "cab";

    cout << sol->shortestCommonSupersequence(str1, str2);

    return 0;
}