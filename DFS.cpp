#include <iostream>   // Para cin, cout
#include <vector>     // Para usar vector<bool>
#include <iomanip>    // Para setw (alinear columnas)
using namespace std;

// Maximo numero de nodos que puede tener el grafo
const int MAXN = 50;

// Valor que representa "no hay arista" dentro de la matriz
const int NO_EDGE = 0;

// ===================================================================
// FUNCION DFS (recursiva)
// u = nodo actual
// n = numero total de nodos
// mat = matriz de adyacencia
// visitado = vector que indica si un nodo ya fue visitado
// elementos = arreglo con las letras A, B, C...
// ===================================================================
void DFS(int u, int n, int mat[MAXN][MAXN], vector<bool> &visitado, char elementos[]) {

    visitado[u] = true;      // Marco este nodo como visitado para no repetirlo

    cout << elementos[u] << " ";  // Imprimo la letra del nodo que estoy visitando

    // Recorro todos los posibles vecinos del nodo u
    for(int v = 0; v < n; v++) {

        // Si hay arista y todavia no visitamos ese nodo
        if(mat[u][v] != NO_EDGE && !visitado[v]) {

            // Llamamos a DFS recursivamente sobre ese nodo vecino
            DFS(v, n, mat, visitado, elementos);
        }
    }
}

int main() {

    int n;              // Numero de nodos
    bool directed;      // El grafo es dirigido
    bool weighted;      // El grafo es ponderado

    // Encabezado bonito
    cout << "========================================\n";
    cout << "                  DFS                   \n";
    cout << "========================================\n";

    // --------------------------------------------------------------
    // SELECCION DEL TIPO DE GRAFO (PONDERADO O NO PONDERADO)
    // --------------------------------------------------------------
    int choice;
    cout << "Seleccione el tipo de grafo:\n";
    cout << "1. No ponderado (matriz de 0/1)\n";
    cout << "2. Ponderado (lista de adyacencia con pesos)\n";
    cout << "Ingrese su opcion (1 o 2): ";
    cin >> choice;

    switch(choice) {
        case 1:
            weighted = false;   // El grafo solo tendra 0/1 → hay arista o no
            break;
        case 2:
            weighted = true;    // El grafo tendra pesos en las aristas
            break;
        default:
            cout << "Opcion invalida.\n";
            return 1;           // Termina el programa por error
    }

    // --------------------------------------------------------------
    // ES DIRIGIDO
    // --------------------------------------------------------------
    cout << "El grafo es dirigido (0=No, 1=Si): ";
    cin >> directed;

    // --------------------------------------------------------------
    // INGRESO DEL NUMERO DE NODOS
    // --------------------------------------------------------------
    cout << "Ingrese el numero de nodos (max " << MAXN << "): ";
    cin >> n;

    // Validacion de rango
    if(n <= 0 || n > MAXN){
        cout << "Numero invalido.\n";
        return 1;
    }

    // Letras para representar cada nodo (A, B, C...)
    char elementos[] = {'A','B','C','D','E','F','G','H','I','J',
                        'K','L','M','N','O','P','Q','R','S','T',
                        'U','V','W','X','Y','Z'};

    int mat[MAXN][MAXN];   // Matriz de adyacencia

    // ===================================================================
    //                 INGRESO DE LA ESTRUCTURA DEL GRAFO
    //     Dependiendo si es ponderado o no, cambia la forma de entrada
    // ===================================================================
    if(!weighted){

        // ------------------------------------------------------------
        // GRAFO NO PONDERADO (solo 0 o 1)
        // ------------------------------------------------------------
        cout << "\n=== Ingrese la matriz de adyacencia 0/1 ===\n";

        // Se ingresa la matriz directamente
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> mat[i][j];

        // Si el grafo NO es dirigido, se copia la simetria
        if(!directed){
            for(int i=0;i<n;i++)
                for(int j=i+1;j<n;j++)
                    mat[j][i] = mat[i][j];
        }

    } else {

        // ------------------------------------------------------------
        // GRAFO PONDERADO (lista de adyacencia con pesos)
        // ------------------------------------------------------------
        cout << "\n=== Ingrese la lista de adyacencia con pesos ===\n";
        cout << "Para cada nodo, ingrese num_vecinos seguido de (vecino peso)\n";

        vector<pair<int,int>> adj[MAXN];   // Lista de adyacencia temporal

        for(int i=0;i<n;i++){
            int num;
            cin >> num;    // Cantidad de vecinos de este nodo

            for(int k=0;k<num;k++){
                int v, w;
                cin >> v >> w;   // vecino y peso
                adj[i].push_back({v, w});  // Agrego la arista a la lista

                // Si no es dirigido, tambien agrego la inversa
                if(!directed)
                    adj[v].push_back({i, w});
            }
        }

        // Inicializo toda la matriz como sin aristas
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                mat[i][j] = NO_EDGE;

        // Paso la lista a matriz
        for(int i=0;i<n;i++)
            for(size_t k=0;k<adj[i].size();k++)
                mat[i][ adj[i][k].first ] = adj[i][k].second;
    }

    // ===================================================================
    //           SECCION 1 — MOSTRAR LA MATRIZ DE ADYACENCIA
    // ===================================================================
    cout << "\n=== Matriz de adyacencia ===\n";

    // Encabezado de columnas (A, B, C...)
    cout << setw(6) << " ";   // Espacio alineado antes del encabezado
    for(int j=0;j<n;j++)
        cout << setw(6) << elementos[j];
    cout << "\n";

    // Imprimir fila por fila
    for(int i=0;i<n;i++){

        cout << setw(6) << elementos[i];   // Etiqueta de la fila

        for(int j=0;j<n;j++)
            cout << setw(6) << mat[i][j]; // Valores de la fila

        cout << "\n";
    }

    // ===================================================================
    //           SECCION 2 — PEDIR EL NODO DE INICIO DEL DFS
    // ===================================================================
    char origen;
    cout << "\nIngrese el nodo de inicio para DFS (letra): ";
    cin >> origen;

    int src = -1;  // Indice del nodo de inicio (A=0, B=1,...)

    // Busco que numero corresponde a la letra ingresada
    for(int i=0;i<n;i++)
        if(elementos[i] == origen)
            src = i;

    // Si la letra no existe dentro de los nodos validos
    if(src == -1){
        cout << "Nodo invalido\n";
        return 1;
    }

    // ===================================================================
    //           SECCION 3 — EJECUTAR EL RECORRIDO DFS
    // ===================================================================
    vector<bool> visitado(n, false);  // Todos los nodos comienzan como no visitados

    cout << "\n=== Recorrido DFS desde nodo " << origen << " ===\n";

    // Llamada a la funcion DFS (procesa el grafo recursivamente)
    DFS(src, n, mat, visitado, elementos);

    cout << "\n========================================\n";

    return 0;  // Fin del programa
}
  