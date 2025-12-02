#include <iostream>     // Para imprimir en pantalla y leer datos del usuario
#include <queue>        // Para usar la estructura de cola (queue) necesaria para BFS
using namespace std;

const int MAXN = 100;   // Tamaño maximo permitido para la matriz

// --------------------------------------------------------------
// VARIABLES GLOBALES
// --------------------------------------------------------------

int n;                          // Numero de nodos reales del grafo
int grafo[MAXN][MAXN];          // Matriz de adyacencia del grafo
bool visitado[MAXN];            // Arreglo para marcar los nodos visitados en BFS

// --------------------------------------------------------------
// LIMPIAR MATRIZ
// --------------------------------------------------------------
void limpiarMatriz() {

    // Recorre todas las filas de la matriz
    for (int i = 0; i < MAXN; i++)
        // Recorre todas las columnas
        for (int j = 0; j < MAXN; j++)
            grafo[i][j] = 0;    // Coloca 0 en cada posicion
}

// --------------------------------------------------------------
// GRAFO PREDEFINIDO: NO DIRIGIDO Y NO PONDERADO
// --------------------------------------------------------------
void cargarNoDirigidoNoPonderado() {

    n = 5;               // El grafo predefinido tendra 5 nodos: 0,1,2,3,4
    limpiarMatriz();     // Se asegura que la matriz este totalmente en ceros

    // Lista de aristas representada como pares (u, v)
    int aristas[][2] = {
        {0,1}, {0,4}, {0,3},
        {1,0}, {1,3}, {1,2},
        {2,1}, {2,3},
        {3,2}, {3,1}, {3,0},
        {4,0}
    };

    int total = 12;      // Total de aristas definidas arriba

    // Recorre el arreglo de aristas
    for(int i = 0; i < total; i++) {

        int u = aristas[i][0];  // Primer nodo de la arista
        int v = aristas[i][1];  // Segundo nodo de la arista

        grafo[u][v] = 1;        // Al ser no ponderado se usa 1 para conectar
    }
}

// --------------------------------------------------------------
// LEER GRAFO MANUALMENTE
// --------------------------------------------------------------
void leerGrafoManual() {

    cout << "Ingrese el numero de nodos: ";
    cin >> n;                        // El usuario ingresa cuantos nodos tiene el grafo

    limpiarMatriz();                 // Limpia la matriz antes de llenarla

    cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";

    // Recorre cada fila
    for (int i = 0; i < n; i++)
        // Recorre cada columna
        for (int j = 0; j < n; j++)
            cin >> grafo[i][j];     // El usuario ingresa un 0 o 1
}

// --------------------------------------------------------------
// BFS (BREADTH FIRST SEARCH)
// --------------------------------------------------------------
void bfs(int inicio) {

    queue<int> q;                   // Cola que mantiene los nodos pendientes por visitar
    q.push(inicio);                 // Inserta el nodo inicial en la cola
    visitado[inicio] = true;        // Marca el nodo inicial como visitado

    // Mientras haya nodos dentro de la cola
    while (!q.empty()) {

        int u = q.front();          // Obtiene el nodo al frente de la cola (sin eliminarlo)
        q.pop();                    // Lo elimina de la cola para procesarlo

        cout << u << " ";           // Imprime el nodo actual

        // Recorre todos los posibles vecinos del nodo u
        for (int v = 0; v < n; v++) {

            // Si hay conexion (grafo[u][v] == 1) y no ha sido visitado
            if (grafo[u][v] == 1 && !visitado[v]) {

                visitado[v] = true; // Marca el nodo como visitado
                q.push(v);          // Agrega el nodo a la cola para explorarlo mas tarde
            }
        }
    }
}

// --------------------------------------------------------------
// MAIN
// --------------------------------------------------------------
int main() {

    // Encabezado del programa
    cout << "========================================\n";
    cout << "     COMPONENTES CONEXAS (BFS)          \n";
    cout << "========================================\n";

    // Menu de opciones
    cout << "\nGRAFOS PREDEFINIDOS:\n";
    cout << "1. No dirigido y no ponderado\n";
    cout << "2. Ingresar grafo manualmente\n";

    int opcion;
    cout << "\nElija una opcion: ";
    cin >> opcion;                   // Lee la opcion del usuario

    // Selecciona la opcion correspondiente
    if(opcion == 1) {
        cargarNoDirigidoNoPonderado();   // Carga grafo fijo
    }
    else if(opcion == 2) {
        leerGrafoManual();               // Permite al usuario ingresar uno propio
    }
    else {
        cout << "Opcion invalida.\n";    // Si el usuario ingresa algo incorrecto
        return 0;                        // Termina el programa
    }

    // Inicializa todos los nodos como NO visitados
    for (int i = 0; i < n; i++)
        visitado[i] = false;

    cout << "\n=== Componentes Conexas ===\n";

    // Recorre todos los nodos para buscar componentes
    for (int i = 0; i < n; i++) {

        // Si el nodo aun no ha sido visitado
        if (!visitado[i]) {

            cout << "CC: ";      // Imprime encabezado de la componente conexa

            bfs(i);              // Llama BFS para explorar esta componente

            cout << "\n";        // Salto de linea para separar componentes
        }
    }

    cout << "========================================\n";
    return 0;                    // Fin del programa
}
