#include <iostream>   // Herramienta para hablar con el usuario (mostrar mensajes y pedir datos).
#include <vector>     // Permite crear listas o tablas flexibles.
#include <queue>      // Una herramienta especial para guardar elementos en orden de llegada (como una cola de supermercado). Es clave para la funcion BFS.
#include <climits>    // Nos da el numero mas grande posible (INT_MAX), usado aqui como un valor para "infinito" (INF).

using namespace std; // Para escribir 'cout' y 'cin' en lugar de 'std::cout' y 'std::cin'.

// Define dos valores especiales que se usan en el algoritmo:
int NIL = 0;   // Representa un nodo "nulo" o que no esta emparejado.
int INF = INT_MAX; // Representa una distancia "infinita" (muy, muy lejos).

// ============================
// MOSTRAR TITULO
// ============================
// Esta funcion solo muestra el titulo y la descripcion del programa.
void mostrarTitulo() {
    // Bloque de texto que se muestra al usuario sin modificar.
    cout << "\n============================================================\n";
    cout << "     ALGORITMO DE HOPCROFT-KARP - MATCHING MAXIMO\n";
    cout << "============================================================\n";
    cout << "[NOTA]: Este algoritmo SOLO funciona con grafos bipartitos\n";
    cout << "       no dirigidos y NO PONDERADOS.\n";
    cout << "------------------------------------------------------------\n";
}

// ============================
// BFS (Busqueda en Amplitud)
// ============================
// El BFS es la primera parte del algoritmo. Su trabajo es encontrar los caminos mas cortos
// que pueden usarse para aumentar el numero de parejas.
bool bfs(vector< vector<int> >& adj, vector<int>& dist,
          vector<int>& pairU, vector<int>& pairV, int n) {

    queue<int> q; // La "cola" de nodos por visitar.

    // 1. Inicializa:
    for (int u = 1; u <= n; u++) {
        if (pairU[u] == NIL) { // Si el nodo 'u' no tiene pareja...
            dist[u] = 0; // ...su distancia es 0 (es el inicio del camino).
            q.push(u);   // ...y se agrega a la cola para empezar a buscar.
        } else {
            dist[u] = INF; // Si ya tiene pareja, la distancia es "infinita" por ahora.
        }
    }

    dist[NIL] = INF; // El nodo nulo tambien tiene distancia infinita.

    // 2. Procesa la cola:
    while (!q.empty()) {
        int u = q.front(); // Toma el nodo al inicio de la cola.
        q.pop();           // Lo quita de la cola.

        // Si la distancia al nodo 'u' no es infinita (es decir, es un nodo alcanzable en este nivel)...
        if (dist[u] < dist[NIL]) {
            // Recorre todos los vecinos (conexiones) del nodo 'u'.
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                // Verifica la pareja del vecino: si la pareja del vecino 'v' (pairV[v])
                // tiene distancia infinita, significa que su camino no ha sido explorado todavía.
                if (dist[pairV[v]] == INF) {
                    // Actualiza la distancia: la pareja de 'v' esta un paso mas alla que 'u'.
                    dist[pairV[v]] = dist[u] + 1;
                    // Agrega la pareja de 'v' a la cola.
                    q.push(pairV[v]);
                }
            }
        }
    }

    // Devuelve verdadero si el nodo nulo (NIL) tiene una distancia definida (no infinita).
    // Esto significa que se encontro al menos un camino aumentante (un camino para hacer una nueva pareja).
    return (dist[NIL] != INF);
}

// ============================
// DFS (Busqueda en Profundidad)
// ============================
// El DFS se usa despues del BFS. Su trabajo es seguir los caminos mas cortos
// encontrados por el BFS para realmente formar las nuevas parejas.
bool dfs(int u, vector< vector<int> >& adj, vector<int>& dist,
          vector<int>& pairU, vector<int>& pairV) {

    if (u != NIL) { // Si el nodo actual no es el nodo nulo (si es un nodo real)...
        // Recorre todos los vecinos del nodo 'u'.
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            // Condicion clave: Solo sigue el camino si es el camino mas corto (dist[pairV[v]] == dist[u] + 1)
            // Y si la llamada recursiva (dfs) tambien encuentra una ruta hasta el final.
            if (dist[pairV[v]] == dist[u] + 1 &&
                dfs(pairV[v], adj, dist, pairU, pairV)) {

                // ¡Exito! Se encontro y se uso un camino aumentante.
                // Se actualizan las parejas:
                pairU[u] = v; // 'u' se empareja con 'v'.
                pairV[v] = u; // 'v' se empareja con 'u'.
                return true; // Devuelve verdadero para que el camino anterior sepa que tuvo exito.
            }
        }

        dist[u] = INF; // Si no se encuentra un camino a traves de 'u', su distancia se marca como infinita.
        return false;  // Devuelve falso, no se pudo formar una pareja a traves de este nodo.
    }
    return true; // Base de la recursion: si llegamos al nodo nulo, el camino fue exitoso.
}

// ============================
// HOPCROFT–KARP
// ============================
// La funcion principal que orquesta el algoritmo.
// Recibe la lista de adyacencia (adj) y el numero de nodos de cada lado (n y m).
int hopcroftKarp(vector< vector<int> >& adj, int n, int m) {

    // pairU[u]: Guarda la pareja del nodo 'u' (del lado izquierdo).
    // pairV[v]: Guarda la pareja del nodo 'v' (del lado derecho).
    // dist: La lista de distancias generada por el BFS.
    vector<int> pairU(n + 1, NIL);
    vector<int> pairV(m + 1, NIL);
    vector<int> dist(n + 1);

    int result = 0; // Aqui se guarda el numero total de parejas encontradas.

    // El corazon del algoritmo: repite mientras el BFS encuentre caminos aumentantes.
    while (bfs(adj, dist, pairU, pairV, n)) {
        // Para todos los nodos libres del lado izquierdo...
        for (int u = 1; u <= n; u++) {
            // ...si 'u' no tiene pareja (pairU[u] == NIL)...
            // ...y el DFS logra formar una nueva pareja a traves de 'u'...
            if (pairU[u] == NIL && dfs(u, adj, dist, pairU, pairV)) {
                result++; // ...entonces se incrementa el contador de parejas (el Matching Maximo).
            }
        }
    }

    return result; // Devuelve el numero final de parejas.
}

// ============================
// PROGRAMA PRINCIPAL
// ============================
// Aqui es donde el programa interactua con el usuario.
int main() {

    mostrarTitulo();

    int n, m, e; // n: nodos lado A; m: nodos lado B; e: numero de conexiones (aristas).

    cout << "Ingrese el numero de nodos del lado izquierdo (A): ";
    cin >> n;

    cout << "Ingrese el numero de nodos del lado derecho (B): ";
    cin >> m;

    cout << "Ingrese el numero de aristas: ";
    cin >> e;

    // Crea la estructura para guardar las conexiones (lista de adyacencia).
    // adj[u] sera una lista de todos los nodos del lado B a los que esta conectado el nodo 'u' del lado A.
    vector< vector<int> > adj(n + 1);

    cout << "\n============================================================\n";
    cout << "                 INGRESO DE ARISTAS\n";
    cout << "============================================================\n";
    cout << "Formato: u v   (u en A, v en B)\n";

    // Pide al usuario que ingrese las conexiones.
    for (int i = 0; i < e; i++) {
        int u, v;
        cout << "Arista " << i + 1 << ": ";
        cin >> u >> v;

        // Validacion simple para asegurar que los numeros ingresados esten dentro del rango de nodos.
        if (u < 1 || u > n || v < 1 || v > m) {
            cout << "[ERROR]: Vertices fuera de rango. Reingrese.\n";
            i--; // Decrementa 'i' para repetir el ingreso de esta arista.
        } else {
            // Guarda la conexion: el nodo 'u' esta conectado al nodo 'v'.
            adj[u].push_back(v);
        }
    }

    cout << "\n============================================================\n";
    cout << "                 PROCESANDO ALGORITMO\n";
    cout << "============================================================\n";

    // Llama a la funcion principal para calcular el Pareo Maximo.
    int matchingMax = hopcroftKarp(adj, n, m);

    cout << "\n============================================================\n";
    cout << "                 RESULTADO FINAL\n";
    cout << "============================================================\n";
    // Muestra el numero total de parejas encontradas.
    cout << "[MATCHING MAXIMO]: " << matchingMax << endl;
    cout << "============================================================\n";

    return 0; // El programa termina.
}
