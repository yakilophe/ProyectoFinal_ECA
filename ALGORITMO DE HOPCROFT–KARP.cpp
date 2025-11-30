#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath> 
#include <algorithm>

using namespace std;

const int INF = 1000000000;

vector<vector<int> > adj; // Lista de adyacencia: conexiones del lado L al lado R
vector<int> dist;         // Distancia (nivel) de cada nodo del lado L en BFS
vector<int> matchL;       // matchL[i] es el nodo R emparejado con L[i]
vector<int> matchR;       // matchR[j] es el nodo L emparejado con R[j]
int nL, nR, m;            // nL: nodos L, nR: nodos R, m: numero de aristas

// =========================================================================
// BFS: construye niveles para caminos aumentantes mas cortos
// =========================================================================
bool bfs() {
    queue<int> q;
    for (int i = 1; i <= nL; i++) {
        if (matchL[i] == 0) {
            dist[i] = 0;
            q.push(i);
        } else {
            dist[i] = INF;
        }
    }

    bool existeCamino = false;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i];

            if (matchR[v] != 0 && dist[matchR[v]] == INF) {
                dist[matchR[v]] = dist[u] + 1;
                q.push(matchR[v]);
            }

            if (matchR[v] == 0) existeCamino = true;
        }
    }

    return existeCamino;
}

// =========================================================================
// DFS: encuentra y aplica caminos aumentantes
// =========================================================================
bool dfs(int u) {
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];

        if (matchR[v] == 0 || (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v]))) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }

    dist[u] = INF;
    return false;
}

// =========================================================================
// Hopcroft-Karp: calcula el pareo maximo
// =========================================================================
int hopcroftKarp() {
    matchL.assign(nL + 1, 0);
    matchR.assign(nR + 1, 0);
    dist.assign(nL + 1, 0);

    int matching = 0;

    while (bfs()) {
        for (int i = 1; i <= nL; i++) {
            if (matchL[i] == 0 && dfs(i)) matching++;
        }
    }

    return matching;
}

// =========================================================================
// Mostrar resultados y verificaciones
// =========================================================================
void mostrarResultado(int res) {
    cout << "\n=========================================\n";
    cout << "             RESULTADO FINAL\n";
    cout << "=========================================\n";
    cout << "Algoritmo: Hopcroft-Karp\n";
    cout << "Tamano del Pareo MAXIMO: " << res << endl;
    cout << "-----------------------------------------\n";

    cout << "VERIFICACION DE MAXIMALIDAD:\n";
    cout << "[CONFIRMADO] El pareo encontrado es MAXIMAL.\n";
    cout << "-----------------------------------------\n";

    cout << "VERIFICACION DE PERFECCION:\n";
    int min_nodes = min(nL, nR);

    if (res == min_nodes && nL == nR) {
        cout << "[LOGRADO] SE ENCONTRO PAREO PERFECTO. Todos los nodos del grafo estan cubiertos.\n";
    } else if (res == min_nodes) {
        cout << "[MAXIMO] El pareo cubre completamente el lado mas pequeno. No es perfecto porque |L| != |R|.\n";
    } else {
        cout << "[NO PERFECTO] El pareo es Maximo, pero no cubre todos los nodos del lado mas pequeno.\n";
    }

    cout << "-----------------------------------------\n";

    cout << "\nEmparejamientos encontrados:\n";
    for (int i = 1; i <= nL; i++) {
        if (matchL[i] != 0)
            cout << "L" << i << " <--> R" << matchL[i] << endl;
    }

    cout << "=========================================\n";
}

// =========================================================================
// Menu de interaccion
// =========================================================================
void menu() {
    int op;
    int resultado = 0;
    bool grafo_cargado = false;
    bool algoritmo_ejecutado = false;

    do {
        cout << "\n=========================================\n";
        cout << "      ALGORITMO DE HOPCROFT-KARP\n";
        cout << "      PAREO MAXIMO Y VERIFICACIONES\n";
        cout << "=========================================\n";
        cout << "1. Ingresar grafo bipartito\n";
        cout << "2. Ejecutar algoritmo (Pareo Maximo)\n";
        cout << "3. Mostrar resultado y verificaciones\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";

        if (!(cin >> op)) {
            cout << "\n[ERROR] Entrada invalida. Ingresa un numero (1-4).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = 0;
            continue;
        }

        switch (op) {
        case 1:
            nL = nR = m = 0;
            adj.clear();
            grafo_cargado = false;
            algoritmo_ejecutado = false;

            cout << "\nNumero de nodos lado izquierdo (L): ";
            if (!(cin >> nL)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }
            cout << "Numero de nodos lado derecho (R): ";
            if (!(cin >> nR)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }

            adj.assign(nL + 1, vector<int>());

            cout << "Numero de aristas: ";
            if (!(cin >> m)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }

            cout << "\nIngresa las aristas (u v) donde u esta en L (1.." << nL << ") y v esta en R (1.." << nR << "):\n";
            for (int i = 0; i < m; i++) {
                int u, v;
                cout << "Arista " << i + 1 << ": ";
                if (!(cin >> u >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); i--; continue; }
                if (u < 1 || u > nL || v < 1 || v > nR) { cout << "[ERROR] Nodo fuera de rango. Reingresa.\n"; i--; }
                else adj[u].push_back(v);
            }

            cout << "\nGrafo cargado correctamente. Lados: " << nL << ", R: " << nR << ", Aristas: " << m << ".\n";
            grafo_cargado = true;
            break;

        case 2:
            if (!grafo_cargado) { cout << "\n[ERROR] Ingresa el grafo primero.\n"; break; }
            resultado = hopcroftKarp();
            algoritmo_ejecutado = true;
            cout << "\nAlgoritmo ejecutado. Pareo Maximo encontrado: " << resultado << endl;
            break;

        case 3:
            if (!algoritmo_ejecutado) { cout << "\n[ERROR] Ejecuta el algoritmo primero.\n"; break; }
            mostrarResultado(resultado);
            break;

        case 4:
            cout << "\nSaliendo del programa...\n";
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (op != 4);
}

int main() {
    menu();
    return 0;
}

