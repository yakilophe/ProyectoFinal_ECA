#include <iostream>   // Libreria para entrada y salida (cin, cout)
#include <vector>     // Para usar vectores dinámicos (std::vector)
#include <limits>     // Para constantes de limites numericos
using namespace std;  // Para no escribir std:: cada vez

const int MAXN = 50;          // Maximo numero de nodos
const int NO_EDGE = 0;        // Valor que representa "no hay arista"
const int INF = 1000000000;   // Valor infinito usado para inicializar el mejor costo

int n;                        // Numero de nodos
bool directed;                 // Indica si el grafo es dirigido
bool weighted;                 // Indica si el grafo es ponderado
int mat[MAXN][MAXN];           // Matriz de adyacencia
char elementos[] = {            // Etiquetas de los nodos (A, B, C,...)
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// ======================= Limpiar matriz =======================
void limpiarMatriz() {
    // Inicializa todas las posiciones de la matriz a NO_EDGE
    for(int i=0;i<MAXN;i++)
        for(int j=0;j<MAXN;j++)
            mat[i][j] = NO_EDGE;
}

// ======================= Grafos predefinidos =======================

// Grafo no dirigido y no ponderado
void grafoNoDirNoPond() {
    n = 5;
    directed = false;
    weighted = false;
    limpiarMatriz();
    int aristas[][2] = {
        {0,1},{0,4},{0,3},
        {1,0},{1,3},{1,2},
        {2,1},{2,3},
        {3,2},{3,1},{3,0},
        {4,0}
    };
    int total = 12;
    for(int i=0;i<total;i++) {
        mat[aristas[i][0]][aristas[i][1]] = 1; // Marcamos arista en la matriz
    }
}

// Grafo dirigido y no ponderado
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
        mat[aristas[i][0]][aristas[i][1]] = 1;
}

// Grafo no dirigido y ponderado
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
        int u=aristas[i][0],v=aristas[i][1],w=aristas[i][2];
        mat[u][v]=w;
        mat[v][u]=w; // porque es no dirigido
    }
}

// Grafo dirigido y ponderado
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
        int u=aristas[i][0],v=aristas[i][1],w=aristas[i][2];
        mat[u][v]=w;
    }
}

// ======================= Mostrar matriz =======================
void mostrarMatriz() {
    cout << "\n=== Matriz de adyacencia ===\n   ";
    for(int j=0;j<n;j++) cout << " " << elementos[j];
    cout << "\n";
    for(int i=0;i<n;i++){
        cout << " " << elementos[i] << " ";
        for(int j=0;j<n;j++){
            cout << " " << mat[i][j];
        }
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

        if(!directed){ // si no es dirigido, copiamos la mitad superior a la inferior
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++)
                    mat[j][i]=mat[i][j];
        }
    } else { // grafo ponderado
        cout << "Ingrese la matriz de pesos (0=no arista):\n";
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> mat[i][j];

        if(!directed){ // si no es dirigido, aseguramos simetria
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++){
                    if(mat[i][j]!=NO_EDGE && mat[j][i]==NO_EDGE) mat[j][i]=mat[i][j];
                    else if(mat[j][i]!=NO_EDGE && mat[i][j]==NO_EDGE) mat[i][j]=mat[j][i];
                }
        }
    }
}

// ======================= Backtracking con poda =======================
int bestCost;            // Mejor costo encontrado
vector<int> bestPath;    // Mejor camino encontrado

// Funcion para obtener el indice del nodo a partir de su letra
int indiceNodo(char c){
    for(int i=0;i<n;i++) if(elementos[i]==c) return i;
    return -1; // si no existe
}

// Funcion recursiva de backtracking con poda
void backtrack(int u, int dest, int currCost, vector<int> &path, vector<bool> &visited){
    if(currCost>=bestCost) return; // poda: no explorar caminos mas caros
    if(u==dest){ // llegamos al destino
        bestCost=currCost;
        bestPath=path;
        return;
    }
    for(int v=0;v<n;v++){
        if(mat[u][v]!=NO_EDGE && !visited[v]){ // si hay arista y no visitado
            int w=weighted? mat[u][v]:1;       // costo de la arista
            visited[v]=true;                   // marcamos como visitado
            path.push_back(v);                 // agregamos al camino
            backtrack(v,dest,currCost+w,path,visited); // llamada recursiva
            path.pop_back();                   // desmarcamos el nodo
            visited[v]=false;
        }
    }
}

// Funcion para ejecutar el backtracking desde entrada del usuario
void ejecutarBacktracking(){
    char ca,cb;
    cout << "\nIngrese nodo origen (letra A..): ";
    cin >> ca;
    cout << "Ingrese nodo destino (letra A..): ";
    cin >> cb;
    int src=indiceNodo(ca);
    int dest=indiceNodo(cb);
    if(src==-1 || dest==-1){
        cout << "Nodo invalido.\n";
        return;
    }

    bestCost=INF;
    bestPath.clear();
    vector<int> path;
    vector<bool> visited(n,false);
    visited[src]=true;
    path.push_back(src);
    backtrack(src,dest,0,path,visited);

    if(bestCost==INF) cout << "\nNo existe camino entre " << ca << " y " << cb << ".\n";
    else{
        cout << "\nMejor costo: " << bestCost << "\nCamino: ";
        for(size_t i=0;i<bestPath.size();i++){
            cout << elementos[ bestPath[i] ];
            if(i+1<bestPath.size()) cout << " -> ";
        }
        cout << "\n";
    }
}

// ======================= Main con menu =======================
int main(){
    cout << "===== BACKTRACKING CON PODA - CAMINO MAS CORTO =====\n";
    cout << "1. Grafo No Dirigido y No Ponderado\n";
    cout << "2. Grafo Dirigido y No Ponderado\n";
    cout << "3. Grafo No Dirigido y Ponderado\n";
    cout << "4. Grafo Dirigido y Ponderado\n";
    cout << "5. Ingresar grafo manualmente\n";
    cout << "Seleccione opcion: ";
    int opcion;
    cin >> opcion;

    // Cargamos el grafo segun la opcion
    switch(opcion){
        case 1: grafoNoDirNoPond(); break;
        case 2: grafoDirNoPond(); break;
        case 3: grafoNoDirPond(); break;
        case 4: grafoDirPond(); break;
        case 5: leerGrafoManual(); break;
        default: cout << "Opcion invalida.\n"; return 0;
    }

    mostrarMatriz();       // Mostramos la matriz de adyacencia
    ejecutarBacktracking(); // Ejecutamos el backtracking para camino minimo

    return 0;
}
