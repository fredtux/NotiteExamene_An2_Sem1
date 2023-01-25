/**
 * Conectam in prima faza toate blocurile la centrale si tinem cont de distante.
 * Apoi incepem cu blocul cu distanta minima si cautam sa vedem daca sunt si alte blocuri care se pot conecta la el.
 * Plecam de la urmatorul bloc de distanta minima si facem o retea intre blocuri cu aceeasi pasi.
 *
 * Complexitate: O(n*m) pentru primul pas si O(m * bviz) pentru al doilea pas, unde bviz sunt blocurile vizitate.
 * Total: O(n^2).
 *
 * Infoarena: https://www.infoarena.ro/job_detail/2944688
 */

#include <bits/stdc++.h>

using namespace std;

inline double deuc(int p1[2] ,int p2[2]){
    return sqrt(1LL * pow(1LL * p1[0] - p2[0], 2) + 1LL * pow(1LL * p1[1] - p2[1], 2));
}

ifstream fin("retea2.in");
ofstream fout("retea2.out");
int n, m, i, j;
int tmp1, tmp2;
int centrale[2001][2], blocuri[2001][2];
double dist[2001] , mind = DBL_MAX, result;
bool v[2001];
int minb = INT_MIN, currb;

int main() {
    // Citim datele
    fin >> n >> m;

    // Umplem dist cu DBL_MAX
    fill_n(dist, m, DBL_MAX);

    for(i = 0; i < n; ++i){
        fin >> tmp1 >> tmp2;
        centrale[i][0] = tmp1;
        centrale[i][1] = tmp2;
    }

    for(i = 0; i < m; ++i){
        fin >> tmp1 >> tmp2;
        blocuri[i][0] = tmp1;
        blocuri[i][1] = tmp2;
    }

    // Calculam distantele de la fiecare bloc la fiecare centrala
    for(i = 0; i < m; ++i){
        for(j = 0; j < n; ++j){
            dist[i] = min(dist[i], deuc(blocuri[i], centrale[j]));
        }

        // Pastram distanta minima si blocul aferent ca sa avem de unde incepe pasul urmator
        if(mind > dist[i]){
            mind = dist[i];
            minb = i;
        }
    }

    // Calculam distanta minima
    while(minb != INT_MIN){ // Daca nu mai e niciun bloc de conectat, ne oprim
        // Adaugam distanta minima la raspuns
        result += mind;
        // Blocul curent este cel minim
        currb = minb;
        // Vizitam blocul curent
        v[minb] = true;

        // Resetam valorile de minim pentru pasul urmator
        mind = DBL_MAX;
        minb = INT_MIN;

        // Dupa ce am conectat blocul, reactualizam lista de distante fata de celelalte blocuri
        for(int i = 0; i < m; ++i){
            // Daca blocul nu a fost adaugat
            if(!v[i]){
                // Distanta fata de blocul curent
                dist[i] = min(dist[i], deuc(blocuri[currb], blocuri[i]));

                // Tracking pe minim
                if(mind > dist[i]){
                    mind = dist[i];
                    minb = i;
                }
            }
        }

    }

    // Afisam rezultatul
    fout << setprecision(6) << fixed << result;



    return 0;
}