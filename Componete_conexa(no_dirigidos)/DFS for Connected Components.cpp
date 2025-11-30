#include <iostream>
using namespace std;

const int MAXN = 100;
int n;
int grafo[MAXN][MAXN];
bool visitado[MAXN];

void dfs(int u) {
    visitado[u] = true;
    cout << u << " ";

    for (int v = 0; v < n; v++) {
        if (grafo[u][v] == 1 && !visitado[v]) {
            dfs(v);
        }
    }
}

int main() {
    cout << "Número de nodos: ";
    cin >> n;

    cout << "Ingresa la Matriz de adyacencia:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grafo[i][j];

    for (int i = 0; i < n; i++) visitado[i] = false;

    cout << "\nComponentes Conexas:\n";
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            cout << "CC: ";
            dfs(i);
            cout << "\n";
        }
    }

    return 0;
}

