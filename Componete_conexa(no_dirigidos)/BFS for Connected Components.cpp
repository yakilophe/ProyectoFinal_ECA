#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 100;
int n;
int grafo[MAXN][MAXN];
bool visitado[MAXN];

void bfs(int inicio) {
    queue<int> q;
    q.push(inicio);
    visitado[inicio] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";

        for (int v = 0; v < n; v++) {
            if (grafo[u][v] == 1 && !visitado[v]) {
                visitado[v] = true;
                q.push(v);
            }
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
            bfs(i);
            cout << "\n";
        }
    }

    return 0;
}

