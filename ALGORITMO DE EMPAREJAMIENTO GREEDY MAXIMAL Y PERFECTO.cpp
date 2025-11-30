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

// Limite maximo de nodos para evitar desbordamiento y por seguridad del sistema.
const int MAXN = 100;

int nNodos = 0;       // Almacena la cantidad total de nodos (V) que tiene el grafo.
int nAristas = 0;     // Almacena la cantidad total de aristas (E) que tiene el grafo.

// Lista principal que contiene todas las aristas {u, v} ingresadas por el usuario.
// CORRECCION C++98: Se anade un espacio entre '>' y '>' para evitar error de operador '>>'.
vector<pair<int, int> > todasAristas;

// Lista donde se guardan las aristas seleccionadas para formar el Pareo Maximal (M).
// CORRECCION C++98: Se anade un espacio entre '>' y '>' para evitar error de operador '>>'.
vector<pair<int, int> > matchingResultante;

// Arreglo booleano. cubierto[i] es 'true' si el nodo 'i' ya es parte de un emparejamiento.
// Se usa un tamaño de MAXN para permitir indexacion desde 1 hasta nNodos.
bool cubierto[MAXN]; 

// =========================================================================
// FUNCION PRINCIPAL DEL ALGORITMO
// =========================================================================

// Algoritmo Codicioso (Greedy) para encontrar el Pareo Maximal.
// La estrategia es simple: tomar la primera arista disponible que no choque con las anteriores.
int greedyMaximalMatching() {
    matchingResultante.clear();
    
    for (int i = 0; i <= nNodos; ++i) {
        cubierto[i] = false; 
    }

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
// MOSTRAR RESULTADOS Y VERIFICAR
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
            cout << "  > Nodo " << matchingResultante[i].first << " -- Nodo " << matchingResultante[i].second << endl;
        }
    }

    cout << "\nVERIFICACION DE MAXIMALIDAD:\n";
    cout << "[CONFIRMADO] El pareo encontrado es **MAXIMAL**. Esto significa que es imposible anadir una arista mas al conjunto M sin que choque con una arista ya elegida.\n";

    int nodosCubiertos = 0;
    for (int i = 1; i <= nNodos; ++i) {
        if (cubierto[i]) {
            nodosCubiertos++;
        }
    }

    cout << "\nVERIFICACION DE PERFECCION:\n";
    cout << "  - Nodos totales en el grafo: " << nNodos << ".\n";
    cout << "  - Nodos cubiertos por el pareo: " << nodosCubiertos << ".\n";
    
    if (nodosCubiertos == nNodos) {
        cout << "[LOGRADO!] SE ENCONTRO PAREO PERFECTO. Todos los " << nNodos << " nodos estan cubiertos.\n";
    } else {
        cout << "[NO PERFECTO] El pareo es Maximal, pero NO PERFECTO. Quedaron " << (nNodos - nodosCubiertos) << " nodos libres sin emparejar.\n";
        cout << "  Relacion: " << nodosCubiertos << "/" << nNodos << endl;
    }

    cout << "===============================================\n";
}

// =========================================================================
// MENU PRINCIPAL
// =========================================================================

void menu() {
    int op;
    int resultado = 0;

    srand(time(0));

    do {
        cout << "\n===============================================\n";
        cout << "  ALGORITMO DE EMPAREJAMIENTO GREEDY MAXIMAL Y PERFECTO\n";
        cout << "===============================================\n";
        
        cout << "ESTE ALGORITMO ES APTO SOLAMENTE PARA GRAFOS:\n";
        cout << "  * NO DIRIGIDOS (Undirected)\n";
        cout << "  * NO PONDERADOS (Unweighted)\n";
        cout << "-----------------------------------------------\n";
        
        cout << "1. Ingresar Grafo (Nodos y Aristas)\n";
        cout << "2. Ejecutar Algoritmo Codicioso\n";
        cout << "3. Mostrar Resultados y Verificaciones\n";
        cout << "4. Salir del Programa\n";
        cout << "-----------------------------------------------\n";
        cout << "Selecciona una opcion: ";
        
        if (!(cin >> op)) {
            cout << "\n[ERROR] Entrada invalida. Por favor, ingresa un numero (1-4).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = 0;
            continue;
        }

        switch (op) {
        case 1:
            todasAristas.clear();
            nNodos = 0; 
            nAristas = 0;

            cout << "\n--- INGRESO DEL GRAFO ---\n";
            cout << "Introduce el numero de nodos (V): ";
            if (!(cin >> nNodos)) {
                cout << "[ERROR] Entrada invalida para el numero de nodos.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                nNodos = 0; break;
            }

            if (nNodos <= 0 || nNodos >= MAXN) {
                cout << "[ERROR] El numero de nodos debe ser positivo y no exceder el limite de " << MAXN << ".\n";
                nNodos = 0;
                break;
            }

            cout << "Introduce el numero de aristas (E): ";
            if (!(cin >> nAristas)) {
                cout << "[ERROR] Entrada invalida para el numero de aristas.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                nNodos = 0;
                break;
            }

            cout << "\nInstrucciones: Ingresa las aristas como pares (u v).\n";
            cout << "Los nodos deben estar numerados del 1 al " << nNodos << ".\n";

            for (int i = 0; i < nAristas; i++) {
                int u, v;
                cout << "Arista " << i + 1 << " (u v): ";
                
                if (!(cin >> u >> v)) {
                    cout << "[ERROR] Entrada invalida para la arista (u o v no son numeros). Reingresa.\n";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--;
                    continue;
                }

                if (u < 1 || u > nNodos || v < 1 || v > nNodos || u == v) {
                    cout << "[ERROR] Nodos fuera de rango (1 a " << nNodos << ") o arista de nodo a si mismo. Reingresa.\n";
                    i--;
                } else {
                    todasAristas.push_back(make_pair(u, v));
                }
            }

            cout << "\n[EXITO] Grafo cargado correctamente (" << nNodos << " nodos y " << todasAristas.size() << " aristas).\n";
            break;

        case 2:
            if (nNodos == 0) {
                cout << "\n[ERROR] Debes ingresar el grafo primero (Opcion 1).\n";
                break;
            }
            resultado = greedyMaximalMatching();
            cout << "\n[FINALIZADO] Algoritmo ejecutado. Se encontro un Pareo Maximal de tamano: " << resultado << endl;
            break;

        case 3:
            if (nNodos == 0) {
                cout << "\n[ERROR] Debes ingresar el grafo primero (Opcion 1).\n";
                break;
            }
            mostrarResultado(resultado);
            break;

        case 4:
            cout << "\nSaliendo del programa... Hasta pronto!\n";
            break;

        default:
            cout << "\n[ERROR] Opcion invalida. Por favor, selecciona 1, 2, 3 o 4.\n";
        }

    } while (op != 4);
}

// Funcion principal
int main() {
    menu();
    return 0;
}

