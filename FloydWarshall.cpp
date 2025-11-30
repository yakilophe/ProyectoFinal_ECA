#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAXN = 50;
const int INF = 1000000000;
const int NO_EDGE = 0;

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
    cout << "===== FLOYD-WARSHALL - CAMINOS MINIMOS =====\n";
    cout << "Seleccione el tipo de grafo:\n";
    cout << "1. No ponderado (matriz 0/1)\n";
    cout << "2. Ponderado (matriz de pesos, 0 = no arista)\n";
    cout << "Opcion (1 o 2): ";
    cin >> choice;
    weighted = (choice == 2);

    cout << "El grafo es dirigido? (0=No, 1=Si): ";
    cin >> directed;

    cout << "Ingrese el numero de nodos (max " << MAXN << "): ";
    cin >> n;
    if(n <= 0 || n > MAXN) {
        cout << "Numero de nodos invalido. Saliendo.\n";
        exit(1);
    }
}

// ---------------- Leer matriz ----------------
void leerMatriz() {
    cout << "\nIngrese la matriz fila por fila:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> mat[i][j];

    if(!directed) {
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++) {
                if(mat[i][j] != NO_EDGE && mat[j][i] == NO_EDGE) mat[j][i] = mat[i][j];
                else if(mat[j][i] != NO_EDGE && mat[i][j] == NO_EDGE) mat[i][j] = mat[j][i];
            }
    }
}

// ---------------- Mostrar matriz ----------------
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

// ---------------- Floyd-Warshall ----------------
void floydWarshall() {
    int dist[MAXN][MAXN];

    // Inicializar distancias
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            if(i==j) dist[i][j] = 0;
            else if(mat[i][j] != NO_EDGE) dist[i][j] = weighted ? mat[i][j] : 1;
            else dist[i][j] = INF;
        }

    // Algoritmo principal
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dist[i][k]!=INF && dist[k][j]!=INF && dist[i][k]+dist[k][j]<dist[i][j])
                    dist[i][j] = dist[i][k]+dist[k][j];

    // Mostrar resultados
    cout << "\n=== Matriz de distancias minimas ===\n   ";
    for(int j=0;j<n;j++) cout << " " << elementos[j];
    cout << "\n";
    for(int i=0;i<n;i++){
        cout << " " << elementos[i] << " ";
        for(int j=0;j<n;j++){
            if(dist[i][j] == INF) cout << " INF";
            else cout << setw(4) << dist[i][j];
        }
        cout << "\n";
    }
}

// ---------------- MAIN ----------------
int main() {
    leerParametros();
    leerMatriz();
    mostrarMatriz();
    floydWarshall();
    return 0;
}
