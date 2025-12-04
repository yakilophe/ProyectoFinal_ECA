# Algoritmos de Emparejamiento (Matching) en Grafos

## Introducción
Un matching (emparejamiento) en un grafo es un conjunto de aristas sin vértices en común. Los algoritmos de matching buscan encontrar el máximo número de aristas disjuntas o el matching de peso máximo/mínimo.

## 1. Clasificación de Algoritmos de Matching

### Por Tipo de Grafo:
```
1. Grafos Bipartitos:
   - Hopcroft-Karp (matching máximo cardinalidad)
   - Húngaro (matching máximo peso)
   - Algoritmo Greedy (matching maximal)

2. Grafos Generales:
   - Edmonds (Blossom Algorithm)
   - Algoritmos aleatorios:
     * Luby (matching maximal)
     * Israeli-HITAI (matching maximal)
```

## 2. Algoritmo de Hopcroft-Karp (Bipartito)

### Concepto
Encuentra el matching máximo en grafos bipartitos en O(E√V). Usa BFS para encontrar caminos aumentantes más cortos y DFS para aumentarlos.

```cpp
// src/Algoritmo_Hopcroft_Karp_MatchingMaximo.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class HopcroftKarp {
private:
    int U, V;
    vector<vector<int>> grafo;
    vector<int> parejaU, parejaV, distancia;
    const int INF = 1e9;
    
public:
    HopcroftKarp(int u, int v) : U(u), V(v) {
        grafo.resize(U);
        parejaU.assign(U, -1);
        parejaV.assign(V, -1);
        distancia.resize(U);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
    }
    
    bool bfs() {
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
    
    bool dfs(int u) {
        for (int v : grafo[u]) {
            if (parejaV[v] == -1 || 
                (distancia[parejaV[v]] == distancia[u] + 1 && 
                 dfs(parejaV[v]))) {
                parejaU[u] = v;
                parejaV[v] = u;
                return true;
            }
        }
        distancia[u] = INF;
        return false;
    }
    
    int maxMatching() {
        int matching = 0;
        
        while (bfs()) {
            for (int u = 0; u < U; u++) {
                if (parejaU[u] == -1 && dfs(u)) {
                    matching++;
                }
            }
        }
        
        return matching;
    }
    
    vector<pair<int, int>> obtenerMatching() {
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

**Características:**
- **Complejidad:** O(E√V)
- **Ventaja:** Muy eficiente para grafos bipartitos
- **Aplicaciones:** Asignación de tareas, emparejamiento estable

## 3. Algoritmo Húngaro (Asignación)

### Concepto
Resuelve el problema de asignación: encontrar matching perfecto de costo mínimo/máximo en grafos bipartitos completos.

```cpp
// src/Algoritmo_Húngaro_MatchingMáximo.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class AlgoritmoHungaro {
private:
    int n;
    vector<vector<int>> costos;
    
public:
    AlgoritmoHungaro(const vector<vector<int>>& _costos) : costos(_costos) {
        n = costos.size();
    }
    
    // Para maximización (convierte a minimización)
    vector<int> asignacionMaxima() {
        // Convertir a minimización
        int maxVal = 0;
        for (const auto& fila : costos) {
            maxVal = max(maxVal, *max_element(fila.begin(), fila.end()));
        }
        
        vector<vector<int>> costosMin = costos;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                costosMin[i][j] = maxVal - costos[i][j];
            }
        }
        
        return asignacionMinima(costosMin);
    }
    
    vector<int> asignacionMinima(const vector<vector<int>>& costos) {
        vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
        
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv(n + 1, INT_MAX);
            vector<bool> used(n + 1, false);
            
            do {
                used[j0] = true;
                int i0 = p[j0], delta = INT_MAX, j1;
                
                for (int j = 1; j <= n; j++) {
                    if (!used[j]) {
                        int cur = costos[i0 - 1][j - 1] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }
                
                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                
                j0 = j1;
            } while (p[j0] != 0);
            
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        
        vector<int> asignacion(n);
        for (int j = 1; j <= n; j++) {
            if (p[j] != 0) {
                asignacion[p[j] - 1] = j - 1;
            }
        }
        
        return asignacion;
    }
    
    int costoTotal(const vector<int>& asignacion) {
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += costos[i][asignacion[i]];
        }
        return total;
    }
};
```

**Características:**
- **Complejidad:** O(n³)
- **Aplicaciones:** Asignación óptima de trabajos a trabajadores
- **Variante:** Puede manejar maximización y minimización

## 4. Algoritmo de Edmonds (Blossom Algorithm)

### Concepto
Encuentra matching máximo en grafos generales (no necesariamente bipartitos). Detecta y contrae "blossoms" (flores) - ciclos de longitud impar.

```cpp
// src/Algoritmo_Edmonds.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class EdmondsBlossom {
private:
    int n;
    vector<vector<int>> grafo;
    vector<int> pareja, padre, base, estado;
    queue<int> q;
    
    int lca(int a, int b) {
        vector<bool> marcado(n, false);
        while (true) {
            a = base[a];
            marcado[a] = true;
            if (pareja[a] == -1) break;
            a = padre[pareja[a]];
        }
        while (true) {
            b = base[b];
            if (marcado[b]) return b;
            b = padre[pareja[b]];
        }
        return -1;
    }
    
    void marcarCamino(int v, int b, int hijo) {
        while (base[v] != b) {
            estado[pareja[v]] = 1;
            padre[v] = hijo;
            hijo = pareja[v];
            v = padre[hijo];
        }
    }
    
    void contraer(int a, int b) {
        int raiz = lca(a, b);
        vector<bool> enBlossom(n, false);
        
        marcarCamino(a, raiz, b);
        marcarCamino(b, raiz, a);
        
        for (int i = 0; i < n; i++) {
            if (enBlossom[base[i]]) {
                base[i] = raiz;
                if (estado[i] == 0) {
                    q.push(i);
                    estado[i] = 1;
                }
            }
        }
    }
    
    bool bfs(int inicio) {
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
                        // Camino aumentante encontrado
                        while (v != -1) {
                            int pv = pareja[v];
                            int pu = u;
                            pareja[u] = v;
                            pareja[v] = u;
                            u = pv;
                            v = padre[pv];
                        }
                        return true;
                    } else {
                        padre[u] = v;
                        estado[u] = 1;
                        estado[pareja[u]] = 0;
                        q.push(pareja[u]);
                    }
                } else if (estado[u] == 0 && base[v] != base[u]) {
                    // Blossom encontrado
                    int b = lca(v, u);
                    contraer(v, u);
                }
            }
        }
        return false;
    }
    
public:
    EdmondsBlossom(int _n) : n(_n) {
        grafo.resize(n);
        pareja.assign(n, -1);
        padre.resize(n);
        base.resize(n);
        estado.resize(n);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    int maxMatching() {
        int matching = 0;
        
        for (int i = 0; i < n; i++) {
            if (pareja[i] == -1 && bfs(i)) {
                matching++;
            }
        }
        
        return matching;
    }
    
    vector<pair<int, int>> obtenerMatching() {
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

**Características:**
- **Complejidad:** O(V³)
- **Ventaja:** Funciona en grafos generales
- **Concepto clave:** Detección y contracción de blossoms

## 5. Algoritmos de Matching Maximal Aleatorios

### 5.1 Algoritmo Greedy (Secuencial)
```cpp
// src/Algoritmo_Greedy_MatchingMaximal.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class GreedyMatching {
private:
    int n;
    vector<vector<int>> grafo;
    
public:
    GreedyMatching(int _n) : n(_n) {
        grafo.resize(n);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    vector<pair<int, int>> matchingMaximal() {
        vector<bool> cubierto(n, false);
        vector<pair<int, int>> matching;
        
        for (int u = 0; u < n; u++) {
            if (!cubierto[u]) {
                for (int v : grafo[u]) {
                    if (!cubierto[v]) {
                        matching.push_back({u, v});
                        cubierto[u] = true;
                        cubierto[v] = true;
                        break;
                    }
                }
            }
        }
        
        return matching;
    }
    
    // Greedy aleatorizado
    vector<pair<int, int>> matchingMaximalAleatorizado() {
        vector<bool> cubierto(n, false);
        vector<pair<int, int>> matching;
        vector<int> vertices(n);
        
        for (int i = 0; i < n; i++) vertices[i] = i;
        random_shuffle(vertices.begin(), vertices.end());
        
        for (int u : vertices) {
            if (!cubierto[u]) {
                vector<int> vecinosDisponibles;
                for (int v : grafo[u]) {
                    if (!cubierto[v]) {
                        vecinosDisponibles.push_back(v);
                    }
                }
                
                if (!vecinosDisponibles.empty()) {
                    random_shuffle(vecinosDisponibles.begin(), vecinosDisponibles.end());
                    int v = vecinosDisponibles[0];
                    matching.push_back({u, v});
                    cubierto[u] = true;
                    cubierto[v] = true;
                }
            }
        }
        
        return matching;
    }
};
```

### 5.2 Algoritmo de Luby
```cpp
// src/Algoritmo_Luby_MatchingMaximal.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

class LubyMatching {
private:
    int n;
    vector<vector<int>> grafo;
    mt19937 rng;
    
public:
    LubyMatching(int _n) : n(_n), rng(chrono::steady_clock::now().time_since_epoch().count()) {
        grafo.resize(n);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    vector<pair<int, int>> matchingMaximal() {
        vector<bool> activo(n, true);
        vector<bool> enMatching(n, false);
        vector<pair<int, int>> matching;
        
        while (true) {
            // Paso 1: Selección aleatoria independiente
            vector<bool> seleccionado(n, false);
            for (int u = 0; u < n; u++) {
                if (activo[u] && !enMatching[u]) {
                    uniform_real_distribution<double> dist(0.0, 1.0);
                    double prob = 1.0 / (2.0 * grafo[u].size());
                    if (dist(rng) < prob) {
                        seleccionado[u] = true;
                    }
                }
            }
            
            // Paso 2: Resolver conflictos
            for (int u = 0; u < n; u++) {
                if (seleccionado[u]) {
                    for (int v : grafo[u]) {
                        if (seleccionado[v]) {
                            // Conflicto, mantener solo uno
                            if (u < v) {
                                seleccionado[v] = false;
                            } else {
                                seleccionado[u] = false;
                            }
                        }
                    }
                }
            }
            
            // Paso 3: Agregar al matching
            bool cambio = false;
            for (int u = 0; u < n; u++) {
                if (seleccionado[u]) {
                    // Encontrar vecino disponible
                    for (int v : grafo[u]) {
                        if (activo[v] && !enMatching[v]) {
                            matching.push_back({u, v});
                            enMatching[u] = enMatching[v] = true;
                            cambio = true;
                            break;
                        }
                    }
                }
            }
            
            // Paso 4: Actualizar conjunto activo
            for (int u = 0; u < n; u++) {
                if (enMatching[u]) {
                    activo[u] = false;
                    for (int v : grafo[u]) {
                        activo[v] = false;
                    }
                }
            }
            
            if (!cambio) break;
        }
        
        return matching;
    }
};
```

### 5.3 Algoritmo Israeli-HITAI
```cpp
// src/Algoritmo_Israeli_HITAI_MatchingMaximal.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
using namespace std;

class IsraeliHITAI {
private:
    int n;
    vector<vector<int>> grafo;
    
public:
    IsraeliHITAI(int _n) : n(_n) {
        grafo.resize(n);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    vector<pair<int, int>> matchingMaximal() {
        vector<int> estado(n, 0); // 0 = disponible, 1 = en matching, 2 = eliminado
        vector<pair<int, int>> matching;
        
        for (int u = 0; u < n; u++) {
            if (estado[u] == 0) {
                // Etapa 1: Los vértices proponen
                for (int v : grafo[u]) {
                    if (estado[v] == 0) {
                        // Ambos disponibles, lanzar moneda
                        if (rand() % 2 == 0) {
                            matching.push_back({u, v});
                            estado[u] = estado[v] = 1;
                            break;
                        }
                    }
                }
            }
        }
        
        // Etapa 2: Eliminar vértices cubiertos
        for (int u = 0; u < n; u++) {
            if (estado[u] == 1) {
                for (int v : grafo[u]) {
                    if (estado[v] == 0) {
                        estado[v] = 2; // Eliminar
                    }
                }
            }
        }
        
        // Etapa 3: Procesar vértices restantes
        for (int u = 0; u < n; u++) {
            if (estado[u] == 0) {
                for (int v : grafo[u]) {
                    if (estado[v] == 0) {
                        matching.push_back({u, v});
                        estado[u] = estado[v] = 1;
                        break;
                    }
                }
            }
        }
        
        return matching;
    }
    
    // Versión iterativa mejorada
    vector<pair<int, int>> matchingMaximalIterativo(int iteraciones = 10) {
        vector<pair<int, int>> mejorMatching;
        
        for (int it = 0; it < iteraciones; it++) {
            auto matchingActual = matchingMaximal();
            if (matchingActual.size() > mejorMatching.size()) {
                mejorMatching = matchingActual;
            }
        }
        
        return mejorMatching;
    }
};
```

## 6. Comparación de Algoritmos

### Tabla Comparativa

| Algoritmo | Tipo de Grafo | Complejidad | Calidad | Aplicaciones |
|-----------|---------------|-------------|---------|--------------|
| **Hopcroft-Karp** | Bipartito | O(E√V) | Óptimo | Asignación de tareas |
| **Húngaro** | Bipartito completo | O(n³) | Óptimo | Asignación con pesos |
| **Edmonds** | General | O(V³) | Óptimo | Redes sociales |
| **Greedy** | General | O(E) | 0.5-aprox | Simple, rápido |
| **Luby** | General | O(log V) paralelo | 0.5-aprox | Computación paralela |
| **Israeli-HITAI** | General | O(E) | 0.5-aprox | Distribuido |

### Factores de Aproximación
```
Matching Maximal vs Matching Máximo:
- Greedy: ≥ 0.5 del óptimo
- Aleatorizados: Esperado ≥ 0.5 del óptimo
- Determinísticos: Pueden ser > 0.5 en práctica
```

## 7. Aplicaciones Prácticas

### 1. Sistemas de Recomendación
- **Matching usuario-ítem:** Emparejamiento óptimo
- **Colaborativo:** Encontrar pares similares

### 2. Redes de Transporte
- **Taxi-pasajero:** Asignación en tiempo real
- **Logística:** Emparejamiento camiones-cargas

### 3. Redes Sociales
- **Amistades:** Encontrar matching máximo
- **Dating apps:** Emparejamiento estable

### 4. Computación Distribuida
- **Asignación de tareas:** Matching procesador-tarea
- **Balanceo de carga:** Distribuir trabajo uniformemente

## 8. Ejemplos y Casos de Uso

### Ejemplo 1: Asignación de Trabajos (Húngaro)
```
Trabajadores: A, B, C
Trabajos: X, Y, Z
Costos:
  A: [3, 2, 7]
  B: [5, 4, 3]
  C: [6, 8, 1]

Asignación óptima:
A → Y (2)
B → X (5) 
C → Z (1)
Costo total: 8
```

### Ejemplo 2: Matching en Red Social (Edmonds)
```
Amistades: A-B, A-C, B-C, C-D, D-E
Grafo no bipartito (triángulo A-B-C)

Matching máximo: 2 aristas
Posibles: (A-B, D-E) o (A-C, D-E)
```

### Ejemplo 3: Matching Aleatorio (Luby)
```
Grafo: 6 vértices, 8 aristas
Iteración 1: Matching de tamaño 2
Iteración 2: Matching de tamaño 3 (mejor)
...
```

## 9. Implementación Completa y Comparativa

```cpp
#include <iostream>
#include "Algoritmo_Hopcroft_Karp_MatchingMaximo.cpp"
#include "Algoritmo_Húngaro_MatchingMáximo.cpp"
#include "Algoritmo_Edmonds.cpp"
#include "Algoritmo_Greedy_MatchingMaximal.cpp"
#include "Algoritmo_Luby_MatchingMaximal.cpp"
#include "Algoritmo_Israeli_HITAI_MatchingMaximal.cpp"

void compararAlgoritmos() {
    // Crear grafo bipartito de ejemplo
    int U = 4, V = 4;
    vector<pair<int, int>> aristas = {
        {0, 0}, {0, 1}, {1, 0}, {1, 2}, 
        {2, 1}, {2, 3}, {3, 2}, {3, 3}
    };
    
    cout << "=== Hopcroft-Karp (Bipartito) ===" << endl;
    HopcroftKarp hk(U, V);
    for (auto& [u, v] : aristas) hk.agregarArista(u, v);
    cout << "Matching tamaño: " << hk.maxMatching() << endl;
    
    cout << "\n=== Greedy ===" << endl;
    GreedyMatching greedy(U + V);
    for (auto& [u, v] : aristas) greedy.agregarArista(u, V + v);
    auto mGreedy = greedy.matchingMaximal();
    cout << "Matching tamaño: " << mGreedy.size() << endl;
    
    cout << "\n=== Luby (Aleatorizado) ===" << endl;
    LubyMatching luby(U + V);
    for (auto& [u, v] : aristas) luby.agregarArista(u, V + v);
    auto mLuby = luby.matchingMaximal();
    cout << "Matching tamaño: " << mLuby.size() << endl;
}
```

## 10. Optimizaciones y Consideraciones

### Para Grafos Muy Grandes
```cpp
// Estrategias:
// 1. Sampling: Procesar subgrafos aleatorios
// 2. Paralelización: Dividir el grafo
// 3. Streaming: Procesar aristas en flujo

class MatchingEscalable {
    // Combinar múltiples estrategias
};
```

### Matching con Restricciones
```cpp
// Matching con capacidades (b-matching)
// Matching con preferencias (stable marriage)
// Matching en grafos dinámicos
```

### Calidad vs Velocidad
```
Algoritmo          Velocidad    Calidad    Uso
---------------    ---------    -------    -----
Greedy             Muy rápida   50%        Prototipos
Hopcroft-Karp      Rápida       100%       Bipartitos óptimo
Edmonds            Lenta        100%       General óptimo
Aleatorizados      Media        50-70%     Paralelo/distribuido
```

## Conclusión

### Guía de Selección:
```
¿Es el grafo bipartito?
├── Sí → ¿Necesitas matching perfecto con pesos?
│   ├── Sí → Algoritmo Húngaro (O(n³))
│   └── No → Hopcroft-Karp (O(E√V))
└── No → ¿Necesitas optimalidad?
    ├── Sí → Edmonds (O(V³)) 
    └── No → ¿Necesitas velocidad o paralelismo?
        ├── Velocidad → Greedy (O(E))
        ├── Paralelo → Luby
        └── Distribuido → Israeli-HITAI
```

### Puntos Clave:
1. **Hopcroft-Karp:** Mejor para bipartitos grandes
2. **Húngaro:** Para asignación con costos
3. **Edmonds:** Único óptimo para grafos generales
4. **Algoritmos aleatorios:** Buen equilibrio velocidad-calidad
5. **Greedy:** Simple y rápido para prototipos

> **Importante:** Matching maximal ≠ Matching máximo. Los algoritmos greedy garantizan al menos 50% del óptimo, lo cual es aceptable en muchas aplicaciones prácticas.

---

**Implementaciones completas** en C++ disponibles en la carpeta `src/` con benchmarks, pruebas de correctitud y ejemplos para cada tipo de grafo y requisito de aplicación.
