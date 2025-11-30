#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 50;

int n;
int matriz[MAXN][MAXN];
char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// Variables de Tarjan
int ids[MAXN], low[MAXN];
bool enPila[MAXN];
stack<int> pilaTarjan;
int idActual = 0;
int sccCount = 0;

// ============================================
// Funcion: leerGrafo
// ============================================
void leerGrafo() {
    cout << "Ingrese el numero de vertices (max 26): ";
    cin >> n;

    if(n > 26) {
        cout << "Maximo permitido: 26\n";
        exit(0);
    }

    cout << "\nIngrese la matriz de adyacencia\n";

    for(int i = 0; i < n; i++) {
        cout << "Fila del nodo " << elementos[i] << ": ";
        for(int j = 0; j < n; j++)
            cin >> matriz[i][j];
    }
}

// ============================================
// Funcion: inicializarTarjan
// ============================================
void inicializarTarjan() {
    for(int i = 0; i < n; i++) {
        ids[i] = -1;
        low[i] = 0;
        enPila[i] = false;
    }
    idActual = 0;
    sccCount = 0;
}

// ============================================
// Funcion Tarjan (DFS)
// ============================================
void tarjanDFS(int u) {
    ids[u] = low[u] = idActual++;
    pilaTarjan.push(u);
    enPila[u] = true;

    for(int v = 0; v < n; v++) {
        if(matriz[u][v] == 1) { // arista u -> v
            if(ids[v] == -1) {
                tarjanDFS(v);
                low[u] = min(low[u], low[v]);
            }
            else if(enPila[v]) {
                low[u] = min(low[u], ids[v]);
            }
        }
    }

    // Si u es raiz de una SCC
    if(ids[u] == low[u]) {
        cout << "\nComponente #" << ++sccCount << ": ";

        while(true) {
            int v = pilaTarjan.top();
            pilaTarjan.pop();
            enPila[v] = false;

            cout << elementos[v] << " ";
            if(v == u) break;
        }
        cout << "\n";
    }
}

// ============================================
// Funcion: ejecutarTarjan
// ============================================
void ejecutarTarjan() {
    inicializarTarjan();

    for(int i = 0; i < n; i++)
        if(ids[i] == -1)
            tarjanDFS(i);
}

// ============================================
// MAIN
// ============================================
int main() {
    cout << "===== TARJAN - SCC (matriz de adyacencia) =====\n\n";

    leerGrafo();
    ejecutarTarjan();

    return 0;
}
