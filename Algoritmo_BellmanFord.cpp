#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int MAXN = 50;          // Máximo número de nodos que puede tener el grafo
const int NO_EDGE = 0;        // Valor que indica que no existe arista
const int INF = 1000000000;   // Valor "infinito" para inicializar distancias

int n;                        // Número de nodos en el grafo
bool directed;                 // Indica si el grafo es dirigido (true) o no (false)
bool weighted;                 // Indica si el grafo es ponderado (true) o no (false)
int mat[MAXN][MAXN];           // Matriz de adyacencia del grafo
char elementos[] = {           // Etiquetas de los nodos (A, B, C, ...)
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// ======================= Limpiar matriz =======================
void limpiarMatriz() {
    // Se inicializa toda la matriz con NO_EDGE (0), indicando que no hay aristas
    for(int i=0;i<MAXN;i++)
        for(int j=0;j<MAXN;j++)
            mat[i][j] = NO_EDGE;
}

// ======================= Grafos predefinidos =======================

void grafoNoDirNoPond() {
    n = 5;
    directed = false;
    weighted = false;
    limpiarMatriz();
    // Lista de aristas (no ponderadas, no dirigidas)
    int aristas[][2] = {
        {0,1},{0,4},{0,3},
        {1,0},{1,3},{1,2},
        {2,1},{2,3},
        {3,2},{3,1},{3,0},
        {4,0}
    };
    int total = 12;
    for(int i=0;i<total;i++)
        mat[aristas[i][0]][aristas[i][1]] = 1; // marcamos existencia de arista
}

void grafoDirNoPond() {
    n = 5;
    directed = true;
    weighted = false;
    limpiarMatriz();
    int aristas[][2] = {
        {1,0},{0,3},{1,2},{3,2},{3,1},{4,0}
    };
    int total = 6;
    for(int i=0;i<total;i++)
        mat[aristas[i][0]][aristas[i][1]] = 1; // solo direccion u->v
}

void grafoNoDirPond() {
    n = 5;
    directed = false;
    weighted = true;
    limpiarMatriz();
    int aristas[][3] = {
        {0,1,4},{0,4,6},{0,3,9},
        {1,3,8},{1,2,7},
        {2,3,5}
    };
    int total = 6;
    for(int i=0;i<total;i++){
        int u=aristas[i][0], v=aristas[i][1], w=aristas[i][2];
        mat[u][v]=w;
        mat[v][u]=w; // simetría: en grafo no dirigido u<->v
    }
}

void grafoDirPond() {
    n = 5;
    directed = true;
    weighted = true;
    limpiarMatriz();
    int aristas[][3] = {
        {1,0,3},{0,3,12},{1,2,18},{3,2,15},{3,1,9},{4,0,6}
    };
    int total = 6;
    for(int i=0;i<total;i++){
        int u=aristas[i][0], v=aristas[i][1], w=aristas[i][2];
        mat[u][v]=w; // solo dirección u->v
    }
}

// ======================= Mostrar matriz =======================
void mostrarMatriz() {
    cout << "\n=== Matriz de adyacencia ===\n   ";
    for(int j=0;j<n;j++) cout << " " << elementos[j];
    cout << "\n";
    for(int i=0;i<n;i++){
        cout << " " << elementos[i] << " ";
        for(int j=0;j<n;j++) cout << " " << mat[i][j];
        cout << "\n";
    }
}

// ======================= Leer grafo manual =======================
void leerGrafoManual() {
    cout << "Ingrese si el grafo es dirigido (0=No, 1=Si): ";
    cin >> directed;
    cout << "Ingrese si el grafo es ponderado (0=No, 1=Si): ";
    cin >> weighted;
    cout << "Ingrese numero de nodos: ";
    cin >> n;
    limpiarMatriz();

    if(!weighted){ // grafo no ponderado
        cout << "Ingrese la matriz de adyacencia (0/1):\n";
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> mat[i][j];

        if(!directed){
            // -----------------------------
            // SIMETRÍA: Si el grafo no es dirigido, 
            // copiamos la mitad superior de la matriz a la inferior
            // para reflejar que A->B es lo mismo que B->A
            // -----------------------------
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++)
                    mat[j][i]=mat[i][j];
        }
    } else { // grafo ponderado
        cout << "Ingrese la matriz de pesos (0 = no arista):\n";
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> mat[i][j];

        if(!directed){
            // -----------------------------
            // SIMETRÍA ponderada: si hay peso en una dirección pero no en la otra,
            // lo copiamos para mantener la simetría en grafo no dirigido
            // -----------------------------
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++){
                    if(mat[i][j]!=NO_EDGE && mat[j][i]==NO_EDGE) mat[j][i]=mat[i][j];
                    else if(mat[j][i]!=NO_EDGE && mat[i][j]==NO_EDGE) mat[i][j]=mat[j][i];
                }
        }
    }
}

// ======================= Indice de nodo =======================
int indiceNodo(char c) {
    for(int i=0;i<n;i++)
        if(elementos[i]==c) return i;
    return -1; // nodo invalido
}

// ======================= Algoritmo Bellman-Ford =======================
void bellmanFord() {
    char ca;
    cout << "\nIngrese nodo origen (letra A..): ";
    cin >> ca;
    int src = indiceNodo(ca);
    if (src == -1) { cout << "Nodo invalido.\n"; return; }

    vector<int> dist(n, INF); // Inicializamos distancias a infinito
    dist[src] = 0;             // Distancia al nodo origen es 0

    // -----------------------------
    // RELAJACIÓN DE ARISTAS
    // Repetimos n-1 veces: propiedad de Bellman-Ford
    // -----------------------------
    for (int k = 0; k < n-1; ++k) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (mat[u][v] != NO_EDGE) {   // si hay arista u->v
                    int w = weighted ? mat[u][v] : 1;
                    if (dist[u] != INF && dist[u] + w < dist[v])
                        dist[v] = dist[u] + w; // relajamos la arista
                }
            }
        }
    }

    // -----------------------------
    // DETECCIÓN DE CICLOS NEGATIVOS
    // Si aún se puede relajar alguna arista, hay ciclo negativo accesible
    // -----------------------------
    bool cicloNegativo = false;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (mat[u][v] != NO_EDGE) {
                int w = weighted ? mat[u][v] : 1;
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    cicloNegativo = true; // ciclo negativo detectado
                    break;
                }
            }
        }
        if (cicloNegativo) break;
    }

    if (cicloNegativo)
        cout << "\nEl grafo tiene ciclo negativo. Bellman-Ford no puede garantizar distancias.\n";
    else {
        cout << "\nDistancias minimas desde " << ca << ":\n";
        for (int i = 0; i < n; ++i) {
            cout << elementos[i] << ": ";
            if (dist[i] == INF) cout << "INF\n"; // nodo inalcanzable
            else cout << dist[i] << "\n";
        }
    }
}

// ======================= Main con menú =======================
int main() {
    cout << "===== BELLMAN-FORD - CAMINOS MINIMOS =====\n";
    cout << "1. Grafo No Dirigido y No Ponderado\n";
    cout << "2. Grafo Dirigido y No Ponderado\n";
    cout << "3. Grafo No Dirigido y Ponderado\n";
    cout << "4. Grafo Dirigido y Ponderado\n";
    cout << "5. Ingresar grafo manualmente\n";
    cout << "Seleccione opcion: ";
    int opcion;
    cin >> opcion;

    // Cargamos el grafo según la opción
    switch(opcion){
        case 1: grafoNoDirNoPond(); break;
        case 2: grafoDirNoPond(); break;
        case 3: grafoNoDirPond(); break;
        case 4: grafoDirPond(); break;
        case 5: leerGrafoManual(); break;
        default: cout << "Opcion invalida.\n"; return 0;
    }

    mostrarMatriz(); // Mostramos matriz
    bellmanFord();   // Ejecutamos Bellman-Ford

    return 0;
}
