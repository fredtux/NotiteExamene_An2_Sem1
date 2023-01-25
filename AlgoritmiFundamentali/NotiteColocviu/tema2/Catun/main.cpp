/**
 * Practic avem de facut algoritmul lui Dijkstra din fiecare fortareata in fiecare sat
 * Daca gasim egalitate, facem ca in enunt
 *
 * Complexitate: O(log(k) + (n + m) * k), deoarece avem sortare, apoi Dijkstra implementat prin min heap pe care il facem pentru k fortarete
 */

#include <bits/stdc++.h>

using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");

int n, m, k, i, x, y, z, tmp;
vector<int> f,d;
vector<vector<pair<int, int>>> adi;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int dnode, nnode, dv, nv;
vector<int> res;

/**
 * Algoritmul lui dijkstra cu modificari in ceea ce tine de fortarete
 * @param node
 */
void dijkstra(int &node){
    d[node] = 0;
    pq.push({0, node});

    while(!pq.empty()){
        dnode = pq.top().first;
        nnode = pq.top().second;
        pq.pop();

        for(auto it: adi[nnode]){
            nv = it.first;
            dv = it.second;

            if(find(f.begin(), f.end(), nv) != f.end())
                continue;

            if(d[nv] > d[nnode] + dv){
                d[nv] = d[nnode] + dv;
                res[nv] = node;
                pq.push({d[nv], nv});
            } else if(d[nv] == d[nnode] + dv){
                if(res[nv] > node)
                    res[nv] = node;
            }
        }
    }
}

int main() {
    // Citim datele
    fin >> n >> m >> k;

    // Marim vectorul de rezultat ca sa incapa toate nodurile
    res.resize(n + 1, 0);

    // Marim vectorul de distante ca sa incapa toate nodurile
    d.resize(n + 1, INT_MAX);

    // Marim lista de adiacenta ca sa incapa toate nodurile
    adi.resize(n + 1);

    // Marim vectorul de fortarete ca sa incapa toate
    f.resize(k);

    // Citim numerele de ordine ale fortaretelor
    for(i = 0; i < k; ++i){
        fin >> tmp;
        f[i] = tmp;
    }
    // Sortam fortaretele
    sort(f.begin(), f.end(), less<int>());


    // Citim drumurile
    for(i = 0; i < m; ++i){
        fin >> x >> y >> z;
        adi[x].push_back({y, z});
        adi[y].push_back({x, z});
    }

    // Facem dijkstra de la fiecare fortareata
    for(auto x : f)
        dijkstra(x);

    // Afisam rezultatul
    for(auto it = res.begin() + 1; it != res.end(); ++it)
        fout << *it << " ";

    return 0;
}