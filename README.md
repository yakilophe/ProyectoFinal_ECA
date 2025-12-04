# Algoritmos de Emparejamiento Perfecto y Maximal

## Introducción
Emparejamiento perfecto cubre todos los vértices del grafo. Los algoritmos especializados buscan encontrar estos emparejamientos de manera eficiente en diferentes tipos de grafos.

## 1. Clasificación de Algoritmos

### Por Tipo de Emparejamiento:
```
1. Emparejamiento Perfecto:
   - Edmonds (Blossom Algorithm) - General
   - Micali-Vazirani - General optimizado
   - Hopcroft-Karp - Bipartito
   - Kuhn - Bipartito

2. Emparejamiento Maximal:
   - Greedy (Codicioso) - General
   - Heurístico Aleatorio - General
```

## 2. Algoritmo de Edmonds (Blossom) para Emparejamiento Perfecto

### Concepto
Extensión del algoritmo de Edmonds para encontrar emparejamientos perfectos en grafos generales.

```cpp
// src/Algoritmo_Edmonds_PerfectoMaximal_Blossom.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class EdmondsPerfecto {
private:
    int n;
    vector<vector<int>> grafo;
    vector<int> pareja, padre, base, estado;
    vector<bool> enBlossom;
    queue<int> q;
    
    int encontrarBase(int x) {
        while (base[x] != x) x = base[x];
        return x;
    }
    
    int LCA(int a, int b) {
        vector<bool> visitado(n, false);
        while (true) {
            a = encontrarBase(a);
            visitado[a] = true;
            if (pareja[a] == -1) break;
            a = padre[pareja[a]];
        }
        
        while (true) {
            b = encontrarBase(b);
            if (visitado[b]) return b;
            b = padre[pareja[b]];
        }
        return -1;
    }
    
    void marcarRuta(int v, int b, int hijo) {
        while (encontrarBase(v) != b) {
            enBlossom[encontrarBase(v)] = true;
            enBlossom[encontrarBase(pareja[v])] = true;
            padre[v] = hijo;
            hijo = pareja[v];
            v = padre[hijo];
        }
    }
    
    void contraer(int a, int b) {
        int blossomBase = LCA(a, b);
        fill(enBlossom.begin(), enBlossom.end(), false);
        
        marcarRuta(a, blossomBase, b);
        marcarRuta(b, blossomBase, a);
        
        for (int i = 0; i < n; i++) {
            if (enBlossom[encontrarBase(i)]) {
                base[i] = blossomBase;
                if (estado[i] == 0) {
                    estado[i] = 1;
                    q.push(i);
                }
            }
        }
    }
    
    bool BFS(int inicio) {
        for (int i = 0; i < n; i++) {
            padre[i] = -1;
            estado[i] = -1;
            base[i] = i;
        }
        
        while (!q.empty()) q.pop();
        
        q.push(inicio);
        estado[inicio] = 0;
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            
            for (int u : grafo[v]) {
                if (estado[u] == -1) {
                    if (pareja[u] == -1) {
                        // Emparejar
                        pareja[u] = v;
                        int w = v;
                        while (w != -1) {
                            int temp = pareja[w];
                            pareja[w] = u;
                            u = temp;
                            w = padre[u];
                        }
                        return true;
                    } else {
                        padre[u] = v;
                        estado[u] = 1;
                        estado[pareja[u]] = 0;
                        q.push(pareja[u]);
                    }
                } else if (estado[u] == 0 && encontrarBase(v) != encontrarBase(u)) {
                    // Encontrar blossom
                    contraer(v, u);
                }
            }
        }
        return false;
    }
    
public:
    EdmondsPerfecto(int _n) : n(_n) {
        grafo.resize(n);
        pareja.assign(n, -1);
        padre.resize(n);
        base.resize(n);
        estado.resize(n);
        enBlossom.resize(n, false);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    vector<pair<int, int>> encontrarEmparejamientoPerfecto() {
        // Verificar si existe emparejamiento perfecto
        if (n % 2 != 0) return {};
        
        // Intentar emparejar cada vértice
        for (int i = 0; i < n; i++) {
            if (pareja[i] == -1) {
                if (!BFS(i)) {
                    return {}; // No existe emparejamiento perfecto
                }
            }
        }
        
        // Reconstruir emparejamiento
        vector<pair<int, int>> resultado;
        for (int i = 0; i < n; i++) {
            if (pareja[i] != -1 && i < pareja[i]) {
                resultado.push_back({i, pareja[i]});
            }
        }
        
        return resultado;
    }
    
    bool existeEmparejamientoPerfecto() {
        auto matching = encontrarEmparejamientoPerfecto();
        return matching.size() * 2 == n;
    }
    
    // Encontrar máximo emparejamiento
    vector<pair<int, int>> encontrarMaxEmparejamiento() {
        for (int i = 0; i < n; i++) {
            if (pareja[i] == -1) {
                BFS(i);
            }
        }
        
        vector<pair<int, int>> resultado;
        for (int i = 0; i < n; i++) {
            if (pareja[i] != -1 && i < pareja[i]) {
                resultado.push_back({i, pareja[i]});
            }
        }
        return resultado;
    }
};
```

## 3. Algoritmo de Micali-Vazirani

### Concepto
Optimización del algoritmo de emparejamiento para grafos generales con complejidad O(√V E).

```cpp
// src/Algoritmo_MicaliVazirani_MaximalesPerfecto.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

class MicaliVazirani {
private:
    int n;
    vector<vector<int>> grafo;
    vector<int> nivel, pareja, padre;
    vector<bool> activo, emparejado;
    
    struct Blossom {
        int base;
        vector<int> vertices;
    };
    
    void inicializar() {
        nivel.assign(n, -1);
        pareja.assign(n, -1);
        padre.assign(n, -1);
        activo.assign(n, true);
        emparejado.assign(n, false);
    }
    
    void BFSFases(vector<int>& fuentes) {
        queue<int> q;
        for (int s : fuentes) {
            if (activo[s] && !emparejado[s]) {
                nivel[s] = 0;
                q.push(s);
            }
        }
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            
            for (int u : grafo[v]) {
                if (activo[u] && nivel[u] == -1) {
                    if (emparejado[u]) {
                        nivel[u] = nivel[v] + 1;
                        padre[u] = v;
                        int w = pareja[u];
                        nivel[w] = nivel[u] + 1;
                        padre[w] = u;
                        q.push(w);
                    } else {
                        // Camino aumentante encontrado
                        aumentarCamino(v, u);
                        return;
                    }
                }
            }
        }
    }
    
    void aumentarCamino(int v, int u) {
        vector<int> camino;
        camino.push_back(u);
        
        int actual = v;
        while (actual != -1) {
            camino.push_back(actual);
            actual = padre[actual];
        }
        
        reverse(camino.begin(), camino.end());
        
        // Aplicar emparejamiento alternante
        for (size_t i = 0; i < camino.size(); i += 2) {
            int a = camino[i];
            int b = camino[i + 1];
            pareja[a] = b;
            pareja[b] = a;
            emparejado[a] = emparejado[b] = true;
        }
    }
    
    Blossom encontrarBlossom(int a, int b) {
        vector<bool> visitado(n, false);
        vector<int> caminoA, caminoB;
        
        // Reconstruir caminos a la raíz
        int x = a;
        while (x != -1) {
            caminoA.push_back(x);
            visitado[x] = true;
            if (!emparejado[x]) break;
            x = padre[pareja[x]];
        }
        
        x = b;
        while (x != -1 && !visitado[x]) {
            caminoB.push_back(x);
            x = padre[pareja[x]];
        }
        
        // Encontrar base del blossom
        int base = x;
        Blossom blossom;
        blossom.base = base;
        
        // Agregar vértices del blossom
        for (int v : caminoA) {
            blossom.vertices.push_back(v);
            if (v == base) break;
        }
        
        for (auto it = caminoB.rbegin(); it != caminoB.rend(); ++it) {
            blossom.vertices.push_back(*it);
        }
        
        return blossom;
    }
    
    void contraerBlossom(const Blossom& blossom) {
        int base = blossom.base;
        
        // Marcar vértices del blossom como inactivos
        for (int v : blossom.vertices) {
            if (v != base) {
                activo[v] = false;
                // Redirigir aristas al base
                for (int u : grafo[v]) {
                    if (activo[u]) {
                        grafo[base].push_back(u);
                        grafo[u].push_back(base);
                    }
                }
            }
        }
    }
    
public:
    MicaliVazirani(int _n) : n(_n) {
        grafo.resize(n);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    vector<pair<int, int>> encontrarMaxEmparejamiento() {
        inicializar();
        
        int maxFases = sqrt(n);
        for (int fase = 0; fase < maxFases; fase++) {
            // Seleccionar fuentes no emparejadas
            vector<int> fuentes;
            for (int i = 0; i < n; i++) {
                if (activo[i] && !emparejado[i]) {
                    fuentes.push_back(i);
                }
            }
            
            if (fuentes.empty()) break;
            
            BFSFases(fuentes);
            
            // Buscar y contraer blossoms
            for (int i = 0; i < n; i++) {
                for (int j : grafo[i]) {
                    if (i < j && nivel[i] % 2 == 0 && nivel[j] % 2 == 0) {
                        Blossom blossom = encontrarBlossom(i, j);
                        contraerBlossom(blossom);
                    }
                }
            }
        }
        
        // Reconstruir emparejamiento
        vector<pair<int, int>> resultado;
        for (int i = 0; i < n; i++) {
            if (pareja[i] != -1 && i < pareja[i]) {
                resultado.push_back({i, pareja[i]});
            }
        }
        
        return resultado;
    }
    
    bool esPerfecto() {
        auto matching = encontrarMaxEmparejamiento();
        return matching.size() * 2 == n;
    }
};
```

## 4. Algoritmo de Hopcroft-Karp para Bipartitos

### Concepto
Versión especializada para emparejamiento perfecto en grafos bipartitos.

```cpp
// src/Algoritmo_Hopcroft-Karp.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class HopcroftKarpPerfecto {
private:
    int U, V;
    vector<vector<int>> grafo;
    vector<int> parejaU, parejaV, distancia;
    const int INF = 1e9;
    
public:
    HopcroftKarpPerfecto(int u, int v) : U(u), V(v) {
        grafo.resize(U);
        parejaU.assign(U, -1);
        parejaV.assign(V, -1);
        distancia.resize(U);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
    }
    
    bool BFS() {
        queue<int> q;
        
        for (int u = 0; u < U; u++) {
            if (parejaU[u] == -1) {
                distancia[u] = 0;
                q.push(u);
            } else {
                distancia[u] = INF;
            }
        }
        
        bool encontrado = false;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : grafo[u]) {
                if (parejaV[v] != -1) {
                    if (distancia[parejaV[v]] == INF) {
                        distancia[parejaV[v]] = distancia[u] + 1;
                        q.push(parejaV[v]);
                    }
                } else {
                    encontrado = true;
                }
            }
        }
        
        return encontrado;
    }
    
    bool DFS(int u) {
        for (int v : grafo[u]) {
            if (parejaV[v] == -1 || 
                (distancia[parejaV[v]] == distancia[u] + 1 && 
                 DFS(parejaV[v]))) {
                parejaU[u] = v;
                parejaV[v] = u;
                return true;
            }
        }
        distancia[u] = INF;
        return false;
    }
    
    vector<pair<int, int>> encontrarPerfecto() {
        // Verificar condición necesaria
        if (U != V) return {};
        
        int matching = 0;
        
        while (BFS()) {
            for (int u = 0; u < U; u++) {
                if (parejaU[u] == -1 && DFS(u)) {
                    matching++;
                }
            }
        }
        
        // Verificar si es perfecto
        if (matching != U) return {};
        
        vector<pair<int, int>> resultado;
        for (int u = 0; u < U; u++) {
            resultado.push_back({u, parejaU[u]});
        }
        
        return resultado;
    }
    
    vector<pair<int, int>> encontrarMax() {
        int matching = 0;
        
        while (BFS()) {
            for (int u = 0; u < U; u++) {
                if (parejaU[u] == -1 && DFS(u)) {
                    matching++;
                }
            }
        }
        
        vector<pair<int, int>> resultado;
        for (int u = 0; u < U; u++) {
            if (parejaU[u] != -1) {
                resultado.push_back({u, parejaU[u]});
            }
        }
        
        return resultado;
    }
};
```

## 5. Algoritmo de Kuhn (Alternativo para Bipartitos)

```cpp
// src/Algoritmo_Kuhn_PareoMáximoMaximalPerfecto_Bipartitos.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class KuhnBipartito {
private:
    int U, V;
    vector<vector<int>> grafo;
    vector<int> parejaU, parejaV;
    vector<bool> visitado;
    
    bool DFS(int u) {
        if (visitado[u]) return false;
        visitado[u] = true;
        
        for (int v : grafo[u]) {
            if (parejaV[v] == -1 || DFS(parejaV[v])) {
                parejaU[u] = v;
                parejaV[v] = u;
                return true;
            }
        }
        return false;
    }
    
public:
    KuhnBipartito(int u, int v) : U(u), V(v) {
        grafo.resize(U);
        parejaU.assign(U, -1);
        parejaV.assign(V, -1);
        visitado.resize(U);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
    }
    
    vector<pair<int, int>> encontrarMax() {
        // Heurística: ordenar por grado
        vector<int> orden(U);
        for (int i = 0; i < U; i++) orden[i] = i;
        
        sort(orden.begin(), orden.end(), [&](int a, int b) {
            return grafo[a].size() < grafo[b].size();
        });
        
        for (int u : orden) {
            if (parejaU[u] == -1) {
                fill(visitado.begin(), visitado.end(), false);
                DFS(u);
            }
        }
        
        vector<pair<int, int>> resultado;
        for (int u = 0; u < U; u++) {
            if (parejaU[u] != -1) {
                resultado.push_back({u, parejaU[u]});
            }
        }
        
        return resultado;
    }
    
    vector<pair<int, int>> encontrarPerfecto() {
        auto matching = encontrarMax();
        if (matching.size() * 2 != U + V) return {};
        return matching;
    }
    
    // Versión optimizada con heurística greedy inicial
    vector<pair<int, int>> encontrarMaxOptimizado() {
        // Paso 1: Greedy matching inicial
        vector<bool> usadoV(V, false);
        
        for (int u = 0; u < U; u++) {
            for (int v : grafo[u]) {
                if (!usadoV[v]) {
                    parejaU[u] = v;
                    parejaV[v] = u;
                    usadoV[v] = true;
                    break;
                }
            }
        }
        
        // Paso 2: Aumentar con DFS
        for (int u = 0; u < U; u++) {
            if (parejaU[u] == -1) {
                fill(visitado.begin(), visitado.end(), false);
                DFS(u);
            }
        }
        
        vector<pair<int, int>> resultado;
        for (int u = 0; u < U; u++) {
            if (parejaU[u] != -1) {
                resultado.push_back({u, parejaU[u]});
            }
        }
        
        return resultado;
    }
};
```

## 6. Algoritmo Greedy para Emparejamiento Maximal Perfecto

```cpp
// src/Algoritmo_Emparejamiento_Greddy_MaximalPerfecto.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class GreedyMaximalPerfecto {
private:
    int n;
    vector<vector<int>> grafo;
    mt19937 rng;
    
public:
    GreedyMaximalPerfecto(int _n) : n(_n), rng(random_device{}()) {
        grafo.resize(n);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    // Greedy determinístico
    vector<pair<int, int>> greedyDeterministico() {
        vector<bool> cubierto(n, false);
        vector<pair<int, int>> matching;
        
        // Ordenar vértices por grado (heurística)
        vector<int> vertices(n);
        for (int i = 0; i < n; i++) vertices[i] = i;
        
        sort(vertices.begin(), vertices.end(), [&](int a, int b) {
            return grafo[a].size() < grafo[b].size();
        });
        
        for (int u : vertices) {
            if (!cubierto[u]) {
                // Buscar vecino no cubierto
                for (int v : grafo[u]) {
                    if (!cubierto[v]) {
                        matching.push_back({u, v});
                        cubierto[u] = cubierto[v] = true;
                        break;
                    }
                }
            }
        }
        
        return matching;
    }
    
    // Greedy aleatorizado
    vector<pair<int, int>> greedyAleatorizado(int iteraciones = 10) {
        vector<pair<int, int>> mejorMatching;
        
        for (int it = 0; it < iteraciones; it++) {
            vector<bool> cubierto(n, false);
            vector<pair<int, int>> matching;
            vector<int> vertices(n);
            
            for (int i = 0; i < n; i++) vertices[i] = i;
            shuffle(vertices.begin(), vertices.end(), rng);
            
            for (int u : vertices) {
                if (!cubierto[u]) {
                    // Buscar vecinos no cubiertos
                    vector<int> candidatos;
                    for (int v : grafo[u]) {
                        if (!cubierto[v]) {
                            candidatos.push_back(v);
                        }
                    }
                    
                    if (!candidatos.empty()) {
                        uniform_int_distribution<int> dist(0, candidatos.size() - 1);
                        int v = candidatos[dist(rng)];
                        matching.push_back({u, v});
                        cubierto[u] = cubierto[v] = true;
                    }
                }
            }
            
            if (matching.size() > mejorMatching.size()) {
                mejorMatching = matching;
            }
        }
        
        return mejorMatching;
    }
    
    // Intentar hacerlo perfecto (si es posible)
    vector<pair<int, int>> greedyPerfecto() {
        auto matching = greedyAleatorizado(20);
        
        if (matching.size() * 2 == n) {
            return matching; // Ya es perfecto
        }
        
        // Intentar mejorar
        vector<bool> cubierto(n, false);
        for (auto& [u, v] : matching) {
            cubierto[u] = cubierto[v] = true;
        }
        
        // Buscar vértices no cubiertos
        for (int u = 0; u < n; u++) {
            if (!cubierto[u]) {
                for (int v : grafo[u]) {
                    if (!cubierto[v]) {
                        // Podríamos agregar esta arista
                        matching.push_back({u, v});
                        cubierto[u] = cubierto[v] = true;
                        break;
                    }
                }
            }
        }
        
        return matching;
    }
};
```

## 7. Algoritmo Heurístico Codicioso Aleatorio

```cpp
// src/Algoritmo_HeurísticoCodiciosoAleatorio.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

class HeuristicoCodiciosoAleatorio {
private:
    int n;
    vector<vector<int>> grafo;
    mt19937 rng;
    
public:
    HeuristicoCodiciosoAleatorio(int _n) : n(_n), 
        rng(chrono::steady_clock::now().time_since_epoch().count()) {
        grafo.resize(n);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    // Heurística 1: Selección aleatoria adaptativa
    vector<pair<int, int>> heuristicaAdaptativa() {
        vector<bool> disponible(n, true);
        vector<pair<int, int>> matching;
        
        while (true) {
            // Seleccionar vértice aleatorio disponible
            vector<int> disponibles;
            for (int i = 0; i < n; i++) {
                if (disponible[i]) disponibles.push_back(i);
            }
            
            if (disponibles.empty()) break;
            
            uniform_int_distribution<int> dist(0, disponibles.size() - 1);
            int u = disponibles[dist(rng)];
            
            // Buscar vecino disponible
            vector<int> vecinosDisponibles;
            for (int v : grafo[u]) {
                if (disponible[v]) vecinosDisponibles.push_back(v);
            }
            
            if (!vecinosDisponibles.empty()) {
                uniform_int_distribution<int> dist2(0, vecinosDisponibles.size() - 1);
                int v = vecinosDisponibles[dist2(rng)];
                
                matching.push_back({u, v});
                disponible[u] = disponible[v] = false;
            } else {
                disponible[u] = false; // Vértice aislado en este momento
            }
        }
        
        return matching;
    }
    
    // Heurística 2: Basada en grados dinámicos
    vector<pair<int, int>> heuristicaGradosDinamicos() {
        vector<bool> disponible(n, true);
        vector<int> gradoDinamico(n);
        vector<pair<int, int>> matching;
        
        // Calcular grados iniciales
        for (int i = 0; i < n; i++) {
            gradoDinamico[i] = grafo[i].size();
        }
        
        while (true) {
            // Seleccionar vértice con mínimo grado dinámico
            int u = -1;
            int minGrado = n + 1;
            
            for (int i = 0; i < n; i++) {
                if (disponible[i] && gradoDinamico[i] < minGrado) {
                    minGrado = gradoDinamico[i];
                    u = i;
                }
            }
            
            if (u == -1) break;
            
            // Buscar mejor vecino (también con grado bajo)
            int mejorVecino = -1;
            int mejorGrado = n + 1;
            
            for (int v : grafo[u]) {
                if (disponible[v] && gradoDinamico[v] < mejorGrado) {
                    mejorGrado = gradoDinamico[v];
                    mejorVecino = v;
                }
            }
            
            if (mejorVecino != -1) {
                matching.push_back({u, mejorVecino});
                disponible[u] = disponible[mejorVecino] = false;
                
                // Actualizar grados dinámicos de vecinos
                for (int w : grafo[u]) {
                    if (disponible[w]) gradoDinamico[w]--;
                }
                for (int w : grafo[mejorVecino]) {
                    if (disponible[w]) gradoDinamico[w]--;
                }
            } else {
                disponible[u] = false;
            }
        }
        
        return matching;
    }
    
    // Heurística 3: Búsqueda local
    vector<pair<int, int>> busquedaLocal(const vector<pair<int, int>>& matchingInicial, 
                                         int iteraciones = 100) {
        vector<pair<int, int>> mejorMatching = matchingInicial;
        int mejorTamano = mejorMatching.size();
        
        for (int it = 0; it < iteraciones; it++) {
            // Crear copia para modificar
            vector<pair<int, int>> actual = mejorMatching;
            
            // Intentar intercambio aleatorio
            if (actual.size() >= 2) {
                uniform_int_distribution<int> dist(0, actual.size() - 1);
                int i = dist(rng);
                int j = dist(rng);
                
                if (i != j) {
                    auto [a, b] = actual[i];
                    auto [c, d] = actual[j];
                    
                    // Verificar si podemos intercambiar
                    if (find(grafo[a].begin(), grafo[a].end(), d) != grafo[a].end() &&
                        find(grafo[c].begin(), grafo[c].end(), b) != grafo[c].end()) {
                        // Intercambiar
                        actual[i] = {a, d};
                        actual[j] = {c, b};
                        
                        // Verificar si podemos agregar nueva arista
                        for (int u = 0; u < n; u++) {
                            bool cubierto = false;
                            for (auto& [x, y] : actual) {
                                if (u == x || u == y) {
                                    cubierto = true;
                                    break;
                                }
                            }
                            
                            if (!cubierto) {
                                for (int v : grafo[u]) {
                                    bool vCubierto = false;
                                    for (auto& [x, y] : actual) {
                                        if (v == x || v == y) {
                                            vCubierto = true;
                                            break;
                                        }
                                    }
                                    
                                    if (!vCubierto) {
                                        actual.push_back({u, v});
                                        break;
                                    }
                                }
                            }
                        }
                        
                        if (actual.size() > mejorTamano) {
                            mejorMatching = actual;
                            mejorTamano = actual.size();
                        }
                    }
                }
            }
        }
        
        return mejorMatching;
    }
    
    // Heurística combinada
    vector<pair<int, int>> heuristicaCombinada() {
        // Paso 1: Heurística adaptativa
        auto matching1 = heuristicaAdaptativa();
        
        // Paso 2: Búsqueda local
        auto matching2 = busquedaLocal(matching1, 50);
        
        // Paso 3: Intentar hacerlo maximal
        vector<bool> cubierto(n, false);
        for (auto& [u, v] : matching2) {
            cubierto[u] = cubierto[v] = true;
        }
        
        for (int u = 0; u < n; u++) {
            if (!cubierto[u]) {
                for (int v : grafo[u]) {
                    if (!cubierto[v]) {
                        matching2.push_back({u, v});
                        cubierto[u] = cubierto[v] = true;
                        break;
                    }
                }
            }
        }
        
        return matching2;
    }
};
```

## 8. Comparación de Algoritmos

### Tabla Comparativa

| Algoritmo | Tipo Grafo | Complejidad | Perfecto | Calidad | Aplicaciones |
|-----------|------------|-------------|----------|---------|--------------|
| **Edmonds** | General | O(V³) | Sí | Óptimo | Redes generales |
| **Micali-Vazirani** | General | O(√V E) | Sí | Óptimo | Grafos grandes |
| **Hopcroft-Karp** | Bipartito | O(E√V) | Sí | Óptimo | Asignaciones |
| **Kuhn** | Bipartito | O(VE) | Sí | Óptimo | Simple bipartito |
| **Greedy** | General | O(E) | No | 0.5-aprox | Rápido, simple |
| **Heurístico Aleatorio** | General | Varía | No | 0.5-0.7 | Paralelizable |

### Factores de Selección

```
¿Es el grafo bipartito?
├── Sí → ¿Necesitas optimalidad?
│   ├── Sí → Hopcroft-Karp (O(E√V))
│   └── No → Kuhn (O(VE)) o Greedy
└── No → ¿Necesitas emparejamiento perfecto?
    ├── Sí → Edmonds (O(V³)) o Micali-Vazirani
    └── No → Greedy o Heurístico Aleatorio
```

## 9. Aplicaciones Prácticas

### 1. Sistemas de Emparejamiento
- **Dating apps:** Emparejamiento perfecto estable
- **Tutorías:** Emparejar estudiantes con tutores

### 2. Planificación de Recursos
- **Máquinas-trabajos:** Asignación óptima
- **Hospitales:** Asignación médicos a turnos

### 3. Redes de Comunicación
- **Switches:** Emparejamiento en redes de paquetes
- **Sensores:** Emparejar sensores con estaciones base

### 4. Problemas de Asignación
- **Exámenes:** Asignar salas a estudiantes
- **Transporte:** Emparejar viajes con conductores

## 10. Implementación Completa con Tests

```cpp
#include <iostream>
#include <vector>
#include "Algoritmo_Edmonds_PerfectoMaximal_Blossom.cpp"
#include "Algoritmo_MicaliVazirani_MaximalesPerfecto.cpp"
#include "Algoritmo_Hopcroft-Karp.cpp"
#include "Algoritmo_Kuhn_PareoMáximoMaximalPerfecto_Bipartitos.cpp"
#include "Algoritmo_Emparejamiento_Greddy_MaximalPerfecto.cpp"
#include "Algoritmo_HeurísticoCodiciosoAleatorio.cpp"

void testGrafoBipartito() {
    cout << "=== TEST GRAFO BIPARTITO ===" << endl;
    
    int U = 4, V = 4;
    vector<pair<int, int>> aristas = {
        {0, 0}, {0, 1}, {1, 0}, {1, 2},
        {2, 1}, {2, 3}, {3, 2}, {3, 3}
    };
    
    HopcroftKarpPerfecto hk(U, V);
    KuhnBipartito kuhn(U, V);
    
    for (auto& [u, v] : aristas) {
        hk.agregarArista(u, v);
        kuhn.agregarArista(u, v);
    }
    
    cout << "Hopcroft-Karp: " << hk.encontrarMax().size() << " aristas" << endl;
    cout << "Kuhn: " << kuhn.encontrarMax().size() << " aristas" << endl;
}

void testGrafoGeneral() {
    cout << "\n=== TEST GRAFO GENERAL ===" << endl;
    
    int n = 6;
    vector<pair<int, int>> aristas = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3},
        {2, 3}, {2, 4}, {3, 4}, {3, 5}, {4, 5}
    };
    
    EdmondsPerfecto edmonds(n);
    GreedyMaximalPerfecto greedy(n);
    
    for (auto& [u, v] : aristas) {
        edmonds.agregarArista(u, v);
        greedy.agregarArista(u, v);
    }
    
    cout << "Edmonds: " << edmonds.encontrarMaxEmparejamiento().size() << " aristas" << endl;
    cout << "Greedy: " << greedy.greedyDeterministico().size() << " aristas" << endl;
}

int main() {
    testGrafoBipartito();
    testGrafoGeneral();
    return 0;
}
```

## Conclusión

### Resumen de Recomendaciones:

1. **Para grafos bipartitos:**
   - **Óptimo:** Hopcroft-Karp (más rápido)
   - **Simple:** Kuhn (fácil implementación)

2. **Para grafos generales:**
   - **Óptimo:** Micali-Vazirani (más eficiente)
   - **Clásico:** Edmonds (más entendible)
   - **Aproximado:** Greedy (muy rápido)

3. **Para aplicaciones prácticas:**
   - **Tiempo real:** Algoritmos greedy/heurísticos
   - **Óptimo exacto:** Algoritmos exactos
   - **Paralelización:** Algoritmos aleatorizados

### Puntos Clave:
- Los algoritmos exactos garantizan optimalidad pero son más complejos
- Los algoritmos aproximados son más rápidos y prácticos
- La elección depende del tamaño del grafo y requisitos de optimalidad
- Los emparejamientos perfectos solo existen en grafos con número par de vértices

>
