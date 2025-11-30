#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 100;

int n;
int grafo[MAXN][MAXN];
int transpuesto[MAXN][MAXN];
bool visitado[MAXN];
stack<int> pila;

// ===============================
// Funcion: limpiarVisitados
// ===============================
void limpiarVisitados() {
    for (int i = 0; i < n; i++)
        visitado[i] = false;
}

// ===============================
// Funcion: leerGrafo
// ===============================
void leerGrafo() {
    cout << "Ingresa el numero de nodos: ";
    cin >> n;

    cout << "Ingresa la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grafo[i][j];
}

// ===============================
// Funcion: dfs1 (primer pasada)
// ===============================
void dfs1(int u) {
    visitado[u] = true;

    for (int v = 0; v < n; v++)
        if (grafo[u][v] == 1 && !visitado[v])
            dfs1(v);

    pila.push(u);
}

// ===============================
// Funcion: transponerGrafo
// ===============================
void transponerGrafo() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            transpuesto[i][j] = grafo[j][i];
}

// ===============================
// Funcion: dfs2 (segunda pasada)
// ===============================
void dfs2(int u) {
    cout << u << " ";
    visitado[u] = true;

    for (int v = 0; v < n; v++)
        if (transpuesto[u][v] == 1 && !visitado[v])
            dfs2(v);
}

// ===============================
// Funcion: ejecutarKosaraju
// ===============================
void ejecutarKosaraju() {
    limpiarVisitados();

    for (int i = 0; i < n; i++)
        if (!visitado[i])
            dfs1(i);

    transponerGrafo();
    limpiarVisitados();

    cout << "\nComponentes fuertemente conexas:\n";

    while (!pila.empty()) {
        int u = pila.top();
        pila.pop();

        if (!visitado[u]) {
            cout << "SCC: ";
            dfs2(u);
            cout << "\n";
        }
    }
}

// ===============================
// MAIN
// ===============================
int main() {
    leerGrafo();
    ejecutarKosaraju();
    return 0;
}
