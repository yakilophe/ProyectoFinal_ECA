#include <iostream>     // Incluye libreria para imprimir y leer datos
#include <stack>        // Incluye estructura de pila (stack) requerida por Tarjan
#include <algorithm>    // Incluye funciones como min()
using namespace std;

const int MAXN = 50;    // Maximo numero de nodos permitido

int n;                          // Numero real de nodos que se esta usando
int matriz[MAXN][MAXN];         // Matriz de adyacencia del grafo

// Arreglo de letras para representar los nodos A, B, C, ...
char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// Variables propias del algoritmo de Tarjan
int ids[MAXN];                  // Guarda el identificador de descubrimiento del nodo
int low[MAXN];                  // Guarda el menor id alcanzable desde el nodo
bool enPila[MAXN];              // Indica si un nodo esta dentro de la pila
stack<int> pilaTarjan;          // Pila utilizada por Tarjan para almacenar nodos
int idActual = 0;               // Contador global para asignar IDs crecientes
int sccCount = 0;               // Numero total de componentes encontradas

// =====================================================
// LIMPIAR MATRIZ
// =====================================================
void limpiarMatriz() {
    for(int i = 0; i < MAXN; i++)         // Recorre filas
        for(int j = 0; j < MAXN; j++)     // Recorre columnas
            matriz[i][j] = 0;             // Coloca 0 en cada celda
}

// =====================================================
// GRAFO PREDEFINIDO (dirigido no ponderado)
// =====================================================
void cargarDirigidoNoPonderado() {
    n = 5;                 // Este grafo usa los nodos A, B, C, D, E
    limpiarMatriz();       // Asegura que la matriz este en ceros

    matriz[1][0] = 1;     // B -> A
    matriz[0][3] = 1;     // A -> D
    matriz[1][2] = 1;     // B -> C
    matriz[3][2] = 1;     // D -> C
    matriz[3][1] = 1;     // D -> B
    matriz[4][0] = 1;     // E -> A
}

// =====================================================
// LEER MATRIZ MANUALMENTE
// =====================================================
void leerGrafoManual() {

    cout << "\nIngrese el numero de vertices (max 26): ";
    cin >> n;                          // Lee la cantidad de nodos

    if(n > 26 || n <= 0) {             // Valida rango de nodos permitidos
        cout << "Numero invalido.\n";
        exit(0);
    }

    limpiarMatriz();                   // Inicializa la matriz en ceros

    cout << "\nIngrese la matriz de adyacencia (0 o 1)\n";
    for(int i = 0; i < n; i++) {       // Itera sobre cada fila
        cout << "Fila del nodo " << elementos[i] << ": ";
        for(int j = 0; j < n; j++)     // Itera sobre columnas
            cin >> matriz[i][j];       // Lee cada valor 0 o 1
    }
}

// =====================================================
// MOSTRAR MATRIZ
// =====================================================
void mostrarMatriz() {

    cout << "\n=== Matriz usada ===\n\n";

    cout << "    ";                          // Espacio para alineacion
    for (int j = 0; j < n; j++)              // Imprime encabezados de columna
        cout << elementos[j] << "   ";
    cout << "\n";

    for (int i = 0; i < n; i++) {            // Recorre filas
        cout << elementos[i] << "   ";       // Imprime letra del nodo
        for (int j = 0; j < n; j++)          // Recorre columnas
            cout << matriz[i][j] << "   ";   // Imprime valor 0 o 1
        cout << "\n";
    }
}

// =====================================================
// INICIALIZAR VARIABLES DE TARJAN
// =====================================================
void inicializarTarjan() {

    for(int i = 0; i < n; i++) {
        ids[i] = -1;              // Nodo aun no visitado
        low[i] = 0;               // Low se llena despues
        enPila[i] = false;        // Ningun nodo inicia en la pila
    }

    idActual = 0;                 // Reinicia contador global de IDs
    sccCount = 0;                 // Reinicia el contador de componentes

    while(!pilaTarjan.empty())    // Limpia la pila por seguridad
        pilaTarjan.pop();
}

// =====================================================
// TARJAN DFS (Algoritmo principal)
// =====================================================
void tarjanDFS(int u) {

    ids[u] = low[u] = idActual++;     // Asigna id inicial y low iguales
    pilaTarjan.push(u);               // Coloca u en la pila
    enPila[u] = true;                 // Marca que u esta en la pila

    // -----------------------
    // Explorar vecinos de u
    // -----------------------
    for(int v = 0; v < n; v++) {

        if(matriz[u][v] == 1) {       // Si hay arista u -> v

            if(ids[v] == -1) {        // Si v aun no fue visitado
                tarjanDFS(v);         // Llama recursivamente a Tarjan en v
                low[u] = min(low[u], low[v]);    // Actualiza low de u
            }
            else if(enPila[v]) {      // Si v esta en la pila, es parte del SCC actual
                low[u] = min(low[u], ids[v]);    // Actualiza low usando id de v
            }
        }
    }

    // ---------------------------------------------
    // Si u es una raiz de SCC (low[u] == ids[u])
    // ---------------------------------------------
    if(ids[u] == low[u]) {

        cout << "\nComponente #" << ++sccCount << ": ";

        // Extraer nodos del SCC desde la pila
        while(true) {

            int v = pilaTarjan.top();   // Obtiene el nodo superior
            pilaTarjan.pop();           // Lo quita de la pila
            enPila[v] = false;          // Marca que ya no esta en la pila

            cout << elementos[v] << " "; // Imprime el nodo encontrado

            if(v == u)                  // Si llegamos al nodo raiz, detener
                break;
        }

        cout << "\n";                   // Salto de linea
    }
}

// =====================================================
// EJECUTAR TARJAN COMPLETO
// =====================================================
void ejecutarTarjan() {

    inicializarTarjan();                // Prepara todas las variables

    for(int i = 0; i < n; i++)          // Recorre todos los nodos
        if(ids[i] == -1)               // Si el nodo aun no fue visitado
            tarjanDFS(i);              // Aplica DFS de Tarjan
}

// =====================================================
// MAIN
// =====================================================
int main() {

    cout << "========================================\n";
    cout << "           TARJAN - SCC                 \n";
    cout << "========================================\n";

    cout << "\nGRAFOS PREDEFINIDOS:\n";
    cout << "1. Dirigido y no ponderado\n";
    cout << "2. Ingresar grafo manualmente\n";

    int opcion;
    cout << "\nElija una opcion: ";
    cin >> opcion;

    if(opcion == 1) {
        cargarDirigidoNoPonderado();   // Carga grafo definido en el codigo
    }
    else if(opcion == 2) {
        leerGrafoManual();             // Permite ingresar matriz manualmente
    }
    else {
        cout << "Opcion invalida.\n";
        return 0;                      // Finaliza el programa
    }

    mostrarMatriz();                   // Muestra la matriz que se usara

    cout << "\n===== Componentes fuertemente conexas =====\n";
    ejecutarTarjan();                  // Ejecuta Tarjan

    cout << "========================================\n";
    return 0;
}
