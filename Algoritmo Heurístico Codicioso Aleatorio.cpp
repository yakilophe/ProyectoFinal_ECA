#include <iostream>   // Librería para entrada y salida (mostrar y leer datos)
#include <vector>     // Librería para usar vectores dinámicos
#include <algorithm>  // Librería con funciones como random_shuffle
#include <utility>    // Librería para usar pair (pares de valores)
#include <limits>     // Librería para manejar límites de entrada
#include <cstdlib>    // Librería para funciones de números aleatorios
#include <ctime>      // Librería para obtener la hora actual (semilla aleatoria)

using namespace std;

const int MAXN = 100;              // Máximo número de nodos permitido
int nNodos = 0;                    // Número de nodos actual
vector<pair<int, int> > todasAristas; // Lista de aristas del grafo

// =========================================================
// IMPRIMIR MATRIZ DE ADYACENCIA
// =========================================================
void imprimirMatriz(const vector<pair<int,int> >& aristas, int nodos) {
    int M[101][101]; // Matriz de adyacencia

    // Inicializar matriz en ceros
    for (int i = 0; i < nodos; i++)
        for (int j = 0; j < nodos; j++)
            M[i][j] = 0;

    // Llenar con las aristas (grafo no dirigido)
    for (size_t i = 0; i < aristas.size(); i++) {
        int u = aristas[i].first;
        int v = aristas[i].second;
        M[u][v] = 1;
        M[v][u] = 1;
    }

    // Mostrar matriz
    cout << "\nMATRIZ DE ADYACENCIA (" << nodos << " nodos)\n";
    cout << "-------------------------------------\n";

    for (int i = 0; i < nodos; i++) {
        for (int j = 0; j < nodos; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

// =========================================================
// HEURÍSTICA ALEATORIA (Greedy con orden aleatorio)
// =========================================================
int randomGreedyMatching() {

    vector<pair<int, int> > matchingResultante; // Resultado del emparejamiento
    vector<bool> cubierto(nNodos + 1, false);   // Marca si un nodo ya está emparejado

    cout << "\n[PROCESO] Barajando el orden de las aristas aleatoriamente...\n";

    // Mezclar el orden de las aristas
    random_shuffle(todasAristas.begin(), todasAristas.end());

    cout << "[PROCESO] Analizando aristas en orden aleatorio Codicioso...\n";

    // Recorrer todas las aristas
    for (size_t i = 0; i < todasAristas.size(); ++i) {
        int u = todasAristas[i].first;
        int v = todasAristas[i].second;

        // Si ambos nodos están libres, aceptar la arista
        if (!cubierto[u] && !cubierto[v]) {
            matchingResultante.push_back(todasAristas[i]);
            cubierto[u] = true;
            cubierto[v] = true;

            cout << " -> Emparejado: (" << u << " -- " << v << ")\n";
        }
    }

    // Guardar el resultado en la lista global
    todasAristas = matchingResultante;

    return matchingResultante.size(); // Devolver tamaño del matching
}

// =========================================================
// MOSTRAR RESULTADOS
// =========================================================
void mostrarResultado(int res, const vector<pair<int, int> >& aristasOriginales) {

    vector<pair<int, int> > matchingResultante = todasAristas;
    vector<bool> cubierto(nNodos + 1, false);

    // Marcar nodos cubiertos
    for (size_t i = 0; i < matchingResultante.size(); ++i) {
        cubierto[matchingResultante[i].first] = true;
        cubierto[matchingResultante[i].second] = true;
    }

    cout << "\n===============================================\n";
    cout << "          RESULTADO DE LA HEURISTICA ALEATORIA\n";
    cout << "===============================================\n";
    cout << "  Tamano del Pareo: " << res << endl;
    cout << "  Aristas totales en el grafo: " << aristasOriginales.size() << endl;
    cout << "-----------------------------------------------\n";

    cout << "  Aristas en el Emparejamiento:\n";
    for (size_t i = 0; i < matchingResultante.size(); ++i) {
        cout << "   (" << matchingResultante[i].first
             << " -- " << matchingResultante[i].second << ")\n";
    }

    // Verificación de maximalidad
    cout << "\nVERIFICACION DE MAXIMALIDAD:\n";
    cout << "[SI ES MAXIMAL!] La logica Codiciosa garantiza que el resultado es **MAXIMAL**.\n";

    int nodosCubiertos = 0;
    for (int i = 1; i <= nNodos; ++i)
        if (cubierto[i]) nodosCubiertos++;

    // Verificación de perfección
    cout << "\nVERIFICACION DE PERFECCION Y MAXIMO (No Garantizado):\n";
    cout << "  - Nodos totales en el grafo: " << nNodos << ".\n";
    cout << "  - Nodos cubiertos por el pareo: " << nodosCubiertos << ".\n";

    if (nodosCubiertos == nNodos)
        cout << "[POSIBLEMENTE PERFECTO!] El pareo cubre todos los nodos.\n";
    else
        cout << "[NO PERFECTO] Quedaron " << (nNodos - nodosCubiertos) << " nodos libres.\n";

    cout << "[ADVERTENCIA] Es Maximal, pero **NO** garantiza ser Maximo.\n";
    cout << "===============================================\n";
}

// =========================================================
// MENÚ PRINCIPAL
// =========================================================
void menu() {
    int op;                // Opción del menú
    int resultado = 0;     // Resultado del matching
    vector<pair<int, int> > aristasOriginales; // Copia de aristas originales

    srand(time(0)); // Inicializar semilla aleatoria

    do {
        cout << "\n===============================================\n";
        cout << "  ALGORITMO HEURISTICO: CODICIOSO ALEATORIO\n";
        cout << "1. Ingresar Grafo (Nodos y Aristas)\n";
        cout << "2. Ejecutar Algoritmo Heuristico (Orden Aleatorio)\n";
        cout << "3. Mostrar Resultados y Verificaciones\n";
        cout << "4. Salir del Programa\n";
        cout << "5. Usar Grafo No Dirigido y No Ponderado (Preestablecido)\n";

        // Validar entrada
        if (!(cin >> op)) {
            cout << "\n[ERROR] Entrada invalida. Ingresa un numero (1-5).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = 0;
            continue;
        }

        switch (op) {

        // Opción 1: Ingresar grafo manualmente
        case 1: {
            todasAristas.clear();
            aristasOriginales.clear();

            cout << "\nIngresa el numero de nodos (1-" << MAXN << "): ";
            cin >> nNodos;

            if (nNodos < 1 || nNodos > MAXN) {
                cout << "[ERROR] Numero invalido.\n";
                nNodos = 0;
                break;
            }

            int m;
            cout << "Ingresa el numero de aristas: ";
            cin >> m;

            cout << "Ingresa las aristas (u v):\n";
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;

                if (u < 0 || u >= nNodos || v < 0 || v >= nNodos || u == v) {
                    cout << "[ERROR] Arista invalida, ignorada.\n";
                    continue;
                }

                pair<int,int> p;
                p.first  = u;
                p.second = v;

                aristasOriginales.push_back(p);
            }

            todasAristas = aristasOriginales;

            cout << "[OK] Grafo almacenado.\n";
            break;
        }

        // Opción 2: Ejecutar algoritmo
        case 2:
            if (nNodos == 0) {
                cout << "\n[ERROR] No hay grafo cargado.\n";
                break;
            }

            todasAristas = aristasOriginales;

            resultado = randomGreedyMatching();
            cout << "\n[FINALIZADO] Pareo Maximal encontrado: " << resultado << endl;
            break;

        // Opción 3: Mostrar resultados
        case 3:
            if (resultado == 0 && todasAristas.empty()) {
                cout << "\n[ERROR] No hay resultados para mostrar.\n";
                break;
            }
            mostrarResultado(resultado, aristasOriginales);
            break;

        // Opción 5: Grafo preestablecido no dirigido
        case 5: {
            aristasOriginales.clear();
            todasAristas.clear();

            nNodos = 5;

            int edges[][2] = {
                {0,1}, {0,4}, {0,3},
                {1,0}, {1,3}, {1,2},
                {2,1}, {2,3},
                {3,2}, {3,1}, {3,0},
                {4,0}
            };

            int m = sizeof(edges)/sizeof(edges[0]);

            for (int i = 0; i < m; i++) {
                pair<int,int> p;
                p.first  = edges[i][0];
                p.second = edges[i][1];
                aristasOriginales.push_back(p);
            }

            todasAristas = aristasOriginales;

            cout << "\n[OK] Grafo NO DIRIGIDO y NO PONDERADO cargado automáticamente.\n";
            cout << "Nodos: 5\nAristas: " << m << endl;

            cout << "\nLista de Aristas:\n";
            for (size_t i = 0; i < aristasOriginales.size(); i++) {
                cout << "(" << aristasOriginales[i].first
                     << " -- " << aristasOriginales[i].second << ")\n";
            }

            imprimirMatriz(aristasOriginales, nNodos);
            break;
        }

        // Opción 4: Salir
        case 4:
            cout << "\nSaliendo del programa... Hasta pronto!\n";
            break;

        default:
            cout << "\n[ERROR] Opcion invalida.\n";
        }

    } while (op != 4); // Repetir menú hasta que el usuario elija salir
}

// =========================================================
// FUNCIÓN PRINCIPAL
// =========================================================
int main() {
    menu();   // Llamar al menú principal
    return 0; // Fin del programa
}
