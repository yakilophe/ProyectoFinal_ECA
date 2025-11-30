#include <iostream>   // Para entrada y salida (cin, cout)
#include <vector>     // Para manejar listas dinamicas y vectores
#include <iomanip>    // Para setw, que nos ayuda a alinear la matriz
using namespace std;

const int MAXN = 50;   // Maximo numero de nodos permitidos
const int NO_EDGE = 0; // Valor que representa que no hay arista entre dos nodos

// ----------------------
//   FUNCION DFS
// ----------------------
// u: nodo actual
// n: numero total de nodos
// mat: matriz de adyacencia
// visitado: vector para evitar repetir nodos
// elementos: arreglo de letras que representan cada nodo
void DFS(int u, int n, int mat[MAXN][MAXN], vector<bool> &visitado, char elementos[]) {

    visitado[u] = true;           // Marcamos el nodo actual como visitado
    cout << elementos[u] << " ";  // Imprimimos el nodo actual en el recorrido

    // Recorremos todos los nodos posibles para ver si son vecinos
    for(int v = 0; v < n; v++) {
        // Si existe arista y el nodo NO ha sido visitado
        if(mat[u][v] != NO_EDGE && !visitado[v]) {
            // Llamada recursiva para seguir la profundidad desde el vecino
            DFS(v, n, mat, visitado, elementos);
        }
    }
}

int main() {
    int n;
    bool directed, weighted;

    cout << "========================================\n";
    cout << "                  DFS                   \n";
    cout << "========================================\n";

    // Menu para elegir si el grafo es ponderado o no
    int choice;
    cout << "Seleccione el tipo de grafo:\n";
    cout << "1. No ponderado (matriz de 0/1)\n";
    cout << "2. Ponderado (lista de adyacencia con pesos)\n";
    cout << "Ingrese su opcion (1 o 2): ";
    cin >> choice;

    // Segun la opcion, activamos o no el modo ponderado
    switch(choice) {
        case 1: weighted = false; break;
        case 2: weighted = true; break;
        default: cout << "Opcion invalida.\n"; return 1;
    }

    // Preguntamos si el grafo tiene direcciones (aristas un sentido)
    cout << "El grafo es dirigido? (0=No, 1=Si): ";
    cin >> directed;

    // Pedimos el numero de nodos
    cout << "Ingrese el numero de nodos (max " << MAXN << "): ";
    cin >> n;
    if(n <= 0 || n > MAXN){ 
        cout << "Numero invalido.\n"; 
        return 1; 
    }

    // Nombres de los nodos
    char elementos[] = {'A','B','C','D','E','F','G','H','I','J',
                        'K','L','M','N','O','P','Q','R','S','T',
                        'U','V','W','X','Y','Z'};

    int mat[MAXN][MAXN]; // Matriz de adyacencia

    // -------------------------------------
    //           GRAFO NO PONDERADO
    // -------------------------------------
    if(!weighted){
        cout << "\n=== Ingrese la matriz de adyacencia 0/1 ===\n";
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> mat[i][j];

        // Si NO es dirigido, simetrizamos la matriz
        // (lo que hay en [i][j] tambien va en [j][i])
        if(!directed){
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++)
                    mat[j][i] = mat[i][j];
        }

    } else {

        // -------------------------------------
        //           GRAFO PONDERADO
        // -------------------------------------

        cout << "\n=== Ingrese la lista de adyacencia con pesos ===\n";
        cout << "Para cada nodo, ingrese num_vecinos seguido de (vecino peso)\n";

        vector<pair<int,int> > adj[MAXN]; // Lista de pares (nodo vecino, peso)

        // Leemos la lista con pesos
        for(int i=0;i<n;i++){
            int num; cin >> num; // numero de vecinos del nodo i
            for(int k=0;k<num;k++){
                int v,w; cin >> v >> w; // v = vecino, w = peso
                adj[i].push_back(make_pair(v,w));

                // Si no es dirigido, agregamos la arista en ambos sentidos
                if(!directed) adj[v].push_back(make_pair(i,w));
            }
        }

        // Inicializamos la matriz en ceros
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                mat[i][j] = NO_EDGE;

        // Convertimos la lista de adyacencia a matriz
        for(int i=0;i<n;i++)
            for(size_t k=0;k<adj[i].size();k++)
                mat[i][adj[i][k].first] = adj[i][k].second;
    }

    // ---------------------------------------
    //     MOSTRAR MATRIZ DE ADYACENCIA
    // ---------------------------------------
    cout << "\n=== Matriz de adyacencia ===\n";
    cout << setw(6) << " "; // Encabezado vacio
    for(int j=0;j<n;j++) cout << setw(6) << elementos[j];
    cout << "\n";

    for(int i=0;i<n;i++){
        cout << setw(6) << elementos[i]; // Fila con letra del nodo
        for(int j=0;j<n;j++)
            cout << setw(6) << mat[i][j]; // Valor de arista
        cout << "\n";
    }

    // ---------------------------------------
    //             NODO INICIAL
    // ---------------------------------------
    char origen;
    cout << "\nIngrese el nodo de inicio para DFS (letra): ";
    cin >> origen;

    int src=-1;
    for(int i=0;i<n;i++) 
        if(elementos[i]==origen) 
            src=i;

    if(src==-1){ 
        cout << "Nodo invalido\n"; 
        return 1; 
    }

    // ---------------------------------------
    //                  DFS
    // ---------------------------------------
    vector<bool> visitado(n,false); // Para evitar repetir nodos

    cout << "\n=== Recorrido DFS desde nodo " << origen << " ===\n";
    DFS(src, n, mat, visitado, elementos); // Llamamos la funcion DFS
    cout << "\n========================================\n";

    return 0;
}
