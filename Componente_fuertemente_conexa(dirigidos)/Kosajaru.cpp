#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 100;
int n;
int grafo[MAXN][MAXN];          // Matriz original
int transpuesto[MAXN][MAXN];    // Matriz transpuesta
bool visitado[MAXN];
stack<int> pila;

// ---------------- DFS normal ----------------
void dfs1(int u) {
    visitado[u] = true;

    for (int v = 0; v < n; v++) {
        if (grafo[u][v] == 1 && !visitado[v]) {
            dfs1(v);
        }
    }

    pila.push(u);   // Guardar en orden de finalización
}

// ---------------- DFS en grafo transpuesto ----------------
void dfs2(int u) {
    cout << u << " ";
    visitado[u] = true;

    for (int v = 0; v < n; v++) {
        if (transpuesto[u][v] == 1 && !visitado[v]) {
            dfs2(v);
        }
    }
}

// -----------------------------------------------------------

int main() {
    cout << "Ingresa el numero de nodos: ";
    cin >> n;

    cout << "Ingresa la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grafo[i][j];
        }
    }

    // ----- PASO 1: DFS para llenar la pila -----
    for (int i = 0; i < n; i++) visitado[i] = false;

    for (int i = 0; i < n; i++) {
        if (!visitado[i])
            dfs1(i);
    }

    // ----- PASO 2: Transponer la matriz -----
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transpuesto[i][j] = grafo[j][i];
        }
    }

    // ----- PASO 3: DFS en la transpuesta -----
    for (int i = 0; i < n; i++) visitado[i] = false;

    cout << "\nComponentes Fuertemente Conexas:\n";

    while (!pila.empty()) {
        int u = pila.top();
        pila.pop();

        if (!visitado[u]) {
            cout << "SCC: ";
            dfs2(u);
            cout << endl;
        }
    }

    return 0;
}

