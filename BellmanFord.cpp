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

// ---------------- Leer parametros ----------------
void leerParametros() {
    int choice;
    cout << "===== BELLMAN-FORD - CAMINOS MINIMOS =====\n";
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

// ---------------- Leer matriz no ponderada ----------------
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

// ---------------- Leer matriz ponderada ----------------
void leerMatrizPonderada() {
    cout << "\nIngrese la matriz de pesos (0 = no arista), fila por fila:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    if (!directed) {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                if (mat[i][j] != NO_EDGE && mat[j][i] == NO_EDGE) mat[j][i] = mat[i][j];
                else if (mat[j][i] != NO_EDGE && mat[i][j] == NO_EDGE) mat[i][j] = mat[j][i];
            }
    }
}

// ---------------- Mostrar matriz ----------------
void mostrarMatriz() {
    cout << "\n=== Matriz de adyacencia ===\n";
    cout << "   ";
    for (int j = 0; j < n; ++j) cout << " " << elementos[j];
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << " " << elementos[i] << " ";
        for (int j = 0; j < n; ++j) cout << " " << mat[i][j];
        cout << "\n";
    }
}

// ---------------- Indice de nodo ----------------
int indiceNodo(char c) {
    for (int i = 0; i < n; ++i)
        if (elementos[i] == c) return i;
    return -1;
}

// ---------------- Algoritmo Bellman-Ford ----------------
void bellmanFord() {
    char ca;
    cout << "\nIngrese nodo origen (letra A..): ";
    cin >> ca;
    int src = indiceNodo(ca);
    if (src == -1) { cout << "Nodo invalido.\n"; return; }

    vector<int> dist(n, INF);
    dist[src] = 0;

    // ---------------- Repetir n-1 veces ----------------
    for (int k = 0; k < n-1; ++k) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (mat[u][v] != NO_EDGE) {
                    int w = weighted ? mat[u][v] : 1;
                    if (dist[u] != INF && dist[u] + w < dist[v])
                        dist[v] = dist[u] + w;
                }
            }
        }
    }

    // ---------------- Detectar ciclos negativos ----------------
    bool cicloNegativo = false;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (mat[u][v] != NO_EDGE) {
                int w = weighted ? mat[u][v] : 1;
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    cicloNegativo = true;
                    break;
                }
            }
        }
        if (cicloNegativo) break;
    }

    // ---------------- Mostrar resultados ----------------
    if (cicloNegativo) cout << "\nEl grafo tiene ciclo negativo. Bellman-Ford no puede garantizar distancias.\n";
    else {
        cout << "\nDistancias minimas desde " << ca << ":\n";
        for (int i = 0; i < n; ++i) {
            cout << elementos[i] << ": ";
            if (dist[i] == INF) cout << "INF\n";
            else cout << dist[i] << "\n";
        }
    }
}

// ---------------- MAIN ----------------
int main() {
    leerParametros();
    if (!weighted) leerMatrizNoPonderada();
    else leerMatrizPonderada();

    mostrarMatriz();
    bellmanFord();

    return 0;
}
