/**
 * Folosim Edmonds Karp cu BFS
 *
 * La citire cream un graf orientat in care muchia dintre nod1 si nod2 reprezinta o legatura si in matricea capacitate stocam
 * capacitatea traficului, dar adaugam si legatura nod2 spre nod1 in care muchia apartine grafului rezidual.
 *
 * Pentru determinarea flowului maxim, vom aplica Edmonds Karp si vom verifica pentru fiecare pas daca putem face o parcurgere BFS.
 * Pentru fiecare parcurgere vom porni de la sink si vom identifica bottleneck-ul, urmand apoi sa actualizam capacitatea si graful rezidual.
 *
 * Rezultatul final va fi dat de flowul determinat in fiecare iteratie a algoritmului Edmonds Karp.
 *
 * Deoarece folosim Edmonds Karp cu BFS stiind de la inceput startul si sinkul, complexitatea este de O(V*E^2), unde V = nr noduri, iar E = nr muchii
 *
 * Infoarena: https://www.infoarena.ro/job_detail/2962341?action=view-source
 */

#include <bits/stdc++.h>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

int n, m, a, b, c, maxfl, fl, start = 1, sink, i;
vector<int> graph[1001];
int tata[1001];
int capacitate[1001][1001];
bool viz[1001];

bool bfs() {
    queue<int> q;
    memset(viz, false, n * sizeof(bool));

    for (i = 1; i <= n; ++i) {
        q.push(start);
        viz[start] = true;


        while (!q.empty()) {
            a = q.front();
            q.pop();

            for (int &vecin: graph[a]) {
                if (!viz[vecin] && capacitate[a][vecin] != 0) {
                    tata[vecin] = a;

                    if (vecin == sink)
                        return true;

                    viz[vecin] = true;
                    q.push(vecin);
                }
            }
        }
    }

    return false;
}

void maxflow() {
    while (bfs()) {
        a = sink;
        fl = INT_MAX;

        while (a != start) {
            b = tata[a];
            if (capacitate[b][a] < fl)
                fl = capacitate[b][a];

            a = b;
        }

        a = sink;

        while (a != start) {
            b = tata[a];
            capacitate[a][b] += fl;
            capacitate[b][a] -= fl;

            a = b;
        }

        maxfl += fl;

    }
}

int main() {
    fin >> n >> m;

    sink = n;
//    viz = (bool *) realloc(viz, n * sizeof(bool));
    tata[start] = -1;


//    graph.resize(n + 1);
//    tata.resize(n + 1);

    for (i = 0; i < m; ++i) {
        fin >> a >> b >> c;
        graph[a].push_back(b);
        graph[b].push_back(a);
        capacitate[a][b] = c;
    }

//    fin.close();

    maxflow();

    fout << maxfl;
//    fout.close();

/**
 * Punctul b)
 */

    srand(time(0));
    int elimina = rand() % n;
    for (auto &x: graph[elimina])
        std::remove(graph[x].begin(), graph[x].end(), elimina);
    graph[elimina].clear();
    if (elimina == 1)
        ++start;
    if (elimina == n)
        --sink;
    memset(tata, false, n * sizeof(int));
    tata[start] = -1;

    maxflow();

    fout << "\n";

    fout << maxfl;


    return 0;
}