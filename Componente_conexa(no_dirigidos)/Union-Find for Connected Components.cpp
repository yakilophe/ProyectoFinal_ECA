#include <iostream>
using namespace std;

const int MAXN = 100;

// --------------------------------------------------------------
// Variables globales
// --------------------------------------------------------------
int n;
int grafo[MAXN][MAXN];
int padre[MAXN];

// --------------------------------------------------------------
// Funcion FIND (con compresion de caminos)
// --------------------------------------------------------------
int findSet(int u) {
    if (padre[u] == u) return u;
    return padre[u] = findSet(padre[u]);
}

// --------------------------------------------------------------
// Funcion UNION (une dos componentes)
// --------------------------------------------------------------
void unite(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) padre[b] = a;
}

// --------------------------------------------------------------
// Main
// --------------------------------------------------------------
int main() {
    cout << "Numero de nodos: ";
    cin >> n;

    cout << "Ingresa la matriz de adyacencia:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grafo[i][j];
        }
    }

    // Inicializar Union-Find
    for (int i = 0; i < n; i++) {
        padre[i] = i;
    }

    // Unir nodos conectados
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grafo[i][j] == 1) {
                unite(i, j);
            }
        }
    }

    cout << "\nComponentes Conexas:\n";
    bool impreso[MAXN] = {false};

    for (int i = 0; i < n; i++) {
        int raiz = findSet(i);

        if (!impreso[raiz]) {
            cout << "CC: ";
            for (int j = 0; j < n; j++) {
                if (findSet(j) == raiz) {
                    cout << j << " ";
                }
            }
            cout << endl;
            impreso[raiz] = true;
        }
    }

    return 0;
}
