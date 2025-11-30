#include <iostream>  // Entrada y salida
#include <vector>    // Vectores y listas de adyacencia
#include <queue>     // Cola para BFS (verificación bipartita)
#include <limits>    // Para cin.ignore
#include <locale.h>  // Para tildes y ñ
#include <cmath>     // Para el cálculo de la perfección (ceil/floor, aunque usaremos aritmética entera)

using namespace std;

// =========================================================================
// ESTRUCTURAS Y VARIABLES GLOBALES
// =========================================================================

// Tamaño máximo del grafo (ajustado para ser un poco más seguro)
const int MAX_NODES = 200; 

int V = 0; // Número total de vértices (nodos)
int E = 0; // Número total de aristas (conexiones)

// Lista de adyacencia del grafo (para la verificación Bipartita)
vector<vector<int> > grafo_adyacencia;

// ***************************************************************
// 1. VERIFICACIÓN DE GRAFO BIPARTITO (Requisito para Kuhn)
// ***************************************************************

// Intenta colorear el grafo con 2 colores (0 y 1) usando BFS.
bool esBipartito(int n_nodos, vector<vector<int> >& grafo, vector<int>& grupo_color) {
    // Si la lista de colores (grupo_color) no tiene el tamaño correcto, la ajustamos y rellenamos con -1 (sin color).
    if (grupo_color.size() != (size_t)n_nodos) {
        grupo_color.assign(n_nodos, -1);
    } else {
        fill(grupo_color.begin(), grupo_color.end(), -1);
    }

    // Recorremos todos los nodos para manejar grafos desconectados.
    for (int inicio = 0; inicio < n_nodos; inicio++) {
        if (grupo_color[inicio] == -1) {
            queue<int> cola;
            cola.push(inicio);
            grupo_color[inicio] = 0; // Asignamos el Color A (0) al nodo inicial

            while (!cola.empty()) {
                int u = cola.front();
                cola.pop();

                // Recorremos los vecinos del nodo u
                // Usamos bucle for tradicional (C++98 compatible)
                for (size_t i = 0; i < grafo[u].size(); ++i) {
                    int vecino = grafo[u][i];

                    // Si el vecino no tiene color, lo coloreamos con el color opuesto
                    if (grupo_color[vecino] == -1) {
                        grupo_color[vecino] = 1 - grupo_color[u];
                        cola.push(vecino);
                    } 
                    // Si el vecino tiene el mismo color, NO es bipartito
                    else if (grupo_color[vecino] == grupo_color[u]) {
                        return false; 
                    }
                }
            }
        }
    }
    
    // Si completamos el recorrido sin conflictos, es bipartito.
    return true;
}

// ***************************************************************
// 2. ALGORITMO DE KUHN (Pareo Máximo en Bipartitos)
// ***************************************************************

// Estructuras específicas de Kuhn
vector<int> match_to; // match_to[v] = u significa que el nodo v está emparejado con u. -1 si está libre.
vector<bool> visited; // Para la búsqueda DFS en cada iteración.

// Función de búsqueda en profundidad (DFS) para encontrar un camino aumentante.
// Intenta emparejar el nodo 'u' (del Grupo A) con un nodo 'v' libre del Grupo B.
// Devuelve true si encuentra un camino aumentante (es decir, logra hacer un nuevo emparejamiento).
bool try_match(int u, vector<vector<int> >& grafo, const vector<int>& grupo_color) {
    
    // Usamos el bucle for tradicional (C++98 compatible)
    for (size_t i = 0; i < grafo[u].size(); ++i) {
        int v = grafo[u][i];

        // Solo consideramos aristas que van de A (u) a B (v).
        // (La verificación de bipartición ya hizo el filtrado de colores)
        if (grupo_color[u] == 0 && grupo_color[v] == 1 && !visited[v]) {
            
            // Marcamos 'v' como visitado en esta ejecución de DFS.
            visited[v] = true;

            // CASO 1: 'v' está libre (match_to[v] == -1), o
            // CASO 2: 'v' está emparejado con otro nodo (match_to[v] = u_anterior),
            // y podemos encontrar un camino aumentante para 'u_anterior' a partir de ahí.

            if (match_to[v] == -1 || try_match(match_to[v], grafo, grupo_color)) {
                // Si encontramos un camino, hacemos el emparejamiento.
                // El camino aumentante invierte el estado de las aristas.
                match_to[v] = u;
                return true; // Éxito: Encontramos un nuevo emparejamiento.
            }
        }
    }
    return false; // No se pudo encontrar un camino aumentante desde 'u'.
}

// Función que ejecuta el algoritmo de Kuhn completo
int kuhnMaxMatching(int n_nodos, vector<vector<int> >& grafo) {
    
    // 1. REQUISITO: VERIFICAR SI EL GRAFO ES BIPARTITO Y OBTENER GRUPOS
    vector<int> grupo_color;
    if (!esBipartito(n_nodos, grafo, grupo_color)) {
        cout << "\n[ERROR GRAFO] El grafo NO es bipartito. El algoritmo de Kuhn solo funciona en grafos bipartitos." << endl;
        return 0;
    }
    
    // 2. PREPARACIÓN DE ESTRUCTURAS DE KUHN
    // Inicializamos el vector de emparejamientos. -1 significa que el nodo está libre.
    match_to.assign(n_nodos, -1);
    int max_matching_size = 0;

    // 3. ENCONTRAR PAREO MÁXIMO
    // Iteramos sobre todos los nodos. Solo necesitamos iterar sobre los nodos del Grupo A (color 0).
    for (int u = 0; u < n_nodos; u++) {
        if (grupo_color[u] == 0) {
            
            // En cada intento de emparejamiento, reiniciamos el vector de visitados.
            visited.assign(n_nodos, false);
            
            if (try_match(u, grafo, grupo_color)) {
                // Si try_match devuelve true, encontramos un camino aumentante y aumentamos el pareo.
                max_matching_size++;
            }
        }
    }

    // El resultado es el tamaño máximo del pareo.
    return max_matching_size;
}

// =========================================================================
// FUNCIONES DE ENTRADA/SALIDA (MENÚ)
// =========================================================================

void imprimirResultadoKuhn(int res) {
    cout << "\n===============================================\n";
    cout << "           RESULTADO DEL PAREO MAXIMO\n";
    cout << "===============================================\n";
    cout << "  Algoritmo: Kuhn (Garantiza Pareo MAXIMO)\n";
    cout << "  Tamaño del Pareo (Numero de aristas): " << res << endl;
    cout << "-----------------------------------------------\n";

    // 1. MAXIMALIDAD (Verificación)
    cout << "VERIFICACION DE MAXIMALIDAD:\n";
    if (res > 0) {
        cout << "[CONFIRMADO] El pareo es MAXIMAL, ya que el pareo MAXIMO siempre es maximal.\n";
    } else {
        cout << "[VACIO] El pareo es vacío (0 aristas), lo cual es trivialmente Maximal.\n";
    }
    cout << "-----------------------------------------------\n";

    // 2. PERFECCIÓN (Verificación)
    int nodos_cubiertos = 2 * res; // Cada arista cubre 2 nodos
    
    cout << "VERIFICACION DE PERFECCION:\n";
    cout << "  - Nodos totales en el grafo: " << V << ".\n";
    cout << "  - Nodos cubiertos por el pareo: " << nodos_cubiertos << ".\n";

    if (V % 2 != 0) {
        cout << "[IMPOSIBLE] No puede haber Pareo Perfecto, el numero de nodos (" << V << ") es impar.\n";
    } else if (nodos_cubiertos == V) {
        cout << "[¡LOGRADO!] SE ENCONTRO PAREO PERFECTO. Todos los " << V << " nodos estan cubiertos.\n";
    } else {
        cout << "[NO PERFECTO] El pareo es Máximo, pero NO Perfecto. Quedaron " << (V - nodos_cubiertos) << " nodos libres sin emparejar.\n";
    }
    cout << "-----------------------------------------------\n";
    
    // 3. Mostrar las aristas del pareo.
    cout << "  Aristas en el Emparejamiento MAXIMO (M):\n";
    if (res == 0) {
        cout << "  [VACIO] No se encontraron emparejamientos.\n";
    } else {
        // Solo necesitamos revisar los nodos del Grupo B (color 1), ya que 'match_to[v]' guarda el par.
        for (int v = 0; v < V; ++v) {
            if (match_to[v] != -1) {
                // match_to[v] es el nodo 'u' del Grupo A. 'v' es el nodo del Grupo B.
                // Sumamos 1 a los IDs para mostrarlos como el usuario los ingresó (desde 1).
                cout << "  > Nodo " << match_to[v] + 1 << " -- Nodo " << v + 1 << endl;
            }
        }
    }

    cout << "===============================================\n";
}

void menu() {
    int op;
    int resultado = 0;
    bool grafo_cargado = false;

    do {
        cout << "\n===============================================\n";
        cout << "  ALGORITMO DE KUHN (PAREO MAXIMO, MAXIMAL Y PERFECTO EN BIPARTITOS)\n";
        cout << "===============================================\n";
        
        cout << "ESTE ALGORITMO ES APTO SOLAMENTE PARA GRAFOS:\n";
        cout << "  * NO DIRIGIDOS y NO PONDERADOS\n";
        cout << "  * **BIPARTITOS** (El programa lo verifica)\n";
        cout << "-----------------------------------------------\n";
        
        cout << "1. Ingresar Grafo (Nodos y Aristas)\n";
        cout << "2. Ejecutar Algoritmo de Kuhn (Pareo Maximo)\n";
        cout << "3. Mostrar Resultados y Verificaciones (Maximalidad y Perfeccion)\n";
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
            // Limpiar datos anteriores
            grafo_adyacencia.clear();
            V = 0; 
            E = 0;
            grafo_cargado = false;

            cout << "\n--- INGRESO DEL GRAFO ---\n";
            cout << "Introduce el numero de nodos (V): ";
            if (!(cin >> V)) {
                cout << "[ERROR] Entrada invalida para el numero de nodos.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                V = 0; break;
            }

            if (V <= 0 || V > MAX_NODES) {
                cout << "[ERROR] El numero de nodos debe ser positivo y no exceder el limite de " << MAX_NODES << ".\n";
                V = 0;
                break;
            }

            cout << "Introduce el numero de aristas (E): ";
            if (!(cin >> E)) {
                cout << "[ERROR] Entrada invalida para el numero de aristas.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                V = 0; 
                break;
            }
            
            // Redimensionar la lista de adyacencia
            grafo_adyacencia.assign(V, vector<int>());

            cout << "\nInstrucciones: Ingresa las aristas como pares (u v).\n";
            cout << "Los nodos deben estar numerados del 1 al " << V << ".\n";

            // Bucle para ingresar las aristas.
            for (int i = 0; i < E; i++) {
                int u, v;
                cout << "Arista " << i + 1 << " (u v): ";
                
                if (!(cin >> u >> v)) {
                    cout << "[ERROR] Entrada invalida para la arista (u o v no son numeros). Reingresa.\n";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; 
                    continue;
                }

                // Ajuste a base 0 para el código
                int u_idx = u - 1;
                int v_idx = v - 1;

                // Validación de rango y auto-lazo.
                if (u < 1 || u > V || v < 1 || v > V || u == v) {
                    cout << "[ERROR] Nodos fuera de rango (1 a " << V << ") o arista de nodo a si mismo. Reingresa.\n";
                    i--; 
                } else {
                    // Agregamos la conexión en ambos sentidos (Grafo No Dirigido).
                    grafo_adyacencia[u_idx].push_back(v_idx);
                    grafo_adyacencia[v_idx].push_back(u_idx); 
                }
            }

            cout << "\n[EXITO] Grafo cargado correctamente (" << V << " nodos y " << E << " aristas).\n";
            grafo_cargado = true;
            break;

        case 2:
            if (!grafo_cargado) {
                cout << "\n[ERROR] Debes ingresar el grafo primero (Opcion 1).\n";
                break;
            }
            // Ejecutar el cálculo.
            resultado = kuhnMaxMatching(V, grafo_adyacencia);
            cout << "\n[FINALIZADO] Algoritmo ejecutado. Se encontro un Pareo MAXIMO de tamaño: " << resultado << endl;
            break;

        case 3:
            if (!grafo_cargado) {
                cout << "\n[ERROR] Debes ingresar el grafo primero (Opcion 1).\n";
                break;
            }
            // Mostrar los resultados detallados.
            imprimirResultadoKuhn(resultado);
            break;

        case 4:
            cout << "\nSaliendo del programa... ¡Hasta pronto!\n";
            break;

        default:
            cout << "\n[ERROR] Opcion invalida. Por favor, selecciona 1, 2, 3 o 4.\n";
        }

    } while (op != 4);
}

// Función principal: lo primero que se ejecuta al iniciar el programa.
int main() {
    // Configura el idioma para mostrar caracteres correctamente.
    setlocale(LC_ALL, ""); 
    
    // Inicia el menu principal.
    menu();
    
    return 0;
}
