/**
 * Maxflow cu BFS
 *
 * Adaugam un nod de start (stanga) si un nod de sink (dreapta) si legam nodurile intre ele
 * Rulam algoritmul Edmonds Karp pentru flux maxim cu bfs.
 *
 * La sfarsit luam doar muchiile saturate si le afisam.
 * 
 * Complexitate: O(V*E^2)
 *
 * Infoarena: https://www.infoarena.ro/job_detail/2962514?action=view-source
 *
 */
#include <bits/stdc++.h>

using namespace std;

ifstream fin("harta.in");
ofstream fout("harta.out");

int n, fl, maxfl, i, j, a, b, sink, cnode;
pair<int, int> nod;
vector<int> graph[202];
int capac[202][202];
int tata[202];
bool viz[202];

bool bfs(){
    queue<pair<int, int>> q;
    memset(tata, 0, (sink+1) * sizeof(int));
    memset(viz, false, (sink+1) * sizeof(bool));

    q.push({0, INT_MAX});
    viz[0] = true;

    while(!q.empty()){
        nod = q.front();
        q.pop();

        for(auto &vecin: graph[nod.first]){
            if(!viz[vecin] && capac[nod.first][vecin] > 0){
                tata[vecin] = nod.first;
                viz[vecin] = true;
                fl = min(nod.second, capac[nod.first][vecin]);

                if(vecin == sink)
                    return true;

                q.push({vecin, fl});
            }
        }
    }

    fl = 0;
    return false;
}

int main() {
    fin >> n;
    sink = 2 * n + 1;

    for(i = 1; i <= n; ++i){
        fin >> a >> b;
        graph[0].push_back(i);
        graph[i].push_back(0);
        capac[0][i] = a;

        graph[n+i].push_back(sink);
        graph[sink].push_back(n+i);
        capac[n+i][sink] = b;
    }

    for(i = 1; i<= n; ++i){
        for(j = n + 1; j < sink; ++j){
            if(j - i == n)
                continue;

            capac[i][j] = 1;
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
    }

    while(bfs()){
        maxfl += fl;
        cnode = sink;

        while(cnode){
            capac[cnode][tata[cnode]] += fl;
            capac[tata[cnode]][cnode] -= fl;

            cnode = tata[cnode];
        }
    }

    fout << maxfl << '\n';
    for(i = 1; i <= n; ++i){
        for(j = n + 1; j < sink; ++j){
            if(capac[j][i] == 1)
                fout << i << ' ' << j - n << '\n';
        }
    }

    return 0;
}