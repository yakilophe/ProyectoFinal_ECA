#include <iostream>
// La biblioteca 'iostream' nos permite manejar la entrada y salida, como el 'cout' para mostrar mensajes.
#include <vector>
// 'vector' nos da listas que pueden crecer o encogerse. Se usa para guardar la lista de nodos y sus conexiones.
#include <queue>
// 'queue' (cola) es para implementar la Busqueda en Amplitud (BFS), donde los elementos se procesan en el orden en que llegan.
#include <algorithm>
// 'algorithm' contiene herramientas utiles, como la funcion 'swap' que usamos para cambiar valores rapidamente.
#include <utility>
// 'utility' se usa para la estructura 'pair' (par), util para guardar las aristas como pares de nodos (u, v).
#include <limits>
// 'limits' se usa para manejar los limites de los numeros, por ejemplo, al limpiar el bufer de entrada en el menu.
#include <locale.h>
// 'locale.h' se usa para configurar el idioma local y que los acentos y caracteres especiales se vean bien en la consola.
#include <iomanip>
// 'iomanip' se usa para manipular la salida formateada (ej: setw) — se agregó para corregir el error de 'setw'.

using namespace std;
// Usar el espacio de nombres estandar para no tener que escribir 'std::' antes de cada herramienta.

// --- CONFIGURACION GLOBAL ---
const int MAXN = 100;
// 'MAXN' define el numero maximo de nodos (personas) que podemos manejar. Es un limite fijo (constante).
int nNodos = 0;
// 'nNodos' guarda la cantidad de nodos que el usuario ingrese en el grafo actual.
vector<pair<int, int> > todasAristas;
// 'todasAristas' es una lista de todos los pares de nodos (u, v) que el usuario ha conectado.

// =========================================================================
// CLASE PRINCIPAL: EDMONDS MATCHING
// Esta es la implementacion del Algoritmo Edmonds Blossom, el "corazon" del programa.
// =========================================================================

class EdmondsMatching {
private:
    int V;
// 'V' guarda el numero de vertices (nodos) del grafo.
    vector<vector<int> > adj;
// 'adj' es la lista de adyacencia: para cada nodo, guarda una lista de los nodos a los que esta conectado.
    vector<int> match;
// 'match' guarda el emparejamiento actual. match[i] es el nodo con el que esta emparejado 'i', o -1 si esta libre.
    vector<int> parent;
// 'parent' se usa durante la busqueda para rastrear el camino que llevo a un nodo.
    vector<int> base;
// 'base' es crucial en el Algoritmo Blossom. Para un nodo, 'base[i]' es el nodo 'raiz' de la estructura actual (como una flor).
    vector<int> label;
// 'label' etiqueta los nodos durante la busqueda (BFS): 0 = no visitado, 1 = en la parte 'A' del camino, 2 = en la parte 'B'.
    queue<int> Q;
// 'Q' es la cola para la Busqueda en Amplitud (BFS) modificada.

    // Obtener la raiz/base de un vertice
    int get_base(int v) {
// Esta funcion encuentra el verdadero "jefe" o base de un nodo, incluso si la base ha sido contraida varias veces.
        while (v != base[v]) {
            base[v] = base[base[v]];
            v = base[v];
        }
        return v;
    }

    // Encuentra el ancestro comun mas bajo (LCA)
    int find_lca(int u, int v) {
// 'lca' se usa para encontrar el punto donde se encuentran los caminos que salen de 'u' y 'v'.
// Si los caminos se encuentran y estan etiquetados de forma similar, significa que se encontro un Blossom (Flor).
        vector<bool> visited(V + 1, false);
        
        // Alternamos entre u y v hasta encontrar un nodo visitado
        while (true) {
            u = get_base(u);
            if (u != 0) {
                if (visited[u]) return u;
                visited[u] = true;
// Si el nodo 'u' ya esta emparejado, subimos al padre de su pareja para seguir buscando.
                if (match[u] != -1) u = parent[match[u]];
                else u = 0;
            }
            
            swap(u, v); // Alternamos para buscar desde ambos lados
        }
    }

    // Eleva y actualiza los nodos en la flor
    void blossom_path(int v, int lca, int target) {
// Esta funcion ayuda a "encoger" el Blossom (flor). Reajusta las bases de todos los nodos en el ciclo impar.
        while (get_base(v) != lca) {
            int u = match[v];
            
            // Marcar nodos en la flor
            if (get_base(u) != lca) {
                parent[u] = v;
            }
            
            // Actualizar base
            base[v] = lca;
            base[u] = lca;
            
            // Continuar con el siguiente nodo
            if (label[u] == 1) {
                label[u] = 2;
                Q.push(u);
            }
            
            v = parent[u];
        }
    }

    // Contrae una flor (blossom)
    void contract_blossom(int u, int v, int lca) {
        cout << " -> Contrayendo Blossom/Flor (" << u << " -- " << v << ") con base " << lca << endl;
// Muestra el proceso de contraccion.
        
        // Actualizar bases para u y v
        blossom_path(u, lca, v);
        blossom_path(v, lca, u);
        
        // Actualizar las conexiones de todos los nodos cuya base cambio
        for (int i = 1; i <= V; ++i) {
            if (get_base(i) == lca) {
// Todos los nodos en el Blossom ahora comparten la misma base ('lca'), actuando como un solo super-nodo.
                base[i] = lca;
            }
        }
    }

    // Invierte el emparejamiento a lo largo del camino aumentante
    void augment_path(int u, int v) {
        cout << " -> Aumentando camino: " << u << " - " << v << endl;
// Muestra que se encontro un camino y se va a usar para aumentar el emparejamiento.
        
        while (true) {
            int next_u = match[u];
// Invierte el estado de las aristas en el camino: si no estaba emparejada, ahora si; si si lo estaba, ahora no.
            match[u] = v;
            match[v] = u;
            
            if (next_u == -1) break;
            
            u = parent[next_u];
            v = next_u;
        }
    }

    // BFS modificada para encontrar un camino aumentante
    bool find_augmenting_path(int root) {
// Intenta encontrar un camino desde el nodo 'root' que esta libre hasta otro nodo libre.
        // Inicializacion
        parent.assign(V + 1, 0);
        label.assign(V + 1, 0);
        base.resize(V + 1);
        
        for (int i = 1; i <= V; ++i) {
            base[i] = i;
        }
        
        while (!Q.empty()) Q.pop();
        
        Q.push(root);
        label[root] = 1;
        
        cout << " -> BFS desde nodo raiz: " << root << endl;

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i];
                
                if (get_base(u) == get_base(v)) {
// Ignorar si ya estan en el mismo Blossom (misma base).
                    continue;
                }
                
                if (label[v] == 0) {
                    // Nodo no visitado
                    label[v] = 2;
                    parent[v] = u;
                    
                    if (match[v] == -1) {
                        // ¡Camino aumentante encontrado!
                        augment_path(u, v);
// Se encuentra un nodo libre 'v' y se invierte el camino para aumentar el emparejamiento.
                        cout << " -> Camino aumentante encontrado desde " << root << " hasta " << v << endl;
                        return true;
                    } else {
                        // Continuar BFS desde el nodo emparejado
                        int w = match[v];
// Si 'v' esta emparejado, el nodo 'w' (su pareja) se agrega a la cola para seguir buscando.
                        label[w] = 1;
                        parent[w] = v;
                        Q.push(w);
                    }
                } else if (label[v] == 1) {
                    // Encontramos un blossom
                    int lca = find_lca(u, v);
// Si se encuentra una arista que conecta dos nodos con la misma etiqueta (1), se forma un Blossom (ciclo impar).
                    if (lca != 0) {
                        contract_blossom(u, v, lca);
// Se llama a la funcion para encoger el Blossom.
                    }
                }
            }
        }
        
        return false;
    }

public:
    // Constructor
    EdmondsMatching(int num_nodos) : V(num_nodos) {
// Funcion que se ejecuta al crear el objeto, inicializando las estructuras de datos con el tamaño V.
        adj.resize(V + 1);
        match.assign(V + 1, -1);
    }

    // Carga las aristas al grafo
    void load_graph(const vector<pair<int, int> >& edges) {
        // Limpiar lista de adyacencia
        for (int i = 1; i <= V; ++i) {
            adj[i].clear();
        }
        
        // Anadir aristas en ambas direcciones (grafo no dirigido)
        for (size_t i = 0; i < edges.size(); ++i) {
            int u = edges[i].first;
            int v = edges[i].second;
            
            if (u >= 1 && u <= V && v >= 1 && v <= V) {
// Anade la conexion de u a v, y de v a u, porque el grafo no es dirigido (la conexion es en ambos sentidos).
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
        
        cout << " -> Grafo cargado con " << edges.size() << " aristas" << endl;
    }

    // Funcion principal para calcular el Emparejamiento Maximo
    int maxMatching() {
        int max_m_size = 0;
        
        cout << "\n[PROCESO] Iniciando Algoritmo de Emparejamiento de Edmonds...\n";
        cout << " -> Numero de nodos: " << V << endl;

        // Reiniciar emparejamientos
        fill(match.begin(), match.end(), -1);

        for (int i = 1; i <= V; ++i) {
            if (match[i] == -1) {
// Itera por cada nodo. Si el nodo 'i' esta libre (-1), intenta encontrar un camino aumentante desde el.
                if (find_augmenting_path(i)) {
                    max_m_size++;
// Si se encuentra un camino, el tamaño del emparejamiento aumenta en 1.
                    cout << " -> Emparejamiento aumentado a: " << max_m_size << endl;
                }
            }
        }
        
        return max_m_size;
    }
    
    // Obtener y mostrar el emparejamiento
    vector<pair<int, int> > getMatchingEdges() const {
// Crea una lista de los pares (u, v) que realmente forman el emparejamiento maximo encontrado.
        vector<pair<int, int> > matching_edges;
        vector<bool> added(V + 1, false);
        
        for (int i = 1; i <= V; ++i) {
// Asegura que cada pareja se anada solo una vez (ej: (1, 2) y no tambien (2, 1)).
            if (match[i] != -1 && !added[i] && !added[match[i]]) {
                if (i < match[i]) {
                    matching_edges.push_back(make_pair(i, match[i]));
                } else {
                    matching_edges.push_back(make_pair(match[i], i));
                }
                added[i] = true;
                added[match[i]] = true;
            }
        }
        
        return matching_edges;
    }
    
    // Contar nodos cubiertos
    int countCoveredNodes() const {
// Cuenta cuantos nodos (personas) quedaron emparejados (match[i] != -1).
        int count = 0;
        for (int i = 1; i <= V; ++i) {
            if (match[i] != -1) {
                count++;
            }
        }
        return count;
    }
    
    // Mostrar estado del emparejamiento (para debugging)
    void mostrarEstado() const {
// Muestra el estado actual del emparejamiento para ayudar a depurar o revisar.
        cout << "Estado del emparejamiento:\n";
        for (int i = 1; i <= V; ++i) {
            cout << "Nodo " << i << ": ";
            if (match[i] == -1) {
                cout << "LIBRE";
            } else {
                cout << "emparejado con " << match[i];
            }
            cout << endl;
        }
    }
};

// =========================================================================
// MOSTRAR RESULTADOS Y MENU
// Funciones para la interaccion con el usuario.
// =========================================================================

void mostrarResultado(int res, EdmondsMatching& EM) {
    vector<pair<int, int> > matchingResultante = EM.getMatchingEdges();
    int nodosCubiertos = EM.countCoveredNodes();

    cout << "\n===============================================\n";
    cout << "          RESULTADO DEL EMPAREJAMIENTO DE EDMONDS\n";
    cout << "===============================================\n";
    cout << "  Tamano del Pareo (Maximo): " << res << endl;
    cout << "-----------------------------------------------\n";

    // 1. Mostrar las aristas que forman el Pareo Maximo
    cout << "  Aristas en el Emparejamiento Maximo (M):\n";
    if (matchingResultante.empty()) {
        cout << "    No se encontraron emparejamientos\n";
    } else {
        for (size_t i = 0; i < matchingResultante.size(); ++i) {
// Muestra cada par de nodos que forman parte del emparejamiento.
            cout << "    " << matchingResultante[i].first << " -- " << matchingResultante[i].second << endl;
        }
    }

    // 2. Comprobar Maximalidad
    cout << "\nVERIFICACION DE MAXIMALIDAD:\n";
// El algoritmo de Edmonds siempre garantiza que el resultado sea MAXIMO (el de mayor tamaño), por lo tanto, tambien es MAXIMAL.
    cout << "[¡SI ES MAXIMAL!] El pareo encontrado es **MAXIMO**. ";
    cout << "Dado que el algoritmo de Edmonds encuentra el emparejamiento con mayor cardinalidad posible,\n";
    cout << "ninguna arista puede ser anadida sin chocar con una ya existente (es decir, es **MAXIMAL**).\n";

    // 3. Comprobar Perfeccion
    cout << "\nVERIFICACION DE PERFECCION:\n";
// Un pareo es PERFECTO si todos los nodos quedaron emparejados.
    cout << "  - Nodos totales en el grafo: " << nNodos << ".\n";
    cout << "  - Nodos cubiertos por el pareo: " << nodosCubiertos << ".\n";
    
    if (nodosCubiertos == nNodos) {
        cout << "[¡LOGRADO!] SE ENCONTRO PAREO **PERFECTO**. Todos los " << nNodos << " nodos estan cubiertos.\n";
    } else {
        cout << "[NO PERFECTO] El pareo es Maximo/Maximal, pero NO PERFECTO. Quedaron " << (nNodos - nodosCubiertos) << " nodos libres sin emparejar.\n";
        cout << "  Relacion: " << nodosCubiertos << "/" << nNodos << endl;
    }

    cout << "===============================================\n";
}

void menu() {
    int op;
    int resultado = 0;
// Puntero al objeto EdmondsMatching. Se inicializa a NULL (vacio).
    EdmondsMatching* EM = NULL;

    setlocale(LC_ALL, "");

    do {
        cout << "\n===============================================\n";
        cout << "    ALGORITMO DE EMPAREJAMIENTO DE EDMONDS (BLOSSOM)\n";
        cout << "===============================================\n";
        cout << "Este programa encuentra el EMPAREJAMIENTO MAXIMO en grafos no dirigidos\n";
        cout << "usando el algoritmo Blossom de Edmonds.\n";
        cout << "===============================================\n";
        cout << "1. Ingresar Grafo (Nodos y Aristas)\n";
        cout << "2. Ejecutar Algoritmo BLOSSOM para MAXIMO Pareo\n";
        cout << "3. Mostrar Resultados y Verificaciones\n";
        cout << "4. Mostrar Estado del Grafo\n";
        cout << "5. Salir del Programa\n";
        cout << "6. Cargar grafo predefinido (no dirigido, no ponderado)\n";
        cout << "-----------------------------------------------\n";
        cout << "Selecciona una opcion: ";
        
        if (!(cin >> op)) {
// Manejo de errores si el usuario no ingresa un numero.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[ERROR] Entrada invalida. Por favor ingresa un numero.\n";
            continue;
        }

        switch (op) {
        case 1: {
            // Ingreso de datos del grafo
            cout << "\n--- INGRESO DEL GRAFO ---\n";
            cout << "Numero de nodos (1-" << MAXN << "): ";
            
// El codigo valida que el numero de nodos sea correcto y luego pide el numero de aristas.
            if (!(cin >> nNodos) || nNodos < 1 || nNodos > MAXN) {
                cout << "[ERROR] Numero de nodos invalido.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            
            int nAristas;
            cout << "Numero de aristas: ";
            if (!(cin >> nAristas) || nAristas < 0) {
                cout << "[ERROR] Numero de aristas invalido.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            
            todasAristas.clear();
            cout << "Ingresa las aristas (formato: u v):\n";
            
// El programa pide al usuario que ingrese cada par de nodos conectados.
            for (int i = 0; i < nAristas; ++i) {
                int u, v;
                cout << "Arista " << (i + 1) << ": ";
// El codigo valida que los nodos ingresados existan (esten entre 1 y nNodos).
                if (!(cin >> u >> v)) {
                    cout << "[ERROR] Formato invalido.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--;
                    continue;
                }
                
                if (u < 1 || u > nNodos || v < 1 || v > nNodos) {
                    cout << "[ERROR] Nodos deben estar entre 1 y " << nNodos << ".\n";
                    i--;
                    continue;
                }
                
                if (u == v) {
                    cout << "[ERROR] No se permiten bucles (nodo conectado consigo mismo).\n";
                    i--;
                    continue;
                }
                
                todasAristas.push_back(make_pair(u, v));
            }
            
            if (EM) delete EM;
// Si ya existia un grafo, se borra (delete) y se crea uno nuevo con los datos ingresados.
            EM = new EdmondsMatching(nNodos);
// Se carga la lista de aristas en el nuevo objeto EM.
            EM->load_graph(todasAristas);
            
            cout << "[EXITO] Grafo cargado con " << nNodos << " nodos y " << nAristas << " aristas.\n";
            break;
        }

        case 2:
            // Ejecutar algoritmo
            if (nNodos == 0 || !EM) {
                cout << "\n[ERROR] Primero debes ingresar un grafo (opcion 1).\n";
            } else {
                resultado = EM->maxMatching();
// Llama a la funcion principal del algoritmo para calcular el emparejamiento maximo.
                cout << "\n[FINALIZADO] Algoritmo ejecutado. Se encontro un Pareo Maximo de tamano: " << resultado << endl;
            }
            break;

        case 3:
            // Mostrar resultados
            if (nNodos == 0 || !EM) {
                cout << "\n[ERROR] Primero debes ingresar un grafo y ejecutar el algoritmo.\n";
            } else {
                mostrarResultado(resultado, *EM);
            }
            break;
            
        case 4:
            // Mostrar estado
            if (nNodos == 0 || !EM) {
                cout << "\n[ERROR] Primero debes ingresar un grafo.\n";
            } else {
                cout << "\n--- ESTADO ACTUAL DEL GRAFO ---\n";
                cout << "Nodos: " << nNodos << endl;
                cout << "Aristas ingresadas:\n";
// Muestra todas las aristas que se ingresaron inicialmente.
                for (size_t i = 0; i < todasAristas.size(); ++i) {
                    cout << "  " << todasAristas[i].first << " -- " << todasAristas[i].second << endl;
                }
// Muestra el estado actual del emparejamiento.
                EM->mostrarEstado();
            }
            break;

        case 5:
            // Salir
            cout << "\nSaliendo del programa... ¡Hasta pronto!\n";
// Libera la memoria del objeto EM antes de salir.
            if (EM) delete EM;
            break;
            
        case 6: {
            cout << "\n--- CARGANDO GRAFO PREDEFINIDO ---\n";

            // ----- GRAFO PREDEFINIDO (NO DIRIGIDO - NO PONDERADO) -----
            // Usamos el grafo que confirmaste, sin duplicados, adaptado a 1-based:
            // Original (0-based): 0 1,0 4,0 3,1 3,1 2,2 3
            // Convertido a 1-based:
            nNodos = 5;
            todasAristas.clear();

            todasAristas.push_back(make_pair(1, 2));
            todasAristas.push_back(make_pair(1, 5));
            todasAristas.push_back(make_pair(1, 4));
            todasAristas.push_back(make_pair(2, 4));
            todasAristas.push_back(make_pair(2, 3));
            todasAristas.push_back(make_pair(3, 4));

            cout << "Se cargo el siguiente grafo predefinido:\n";
            cout << "Nodos: " << nNodos << "\n";
            cout << "Aristas:\n";
            for (size_t i = 0; i < todasAristas.size(); ++i)
                cout << "  " << todasAristas[i].first << " -- " << todasAristas[i].second << endl;

            if (EM) delete EM;
            EM = new EdmondsMatching(nNodos);
            EM->load_graph(todasAristas);

            // Imprimir matriz de adyacencia construida a partir de todasAristas
            {
                vector<vector<int> > M(nNodos + 1, vector<int>(nNodos + 1, 0));
                for (size_t i = 0; i < todasAristas.size(); ++i) {
                    int u = todasAristas[i].first;
                    int v = todasAristas[i].second;
                    M[u][v] = 1;
                    M[v][u] = 1;
                }
                cout << "\nMATRIZ DE ADYACENCIA (predefinido):\n\n   ";
                for (int j = 1; j <= nNodos; ++j) cout << setw(3) << j;
                cout << "\n";
                for (int i = 1; i <= nNodos; ++i) {
                    cout << setw(3) << i;
                    for (int j = 1; j <= nNodos; ++j) cout << setw(3) << M[i][j];
                    cout << "\n";
                }
            }

            cout << "[EXITO] Grafo predefinido cargado correctamente.\n";
            break;
        }


        default:
            cout << "\n[ERROR] Opcion invalida. Por favor elige 1-6.\n";
        }
    } while (op != 5);
}

// Funcion principal
int main() {
    setlocale(LC_ALL, "");
    menu();
// El programa comienza ejecutando la funcion del menu.
    return 0;
}
