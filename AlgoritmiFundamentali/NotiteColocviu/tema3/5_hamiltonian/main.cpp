/**
 * BFS cu bitmasking
 *
 * Avem maxim 2^n posibile pathuri pentru cele n noduri. Deoarece n este intre 1 si 12, vom avea maxim 2^12 pathuri.
 * Din Acest motiv am folosit o masca pe biti pentru a vedea daca o ruta poate fi explorata.
 *
 * Deoarece ne cere cel mai scurt drum, algoritmul optim este BFS.
 *
 * Pentru a da raspunsul cat mai rapid am folosit o coada de tuplu cu 3 int-uri, primul fiind nodul, al doilea masca si al treilea costul. *
 *
 * Complexitate: O((N* 2^N) * N)
 *
 * Sursa de inspiratie: https://leetcode.com/problems/shortest-path-visiting-all-nodes/solutions/2928987/c-easy-bfs-bitmasking/
 *
 * Leetcode: https://leetcode.com/problems/shortest-path-visiting-all-nodes/description/
 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        queue<tuple<int, int, int>> q;

        set<pair<int,int>> visited;

        int all = pow(2, n) - 1;

        for(int i = 0; i < n; ++i){
            int mask = pow(2, i);

            q.push({i, mask, 1});
            visited.insert({i, mask});
        }

        while(!q.empty()){
            tuple<int, int, int> curr = q.front();
            q.pop();

            if(get<1>(curr) == all)
                return get<2>(curr) - 1;


            for(auto &el: graph[get<0>(curr)]){
                int bv = get<1>(curr);

                bv = bv | (int)pow(2, el);

                if(visited.find({el, bv}) == visited.end()){
                    visited.insert({el, bv});
                    q.push({el, bv, get<2>(curr) + 1});
                }
            }
        }



        return -1;
    }
};

int main(){
    Solution *sol = new Solution();

    vector<vector<int>> graph = {{1,2,3}, {0}, {0}, {0}};
    cout << sol->shortestPathLength(graph);

    return 0;
}