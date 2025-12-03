#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAXN = 50;
const int INF = 1000000000;
const int NO_EDGE = 0;

int n;              // numero de nodos
bool directed;      // true = grafo dirigido, false = no dirigido
bool weighted;      // true = grafo ponderado, false = no ponderado
int mat[MAXN][MAXN]; 
char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// ======================= Limpiar matriz =======================
void limpiarMatriz() {
    for(int i=0;i<MAXN;i++)
        for(int j=0;j<MAXN;j++)
            mat[i][j] = NO_EDGE;  // Inicializa todas las conexiones a "no hay arista"
}

// ======================= Grafos predefinidos =======================

// 1. Grafo No Dirigido y No Ponderado
void grafoNoDirNoPond() {
    n = 5; directed=false; weighted=false; limpiarMatriz();
    // Lista de aristas (bidireccionales, por eso aparece cada conexión dos veces)
    int aristas[][2] = {
        {0,1},{0,4},{0,3},{1,0},{1,3},{1,2},
        {2,1},{2,3},{3,2},{3,1},{3,0},{4,0}
    };
    int total = 12;
    for(int i=0;i<total;i++) mat[aristas[i][0]][aristas[i][1]] = 1;
    // Comentario: La matriz es SIMETRICA porque es no dirigida. 
    // Todos los nodos conectados pueden ir y venir libremente.
}

// 2. Grafo Dirigido y No Ponderado
void grafoDirNoPond() {
    n = 5; directed=true; weighted=false; limpiarMatriz();
    int aristas[][2] = { {1,0},{0,3},{1,2},{3,2},{3,1},{4,0} };
    int total = 6;
    for(int i=0;i<total;i++) mat[aristas[i][0]][aristas[i][1]] = 1;
    // Comentario: La matriz NO es simétrica porque las aristas tienen direccion
    // Ejemplo: existe 1->0 pero no necesariamente 0->1
}

// 3. Grafo No Dirigido y Ponderado
void grafoNoDirPond() {
    n = 5; directed=false; weighted=true; limpiarMatriz();
    int aristas[][3] = { {0,1,4},{0,4,6},{0,3,9},{1,3,8},{1,2,7},{2,3,5} };
    int total = 6;
    for(int i=0;i<total;i++){
        int u=aristas[i][0],v=aristas[i][1],w=aristas[i][2];
        mat[u][v]=w; mat[v][u]=w; // simetría: el peso es igual en ambos sentidos
        // Comentario: No dirigido + ponderado -> puedes calcular distancias mínimas usando pesos
    }
}

// 4. Grafo Dirigido y Ponderado
void grafoDirPond() {
    n = 5; directed=true; weighted=true; limpiarMatriz();
    int aristas[][3] = { {1,0,3},{0,3,12},{1,2,18},{3,2,15},{3,1,9},{4,0,6} };
    int total = 6;
    for(int i=0;i<total;i++){
        int u=aristas[i][0],v=aristas[i][1],w=aristas[i][2];
        mat[u][v]=w; // solo una direccion, por eso NO se copia al inverso
        // Comentario: Dirigido + ponderado -> dirección y peso importan para caminos mínimos
    }
}

// ======================= Leer grafo manual =======================
void leerGrafoManual() {
    cout << "Ingrese si el grafo es dirigido (0=No, 1=Si): "; cin >> directed;
    cout << "Ingrese si el grafo es ponderado (0=No, 1=Si): "; cin >> weighted;
    cout << "Ingrese numero de nodos: "; cin >> n;
    limpiarMatriz();

    if(!weighted){
        cout << "Ingrese la matriz de adyacencia (0/1):\n";
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> mat[i][j];

        if(!directed)  // simetría: reflejar conexiones en la matriz
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++)
                    mat[j][i]=mat[i][j];
    } else {
        cout << "Ingrese la matriz de pesos (0 = no arista):\n";
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> mat[i][j];

        if(!directed) // simetría: reflejar pesos en ambos sentidos
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++){
                    if(mat[i][j]!=NO_EDGE && mat[j][i]==NO_EDGE) mat[j][i]=mat[i][j];
                    else if(mat[j][i]!=NO_EDGE && mat[i][j]==NO_EDGE) mat[i][j]=mat[j][i];
                }
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

// ======================= Floyd-Warshall =======================
void floydWarshall() {
    int dist[MAXN][MAXN];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(i==j) dist[i][j]=0; // distancia a si mismo = 0
            else if(mat[i][j]!=NO_EDGE) dist[i][j]=weighted?mat[i][j]:1;
            else dist[i][j]=INF; // no hay arista directa
        }

    // algoritmo Floyd-Warshall: actualizar distancias mínimas
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dist[i][k]!=INF && dist[k][j]!=INF && dist[i][k]+dist[k][j]<dist[i][j])
                    dist[i][j]=dist[i][k]+dist[k][j];

    // mostrar matriz de distancias mínimas
    cout << "\n=== Matriz de distancias minimas ===\n   ";
    for(int j=0;j<n;j++) cout << " " << elementos[j];
    cout << "\n";
    for(int i=0;i<n;i++){
        cout << " " << elementos[i] << " ";
        for(int j=0;j<n;j++){
            if(dist[i][j]==INF) cout << " INF";
            else cout << setw(4) << dist[i][j];
        }
        cout << "\n";
    }
}

// ======================= MAIN =======================
int main(){
    cout << "===== FLOYD-WARSHALL - CAMINOS MINIMOS =====\n";
    cout << "1. Grafo No Dirigido y No Ponderado\n";
    cout << "2. Grafo Dirigido y No Ponderado\n";
    cout << "3. Grafo No Dirigido y Ponderado\n";
    cout << "4. Grafo Dirigido y Ponderado\n";
    cout << "5. Ingresar grafo manualmente\n";
    cout << "Seleccione opcion: ";
    int opcion; cin >> opcion;

    switch(opcion){
        case 1: grafoNoDirNoPond(); break;
        case 2: grafoDirNoPond(); break;
        case 3: grafoNoDirPond(); break;
        case 4: grafoDirPond(); break;
        case 5: leerGrafoManual(); break;
        default: cout << "Opcion invalida.\n"; return 0;
    }

    mostrarMatriz();   // mostrar matriz de adyacencia
    floydWarshall();   // calcular distancias mínimas con Floyd-Warshall
    return 0;
}
