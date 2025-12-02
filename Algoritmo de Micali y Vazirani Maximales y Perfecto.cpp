#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

// ---------- Configuracion global ----------
const int MAXN = 100;
int nNodos = 0;

// ========== Edmonds (Blossom) - 0-based implementation ==========
class MicaliVazirani {
private:
    int V;
    vector<vector<int> > adj;

    vector<int> match;    // match[v] = u or -1
    vector<int> p;        // parent in bfs
    vector<int> base;     // base of blossom
    vector<bool> used;    // used in bfs
    vector<bool> blossom; // blossom marks
    queue<int> Q;

    int lca(int a, int b) {
        vector<bool> used_path(V, false);
        while (true) {
            a = base[a];
            used_path[a] = true;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (used_path[b]) return b;
            if (match[b] == -1) break;
            b = p[match[b]];
        }
        return -1;
    }

    void mark_path(int v, int b, int children) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    }

    void contract(int v, int u) {
        int b = lca(v, u);
        // reset blossom flags
        for (int i = 0; i < V; ++i) blossom[i] = false;
        mark_path(v, b, u);
        mark_path(u, b, v);
        // set base of involved vertices to b
        for (int i = 0; i < V; ++i) {
            if (blossom[base[i]]) {
                base[i] = b;
                if (!used[i]) {
                    used[i] = true;
                    Q.push(i);
                }
            }
        }
    }

    bool bfs(int root) {
        used.assign(V, false);
        p.assign(V, -1);
        base.resize(V);
        for (int i = 0; i < V; ++i) base[i] = i;
        while (!Q.empty()) Q.pop();

        used[root] = true;
        Q.push(root);

        while (!Q.empty()) {
            int v = Q.front(); Q.pop();
            for (size_t i = 0; i < adj[v].size(); ++i) {
                int to = adj[v][i];
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                    contract(v, to);
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1) {
                        // augmenting path found: augment along path
                        int cur = to;
                        while (cur != -1) {
                            int prev = p[cur];
                            int next = -1;
                            if (prev != -1) next = match[prev];
                            match[cur] = prev;
                            if (prev != -1) match[prev] = cur;
                            cur = next;
                        }
                        return true;
                    } else {
                        if (!used[match[to]]) {
                            used[match[to]] = true;
                            Q.push(match[to]);
                        }
                    }
                }
            }
        }
        return false;
    }

public:
    MicaliVazirani(int n) : V(n) {
        adj.assign(V, vector<int>());
        match.assign(V, -1);
        p.assign(V, -1);
        base.assign(V, 0);
        used.assign(V, false);
        blossom.assign(V, false);
    }

    void load_graph(const vector<pair<int,int> >& edges) {
        adj.assign(V, vector<int>());
        for (size_t i = 0; i < edges.size(); ++i) {
            int u = edges[i].first;
            int v = edges[i].second;
            if (u < 0 || u >= V || v < 0 || v >= V) continue;
            adj[u].push_back(v);
        }
        match.assign(V, -1);
    }

    void addEdgeUndirected(int u, int v) {
        if (u < 0 || u >= V || v < 0 || v >= V) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxMatching() {
        int res = 0;
        // greedy init
        for (int v = 0; v < V; ++v) {
            if (match[v] == -1) {
                for (size_t i = 0; i < adj[v].size(); ++i) {
                    int to = adj[v][i];
                    if (match[to] == -1) {
                        match[v] = to;
                        match[to] = v;
                        ++res;
                        break;
                    }
                }
            }
        }

        while (true) {
            bool found = false;
            used.assign(V, false);
            p.assign(V, -1);
            base.resize(V);
            for (int i = 0; i < V; ++i) base[i] = i;
            blossom.assign(V, false);

            for (int v = 0; v < V; ++v) {
                if (match[v] == -1) {
                    if (bfs(v)) {
                        ++res;
                        found = true;
                        break; // restart after augmentation
                    }
                }
            }
            if (!found) break;
        }
        return res;
    }

    vector<pair<int,int> > getMatchingEdges() const {
        vector<pair<int,int> > edges;
        for (int i = 0; i < V; ++i) {
            if (match[i] != -1 && i < match[i]) {
                edges.push_back(make_pair(i, match[i]));
            }
        }
        return edges;
    }

    int countCoveredNodes() const {
        int covered = 0;
        for (int i = 0; i < V; ++i) {
            if (match[i] != -1) covered++;
        }
        return covered;
    }

    vector<vector<int> > getAdjMatrix() const {
        vector<vector<int> > M(V, vector<int>(V, 0));
        for (int u = 0; u < V; ++u) {
            for (size_t j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j];
                if (v >= 0 && v < V) M[u][v] = 1;
            }
        }
        return M;
    }

    // expose V for external use
    int getV() const { return V; }
};

// ========== Utilidades de impresion ==========
void imprimirMatriz(const vector<vector<int> >& M) {
    if (M.empty()) {
        cout << "(Matriz vacia)\n";
        return;
    }
    int n = (int)M.size();
    cout << "\nMatriz de adyacencia (" << n << " nodos, indices 0.." << (n-1) << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
}

void mostrarResultado(int res, MicaliVazirani& MV) {
    vector<pair<int,int> > matching = MV.getMatchingEdges();
    int covered = MV.countCoveredNodes();

    cout << "\n===============================================\n";
    cout << "  RESULTADO DEL EMPAREJAMIENTO (Edmonds / Blossom)\n";
    cout << "===============================================\n";
    cout << "  Tamano del pareo (maximo): " << res << "\n";
    cout << "-----------------------------------------------\n";

    cout << "  Aristas en el pareo (u -- v):\n";
    if (matching.empty()) {
        cout << "   (ninguna)\n";
    } else {
        for (size_t i = 0; i < matching.size(); ++i) {
            cout << "   (" << matching[i].first << " -- " << matching[i].second << ")\n";
        }
    }

    cout << "\n  Nodos totales: " << MV.getV() << "\n";
    cout << "  Nodos cubiertos por el pareo: " << covered << "\n";
    if (covered == MV.getV()) {
        cout << "  [LOGRADO] Pareo PERFECTO.\n";
    } else {
        cout << "  [NO PERFECTO] Quedaron " << (MV.getV() - covered) << " nodos libres.\n";
    }
    cout << "===============================================\n";
}

// ========== Menu interactivo ==========
void menu() {
    int op = -1;
    MicaliVazirani* MV = NULL;

    do {
        cout << "\n=======================================\n";
        cout << " MICALI-VAZIRANI / EDMONDS (0-based)\n";
        cout << "=======================================\n";
        cout << "1. Ingresar grafo manual (0-based)\n";
        cout << "2. Ejecutar algoritmo (max matching)\n";
        cout << "3. Mostrar resultados del emparejamiento\n";
        cout << "4. Mostrar matriz de adyacencia (si hay grafo)\n";
        cout << "5. Cargar grafo NO dirigido y NO ponderado (predefinido de 5 nodos)\n";
        cout << "6. Eliminar grafo\n";
        cout << "0. Salir\n";
        cout << "Elige opcion: ";
        if (!(cin >> op)) {
            cout << "[ERROR] Entrada invalida.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = -1;
            continue;
        }

        switch (op) {
        case 1: {
            // Ingresar grafo manual (0-based)
            int n;
            cout << "Numero de nodos (max " << MAXN << "): ";
            cin >> n;
            if (n <= 0 || n > MAXN) {
                cout << "[ERROR] Numero de nodos invalido.\n";
                break;
            }
            nNodos = n;
            int m;
            cout << "Numero de aristas: ";
            cin >> m;
            vector<pair<int,int> > edges;
            cout << "Ingresa aristas (u v) con nodos 0.." << (n-1) << " (una por linea):\n";
            for (int i = 0; i < m; ++i) {
                int u,v;
                cin >> u >> v;
                if (u < 0 || u >= n || v < 0 || v >= n) {
                    cout << "[ERROR] Arista invalida ignorada: " << u << " " << v << "\n";
                    continue;
                }
                // For undirected usage, we will add both directions later if desired;
                // Here we store a single directed pair (user can input either).
                edges.push_back(make_pair(u,v));
            }
            if (MV) { delete MV; MV = NULL; }
            MV = new MicaliVazirani(nNodos);
            MV->load_graph(edges);
            cout << "[OK] Grafo manual cargado (0-based).\n";
            break;
        }

        case 2: {
            if (!MV) {
                cout << "[ERROR] No hay grafo cargado.\n";
                break;
            }
            cout << "[INFO] Ejecutando algoritmo para emparejamiento maximo...\n";
            int result = MV->maxMatching();
            cout << "[OK] Tamano del pareo maximo encontrado: " << result << "\n";
            break;
        }

        case 3: {
            if (!MV) {
                cout << "[ERROR] No hay grafo cargado.\n";
                break;
            }
            // compute matching size by calling maxMatching? We assume user ran option 2.
            // But we can call getMatchingEdges and countCoveredNodes.
            vector<pair<int,int> > matching = MV->getMatchingEdges();
            int covered = MV->countCoveredNodes();
            cout << "\n--- Resultado actual (segun estado interno) ---\n";
            cout << "Tamano pareo (en aristas): " << matching.size() << "\n";
            for (size_t i = 0; i < matching.size(); ++i) {
                cout << " (" << matching[i].first << " -- " << matching[i].second << ")\n";
            }
            cout << "Nodos cubiertos: " << covered << " / " << MV->getV() << "\n";
            break;
        }

        case 4: {
            if (!MV) {
                cout << "[ERROR] No hay grafo cargado.\n";
                break;
            }
            vector<vector<int> > M = MV->getAdjMatrix();
            imprimirMatriz(M);
            break;
        }

        case 5: {
            // Cargar el grafo predefinido (0-based), no dirigido: añadimos cada arista en ambas direcciones.
            if (MV) { delete MV; MV = NULL; }
            nNodos = 5;
            MV = new MicaliVazirani(nNodos);

            // Lista original (segun tu entrada). We'll add only unique undirected edges,
            // but since addEdgeUndirected adds both directions, just call it with pairs.
            // Your original edges included duplicates (u->v and v->u); we use set-like behaviour.
            // We'll add the undirected edges (unique) corresponding to the connections:
            // 0-1, 0-4, 0-3, 1-3, 1-2, 2-3  (these cover the list you provided)
            MV->addEdgeUndirected(0, 1);
            MV->addEdgeUndirected(0, 4);
            MV->addEdgeUndirected(0, 3);
            MV->addEdgeUndirected(1, 3);
            MV->addEdgeUndirected(1, 2);
            MV->addEdgeUndirected(2, 3);
            // Note: edges like 3-0 etc are redundant because undirected additions already added them.

            cout << "[OK] Grafo predefinido cargado (5 nodos, 0-based).\n";

            vector<vector<int> > Mat = MV->getAdjMatrix();
            imprimirMatriz(Mat);
            break;
        }

        case 6: {
            if (MV) {
                delete MV;
                MV = NULL;
                nNodos = 0;
                cout << "[OK] Grafo eliminado.\n";
            } else {
                cout << "No hay grafo para eliminar.\n";
            }
            break;
        }

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "[ERROR] Opcion invalida.\n";
        }

    } while (op != 0);

    if (MV) delete MV;
}

// ========== main ==========
int main() {
    menu();
    return 0;
}
