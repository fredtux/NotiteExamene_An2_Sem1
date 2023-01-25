/**
 * Problema se aseamana cu algorimtul lui Dijkstra, dar este modificat astfel incat sa tina drumul cel mai lung
 * Am folosit un max heap pentru algoritm ca sa aiba un timp mai mic de rulare
 * Am explicat implementarea pe pasi, dar ideea de rezolvare este destul de directa
 *
 * Complexitatea: Asemanatoare cu algoritmul lui Dijkstra cu min heap, cu toate ca am folosit max heap, practic nu schimba complexitatea
 * Complexitate finala: O(n + m), unde n este numarul de noduri si m numarul de muchii
 *
 * LeetCode: https://leetcode.com/problems/path-with-maximum-probability/submissions/848238594/
 */
#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    // Helperul este o combinatie de noduri (int) si succProb (double)
    // helper[i] = {j,p} inseamna ca nodul i se va duce in j cu probabilitatea p
    vector<vector< pair<int, double>>> helper;

    // Vom tine un max heap cu toate muchiile vizitate
    priority_queue<pair<double, int>, vector<pair<double, int>>, less<pair<double, int>>> pq;

    // Distantele date de probabilitate pana la un nod
    vector<double> d;
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // Memoram edges.size() ca sa nu-l apelam mai tarziu de prea multe ori
        int m = edges.size();

        // Helperul va avea numarul de noduri
        helper.resize(n);

        // Distantele probabilistice de la fiecare nod la el insusi vor fi 0 (practic numarul cel mai mic)
        d.resize(n, 0);

        // Populam helperul
        for(int i = 0; i < m; ++i){
            helper[edges[i][0]].push_back({edges[i][1], succProb[i]});
            helper[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }

        // Incepem din primul nod cu probabilitatea 1
        pq.push({1, start});

        // Distanta probabilistica pana la el este tot 1
        d[start] = 1;

        // Iteram prin noduri
        while(!pq.empty()){
            // Preluam cel mai mare element din heap si il excludem
            double p = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Pentru fiecare vecin al nodului, vom calcula distantele probabilistice si le vom actualiza daca sunt mai mari
            for(auto x: helper[node]){
                if(d[x.first] < d[node] * x.second){
                    d[x.first] = d[node] * x.second;
                    pq.push({d[x.first], x.first});
                }
            }
        }

        // Returnam distanta probabilistica a ultimului nod, dat fiind ca am plecat din nodul "start"
        return d[end];


    }
};

int main() {

    Solution *s = new Solution();
    int n = 3;
    vector<vector<int>> edges = {{0,1}, {1,2}, {0,2}};
    vector<double> succProb = {0.5,0.5,0.2};
    int start = 0;
    int end = 2;

    cout << s->maxProbability(n, edges, succProb, start, end);

    return 0;
}