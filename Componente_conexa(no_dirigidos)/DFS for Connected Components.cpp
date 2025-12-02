#include <iostream>
using namespace std;

const int MAXN = 100;

// --------------------------------------------------------------
// Variables globales
// --------------------------------------------------------------
int n;
int grafo[MAXN][MAXN];
bool visitado[MAXN];

// --------------------------------------------------------------
// DFS desde un nodo inicial
// --------------------------------------------------------------
void dfs(int u) {
    visitado[u] = true;
    cout << u << " ";

    for (int v = 0; v < n; v++) {
        if (grafo[u][v] == 1 && !visitado[v]) {
            dfs(v);
        }
    }
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

    for (int i = 0; i < n; i++)
        visitado[i] = false;

    cout << "\nComponentes Conexas:\n";
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            cout << "CC: ";
            dfs(i);
            cout << endl;
        }
    }

    return 0;
}
