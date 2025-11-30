#include <iostream>
using namespace std;

const int MAXN = 100;
int n;
int grafo[MAXN][MAXN];
int padre[MAXN];

// ----------- Estructura Union-Find -----------
int find(int u) {
    if (padre[u] == u) return u;
    return padre[u] = find(padre[u]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) padre[b] = a;
}
// ---------------------------------------------

int main() {
    cout << "Número de nodos: ";
    cin >> n;

    cout << "Ingresa la Matriz de adyacencia:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grafo[i][j];

    for (int i = 0; i < n; i++) padre[i] = i;

    // unir todos los que estén conectados
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grafo[i][j] == 1)
                unite(i, j);

    cout << "\nComponentes Conexas:\n";
    bool impreso[MAXN] = {false};

    for (int i = 0; i < n; i++) {
        int raiz = find(i);

        if (!impreso[raiz]) {
            cout << "CC: ";
            for (int j = 0; j < n; j++)
                if (find(j) == raiz)
                    cout << j << " ";
            cout << "\n";
            impreso[raiz] = true;
        }
    }

    return 0;
}

