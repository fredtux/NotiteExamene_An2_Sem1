/**
 * Am folosit unweighted bipartite matching cu maximum flow
 *
 * Am facut graful directionat cu capacitate de 1 pe fiecare muchie
 * Am adaugat drumuri de la sursa la fiecare nod din primul graf si de la fiecare nod din al doilea graf la sink
 * Am calculat maxflow cu BFS
 * Am afisat toate muchiile ramase care sunt de la primul graf la al doilea si care au capacitatea ramasa 0
 *
 * Sursa de inspiratie: https://www.youtube.com/watch?v=GhjwOiJ4SqU
 *
 * Infoarena: https://www.infoarena.ro/job_detail/2962448?action=view-source
 */
#include <bits/stdc++.h>

using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

int n, m, e, d, a, b, nmuchii = -1, i, maxfl, node, vdest, vcapac, fl, minv;
vector<tuple<int, int, int>> muchii;
vector<int> mid[20002];
int tata[20002];
bool viz[20002];


bool bfs() {
    queue<int> q;
    memset(tata, 0, d * sizeof(int) + 2);
    memset(viz, false, d * sizeof(bool) + 2);

    q.push(0);
    viz[0] = true;

    while (!q.empty()) {
        node = q.front();
        q.pop();

        if (node == d)
            continue;

        for (auto &vecin: mid[node]) {
            vdest = get<1>(muchii[vecin]);
            vcapac = get<2>(muchii[vecin]);
            if (!viz[vdest] && vcapac != 0) {
                tata[vdest] = vecin;
                viz[vdest] = true;
                q.push(vdest);
            }
        }
    }

    return viz[d];
}

void maxflow() {
    while (bfs()) {
        for (auto &el: mid[d]) {
            vdest = get<1>(muchii[el]);
            if (viz[vdest] && get<2>(muchii[el - 1]) != 0) {
                node = d;
                fl = 1;
                tata[d] = el - 1;

                while (node != 0) {
                    fl = min(fl, get<2>(muchii[tata[node]]));
                    node = get<0>(muchii[tata[node]]);
                }

                node = d;

                while (node != 0 && fl != 0) {


                    if (tata[node] % 2 == 1) {
                        minv = tata[node] - 1;
                    } else {
                        minv = tata[node] + 1;
                    }

                    get<2>(muchii[tata[node]]) -= fl;
                    get<2>(muchii[minv]) += fl;

                    node = get<0>(muchii[tata[node]]);
                }

                maxfl += fl;
            }
        }

    }
}

int main() {
    fin >> n >> m >> e;

    d = n + m + 1;

    do {
        fin >> a >> b;
        ++nmuchii;

        muchii.push_back({a, b + n, 1});
        mid[a].push_back(nmuchii);

        ++nmuchii;
        muchii.push_back({b + n, a, 0});
        mid[b + n].push_back(nmuchii);
    } while (--e);

    for (i = 1; i <= n; ++i) {
        ++nmuchii;
        muchii.push_back({0, i, 1});
        mid[0].push_back(nmuchii);

        ++nmuchii;
        muchii.push_back({i, 0, 0});
        mid[i].push_back(nmuchii);
    }

    for (i = 1; i <= m; ++i) {
        ++nmuchii;
        muchii.push_back({i + n, d, 1});
        mid[i + n].push_back(nmuchii);

        ++nmuchii;
        muchii.push_back({d, i + n, 0});
        mid[d].push_back(nmuchii);
    }

    maxflow();

    fout << maxfl << '\n';

    for (auto &el: muchii) {
        if (get<0>(el) != 0 && get<0>(el) < get<1>(el) && get<1>(el) != d && get<2>(el) == 0) {
            fout << get<0>(el) << ' ' << get<1>(el) - n << '\n';
        }
    }

    return 0;
}