#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int MAXN = 50;
const int NO_EDGE = 0;
const int INF = 1000000000;

int n;
bool directed;
bool weighted;
int mat[MAXN][MAXN];
char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// --------------- Lectura de parametros ---------------
void leerParametros() {
    int choice;
    cout << "===== BACKTRACKING CON PODA - CAMINO MAS CORTO =====\n";
    cout << "Seleccione el tipo de grafo:\n";
    cout << "1. No ponderado (matriz 0/1)\n";
    cout << "2. Ponderado (matriz de pesos, 0 = no arista)\n";
    cout << "Opcion (1 o 2): ";
    cin >> choice;
    if (choice == 1) weighted = false;
    else weighted = true;

    cout << "El grafo es dirigido? (0=No, 1=Si): ";
    cin >> directed;

    cout << "Ingrese el numero de nodos (max " << MAXN << "): ";
    cin >> n;
    if (n <= 0 || n > MAXN) {
        cout << "Numero de nodos invalido. Saliendo.\n";
        exit(1);
    }
}

// --------------- Lectura matriz no ponderada (0/1) ---------------
void leerMatrizNoPonderada() {
    cout << "\nIngrese la matriz de adyacencia (0/1), fila por fila:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    if (!directed) {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                mat[j][i] = mat[i][j];
    }
}

// --------------- Lectura matriz ponderada (pesos) ---------------
void leerMatrizPonderada() {
    cout << "\nIngrese la matriz de pesos (0 = no arista), fila por fila:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    if (!directed) {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                // Si el usuario dio una mitad, hacemos simetrica
                if (mat[i][j] != NO_EDGE && mat[j][i] == NO_EDGE) mat[j][i] = mat[i][j];
                else if (mat[j][i] != NO_EDGE && mat[i][j] == NO_EDGE) mat[i][j] = mat[j][i];
            }
    }
}

// --------------- Mostrar matriz ---------------
void mostrarMatriz() {
    cout << "\n=== Matriz de adyacencia ===\n";
    cout << "   ";
    for (int j = 0; j < n; ++j) cout << " " << elementos[j];
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << " " << elementos[i] << " ";
        for (int j = 0; j < n; ++j) {
            if (weighted) cout << " " << mat[i][j];
            else cout << " " << mat[i][j];
        }
        cout << "\n";
    }
}

// --------------- Buscar indice de letra ---------------
int indiceNodo(char c) {
    for (int i = 0; i < n; ++i)
        if (elementos[i] == c) return i;
    return -1;
}

// --------------- Backtracking con poda ---------------
int bestCost;
vector<int> bestPath;

void backtrack(int u, int dest, int currCost, vector<int> &path, vector<bool> &visited) {
    // poda
    if (currCost >= bestCost) return;

    if (u == dest) {
        // camino completo
        bestCost = currCost;
        bestPath = path;
        return;
    }

    // explorar vecinos
    for (int v = 0; v < n; ++v) {
        if (mat[u][v] != NO_EDGE && !visited[v]) {
            int w = weighted ? mat[u][v] : 1;
            visited[v] = true;
            path.push_back(v);

            backtrack(v, dest, currCost + w, path, visited);

            // deshacer
            path.pop_back();
            visited[v] = false;
        }
    }
}

// --------------- Ejecutar backtracking ---------------
void ejecutarBacktracking() {
    // leer nodos origen y destino
    char ca, cb;
    cout << "\nIngrese nodo origen (letra A..): ";
    cin >> ca;
    cout << "Ingrese nodo destino (letra A..): ";
    cin >> cb;

    int src = indiceNodo(ca);
    int dest = indiceNodo(cb);
    if (src == -1 || dest == -1) {
        cout << "Nodo invalido.\n";
        return;
    }

    // inicializaciones
    bestCost = INF;
    bestPath.clear();
    vector<int> path;
    vector<bool> visited(n, false);

    // inicio
    visited[src] = true;
    path.push_back(src);
    backtrack(src, dest, 0, path, visited);

    if (bestCost == INF) {
        cout << "\nNo existe camino entre " << ca << " y " << cb << ".\n";
    } else {
        cout << "\nMejor costo: " << bestCost << "\n";
        cout << "Camino: ";
        for (size_t i = 0; i < bestPath.size(); ++i) {
            cout << elementos[ bestPath[i] ];
            if (i + 1 < bestPath.size()) cout << " -> ";
        }
        cout << "\n";
    }
}

// --------------- Main limpio con menu ---------------
int main() {
    leerParametros();

    if (!weighted) leerMatrizNoPonderada();
    else leerMatrizPonderada();

    mostrarMatriz();

    ejecutarBacktracking();

    return 0;
}
