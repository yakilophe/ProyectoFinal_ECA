#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 100;

// --------------------------------------------------------------
// Variables globales
// --------------------------------------------------------------
int n;
int grafo[MAXN][MAXN];
bool visitado[MAXN];

// --------------------------------------------------------------
// BFS desde un nodo inicial
// --------------------------------------------------------------
void bfs(int inicio) {
    queue<int> q;
    q.push(inicio);
    visitado[inicio] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << u << " ";

        for (int v = 0; v < n; v++) {
            if (grafo[u][v] == 1 && !visitado[v]) {
                visitado[v] = true;
                q.push(v);
            }
        }
    }
}

// --------------------------------------------------------------
// Main
// --------------------------------------------------------------
int main() {
    cout << "Numero de nodos: ";
    cin >> n;

    cout << "Ingresa la matriz de adyacencia:" << endl;
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
            bfs(i);
            cout << endl;
        }
    }

    return 0;
}
