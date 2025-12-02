#include <iostream>   // Biblioteca para entrada y salida (cout, cin)
#include <vector>     // Biblioteca estandar, aqui no se usa pero no estorba
#include <stack>      // Biblioteca para usar pila (stack)
#include <iomanip>    // Biblioteca para setw (dar formato en columnas)
using namespace std;  // Permite usar cout y cin sin escribir std::

const int MAXN = 100; // Numero maximo permitido de nodos en el grafo

// ======================================================================
// VARIABLES GLOBALES
// ======================================================================

// Numero real de nodos que va a tener el grafo cargado
int n;

// Matriz de adyacencia del grafo original (grafo[u][v] = 1 si hay arista u→v)
int grafo[MAXN][MAXN];

// Matriz del grafo transpuesto (aristas invertidas)
int transpuesto[MAXN][MAXN];

// Arreglo para marcar si un nodo ya fue visitado en un recorrido DFS
bool visitado[MAXN];

// Pila utilizada por el algoritmo de Kosaraju (guarda el orden de salida)
stack<int> pila;

// ======================================================================
// LIMPIAR VISITADOS: reinicia el arreglo visitado[] a false
// ======================================================================
void limpiarVisitados() {
    for (int i = 0; i < n; i++)   // Recorre todos los nodos existentes
        visitado[i] = false;      // Marca cada nodo como "no visitado"
}

// ======================================================================
// IMPRIMIR MATRIZ: muestra el grafo en forma de matriz de adyacencia
// ======================================================================
void imprimirGrafo() {
    cout << "\n=== Matriz de adyacencia ===\n\n";

    // Imprimir encabezado de columnas
    cout << setw(4) << " ";       // Espacio inicial para alinear
    for (int j = 0; j < n; j++)
        cout << setw(4) << j;     // Imprimir numero de columna
    cout << "\n";

    // Imprimir filas con su respectivo numero
    for (int i = 0; i < n; i++) {
        cout << setw(4) << i;     // Numero de fila
        for (int j = 0; j < n; j++)
            cout << setw(4) << grafo[i][j]; // Imprimir 0 o 1
        cout << "\n";             // Salto de linea por fila
    }
}

// ======================================================================
// OPCION 2: INGRESAR GRAFO MANUALMENTE
// ======================================================================
void leerGrafoManual() {
    cout << "Ingresa el numero de nodos: ";
    cin >> n; // Leer el numero de nodos del grafo

    // Solicitar la matriz de adyacencia completa
    cout << "Ingresa la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)       // Recorrer filas
        for (int j = 0; j < n; j++)   // Recorrer columnas
            cin >> grafo[i][j];       // Leer valor 0 o 1
}

// ======================================================================
// OPCION 1: CARGAR GRAFO PREDEFINIDO (dirigido y no ponderado)
// ======================================================================
void cargarDirigidoNoPonderado() {
    n = 5; // Numero de nodos que tendra el grafo

    // Inicializar matriz en 0
    for (int i = 0; i < n; i++)     // Recorrer filas
        for (int j = 0; j < n; j++) // Recorrer columnas
            grafo[i][j] = 0;        // Asignar 0

    // Aristas dirigidas del grafo (u -> v)
    grafo[1][0] = 1;
    grafo[0][3] = 1;
    grafo[1][2] = 1;
    grafo[3][2] = 1;
    grafo[3][1] = 1;
    grafo[4][0] = 1;

    cout << "\nGrafo dirigido y no ponderado cargado.\n";
}

// ======================================================================
// PRIMER DFS (dfs1): sirve para llenar la pila en orden de salida
// ======================================================================
void dfs1(int u) {
    visitado[u] = true; // Marcar nodo como visitado

    // Explorar todos los nodos v alcanzables desde u
    for (int v = 0; v < n; v++)
        if (grafo[u][v] == 1 && !visitado[v]) // Si hay arista y no visitado
            dfs1(v);                           // Llamada recursiva

    pila.push(u);  // Agregar nodo a la pila al terminar sus recorridos
}

// ======================================================================
// TRANSPONER GRAFO: invierte todas las direcciones de las aristas
// ======================================================================
void transponerGrafo() {
    for (int i = 0; i < n; i++)            // Recorrer filas
        for (int j = 0; j < n; j++)        // Recorrer columnas
            transpuesto[i][j] = grafo[j][i]; // Intercambiar j->i
}

// ======================================================================
// SEGUNDO DFS (dfs2): recorre en el grafo transpuesto e imprime SCC
// ======================================================================
void dfs2(int u) {
    cout << u << " ";     // Mostrar nodo parte de la SCC
    visitado[u] = true;   // Marcar como visitado

    // Explorar aristas en el grafo transpuesto
    for (int v = 0; v < n; v++)
        if (transpuesto[u][v] == 1 && !visitado[v])
            dfs2(v);      // Recursion para seguir explorando SCC
}

// ======================================================================
// EJECUTAR KOSARAJU: realiza las dos pasadas del algoritmo
// ======================================================================
void ejecutarKosaraju() {
    limpiarVisitados(); // Reiniciar visitados antes del primer DFS

    // Primera pasada: llenar pila segun tiempos de finalizacion
    for (int i = 0; i < n; i++)
        if (!visitado[i])
            dfs1(i);

    // Construir el grafo transpuesto
    transponerGrafo();

    // Segunda pasada sobre el grafo transpuesto
    limpiarVisitados();

    cout << "\nComponentes fuertemente conexas:\n";

    // Vaciar pila para determinar SCCs
    while (!pila.empty()) {
        int u = pila.top(); // Obtener cima de la pila
        pila.pop();         // Quitarla

        // Si el nodo no ha sido visitado en la segunda pasada,
        // entonces inicia una nueva SCC
        if (!visitado[u]) {
            cout << "SCC: ";
            dfs2(u);        // Explorar e imprimir los nodos de la SCC
            cout << "\n";
        }
    }
}

// ======================================================================
// MAIN: menu principal del programa
// ======================================================================
int main() {

    // Encabezado del programa
    cout << "========================================\n";
    cout << "         KOSARAJU - SCC                 \n";
    cout << "========================================\n";

    int opcion; // Variable para guardar la eleccion del usuario

    // Menu mostrado exactamente como lo pediste
    cout << "\nGRAFOS PREDEFINIDOS:\n";
    cout << "1. Dirigido y no ponderado\n";
    cout << "2. Ingresar grafo manualmente \n";

    cout << "\nElige una opcion: ";
    cin >> opcion; // Leer opcion seleccionada

    // Segun la opcion, cargar el grafo
    if (opcion == 1)
        cargarDirigidoNoPonderado();
    else if (opcion == 2)
        leerGrafoManual();
    else {
        cout << "Opcion invalida.\n"; // Si la opcion no es correcta
        return 1;                     // Terminar programa
    }

    imprimirGrafo();  // Mostrar matriz del grafo cargado
    ejecutarKosaraju(); // Ejecutar algoritmo completo

    cout << "\n========================================\n";
    return 0; // Fin del programa
}
