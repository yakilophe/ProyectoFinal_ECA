#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAXN = 50;
const int NO_EDGE = 0;

// -------------------------------------------------------------------
// DFS RECURSIVO
// -------------------------------------------------------------------
void DFS(int u, int n, int mat[MAXN][MAXN], vector<bool> &visitado, char elementos[]) {
    visitado[u] = true;
    cout << elementos[u] << " ";

    for(int v = 0; v < n; v++)
        if(mat[u][v] != NO_EDGE && !visitado[v])
            DFS(v, n, mat, visitado, elementos);
}

// -------------------------------------------------------------------
// LECTURA MATRIZ 0/1 NO PONDERADA
// -------------------------------------------------------------------
void leerMatrizNoPonderada(int n, int mat[MAXN][MAXN], bool directed) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> mat[i][j];

    if(!directed) {
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++)
                mat[j][i] = mat[i][j];
    }
}

// -------------------------------------------------------------------
// LECTURA LISTA DE ADYACENCIA PONDERADA Y CONVERSION A MATRIZ
// -------------------------------------------------------------------
void leerListaPonderada(int n, int mat[MAXN][MAXN], bool directed) {
    vector<pair<int,int>> adj[MAXN];

    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;

        for(int k = 0; k < num; k++) {
            int v, w;
            cin >> v >> w;
            adj[i].push_back({v, w});

            if(!directed)
                adj[v].push_back({i, w});
        }
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = NO_EDGE;

    for(int i = 0; i < n; i++)
        for(auto &p : adj[i])
            mat[i][p.first] = p.second;
}

// -------------------------------------------------------------------
// IMPRIMIR MATRIZ
// -------------------------------------------------------------------
void imprimirMatriz(int n, int mat[MAXN][MAXN], char elementos[]) {
    cout << "\n=== Matriz de adyacencia ===\n";

    cout << setw(6) << " ";
    for(int j = 0; j < n; j++)
        cout << setw(6) << elementos[j];
    cout << "\n";

    for(int i = 0; i < n; i++) {
        cout << setw(6) << elementos[i];
        for(int j = 0; j < n; j++)
            cout << setw(6) << mat[i][j];
        cout << "\n";
    }
}

// -------------------------------------------------------------------
// BUSCAR NODO POR LETRA
// -------------------------------------------------------------------
int buscarNodo(char origen, int n, char elementos[]) {
    for(int i = 0; i < n; i++)
        if(elementos[i] == origen)
            return i;
    return -1;
}

// -------------------------------------------------------------------
// MAIN
// -------------------------------------------------------------------
int main() {

    int n;
    bool directed, weighted;

    cout << "========================================\n";
    cout << "                 DFS                    \n";
    cout << "========================================\n";

    // Tipo de grafo
    int choice;
    cout << "Seleccione el tipo de grafo:\n";
    cout << "1. No ponderado (matriz 0/1)\n";
    cout << "2. Ponderado (lista con pesos)\n";
    cout << "Opcion: ";
    cin >> choice;

    if(choice == 1) weighted = false;
    else if(choice == 2) weighted = true;
    else {
        cout << "Opcion invalida.\n";
        return 1;
    }

    cout << "El grafo es dirigido (0=No, 1=Si): ";
    cin >> directed;

    cout << "Numero de nodos (max 50): ";
    cin >> n;

    if(n <= 0 || n > MAXN) {
        cout << "Numero invalido.\n";
        return 1;
    }

    char elementos[] = {
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    int mat[MAXN][MAXN];

    // ----------------------------------------------------------
    // LECTURA DEL GRAFO
    // ----------------------------------------------------------
    if(!weighted)
        leerMatrizNoPonderada(n, mat, directed);
    else
        leerListaPonderada(n, mat, directed);

    // Mostrar matriz final
    imprimirMatriz(n, mat, elementos);

    // ----------------------------------------------------------
    // ORIGEN DFS
    // ----------------------------------------------------------
    char origen;
    cout << "\nNodo de inicio DFS: ";
    cin >> origen;

    int src = buscarNodo(origen, n, elementos);
    if(src == -1) {
        cout << "Nodo invalido\n";
        return 1;
    }

    // ----------------------------------------------------------
    // EJECUTAR DFS
    // ----------------------------------------------------------
    vector<bool> visitado(n, false);

    cout << "\n=== Recorrido DFS ===\n";
    DFS(src, n, mat, visitado, elementos);

    cout << "\n========================================\n";
    return 0;
}
