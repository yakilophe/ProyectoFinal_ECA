#include <iostream>   // Incluye la librería estándar para entrada y salida (cout, cin)
using namespace std;  // Permite usar cout y cin sin escribir std::

// Definimos constantes para el número máximo de nodos y el valor infinito
#define MAX 20        // Máximo número de nodos permitido en el grafo
#define INF 999999    // Representa un valor "infinito" para indicar ausencia de conexión

// Matriz de adyacencia global
int grafo[MAX][MAX];  // Guarda las conexiones entre nodos (ponderadas y no ponderadas)
int n;                // Número de nodos que tendrá el grafo el usuario

// ---------------------------------------------------------------
// --------------------- FUNCIÓN: CREAR GRAFO --------------------
// ---------------------------------------------------------------
void crearGrafoNoPonderado() {
    cout << "\nIngrese el numero de nodos: ";
    cin >> n; // Guarda cuántos nodos usará el grafo

    // Inicializamos toda la matriz a 0 (sin conexiones)
    for(int i = 0; i < n; i++) {       // Recorre filas
        for(int j = 0; j < n; j++) {   // Recorre columnas
            grafo[i][j] = 0;           // Coloca un 0 indicando "sin aristas"
        }
    }

    int aristas;
    cout << "Ingrese el numero de aristas: ";
    cin >> aristas; // Cantidad de aristas que el usuario quiere agregar

    // Leer todas las aristas
    for(int k = 0; k < aristas; k++) {
        int u, v;
        cout << "Arista " << k + 1 << " (nodo1 nodo2): ";
        cin >> u >> v; // Lee dos nodos que se conectan

        // Como es NO ponderado, colocamos un 1 en la matriz
        grafo[u][v] = 1;
        grafo[v][u] = 1; // Se agrega simétricamente porque NO es dirigido
    }
}

// ---------------------------------------------------------------
// ------------------ FUNCIÓN: CREAR GRAFO PONDERADO -------------
// ---------------------------------------------------------------
void crearGrafoPonderado() {
    cout << "\nIngrese el numero de nodos: ";
    cin >> n; // Guarda la cantidad de nodos

    // Inicializamos la matriz con INF (no hay caminos)
    for(int i = 0; i < n; i++) {        // Recorre filas
        for(int j = 0; j < n; j++) {    // Recorre columnas
            if(i == j) grafo[i][j] = 0; // La diagonal es 0 (distancia a sí mismo)
            else grafo[i][j] = INF;     // No existe conexión entre nodos todavía
        }
    }

    int aristas;
    cout << "Ingrese el numero de aristas: ";
    cin >> aristas; // Número de conexiones que se agregarán

    // Leer cada arista con su peso
    for(int k = 0; k < aristas; k++) {
        int u, v, peso;
        cout << "Arista " << k + 1 << " (nodo1 nodo2 peso): ";
        cin >> u >> v >> peso; // Lee nodos y peso

        grafo[u][v] = peso; // Guarda el peso en ambas direcciones
        grafo[v][u] = peso; // Grafo NO dirigido
    }
}

// ---------------------------------------------------------------
// ------------------- FUNCIÓN: MOSTRAR MATRIZ -------------------
// ---------------------------------------------------------------
void mostrarMatriz() {
    cout << "\nMatriz de adyacencia:\n\n";

    for(int i = 0; i < n; i++) {       // Recorre filas
        for(int j = 0; j < n; j++) {   // Recorre columnas
            if(grafo[i][j] == INF)
                cout << "INF ";        // Muestra INF si no hay conexión
            else
                cout << grafo[i][j] << " "; // Muestra el peso o 1 en no ponderado
        }
        cout << "\n"; // Salto de línea al terminar una fila
    }
}

// ---------------------------------------------------------------
// --------------------------- MENÚ PRINCIPAL ---------------------
// ---------------------------------------------------------------
int main() {
    int opcion; // Variable para guardar la opción del menú

    do {
        // Menú principal
        cout << "\n===== MENU DE GRAFOS =====\n";
        cout << "1. Crear grafo NO ponderado\n";
        cout << "2. Crear grafo ponderado\n";
        cout << "3. Mostrar matriz de adyacencia\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion; // El usuario elige qué quiere hacer

        switch(opcion) {
            case 1:
                crearGrafoNoPonderado(); // Llama a la función de grafos no ponderados
                break;
            case 2:
                crearGrafoPonderado();  // Llama a la función de grafos ponderados
                break;
            case 3:
                mostrarMatriz(); // Muestra la matriz actual
                break;
            case 0:
                cout << "Saliendo...\n"; // Mensaje de salida
                break;
            default:
                cout << "Opcion no valida.\n"; // Manejo de error
        }

    } while(opcion != 0); // Repite mientras no se elija salir

    return 0; // Fin del programa
}
