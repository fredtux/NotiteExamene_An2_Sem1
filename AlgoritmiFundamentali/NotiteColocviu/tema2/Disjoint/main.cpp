/**
 * Incepem de la multimi individuale unde fiecare element i apartine multimii formate din el insusi, adica {i}
 * Dupa mai multe reuniuni, multimile vor arata de forma {x1, x2, x3...}, adica reuniune de multimi de elemente individuale
 * Deoarece nu avem intervale, putem considera multimea ca fiind un arbore in care elementul mai mic este tatal elementului mai mare
 * Asadar, reuniunea se reduce la a cauta nodul tata al lui x, nodul tata al lui y si a-l alipi nodului cel mai mic dintre cei doi formand o componenta conexa
 * Este evident ca un nod tata va avea ca tata pe el insusi
 * Pentru afisare, pur si simplu vom vedea daca x si y au acelasi tata, daca au, atunci afisam DA, daca n-au, atunci afisam NU
 *
 * Compelxitate op1: O(tx + ty + 1), unde tx = numarul de noduri mai mici ca x din componenta sa conexa, ty = la fel pentru y si 1 alipirea
 * Final op1: O(n)
 * Complexitate op2: O(tx + ty), aceleasi notatii ca mai sus
 * Final op2: O(n)
 *
 * Complexitatea problemei: O(n * nr_op), unde nr_op este numarul de operatii
 * Complexitatea finala a problemei: O(n)
 */

#include<bits/stdc++.h>

using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

int n, m, op, x, y, i;
int tata[100001];

/**
 * Umplere rapida de array cu numere in ordine crescatoare
 * @param arr
 * @param val
 * @param bound
 */
inline void fill_array(int *arr, int val, int bound) {
    int *arrCpy = arr;
    int *last = arr + bound;
    while (arrCpy != last)
        *arrCpy++ = val++;

}

/**
 * Cautam nodul de inceput (tatal tatilor)
 * @param x
 * @return
 */
inline int cautaTatal(int &x) {
    while (tata[x] != x) {
        tata[x] = tata[tata[x]];
        x = tata[x];
    }

    return x;
}

/**
 * Cautam nodurile de inceput pentru x si y si unim cele 2 componente conexe
 * @param x
 * @param y
 */
void joinset(int &x, int &y) {
    int xx = cautaTatal(x);
    int yy = cautaTatal(y);

    if (x > y)
        tata[xx] = yy;
    else
        tata[yy] = xx;

}

/**
 * Daca x si y au acelasi nod de inceput, atunci sunt in aceeasi componenta conexa, deci in aceeasi multime
 * @param x
 * @param y
 */
inline void show(int &x, int &y) {
    fout << (cautaTatal(x) == cautaTatal(y) ? "DA\n" : "NU\n");
}

int main() {
    fin >> n >> m;

    // Umplem array-ul cu numere in ordine crescatoare
    fill_array(tata, 0, m);

    for (i = 0; i < m; ++i) {
        fin >> op >> x >> y;

        switch (op) {
            case 1:
                joinset(x, y);
                break;
            case 2:
                show(x, y);
                break;
            default:
                return -1;
        }
    }

    return 0;
}