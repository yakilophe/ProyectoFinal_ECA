#include <iostream>   // Libreria para entrada y salida: cin, cout
using namespace std;  // Para no escribir std:: cada vez

const int MAXN = 100;  // Definimos un tamaño máximo para el grafo

// --------------------------------------------------------------
// Variables globales
// --------------------------------------------------------------
int n;                     // Numero de nodos del grafo
int grafo[MAXN][MAXN];      // Matriz de adyacencia del grafo
bool visitado[MAXN];        // Arreglo para marcar nodos visitados en DFS

// --------------------------------------------------------------
// Limpiar matriz
// --------------------------------------------------------------
void limpiarMatriz() {
    // Recorremos toda la matriz grafo
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            grafo[i][j] = 0; // Inicializamos todas las posiciones a 0
}

// --------------------------------------------------------------
// Grafo predefinido: NO dirigido y NO ponderado
// --------------------------------------------------------------
void cargarNoDirigidoNoPonderado() {
    n = 5;             // Definimos que el grafo tiene 5 nodos
    limpiarMatriz();    // Limpiamos la matriz antes de cargar el grafo

    // Lista de aristas (cada arista se representa con par [u,v])
    int aristas[][2] = {
        {0,1}, {0,4}, {0,3},
        {1,0}, {1,3}, {1,2},
        {2,1}, {2,3},
        {3,2}, {3,1}, {3,0},
        {4,0}
    };

    int total = 12;    // Numero total de aristas
    for(int i = 0; i < total; i++) {
        int u = aristas[i][0]; // Nodo origen
        int v = aristas[i][1]; // Nodo destino
        grafo[u][v] = 1;       // Marcamos la arista en la matriz
    }
}

// --------------------------------------------------------------
// Leer grafo manualmente
// --------------------------------------------------------------
void leerGrafoManual() {
    cout << "Ingrese el numero de nodos: ";
    cin >> n;              // Leemos el numero de nodos

    limpiarMatriz();       // Limpiamos la matriz antes de llenarla

    // Solicitamos al usuario que ingrese la matriz de adyacencia
    cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grafo[i][j];  // Leemos cada elemento de la matriz
}

// --------------------------------------------------------------
// DFS desde un nodo inicial
// --------------------------------------------------------------
void dfs(int u) {
    visitado[u] = true;      // Marcamos el nodo como visitado
    cout << u << " ";        // Mostramos el nodo visitado

    // Recorremos todos los nodos para ver conexiones desde u
    for (int v = 0; v < n; v++) {
        // Si hay arista de u a v y v no fue visitado, hacemos DFS recursivo
        if (grafo[u][v] == 1 && !visitado[v]) {
            dfs(v);
        }
    }
}

// --------------------------------------------------------------
// MAIN
// --------------------------------------------------------------
int main() {

    // Encabezado del programa
    cout << "========================================\n";
    cout << "     COMPONENTES CONEXAS (DFS)          \n";
    cout << "========================================\n";

    cout << "\nGRAFOS PREDEFINIDOS:\n";
    cout << "1. No dirigido y no ponderado\n";
    cout << "2. Ingresar grafo manualmente\n";

    int opcion;
    cout << "\nElija una opcion: ";
    cin >> opcion; // Leemos la opcion del usuario

    // Dependiendo de la opcion, cargamos el grafo
    if(opcion == 1) {
        cargarNoDirigidoNoPonderado();
    }
    else if(opcion == 2) {
        leerGrafoManual();
    }
    else {
        cout << "Opcion invalida.\n";
        return 0; // Salimos si la opcion no es valida
    }

    // Inicializamos todos los nodos como no visitados
    for (int i = 0; i < n; i++)
        visitado[i] = false;

    cout << "\n=== Componentes Conexas ===\n";

    // Recorremos todos los nodos y ejecutamos DFS si no fue visitado
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            cout << "CC: "; // Imprimimos etiqueta de Componente Conexa
            dfs(i);          // Ejecutamos DFS desde el nodo i
            cout << "\n";    // Salto de linea al terminar componente
        }
    }

    cout << "========================================\n";
    return 0; // Fin del programa
}
