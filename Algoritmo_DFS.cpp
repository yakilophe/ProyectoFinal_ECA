#include <iostream>   // Permite usar cin y cout para leer y mostrar informacion
#include <vector>     // Permite usar el tipo vector, que es como una lista dinamica
#include <iomanip>    // Permite usar setw, que sirve para alinear columnas en pantalla
using namespace std;

// Constante que define el numero maximo de nodos permitidos en el grafo
const int MAXN = 50;

// Valor que representa "no hay arista" en la matriz de adyacencia
const int NO_EDGE = 0;

// -------------------------------------------------------------------
// DFS RECURSIVO
// -------------------------------------------------------------------
void DFS(int u, int n, int mat[MAXN][MAXN], vector<bool> &visitado, char elementos[]) {

    visitado[u] = true;        // Marcamos el nodo actual como visitado

    cout << elementos[u] << " ";   // Mostramos la letra del nodo actual

    // Recorremos todos los posibles nodos v
    for(int v = 0; v < n; v++)
        // Si hay una conexion (mat[u][v] != 0) y aun no visitamos al nodo v
        if(mat[u][v] != NO_EDGE && !visitado[v])
            DFS(v, n, mat, visitado, elementos);   // Llamada recursiva
}

// -------------------------------------------------------------------
// CARGA DE GRAFOS PREDEFINIDOS
// -------------------------------------------------------------------
void cargarNoDirigidoNoPonderado(int mat[MAXN][MAXN], int &n) {

    n = 5;   // Este grafo fijo tiene 5 nodos

    // Matriz temporal con valores fijos
    int temp[5][5] = {
        {0,1,0,1,1},
        {1,0,1,1,0},
        {0,1,0,1,0},
        {1,1,1,0,0},
        {1,0,0,0,0}
    };

    // Copiamos la matriz temporal al arreglo mat
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = temp[i][j];
}

void cargarDirigidoNoPonderado(int mat[MAXN][MAXN], int &n) {

    n = 5;

    int temp[5][5] = {
        {0,0,0,1,0},
        {1,0,1,0,0},
        {0,0,0,0,0},
        {0,1,1,0,0},
        {1,0,0,0,0}
    };

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j] = temp[i][j];
}

void cargarNoDirigidoPonderado(int mat[MAXN][MAXN], int &n) {

    n = 5;

    int temp[5][5] = {
        {0,4,0,9,6},
        {4,0,7,8,0},
        {0,7,0,5,0},
        {9,8,5,0,0},
        {6,0,0,0,0}
    };

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j] = temp[i][j];
}

void cargarDirigidoPonderado(int mat[MAXN][MAXN], int &n) {

    n = 5;

    int temp[5][5] = {
        {0,0,0,12,0},
        {3,0,18,0,0},
        {0,0,0,0,0},
        {0,9,15,0,0},
        {6,0,0,0,0}
    };

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j] = temp[i][j];
}

// -------------------------------------------------------------------
// INGRESAR MATRIZ MANUAL NO PONDERADA
// -------------------------------------------------------------------
void leerMatrizNoPonderada(int n, int mat[MAXN][MAXN], bool directed) {

    // Leemos n*n valores para la matriz
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> mat[i][j];

    // Si no es dirigido, copiamos la parte superior en la inferior
    if(!directed) {
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++)
                mat[j][i] = mat[i][j];   // Se refleja la matriz
    }
}

// -------------------------------------------------------------------
// INGRESAR GRAFO PONDERADO MANUAL
// Usando listas de pares (destino, peso)
// -------------------------------------------------------------------
void leerListaPonderada(int n, int mat[MAXN][MAXN], bool directed) {

    vector< pair<int,int> > adj[MAXN];  // Lista de adyacencia temporal

    // Leemos la lista de adyacencia
    for(int i = 0; i < n; i++) {

        int num;        // Cantidad de nodos hacia donde i tiene aristas
        cin >> num;

        for(int k = 0; k < num; k++) {

            int v;      // Nodo destino
            int w;      // Peso de la arista
            cin >> v >> w;

            adj[i].push_back(make_pair(v, w)); // Guardamos (destino, peso)

            if(!directed)
                adj[v].push_back(make_pair(i, w));
        }
    }

    // Inicializamos la matriz con 0
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = NO_EDGE;

    // Transferimos los datos de la lista a la matriz
    for(int i = 0; i < n; i++)
        for(int k = 0; k < adj[i].size(); k++)
            mat[i][ adj[i][k].first ] = adj[i][k].second;
}

// -------------------------------------------------------------------
// IMPRIMIR MATRIZ
// -------------------------------------------------------------------
void imprimirMatriz(int n, int mat[MAXN][MAXN], char elementos[]) {

    cout << "\n=== Matriz de adyacencia ===\n";

    cout << setw(6) << " ";   // Espacio antes de la fila de letras

    // Imprimimos las letras de los nodos
    for(int j = 0; j < n; j++)
        cout << setw(6) << elementos[j];
    cout << "\n";

    // Imprimimos cada fila
    for(int i = 0; i < n; i++) {

        cout << setw(6) << elementos[i];   // Imprimimos letra de fila

        for(int j = 0; j < n; j++)
            cout << setw(6) << mat[i][j];  // Valores de la matriz

        cout << "\n";
    }
}

// -------------------------------------------------------------------
// BUSCAR INDICE POR LETRA
// -------------------------------------------------------------------
int buscarNodo(char origen, int n, char elementos[]) {

    // Buscamos la letra en el arreglo elementos
    for(int i = 0; i < n; i++)
        if(elementos[i] == origen)
            return i;

    return -1;   // Si no se encontro, regresamos -1
}

// -------------------------------------------------------------------
// MAIN
// -------------------------------------------------------------------
int main() {

    // Encabezado del programa
    cout << "========================================\n";
    cout << "                 DFS                    \n";
    cout << "========================================\n";

    // Arreglo de letras para representar los nodos
    char elementos[] = {
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    int mat[MAXN][MAXN];   // Matriz del grafo
    int n;                 // Cantidad de nodos
    bool directed = false; // Indica si el grafo es dirigido
    bool weighted = false; // Indica si es ponderado

    // --------------------------------------------------------------
    // MENU DE GRAFOS PREDEFINIDOS
    // --------------------------------------------------------------
    cout << "\nSeleccione el grafo a usar:\n";
    cout << "=== Grafos predefinidos ===\n";
    cout << "1. No dirigido y NO ponderado\n";
    cout << "2. Dirigido y NO ponderado\n";
    cout << "3. No dirigido y ponderado\n";
    cout << "4. Dirigido y ponderado\n";
    cout << "5. Ingresar grafo manualmente\n";
    cout << "Opcion: ";

    int op;        // Variable donde se guarda la opcion elegida
    cin >> op;

    // Dependiendo de la opcion, cargamos el grafo correspondiente
    if(op == 1){
        weighted = false;
        directed = false;
        cargarNoDirigidoNoPonderado(mat, n);
    }
    else if(op == 2){
        weighted = false;
        directed = true;
        cargarDirigidoNoPonderado(mat, n);
    }
    else if(op == 3){
        weighted = true;
        directed = false;
        cargarNoDirigidoPonderado(mat, n);
    }
    else if(op == 4){
        weighted = true;
        directed = true;
        cargarDirigidoPonderado(mat, n);
    }
    else if(op == 5){

        cout << "Ingrese numero de nodos: ";
        cin >> n;

        cout << "Es dirigido? (0=No,1=Si): ";
        cin >> directed;

        cout << "Es ponderado? (0=No,1=Si): ";
        cin >> weighted;

        if(!weighted)
            leerMatrizNoPonderada(n, mat, directed);
        else
            leerListaPonderada(n, mat, directed);
    }
    else {
        cout << "Opcion invalida.\n";
        return 0;
    }

    // Imprimimos la matriz cargada
    imprimirMatriz(n, mat, elementos);

    // --------------------------------------------------------------
    // ORIGEN DFS
    // --------------------------------------------------------------
    char origen;      // Letra del nodo desde donde iniciara DFS
    cout << "\nNodo de inicio (A-Z): ";
    cin >> origen;

    int src = buscarNodo(origen, n, elementos);   // Buscamos su indice

    // Validamos si existe
    if(src == -1){
        cout << "Nodo invalido\n";
        return 1;
    }

    vector<bool> visitado(n, false);   // Vector para saber si un nodo ya se visito

    cout << "\n=== Recorrido DFS ===\n";
    DFS(src, n, mat, visitado, elementos);   // Llamamos DFS

    cout << "\n========================================\n";

    return 0;   // Fin del programa
}
