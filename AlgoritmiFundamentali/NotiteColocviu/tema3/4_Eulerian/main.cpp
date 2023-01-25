/**
 * Transformam perechile intr-un graf orientat
 * Cautam un nod de start pentru graful Eulerian (problema garanteaza existenta lui)
 * Va fi nodul cu out - in = 1
 *
 * Facem un DFS si inseram in postordine
 * Inversam vectorul rezultat
 * 
 * Complexitate: O(V + E)
 *
 * Sursa de inspiratie: https://leetcode.com/problems/valid-arrangement-of-pairs/solutions/1611978/c-eulerian-path-with-explanation/
 *
 * Leetcode: https://leetcode.com/problems/valid-arrangement-of-pairs/submissions/874198437/
 */


#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    unordered_map<int, stack<int>> graph;
    unordered_map<int, int> in;
    unordered_map<int, int> out;
public:
    void postorderdfs(unordered_map<int, stack<int>> &graph, vector<vector<int>> &res, int start){
        auto &s = graph[start];
        while(!s.empty()){
            int neigh = s.top();
            s.pop();
            // cout<< start << ' ';
            postorderdfs(graph, res, neigh);
            res.push_back({start, neigh});
        }
    }

    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        vector<vector<int>> res;
        int n = pairs.size();

        for(int i = 0; i < n; ++i){
            int a = pairs[i][0];
            int b = pairs[i][1];
            ++in[b];
            ++out[a];
            graph[a].push(b);
        }

        int start = INT_MIN;
        for(auto &el: graph){
            // cout << el.first << ' ' << el.second.top() << '\n';
            if(out[el.first] - in[el.first] == -1)
                start = el.first;
        }

        if(start == INT_MIN)
            start = graph.begin()->first;


        postorderdfs(graph, res, start);
        reverse(res.begin(), res.end());
        return res;
    }
};

ostream &operator<<(ostream &out, vector<vector<int>> v) {
    for (auto x: v) {
        out << x[0] << ' ' << x[1] << '\n';
    }
    out << "\n";

    return out;
}

int main() {
    Solution *sol = new Solution();

//    vector<vector<int>> p = {{5,  1},
//                             {4,  5},
//                             {11, 9},
//                             {9,  4}};

    vector<vector<int>> p = {{1,3}, {3,2}, {2,1}};
    cout << sol->validArrangement(p);

    return 0;
}