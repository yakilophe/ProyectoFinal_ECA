#include <iostream>   // Librería para mostrar mensajes en pantalla y leer datos del usuario
#include <vector>     // Librería para usar vectores (listas dinámicas)
#include <iomanip>    // Librería para dar formato a la salida (alinear columnas, etc.)

using namespace std;  // Para no escribir "std::" cada vez

// ---------------------------------------------------------------
// Estructura para representar una arista (conexión entre dos nodos)
// ---------------------------------------------------------------
struct Arista {
    int u, v;   // Los dos nodos que conecta la arista
    int peso;   // El "peso" o valor de la arista (puede ser costo, distancia, etc.)
};

// ---------------------------------------------------------------
// Función para mostrar el título y explicación inicial
// ---------------------------------------------------------------
void mostrarTitulo() {
    cout << "\n=======================================================\n";
    cout << "         ALGORITMO GREEDY MAXIMAL MATCHING\n";
    cout << "=======================================================\n";
    cout << "[IMPORTANTE]: Este algoritmo SOLO es valido para\n";
    cout << "             GRAFOS NO DIRIGIDOS.\n\n";
    cout << "[OBJETIVO]: Encontrar un conjunto MAXIMAL de aristas.\n";
    cout << "[NOTA]: La seleccion de aristas se basa en el ORDEN\n";
    cout << "        de entrada, NO en el peso ni la optimalidad.\n";
    cout << "-------------------------------------------------------\n";
}

// ---------------------------------------------------------------
// Funciones para cargar grafos ya preparados (preestablecidos)
// ---------------------------------------------------------------
void cargarGrafoNoPonderado(vector<Arista>& aristas, int& n, int& m) {
    n = 6;  // Número de nodos
    m = 7;  // Número de aristas

    aristas.clear();  // Limpiar lista de aristas
    // Agregar conexiones (todas con peso 1 porque es no ponderado)
    aristas.push_back({1, 2, 1});
    aristas.push_back({1, 3, 1});
    aristas.push_back({2, 4, 1});
    aristas.push_back({3, 4, 1});
    aristas.push_back({4, 5, 1});
    aristas.push_back({5, 6, 1});
    aristas.push_back({3, 6, 1});
}

void cargarGrafoPonderado(vector<Arista>& aristas, int& n, int& m) {
    n = 6;  // Número de nodos
    m = 7;  // Número de aristas

    aristas.clear();  // Limpiar lista
    // Agregar conexiones con pesos distintos
    aristas.push_back({1, 2, 3});
    aristas.push_back({1, 3, 5});
    aristas.push_back({2, 4, 2});
    aristas.push_back({3, 4, 8});
    aristas.push_back({4, 5, 6});
    aristas.push_back({5, 6, 4});
    aristas.push_back({3, 6, 7});
}

// ---------------------------------------------------------------
// Función para imprimir la matriz de adyacencia
// ---------------------------------------------------------------
void imprimirMatriz(int n, const vector<Arista>& aristas) {
    // Crear matriz n x n inicializada en 0
    vector< vector<int> > A(n + 1, vector<int>(n + 1, 0));

    // Llenar la matriz con las aristas
    for (int i = 0; i < aristas.size(); i++) {
        int u = aristas[i].u;
        int v = aristas[i].v;
        A[u][v] = aristas[i].peso;
        A[v][u] = aristas[i].peso; // Como el grafo es NO dirigido
    }

    // Mostrar la matriz en pantalla
    cout << "\n=======================================================\n";
    cout << "                MATRIZ DE ADYACENCIA\n";
    cout << "=======================================================\n";

    cout << "      ";
    for (int j = 1; j <= n; j++)
        cout << setw(4) << j;  // Encabezado con los números de los nodos
    cout << "\n";

    for (int i = 1; i <= n; i++) {
        cout << setw(4) << i << " ";  // Número de fila
        for (int j = 1; j <= n; j++) {
            cout << setw(4) << A[i][j];  // Valor de la conexión
        }
        cout << "\n";
    }
}

// ---------------------------------------------------------------
// Función principal (main)
// ---------------------------------------------------------------
int main() {

    mostrarTitulo();  // Mostrar título inicial

    int tipo;  // Tipo de grafo (1 = no ponderado, 2 = ponderado)
    cout << "1. Seleccione el tipo de grafo:\n";
    cout << " [1] No ponderado\n";
    cout << " [2] Ponderado\n";
    cout << "Opcion: ";
    cin >> tipo;  // Leer opción del usuario

    if (tipo == 2) {
        cout << "\n[ADVERTENCIA]: Este algoritmo NO garantiza el pareo de mayor peso.\n";
    }

    int opcionPre;  // Opción de grafo (manual o preestablecido)
    vector<Arista> aristas;  // Lista de aristas
    int n = 0, m = 0;        // Número de nodos y aristas

    cout << "\n2. Seleccione modo:\n";
    cout << " [1] Ingresar aristas manualmente\n";
    cout << " [2] Usar grafo preestablecido\n";
    cout << "Opcion: ";
    cin >> opcionPre;

    // Si se usa grafo preestablecido
    if (opcionPre == 2) {
        if (tipo == 1) {
            cargarGrafoNoPonderado(aristas, n, m);
        } else {
            cargarGrafoPonderado(aristas, n, m);
        }
    } else {
        // Si el usuario quiere ingresar manualmente
        cout << "\nIngrese el numero de vertices: ";
        cin >> n;
        cout << "Ingrese el numero de aristas: ";
        cin >> m;

        aristas.resize(m);  // Ajustar tamaño del vector

        cout << "\n=======================================================\n";
        cout << "                INGRESO DE ARISTAS\n";
        cout << "=======================================================\n";

        for (int i = 0; i < m; i++) {
            if (tipo == 1) {
                cout << "Arista " << i + 1 << " (u v): ";
                cin >> aristas[i].u >> aristas[i].v;
                aristas[i].peso = 1;  // Peso fijo en no ponderado
            } else {
                cout << "Arista " << i + 1 << " (u v peso): ";
                cin >> aristas[i].u >> aristas[i].v >> aristas[i].peso;
            }

            // Validar que los nodos existan
            if (aristas[i].u < 1 || aristas[i].u > n || aristas[i].v < 1 || aristas[i].v > n) {
                cout << "[ERROR]: nodos invalidos.\n";
                i--;  // Repetir ingreso
            }
        }
    }

    // Mostrar matriz de adyacencia
    imprimirMatriz(n, aristas);

    // ---------------------------------------------------------------
    // Algoritmo GREEDY (codicioso)
    // ---------------------------------------------------------------
    vector<bool> usado(n + 1, false);  // Marca si un nodo ya está emparejado
    vector<Arista> matching;           // Lista de aristas aceptadas

    cout << "\n=======================================================\n";
    cout << "                PROCESO GREEDY\n";
    cout << "=======================================================\n";

    // Revisar todas las aristas en orden
    for (int i = 0; i < aristas.size(); i++) {
        int u = aristas[i].u;
        int v = aristas[i].v;

        // Si ambos nodos están libres, aceptar la arista
        if (!usado[u] && !usado[v]) {
            matching.push_back(aristas[i]);
            usado[u] = true;
            usado[v] = true;
            cout << " -> [ACEPTADA] (" << u << " , " << v << ") Peso: " << aristas[i].peso << "\n";
        } else {
            cout << " -> [RECHAZADA] (" << u << " , " << v << ")\n";
        }
    }

    // ---------------------------------------------------------------
    // Mostrar resultado final
    // ---------------------------------------------------------------
    cout << "\n=======================================================\n";
    cout << "                RESULTADO FINAL\n";
    cout << "=======================================================\n";

    cout << "Tamaño del pareo: " << matching.size() << "\n";

    int sumaPesos = 0;
    for (int i = 0; i < matching.size(); i++) {
        cout << "PAREJA " << i
