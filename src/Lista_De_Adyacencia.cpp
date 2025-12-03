#include <iostream>     // Para usar cout y cin
#include <string>       // Para manejar textos si se requieren
using namespace std;

// ===================== VARIABLES GLOBALES ==========================

// Máximo de nodos que puede tener el grafo 
const int MAX = 100;

// Matriz de adyacencia del grafo
// Se usa una matriz simple compatible con compiladores antiguos
int matriz[MAX][MAX];

// Variable para guardar cuántos nodos tiene el grafo
int n = 0;

// ===================== FUNCIONES ==================================

// -------------------------------------------------------------------
//  Llena la matriz de adyacencia con ceros.
//  Significa que inicialmente no hay conexiones entre nodos.
// -------------------------------------------------------------------
void inicializarMatriz() {
    for (int i = 0; i < MAX; i++) {           // Recorre filas
        for (int j = 0; j < MAX; j++) {       // Recorre columnas
            matriz[i][j] = 0;                 // Asigna 0 
        }
    }
}

// -------------------------------------------------------------------
//  Permite crear un grafo NO ponderado a partir de aristas que
//  el usuario proporciona. Solo usa 1 para indicar conexión.
//  El grafo ES NO DIRIGIDO, así que matriz[a][b] = matriz[b][a] = 1
// -------------------------------------------------------------------
void crearNoPonderado() {
    int aristas;

    cout << "Ingrese el numero de nodos: ";
    cin >> n;                                 // El usuario indica n nodos

    inicializarMatriz();                      // Borra cualquier grafo anterior

    cout << "Ingrese el numero de aristas: ";
    cin >> aristas;                           // Cantidad de conexiones

    // Se leen las aristas
    for (int i = 0; i < aristas; i++) {
        int a, b;

        // Se pide la conexión entre dos nodos
        cout << "Arista " << i + 1 << " (nodo1 nodo2): ";
        cin >> a >> b;

        // Se marca la conexión en ambos sentidos porque es NO dirigido
        matriz[a][b] = 1;
        matriz[b][a] = 1;
    }
}

// -------------------------------------------------------------------
//  Crea un grafo que sí tiene pesos entre nodos.
//  El usuario proporciona el peso de cada arista.
//  También es NO dirigido.
// -------------------------------------------------------------------
void crearPonderado() {
    int aristas;

    cout << "Ingrese el numero de nodos: ";
    cin >> n;

    inicializarMatriz();                      // Limpia la matriz

    cout << "Ingrese el numero de aristas: ";
    cin >> aristas;

    for (int i = 0; i < aristas; i++) {
        int a, b, peso;

        // Se solicita nodo1, nodo2 y peso
        cout << "Arista " << i + 1 << " (nodo1 nodo2 peso): ";
        cin >> a >> b >> peso;

        // Guardamos el peso en ambas posiciones
        matriz[a][b] = peso;
        matriz[b][a] = peso;
    }
}

// -------------------------------------------------------------------
//  Convierte la matriz de adyacencia en lista de adyacencia.
//
//  Si el valor es:
//       1 = grafo NO ponderado
//  otro = grafo ponderado (muestra el peso)
// -------------------------------------------------------------------
void imprimirLista() {
    cout << "\nLista de adyacencia:\n\n";

    for (int i = 0; i < n; i++) {             // Recorre cada nodo
        cout << i << " -> ";                  // Muestra el nodo inicial

        bool tieneVecinos = false;            // Para saber si tiene conexiones

        // Busca vecinos del nodo i
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] != 0) {          // Si hay conexión
                tieneVecinos = true;

                // Si el grafo es no ponderado (solo hay 1)
                if (matriz[i][j] == 1) {
                    cout << j << "  ";        // Solo imprime el nodo vecino
                }
                else {
                    // Si el peso es distinto de 1, lo imprime
                    cout << "(" << j << ", peso=" << matriz[i][j] << ")  ";
                }
            }
        }

        // Si no tiene vecinos
        if (!tieneVecinos) {
            cout << "sin vecinos";
        }

        cout << endl;                         // Salto de línea
    }

    cout << endl;
}

// ===================== MENÚ PRINCIPAL ==============================

// -------------------------------------------------------------------
//  Presenta un menú para crear grafos y mostrar la lista.
// -------------------------------------------------------------------
int main() {
    int opcion;                               // Para almacenar opción del menú

    do {
        // Menú 
        cout << "===== MENU DE GRAFOS =====\n";
        cout << "1. Crear grafo NO ponderado\n";
        cout << "2. Crear grafo ponderado\n";
        cout << "3. Mostrar lista de adyacencia\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;						  // Guarda la opción del usuario

        // Se evalúa la opción seleccionada
        switch (opcion) {
        case 1:
            crearNoPonderado();               // Crea grafo sin pesos
            break;

        case 2:
            crearPonderado();                 // Crea grafo con pesos
            break;

        case 3:
            imprimirLista();                  // Imprime lista de adyacencia
            break;

        case 0:
            cout << "Saliendo...\n";          // Termina el programa
            break;

        default:
            cout << "Opcion no valida.\n";    // Manejo de error
        }

    } while (opcion != 0);                    // Repite hasta que elija salir

    return 0;                                 // Fin del programa
}
