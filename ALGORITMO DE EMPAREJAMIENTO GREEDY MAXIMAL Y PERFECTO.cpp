#include <iostream>   // Necesario para que el programa pueda 'hablar' con el usuario (pedir datos y mostrar resultados).
#include <vector>     // Necesario para crear listas flexibles (vectores) que crecen con el grafo.
#include <algorithm>  // Estandar para operaciones en contenedores.
#include <ctime>      // Necesario para la semilla de aleatoriedad (srand).
#include <cstdlib>    // Necesario para rand() y srand().
#include <limits>     // Para la gestion robusta de errores de entrada (cin.ignore).
#include <utility>    // Necesario para make_pair (correccion de C++98)

using namespace std;

// =========================================================================
// ESTRUCTURAS DE DATOS GLOBALES
// =========================================================================

const int MAXN = 100;

int nNodos = 0;      
int nAristas = 0;     

vector<pair<int, int> > todasAristas;
vector<pair<int, int> > matchingResultante;

bool cubierto[MAXN]; 

// =========================================================================
// ALGORITMO GREEDY
// =========================================================================

int greedyMaximalMatching() {
    matchingResultante.clear();

    for (int i = 0; i <= nNodos; ++i)
        cubierto[i] = false;

    cout << "\n[PROCESO] Analizando aristas en orden codicioso...\n";
    for (size_t i = 0; i < todasAristas.size(); ++i) {

        int u = todasAristas[i].first;
        int v = todasAristas[i].second;

        if (!cubierto[u] && !cubierto[v]) {
            matchingResultante.push_back(todasAristas[i]);
            cubierto[u] = true;
            cubierto[v] = true;
            cout << " -> Emparejado: (" << u << " -- " << v << ")\n";
        } else {
            cout << " -> Ignorado: (" << u << " -- " << v << ") - Nodos ya cubiertos.\n";
        }
    }

    return matchingResultante.size();
}

// =========================================================================
// MOSTRAR RESULTADOS
// =========================================================================

void mostrarResultado(int res) {

    cout << "\n===============================================\n";
    cout << "            RESULTADO DEL EMPAREJAMIENTO\n";
    cout << "===============================================\n";
    cout << "  Tamano del Pareo (Numero de aristas): " << res << endl;
    cout << "-----------------------------------------------\n";

    cout << "  Aristas en el Emparejamiento (M):\n";
    if (res == 0) {
        cout << "  [VACIO] No se encontro ninguna arista para el emparejamiento.\n";
    } else {
        for (size_t i = 0; i < matchingResultante.size(); ++i) {
            cout << "  > Nodo " << matchingResultante[i].first 
                 << " -- Nodo " << matchingResultante[i].second << endl;
        }
    }

    int nodosCubiertos = 0;
    for (int i = 1; i <= nNodos; ++i)
        if (cubierto[i]) nodosCubiertos++;

    cout << "\nVERIFICACION DE PERFECCION:\n";
    cout << "  Nodos cubiertos: " << nodosCubiertos << " de " << nNodos << endl;

    if (nodosCubiertos == nNodos)
        cout << "  [PERFECTO] El pareo SI cubre todos los nodos.\n";
    else
        cout << "  [NO PERFECTO] Faltan " << (nNodos - nodosCubiertos) << " nodos.\n";
}

// =========================================================================
// CARGAR GRAFO PREDEFINIDO (NO DIRIGIDO - NO PONDERADO)
// =========================================================================

void cargarGrafoPredefinido() {

    todasAristas.clear();

    nNodos = 5;

    // Aristas SIN duplicadas (solo u -> v, no ambas direcciones)
    todasAristas.push_back(make_pair(1, 2));
    todasAristas.push_back(make_pair(1, 5));
    todasAristas.push_back(make_pair(1, 4));
    todasAristas.push_back(make_pair(2, 4));
    todasAristas.push_back(make_pair(2, 3));
    todasAristas.push_back(make_pair(3, 4));

    nAristas = todasAristas.size();

    cout << "\n===============================================\n";
    cout << "   GRAFO PREDEFINIDO CARGADO (NO DIRIGIDO)\n";
    cout << "===============================================\n";
    cout << "  Nodos: 5\n";
    cout << "  Aristas cargadas: " << nAristas << "\n";
    cout << "  Lista de aristas:\n";

    for (size_t i = 0; i < todasAristas.size(); ++i)
        cout << "   (" << todasAristas[i].first << " -- " 
                      << todasAristas[i].second << ")\n";

    cout << "===============================================\n";
}

// =========================================================================
// MENU
// =========================================================================

void menu() {
    int op;
    int resultado = 0;

    do {
        cout << "\n===============================================\n";
        cout << "  ALGORITMO DE EMPAREJAMIENTO GREEDY MAXIMAL\n";
        cout << "===============================================\n";

        cout << "1. Ingresar Grafo Manual\n";
        cout << "2. Ejecutar Algoritmo Codicioso\n";
        cout << "3. Mostrar Resultados\n";
        cout << "4. Salir\n";
        cout << "5. *** Cargar Grafo Predefinido No Dirigido/No Ponderado ***\n";
        cout << "-----------------------------------------------\n";
        cout << "Selecciona una opcion: ";

        cin >> op;

        switch (op) {

        case 1:
            // (tu opcion original sin cambios)
            todasAristas.clear();
            cout << "\n--- INGRESO DEL GRAFO ---\n";
            cout << "Introduce el numero de nodos: ";
            cin >> nNodos;
            cout << "Introduce el numero de aristas: ";
            cin >> nAristas;

            for (int i = 0; i < nAristas; i++) {
                int u, v;
                cout << "Arista " << i + 1 << " (u v): ";
                cin >> u >> v;
                todasAristas.push_back(make_pair(u, v));
            }
            break;

        case 2:
            if (nNodos == 0) {
                cout << "[ERROR] Debes ingresar o cargar un grafo.\n";
                break;
            }
            resultado = greedyMaximalMatching();
            break;

        case 3:
            if (nNodos == 0) {
                cout << "[ERROR] No hay grafo cargado.\n";
                break;
            }
            mostrarResultado(resultado);
            break;

        case 4:
            cout << "\nSaliendo...\n";
            break;

        case 5:
            cargarGrafoPredefinido();
            break;

        default:
            cout << "[ERROR] Opcion invalida.\n";
        }

    } while (op != 4);
}

// =========================================================================
// MAIN
// =========================================================================

int main() {
    menu();
    return 0;
}
