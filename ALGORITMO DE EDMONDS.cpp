#include <iostream> 
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Constantes y variables globales (que se usan en todo el programa)
const int MAXN = 100; // Define el numero maximo de nodos que el grafo puede tener.
vector<int> adj[MAXN]; // Lista de Adyacencia: Es la forma en que se guarda el grafo. adj[i] es una lista de todos los nodos conectados a 'i'.
int matchNode[MAXN], parentNode[MAXN], baseNode[MAXN]; // Listas clave para el algoritmo:
// matchNode: Guarda la pareja de cada nodo (si matchNode[i] = j, entonces 'i' y 'j' estan emparejados).
// parentNode: Guarda el "padre" o nodo anterior en el camino que se esta explorando (similar a una ruta).
// baseNode: Guarda el nodo "base" o la raiz de un 'Blossom' (el ciclo impar).
bool used[MAXN], blossom[MAXN]; // Variables booleanas (verdadero/falso):
// used: Marca si un nodo ya fue visitado en la busqueda de camino.
// blossom: Marca si un nodo es parte de un 'Blossom' (ciclo impar).
queue<int> q; // La cola para la busqueda en amplitud (BFS).
int n, m; // n: numero de nodos, m: numero de aristas.

// =========================================================================
// BUSCAR ANCESTRO COMUN (LCA - Lowest Common Ancestor)
// =========================================================================
int lca(int a, int b) {
    vector<bool> visited(n, false);

    while (true) {
        a = baseNode[a];
        visited[a] = true;
        if (matchNode[a] == -1) break;
        a = parentNode[matchNode[a]];
    }

    while (true) {
        b = baseNode[b];
        if (visited[b]) return b;
        if (matchNode[b] == -1) break;
        b = parentNode[matchNode[b]];
    }

    return -1;
}

// =========================================================================
// MARCAR CICLO IMPAR (BLOSSOM)
// =========================================================================
void markPath(int v, int b, int x) {
    while (baseNode[v] != b) {
        blossom[baseNode[v]] = blossom[baseNode[matchNode[v]]] = true;
        parentNode[v] = x;
        x = matchNode[v];
        v = parentNode[matchNode[v]];
    }
}

// =========================================================================
// BUSCAR CAMINO AUMENTANTE (BFS modificado)
// =========================================================================
int findPath(int start) {
    for (int i = 0; i < n; ++i) used[i] = false;
    for (int i = 0; i < n; ++i) parentNode[i] = -1;
    for (int i = 0; i < n; ++i) baseNode[i] = i;

    while (!q.empty()) q.pop();

    q.push(start);
    used[start] = true;

    while (!q.empty()) {
        int v = q.front(); q.pop();

        for (int idx = 0; idx < (int)adj[v].size(); ++idx) {
            int u = adj[v][idx];

            if (baseNode[v] == baseNode[u] || matchNode[v] == u)
                continue;

            if (u == start ||
                (matchNode[u] != -1 && parentNode[matchNode[u]] != -1)) {

                int b = lca(v, u);
                for (int i = 0; i < n; ++i) blossom[i] = false;
                markPath(v, b, u);
                markPath(u, b, v);

                for (int i = 0; i < n; ++i) {
                    if (blossom[baseNode[i]]) {
                        baseNode[i] = b;
                        if (!used[i]) {
                            used[i] = true;
                            q.push(i);
                        }
                    }
                }
            }
            else if (parentNode[u] == -1) {
                parentNode[u] = v;

                if (matchNode[u] == -1)
                    return u;

                int next = matchNode[u];
                used[next] = true;
                q.push(next);
            }
        }
    }

    return -1;
}

// =========================================================================
// ALGORITMO DE EDMONDS (BLOSSOM)
// =========================================================================
int edmonds() {
    for (int i = 0; i < n; ++i) matchNode[i] = -1;
    int matchCount = 0;

    for (int i = 0; i < n; i++) {
        if (matchNode[i] == -1) {
            int v = findPath(i);
            if (v != -1) {
                while (v != -1) {
                    int pv = parentNode[v];
                    int nv = matchNode[pv];
                    matchNode[v] = pv;
                    matchNode[pv] = v;
                    v = nv;
                }
                matchCount++;
            }
        }
    }

    return matchCount;
}

// =========================================================================
// MOSTRAR EMPAREJAMIENTOS
// =========================================================================
void mostrarMatching() {
    cout << "\nEmparejamientos encontrados:\n";
    for (int i = 0; i < n; i++) {
        if (matchNode[i] != -1 && i < matchNode[i]) {
            cout << "Nodo " << i << " -- Nodo " << matchNode[i] << endl;
        }
    }
}

// =========================================================================
// IMPRIMIR MATRIZ DE ADYACENCIA
// =========================================================================
void imprimirMatriz() {
    int matriz[MAXN][MAXN] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            int v = adj[i][j];
            matriz[i][v] = 1;
        }
    }

    cout << "\nMatriz de Adyacencia:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

// =========================================================================
// CARGAR GRAFO PREESTABLECIDO (NO DIRIGIDO Y NO PONDERADO)
// =========================================================================
void cargarGrafoPredefinido() {
    for (int i = 0; i < MAXN; i++)
        adj[i].clear();

    n = 5;

    adj[0].push_back(1);
    adj[0].push_back(4);
    adj[0].push_back(3);
    adj[1].push_back(0);
    adj[1].push_back(3);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(1);
    adj[3].push_back(0);
    adj[4].push_back(0);

    cout << "\nGrafo preestablecido cargado correctamente.\n";
    imprimirMatriz();
}

// =========================================================================
// MENU PRINCIPAL
// =========================================================================
void menu() {
    int op;

    do {
        cout << "\n==============================\n";
        cout << "    ALGORITMO DE EDMONDS\n";
        cout << "    MATCHING MAXIMO GENERAL\n";
        cout << "==============================\n";
        cout << "1. Cargar grafo predefinido\n";
        cout << "2. Ingresar grafo manual\n";
        cout << "3. Ejecutar algoritmo\n";
        cout << "4. Mostrar emparejamientos\n";
        cout << "5. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            cargarGrafoPredefinido();
            break;

        case 2:
            for (int i = 0; i < MAXN; i++)
                adj[i].clear();

            cout << "\nNumero de nodos: ";
            cin >> n;
            cout << "Numero de aristas: ";
            cin >> m;

            cout << "Ingresa las aristas (u v):\n";
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;

                if (u < 0 || u >= n || v < 0 || v >= n) {
                    cout << "[ERROR]: Vertices fuera de rango.\n";
                    i--;
                    continue;
                }

                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            imprimirMatriz();
            break;

        case 3: {
            int resultado = edmonds();
            cout << "\nMatching maximo encontrado: " << resultado << endl;
            break;
        }

        case 4:
            mostrarMatching();
            break;

        case 5:
            cout << "\nSaliendo del programa...\n";
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (op != 5);
}

// El programa inicia llamando al menu principal.
int main() {
    menu();
    return 0;
}
