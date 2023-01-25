/**
 * In continuare ma voi referi la un test unic. Problema poate fi generalizata pe mai multe teste.
 *
 * Cazul particular al problemei il reprezinta atunci cand toate nodurile au valoare negativa.
 * In acest caz il vom lua pe cel mai mare, pentru ca daca mai adaugam unul, suma doar va scadea
 *
 * Pasul 1
 * Pentru fiecare nod vom calcula numarul de noduri de intrare. Ideea din spate e de a gasi nodurile de start ale grafului
 * Daca gasim un nod cu indegree 0, atunci il vom adauga in coada. Este garantat cel putin 1 astfel de nod dat fiind graful aciclic
 * Daca valoarea sau e negativa, atunci lasam distanta 0, pentru ca plecand de la numere pozitive, un numar negativ poate doar sa scaada suma
 *
 * Pasul 2
 * Cat timp avem elemente in coada, scoatem pe rand cate un element si verificam daca distanta sa e mai mare decat rezultatul
 * Pentru fiecare vecin al nodului scos din coada, vom inlocui distanta cu maximul dintre cea curenta si suma distantei curente cu valoarea nodului scos din coada
 * Pentru fiecare vizitare, muchia se arde si indegreeul scade cu o unitate. Daca indegreeul ajunge la 0, atunci adaugam nodul in coada
 * Facem acest lucru deoarece el reprezinta un nou nod de intrare in graf, dupa ce vecinii sai au fost epuizati
 * Cazul pe care vrem sa-l evitam este sa scadem suma totala, asa ca daca valoarea nodului va produce impreuna cu suma de pana la el un numar negativ, il tratam ca avand distanta 0, deci nod de start
 *
 */
#include <bits/stdc++.h>

using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

int n, m, t, i, x, y, tmp;
vector<int> v;
vector<int> d;
vector<vector<int>> adi;
vector<int> indegree;
queue<int> q;
int res;

void easygraph(){
    // Citim n si m
    fin >> n >> m;

    // Refacem vectorii si coada
    v = vector<int>(n + 1, 0);
    d = vector<int>(n + 1, 0);
    adi = vector<vector<int>>(n + 1, vector<int>());
    indegree = vector<int>(n + 1, 0);
    q = queue<int>();

    // Citim v
    for(auto it = v.begin() + 1; it != v.end(); ++it)
        fin >> *it;

    // Citim muchiile si tinem o lista cu numarul de muchii de intrare
    for(i = 0; i < m; ++i){
        fin >> x >> y;
        adi[x].push_back(y);
        ++indegree[y];
    }

    // Luam prima data elementul cel mai mare
    res = *max_element(v.begin(), v.end());

    // Caz particular, daca cel mai mare element e negativ, atunci il afisam, pentru ca nu are decat sa scada pe viitor
    if(res < 0){
        fout << res << "\n";
        return;
    }

    // Punem in coada toate nodurile fara muchii de intrare
    for(i = 1; i <= n; ++i){
        if(!indegree[i]) {
            q.push(i);
            // Daca valoarea e pozitiva, o punem ca distanta
            if(v[i] > 0)
                d[i] = v[i];
        }
    }

    // Pentru fiecare element din coada
    while(!q.empty()){
        tmp = q.front();
        q.pop();

        // Punem ca rezultat daca e mai mare drumul pana la el
        res = max(res, d[tmp]);

        // Pentru fiecare vecin al elementului scos din coada
        for(auto it: adi[tmp]){
            // Daca distanta e mai mare decat cea actuala, o actualizam
            d[it] = max(d[it], d[tmp] + v[it]);
            // Eliminam una dintre muchii
            --indegree[it];
            // Daca nu mai are muchii, poate fi folosit ca nod de inceput si pus in coada
            if(!indegree[it])
                q.push(it);
        }
    }

    fout << res << "\n";
}

int main() {
    fin >> t;

    while(t--)
        easygraph();

    return 0;
}