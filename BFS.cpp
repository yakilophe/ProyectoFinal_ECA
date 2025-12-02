#include <iostream>   // entrada/salida: cin y cout
#include <queue>      // estructura cola usada por BFS
#include <vector>     // vector dinamico; aqui se usa para visitado y listas
#include <iomanip>    // setw para alinear la salida en columnas
using namespace std;

const int MAXN = 50;   // maximo de nodos que soporta el programa
const int NO_EDGE = 0; // valor que indica "no hay arista" en la matriz

// =====================================================
// Funcion para ingresar un grafo manualmente
// mat    -> matriz de adyacencia que se va a llenar
// n      -> numero de nodos (se retorna por referencia)
// dirigido -> true si las aristas son dirigidas
// ponderado -> true si las aristas tienen peso
// =====================================================
void ingresarGrafoManual(int mat[MAXN][MAXN], int &n, bool &dirigido, bool &ponderado) {

    int aristas;                       // cantidad de aristas que el usuario dira

    cout << "Ingrese numero de nodos (max 50): ";
    cin >> n;                          // leo numero de nodos

    cout << "El grafo es dirigido? (0=No,1=Si): ";
    cin >> dirigido;                   // leo si es dirigido (1) o no (0)

    cout << "El grafo es ponderado? (0=No,1=Si): ";
    cin >> ponderado;                  // leo si tiene pesos en aristas

    cout << "Ingrese numero de aristas: ";
    cin >> aristas;                    // leo cuantas aristas se van a ingresar

    // inicializo toda la matriz en NO_EDGE (sin conexion)
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j] = NO_EDGE;       // poner 0 en cada posicion

    cout << "Ingrese cada arista en el formato:\n";
    cout << "u v peso(si es ponderado)\n";

    // leo una por una las aristas que el usuario ingreso
    for(int i=0;i<aristas;i++){
        int u, v, w = 1;                // u = origen, v = destino, w = peso (por defecto 1)
        cin >> u >> v;                  // leo indices (enteros) de los nodos

        if (ponderado)                  // si el grafo tiene pesos
            cin >> w;                   // entonces leo tambien el peso

        mat[u][v] = w;                  // guardo la arista u->v con peso w

        if (!dirigido)                  // si no es dirigido (es bidireccional)
            mat[v][u] = w;              // copio la arista en sentido inverso
    }
}

// =====================================================
// Funcion para mostrar la matriz de adyacencia
// mat      -> matriz a mostrar
// n        -> cantidad de nodos validos en la matriz
// elementos-> arreglo con letras para mostrar A,B,C...
// =====================================================
void mostrarMatriz(int mat[MAXN][MAXN], int n, char elementos[]) {

    cout << "\n=== Matriz de Adyacencia ===\n";

    cout << setw(4) << " ";            // espacio inicial para alinear encabezado
    for (int j = 0; j < n; j++)
        cout << setw(4) << elementos[j]; // imprimo A,B,C... como header de columnas
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << setw(4) << elementos[i]; // imprimo letra que representa la fila
        for (int j = 0; j < n; j++)
            cout << setw(4) << mat[i][j]; // imprimo valor en la celda i,j
        cout << "\n";
    }
}

// =====================================================
// Funcion para convertir una letra (A,B,C...) a indice
// origen   -> letra ingresada por el usuario
// n        -> cantidad de nodos definidos
// elementos-> arreglo de letras (A=0,B=1,...)
// retorna indice (0..n-1) o -1 si no existe
// =====================================================
int buscarIndiceNodo(char origen, int n, char elementos[]) {

    for (int i = 0; i < n; i++)            // recorro el arreglo de letras
        if (elementos[i] == origen)        // comparo letra por letra
            return i;                      // retorno el indice si coincide

    return -1;                             // si no lo encontro, devuelvo -1
}

// =====================================================
// BFS: Recorrido por niveles (breadth-first search)
// src      -> indice del nodo inicial
// n        -> numero de nodos
// mat      -> matriz de adyacencia
// elementos-> arreglo de letras para imprimir
// =====================================================
void BFS(int src, int n, int mat[MAXN][MAXN], char elementos[]) {

    vector<bool> visitado(n, false); // vector que guarda si ya visite cada nodo
    queue<int> q;                    // cola que maneja el orden de visita

    visitado[src] = true;            // marco el nodo inicial como visitado
    q.push(src);                     // lo añado a la cola para procesarlo

    cout << "\n=== Recorrido BFS ===\n";

    while (!q.empty()) {             // mientras queden nodos en la cola

        int u = q.front();           // tomo el primer nodo en la cola
        q.pop();                     // lo saco de la cola

        cout << elementos[u] << " "; // imprimo la letra correspondiente al nodo

        for (int v = 0; v < n; v++) { // reviso todos los nodos posibles v

            // si existe una arista u->v y v no fue visitado
            if (mat[u][v] != NO_EDGE && !visitado[v]) {
                visitado[v] = true;  // marco v como visitado
                q.push(v);           // encolo v para procesarlo luego
            }
        }
    }

    cout << "\n========================================\n";
}

// =====================================================
// GRAFOS PREDEFINIDOS: funciones que cargan ejemplos
// En cada caso se usa una matriz auxiliar 'aux' y luego se copia a mat
// aux es una forma facil de escribir el grafo directamente en codigo
// =====================================================

// No dirigido y no ponderado (matriz con 0 y 1)
void cargarNoDirNoPond(int mat[MAXN][MAXN], int &n) {
    n = 5;                              // este grafo tiene 5 nodos
    int aux[5][5] = {                   // aux definido para facilitar lectura
        {0,1,0,1,1},
        {1,0,1,1,0},
        {0,1,0,1,0},
        {1,1,1,0,0},
        {1,0,0,0,0}
    };
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j]=aux[i][j];        // copio aux a la matriz principal
}

// Dirigido y no ponderado
void cargarDirNoPond(int mat[MAXN][MAXN], int &n) {
    n = 5;
    int aux[5][5] = {
        {0,0,0,1,0},
        {1,0,1,0,0},
        {0,0,0,0,0},
        {0,1,1,0,0},
        {1,0,0,0,0}
    };
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j]=aux[i][j];
}

// No dirigido y ponderado (valores son pesos, 0 = sin arista)
void cargarNoDirPond(int mat[MAXN][MAXN], int &n) {
    n = 5;
    int aux[5][5] = {
        {0,4,0,9,6},
        {4,0,7,8,0},
        {0,7,0,5,0},
        {9,8,5,0,0},
        {6,0,0,0,0}
    };
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j]=aux[i][j];
}

// Dirigido y ponderado
void cargarDirPond(int mat[MAXN][MAXN], int &n) {
    n = 5;
    int aux[5][5] = {
        {0,0,0,12,0},
        {3,0,18,0,0},
        {0,0,0,0,0},
        {0,9,15,0,0},
        {6,0,0,0,0}
    };
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j]=aux[i][j];
}

// =====================================================
// MAIN: punto de entrada del programa
// =====================================================
int main() {

    int mat[MAXN][MAXN];        // matriz principal donde se guarda el grafo
    int n;                      // numero de nodos reales usados
    bool dirigido;              // true si grafo es dirigido
    bool ponderado;             // true si grafo tiene pesos

    // arreglo que asocia indice -> letra para imprimir (0->A,1->B,...)
    // esto hace la salida mas amigable para usuarios
    char elementos[] = {
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    cout << "========================================\n";
    cout << "                BFS                     \n";
    cout << "========================================\n";

    // Menu de grafos predefinidos o ingreso manual
    cout << "\nGRAFOS PREDEFINIDOS:\n";
    cout << "1. No dirigido y no ponderado\n";
    cout << "2. Dirigido y no ponderado\n";
    cout << "3. No dirigido y ponderado\n";
    cout << "4. Dirigido y ponderado\n";
    cout << "5. Ingresar grafo manualmente \n";
    cout << "\nElija una opcion: ";

    int opcion;
    cin >> opcion;              // leo que opcion eligio el usuario

    // segun la opcion, cargo una matriz ya definida o pido datos manuales
    if (opcion == 1) {
        cargarNoDirNoPond(mat, n); // funcion que llena mat con aux
        dirigido = false;          // no dirigido
        ponderado = false;         // no ponderado
    }
    else if (opcion == 2) {
        cargarDirNoPond(mat, n);
        dirigido = true;
        ponderado = false;
    }
    else if (opcion == 3) {
        cargarNoDirPond(mat, n);
        dirigido = false;
        ponderado = true;
    }
    else if (opcion == 4) {
        cargarDirPond(mat, n);
        dirigido = true;
        ponderado = true;
    }
    else if (opcion == 5) {
        ingresarGrafoManual(mat, n, dirigido, ponderado); // pido grafo al usuario
    }
    else {
        cout << "Opcion invalida\n"; // opcion fuera de rango
        return 0;
    }

    // muestro la matriz que se genero o ingreso
    mostrarMatriz(mat, n, elementos);

    // pregunto desde que nodo iniciar el BFS (letra)
    char inicio;
    cout << "\nNodo de inicio para BFS (A-Z): ";
    cin >> inicio;

    // convierto la letra a indice numerico usando buscarIndiceNodo
    int src = buscarIndiceNodo(inicio, n, elementos);

    if (src == -1) {           // si la letra no corresponde a ningun nodo valido
        cout << "Nodo invalido.\n";
        return 0;
    }

    // llamo a BFS para realizar el recorrido desde src
    BFS(src, n, mat, elementos);

    return 0;                  // termino del programa
}
