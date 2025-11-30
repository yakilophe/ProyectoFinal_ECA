#include <iostream> 
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Constantes y variables globales (que se usan en todo el programa)
const int MAXN = 100; // Define el numero maximo de nodos que el grafo puede tener.
vector<int> adj[MAXN]; // Lista de Adyacencia: Es la forma en que se guarda el grafo. adj[i] es una lista de todos los nodos conectados a 'i'.
int matchNode[MAXN], parentNode[MAXN], baseNode[MAXN]; // Listas clave para el algoritmo:
// matchNode: Guarda la pareja de cada nodo (si matchNode[i] = j, entonces 'i' y 'j' estan emparejados).
// parentNode: Guarda el "padre" o nodo anterior en el camino que se esta explorando (similar a una ruta).
// baseNode: Guarda el nodo "base" o la raiz de un 'Blossom' (el ciclo impar).
bool used[MAXN], blossom[MAXN]; // Variables booleanas (verdadero/falso):
// used: Marca si un nodo ya fue visitado en la busqueda de camino.
// blossom: Marca si un nodo es parte de un 'Blossom' (ciclo impar).
queue<int> q; // La cola para la busqueda en amplitud (BFS).
int n, m; // n: numero de nodos, m: numero de aristas.

// =========================================================================
// BUSCAR ANCESTRO COMUN (LCA - Lowest Common Ancestor)
// =========================================================================
// Esta funcion encuentra el ancestro comun mas bajo (LCA) entre dos nodos 'a' y 'b'.
// En este contexto, ayuda a encontrar donde se unen dos caminos para formar un 'Blossom'.
int lca(int a, int b) {
    vector<bool> visited(n, false); // Crea una lista para marcar nodos visitados.

    // Sube desde el nodo 'a', pasando de nodo a su pareja, y de su pareja a su padre.
    while (true) {
        a = baseNode[a]; // Sube a la "base" del nodo (si es parte de un Blossom).
        visited[a] = true; // Marca este nodo como visitado.
        if (matchNode[a] == -1) break; // Si ya no tiene pareja, detente.
        a = parentNode[matchNode[a]]; // Ve a la pareja del nodo 'a', y luego al padre de esa pareja.
    }

    // Sube desde el nodo 'b' de la misma manera.
    while (true) {
        b = baseNode[b]; // Sube a la "base" del nodo 'b'.
        if (visited[b]) return b; // ¡Si ya visitaste 'b' desde 'a', significa que es el LCA! Regresa 'b'.
        if (matchNode[b] == -1) break; // Si ya no tiene pareja, detente.
        b = parentNode[matchNode[b]]; // Ve a la pareja del nodo 'b', y luego al padre de esa pareja.
    }

    return -1; // No se encontro un ancestro comun.
}

// =========================================================================
// MARCAR CICLO IMPAR (BLOSSOM)
// =========================================================================
// Una vez que se encuentra el ancestro comun 'b', esta funcion recorre el camino
// de vuelta para "encoger" el ciclo impar (el Blossom) a un solo nodo.
void markPath(int v, int b, int x) {
    while (baseNode[v] != b) { // Mientras no lleguemos a la base (LCA)...
        // Marca el nodo 'v' y la pareja de 'v' como parte del Blossom.
        blossom[baseNode[v]] = blossom[baseNode[matchNode[v]]] = true;
        parentNode[v] = x; // Establece el padre de 'v' como 'x'.
        x = matchNode[v]; // 'x' toma el valor de la pareja de 'v'.
        v = parentNode[matchNode[v]]; // 'v' sube al padre de su pareja.
    }
}

// =========================================================================
// BUSCAR CAMINO AUMENTANTE (BFS modificado)
// =========================================================================
// Esta es una Busqueda en Amplitud (BFS) muy especial que tiene la logica para
// detectar y encoger los Blossoms (ciclos impares).
int findPath(int start) {
    // Inicializaciones: Prepara todas las listas para la nueva busqueda.
    for (int i = 0; i < n; ++i) used[i] = false;
    for (int i = 0; i < n; ++i) parentNode[i] = -1;
    for (int i = 0; i < n; ++i) baseNode[i] = i; // Al inicio, la base de cada nodo es el mismo.

    while (!q.empty()) q.pop(); // Vacia la cola.

    q.push(start); // Empieza la busqueda desde el nodo inicial.
    used[start] = true;

    while (!q.empty()) {
        int v = q.front(); q.pop(); // Toma el siguiente nodo de la cola.

        // Recorre todos los vecinos (conexiones) del nodo 'v'.
        for (int idx = 0; idx < (int)adj[v].size(); ++idx) {
            int u = adj[v][idx]; // 'u' es el vecino de 'v'.

            // Si 'v' y 'u' estan en la misma base o ya estan emparejados, ignoralos y continua.
            if (baseNode[v] == baseNode[u] || matchNode[v] == u)
                continue;

            // CASO 1: Se encontro una arista para formar un Blossom (ciclo impar).
            if (u == start ||
                (matchNode[u] != -1 && parentNode[matchNode[u]] != -1)) {

                int b = lca(v, u); // Encuentra la base comun (el punto de union del Blossom).
                for (int i = 0; i < n; ++i) blossom[i] = false; // Reinicia la marca de Blossom.
                markPath(v, b, u); // Marca y encoge el camino del Blossom desde 'v'.
                markPath(u, b, v); // Marca y encoge el camino del Blossom desde 'u'.

                // Actualiza todos los nodos que ahora son parte del Blossom encogido a la nueva base 'b'.
                for (int i = 0; i < n; ++i) {
                    if (blossom[baseNode[i]]) {
                        baseNode[i] = b; // El nuevo nodo base es 'b'.
                        if (!used[i]) {
                            used[i] = true;
                            q.push(i); // Agrega los nuevos nodos del Blossom a la cola para continuar la busqueda.
                        }
                    }
                }
            }
            // CASO 2: Se encontro una arista para continuar el camino aumentante (no es un Blossom).
            else if (parentNode[u] == -1) {
                parentNode[u] = v; // 'v' es el padre de 'u'.

                if (matchNode[u] == -1) // Si 'u' esta libre, ¡se encontro un camino aumentante!
                    return u; // Regresa 'u' para que se pueda hacer la nueva pareja.

                // Si 'u' tiene pareja, se continua la busqueda desde la pareja de 'u'.
                int next = matchNode[u];
                used[next] = true;
                q.push(next);
            }
        }
    }

    return -1; // No se encontro un camino aumentante desde el nodo de inicio.
}

// =========================================================================
// ALGORITMO DE EDMONDS (BLOSSOM)
// =========================================================================
// La funcion principal que ejecuta el Algoritmo de Edmonds.
int edmonds() {
    // Inicializa: Nadie tiene pareja al principio.
    for (int i = 0; i < n; ++i) matchNode[i] = -1;
    int matchCount = 0; // Contador de parejas.

    // Intenta encontrar un camino aumentante desde cada nodo.
    for (int i = 0; i < n; i++) {
        if (matchNode[i] == -1) { // Si el nodo 'i' esta libre...
            int v = findPath(i); // ...busca un camino que termine en un nodo libre 'v'.
            if (v != -1) { // Si se encontro el camino (v != -1)...
                // Se invierte el camino encontrado para crear el nuevo emparejamiento.
                while (v != -1) {
                    int pv = parentNode[v]; // Padre de 'v'.
                    int nv = matchNode[pv]; // Pareja del padre de 'v'.
                    matchNode[v] = pv; // 'v' se empareja con su padre.
                    matchNode[pv] = v; // El padre se empareja con 'v'.
                    v = nv; // Continua invirtiendo el resto del camino.
                }
                matchCount++; // Se cuenta la nueva pareja.
            }
        }
    }

    return matchCount; // Devuelve el numero total de parejas.
}

// =========================================================================
// MOSTRAR EMPAREJAMIENTOS
// =========================================================================
void mostrarMatching() {
    cout << "\nEmparejamientos encontrados:\n";
    // Muestra las parejas, asegurandose de no mostrarlas dos veces (solo si i < matchNode[i]).
    for (int i = 0; i < n; i++) {
        if (matchNode[i] != -1 && i < matchNode[i]) {
            cout << "Nodo " << i << " -- Nodo " << matchNode[i] << endl;
        }
    }
}

// =========================================================================
// MENU PRINCIPAL
// =========================================================================
void menu() {
    int op;

    do {
        // Bloque de texto del menu.
        cout << "\n==============================\n";
        cout << "    ALGORITMO DE EDMONDS\n";
        cout << "    MATCHING MAXIMO GENERAL\n";
        cout << "==============================\n";
        cout << "1. Ingresar grafo\n";
        cout << "2. Ejecutar algoritmo\n";
        cout << "3. Mostrar emparejamientos\n";
        cout << "4. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            // Opcion para ingresar el grafo.
            for (int i = 0; i < MAXN; i++)
                adj[i].clear(); // Limpia el grafo anterior.

            cout << "\nNumero de nodos: ";
            cin >> n;
            cout << "Numero de aristas: ";
            cin >> m;

            cout << "Ingresa las aristas (u v):\n";
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                // Validacion para que los nodos esten en el rango [0, n-1].
                if (u < 0 || u >= n || v < 0 || v >= n) {
                    cout << "[ERROR]: Vertices fuera de rango. Reingresa esta arista.\n";
                    i--;
                    continue;
                }
                adj[u].push_back(v); // Agrega la conexion u -> v.
                adj[v].push_back(u); // Agrega la conexion v -> u (es un grafo NO dirigido).
            }

            cout << "\nGrafo cargado correctamente.\n";
            break;

        case 2: {
            // Opcion para ejecutar el algoritmo.
            int resultado = edmonds();
            cout << "\nMatching maximo encontrado: " << resultado << endl;
            break;
        }

        case 3:
            // Opcion para mostrar los resultados.
            mostrarMatching();
            break;

        case 4:
            cout << "\nSaliendo del programa...\n";
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (op != 4);
}

// El programa inicia llamando al menu principal.
int main() {
    menu();
    return 0;
}
