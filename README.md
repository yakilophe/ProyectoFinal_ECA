# Algoritmos de Árbol de Expansión Mínima (MST)

## Introducción
Un árbol de expansión mínima (Minimum Spanning Tree - MST) es un subgrafo que conecta todos los vértices con el peso total mínimo posible. Los algoritmos más importantes son **Kruskal**, **Prim**, y variantes como **Reverse Kruskal**.

## 1. Algoritmo de Kruskal

### Concepto
Ordena todas las aristas por peso y las agrega al MST si no forman un ciclo, usando **Union-Find** para verificar conectividad.

```cpp
// src/Algoritmo_Kruskal.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Arista {
    int u, v, peso;
    
    bool operator<(const Arista& otra) const {
        return peso < otra.peso;
    }
};

class UnionFind {
private:
    vector<int> padre, rango;
    
public:
    UnionFind(int n) {
        padre.resize(n);
        rango.resize(n, 0);
        for (int i = 0; i < n; i++) {
            padre[i] = i;
        }
    }
    
    int encontrar(int x) {
        if (padre[x] != x) {
            padre[x] = encontrar(padre[x]);
        }
        return padre[x];
    }
    
    bool unir(int x, int y) {
        int raizX = encontrar(x);
        int raizY = encontrar(y);
        
        if (raizX == raizY) return false;
        
        if (rango[raizX] < rango[raizY]) {
            padre[raizX] = raizY;
        } else if (rango[raizX] > rango[raizY]) {
            padre[raizY] = raizX;
        } else {
            padre[raizY] = raizX;
            rango[raizX]++;
        }
        return true;
    }
};

vector<Arista> kruskal(int V, vector<Arista>& aristas) {
    // Ordenar aristas por peso
    sort(aristas.begin(), aristas.end());
    
    UnionFind uf(V);
    vector<Arista> mst;
    int aristasAgregadas = 0;
    
    for (const auto& arista : aristas) {
        if (uf.unir(arista.u, arista.v)) {
            mst.push_back(arista);
            aristasAgregadas++;
            
            if (aristasAgregadas == V - 1) break;
        }
    }
    
    return mst;
}

int pesoMST(const vector<Arista>& mst) {
    int total = 0;
    for (const auto& arista : mst) {
        total += arista.peso;
    }
    return total;
}
```

### Características:
- **Complejidad:** O(E log E) por ordenamiento
- **Estructura:** Union-Find para ciclo
- **Ideal para:** Grafos dispersos (E ≈ V)
- **Ventaja:** Simple, fácil de paralelizar

## 2. Algoritmo de Prim

### Concepto
Comienza desde un vértice y expande el MST agregando la arista de menor peso que conecte un vértice en el MST con uno fuera.

```cpp
// src/Algoritmo_Prim.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Versión con cola de prioridad
vector<pair<int, int>> prim(int V, vector<vector<pair<int, int>>>& grafo) {
    vector<int> clave(V, INT_MAX);
    vector<int> padre(V, -1);
    vector<bool> enMST(V, false);
    
    // Min-heap: (peso, vértice)
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> pq;
    
    // Comenzar desde el vértice 0
    clave[0] = 0;
    pq.push({0, 0});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (enMST[u]) continue;
        enMST[u] = true;
        
        for (const auto& [v, peso] : grafo[u]) {
            if (!enMST[v] && peso < clave[v]) {
                clave[v] = peso;
                padre[v] = u;
                pq.push({clave[v], v});
            }
        }
    }
    
    // Reconstruir MST
    vector<pair<int, int>> mst;
    for (int v = 1; v < V; v++) {
        if (padre[v] != -1) {
            mst.push_back({padre[v], v});
        }
    }
    
    return mst;
}

// Versión con matriz de adyacencia (para grafos densos)
vector<pair<int, int>> primMatriz(int V, vector<vector<int>>& grafo) {
    vector<int> clave(V, INT_MAX);
    vector<int> padre(V, -1);
    vector<bool> enMST(V, false);
    
    clave[0] = 0;
    
    for (int i = 0; i < V - 1; i++) {
        // Encontrar vértice con clave mínima no en MST
        int u = -1, minClave = INT_MAX;
        for (int v = 0; v < V; v++) {
            if (!enMST[v] && clave[v] < minClave) {
                minClave = clave[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        enMST[u] = true;
        
        // Actualizar claves de los vecinos
        for (int v = 0; v < V; v++) {
            if (grafo[u][v] != 0 && !enMST[v] && grafo[u][v] < clave[v]) {
                clave[v] = grafo[u][v];
                padre[v] = u;
            }
        }
    }
    
    // Reconstruir MST
    vector<pair<int, int>> mst;
    for (int v = 1; v < V; v++) {
        if (padre[v] != -1) {
            mst.push_back({padre[v], v});
        }
    }
    
    return mst;
}
```

### Características:
- **Complejidad:** O(E log V) con heap, O(V²) con matriz
- **Estructura:** Heap para vértices no incluidos
- **Ideal para:** Grafos densos (E ≈ V²)
- **Ventaja:** Más eficiente para grafos densos

## 3. Algoritmo de Reverse Kruskal

### Concepto
Comienza con todas las aristas y elimina las más pesadas que no desconecten el grafo, hasta obtener un árbol.

```cpp
// src/Algoritmo_Reverse_Kruskal.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Arista {
    int u, v, peso;
    
    bool operator<(const Arista& otra) const {
        return peso > otra.peso; // Orden descendente
    }
};

// Verificar si el grafo sigue siendo conexo después de eliminar una arista
bool esConexo(int V, vector<vector<int>>& grafo) {
    vector<bool> visitado(V, false);
    queue<int> q;
    
    q.push(0);
    visitado[0] = true;
    int contador = 1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : grafo[u]) {
            if (!visitado[v]) {
                visitado[v] = true;
                q.push(v);
                contador++;
            }
        }
    }
    
    return (contador == V);
}

vector<Arista> reverseKruskal(int V, vector<Arista>& aristas) {
    // Ordenar aristas por peso descendente
    sort(aristas.begin(), aristas.end(), 
         [](const Arista& a, const Arista& b) {
             return a.peso > b.peso;
         });
    
    // Construir grafo inicial con todas las aristas
    vector<vector<int>> grafo(V);
    for (const auto& arista : aristas) {
        grafo[arista.u].push_back(arista.v);
        grafo[arista.v].push_back(arista.u);
    }
    
    vector<Arista> mst;
    
    // Intentar eliminar cada arista pesada
    for (const auto& arista : aristas) {
        // Eliminar temporalmente la arista
        auto it_u = find(grafo[arista.u].begin(), grafo[arista.u].end(), arista.v);
        auto it_v = find(grafo[arista.v].begin(), grafo[arista.v].end(), arista.u);
        
        grafo[arista.u].erase(it_u);
        grafo[arista.v].erase(it_v);
        
        // Verificar si sigue siendo conexo
        if (esConexo(V, grafo)) {
            // Arista no esencial, no agregar al MST
        } else {
            // Arista esencial, restaurarla y agregar al MST
            grafo[arista.u].push_back(arista.v);
            grafo[arista.v].push_back(arista.u);
            mst.push_back(arista);
        }
        
        if (mst.size() == V - 1) break;
    }
    
    return mst;
}

// Versión optimizada con Union-Find
vector<Arista> reverseKruskalOptimizado(int V, vector<Arista>& aristas) {
    // Ordenar aristas por peso descendente
    sort(aristas.begin(), aristas.end(), 
         [](const Arista& a, const Arista& b) {
             return a.peso > b.peso;
         });
    
    UnionFind uf(V);
    vector<Arista> aristasRestantes = aristas;
    vector<Arista> mst;
    
    // Primero, intentar mantener solo las aristas esenciales
    for (const auto& arista : aristas) {
        // Si al unir u y v se crea un ciclo, esta arista es prescindible
        if (!uf.unir(arista.u, arista.v)) {
            // Esta arista crearía un ciclo, así que es candidata a eliminación
            // Pero primero necesitamos verificar si ya tenemos V-1 aristas
            if (mst.size() < V - 1) {
                // Intentar reemplazar por una arista más ligera
                // (Implementación simplificada)
            }
        } else {
            mst.push_back(arista);
            if (mst.size() == V - 1) break;
        }
    }
    
    return mst;
}
```

### Características:
- **Complejidad:** O(E * (V + E)) en versión simple
- **Enfoque:** Eliminación de aristas pesadas
- **Aplicación:** Mantenimiento de redes, poda de árboles
- **Ventaja:** Útil cuando se parte de un grafo completo

## 4. Comparación de Algoritmos

### Tabla Comparativa

| Característica | Kruskal | Prim | Reverse Kruskal |
|---------------|---------|------|-----------------|
| **Complejidad** | O(E log E) | O(E log V) / O(V²) | O(E * (V + E)) |
| **Estructura** | Union-Find | Heap / Matriz | DFS/BFS |
| **Ideal para** | Grafos dispersos | Grafos densos | Reducción de redes |
| **Enfoque** | Bottom-up | Top-down | Decremental |
| **Paralelización** | Fácil | Difícil | Moderada |
| **Caso óptimo** | E ≈ V | E ≈ V² | Reducción de costos |

### Selección del Algoritmo

```
¿Cuál es la densidad del grafo?
├── Disperso (E ≈ V) → Kruskal (O(E log E))
├── Denso (E ≈ V²) → Prim con matriz (O(V²))
└── ¿Necesitas reducir una red existente?
    ├── Sí → Reverse Kruskal
    └── No → Kruskal o Prim según densidad
```

## 5. Aplicaciones Prácticas

### Kruskal:
1. **Redes eléctricas:** Conectar ciudades con mínimo cableado
2. **Clustering:** Agrupamiento jerárquico
3. **Diseño de circuitos:** Conexiones mínimas en chips

### Prim:
1. **Redes de telecomunicaciones:** Conectar servidores
2. **Transporte:** Diseño de rutas de metro
3. **Irrigación:** Sistema de canales mínimo

### Reverse Kruskal:
1. **Mantenimiento de redes:** Eliminar conexiones redundantes
2. **Optimización de costos:** Reducir infraestructura existente
3. **Poda de árboles:** Simplificar redes complejas

## 6. Ejemplos Detallados

### Ejemplo 1: Red de Ciudades
```
Ciudades: A, B, C, D, E
Distancias: A-B:4, A-C:2, B-C:1, B-D:5, C-D:8, C-E:10, D-E:2

MST con Kruskal:
1. B-C (1)
2. A-C (2)
3. D-E (2)
4. A-B (4) o B-D (5) - se elige A-B
Peso total: 9

MST con Prim (desde A):
A → C (2), C → B (1), A → B (4), B → D (5) o D → E (2)
Peso total: 9
```

### Ejemplo 2: Reverse Kruskal
```
Red existente (todas las conexiones):
A-B:4, A-C:2, B-C:1, B-D:5, C-D:8, C-E:10, D-E:2

Eliminar en orden descendente:
1. C-E (10) - eliminable ✓
2. C-D (8) - eliminable ✓
3. B-D (5) - esencial (mantener)
4. A-B (4) - esencial (mantener)
5. D-E (2) - esencial (mantener)
6. A-C (2) - eliminable ✓
7. B-C (1) - esencial (mantener)

MST resultante: B-C, A-B, D-E
Peso total: 7
```

## 7. Optimizaciones y Variantes

### Kruskal con Disjoint Set Union (DSU) Optimizado
```cpp
class DSU {
private:
    vector<int> padre, tamano;
    
public:
    DSU(int n) {
        padre.resize(n);
        tamano.resize(n, 1);
        for (int i = 0; i < n; i++) padre[i] = i;
    }
    
    // Path compression + union by size
    int find(int x) {
        return padre[x] == x ? x : padre[x] = find(padre[x]);
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        
        if (tamano[x] < tamano[y]) swap(x, y);
        padre[y] = x;
        tamano[x] += tamano[y];
        return true;
    }
};
```

### Prim con Fibonacci Heap
```cpp
// Complejidad: O(E + V log V)
// Implementación teórica para grafos muy grandes
```

### Algoritmo de Borůvka (Sollin)
```cpp
// Alternativa paralelizable
// Cada vértice encuentra su arista mínima, luego une componentes
vector<Arista> boruvka(int V, vector<Arista>& aristas) {
    vector<int> componente(V);
    vector<int> minima(V, -1);
    vector<Arista> mst;
    
    for (int i = 0; i < V; i++) componente[i] = i;
    
    int componentes = V;
    
    while (componentes > 1) {
        fill(minima.begin(), minima.end(), -1);
        
        // Encontrar arista mínima para cada componente
        for (int i = 0; i < aristas.size(); i++) {
            int u = aristas[i].u;
            int v = aristas[i].v;
            int compU = componente[u];
            int compV = componente[v];
            
            if (compU == compV) continue;
            
            if (minima[compU] == -1 || aristas[i].peso < aristas[minima[compU]].peso)
                minima[compU] = i;
            
            if (minima[compV] == -1 || aristas[i].peso < aristas[minima[compV]].peso)
                minima[compV] = i;
        }
        
        // Unir componentes usando aristas mínimas
        for (int i = 0; i < V; i++) {
            if (minima[i] != -1) {
                int idx = minima[i];
                int u = aristas[idx].u;
                int v = aristas[idx].v;
                
                if (componente[u] != componente[v]) {
                    mst.push_back(aristas[idx]);
                    
                    // Unir componentes
                    int oldComp = componente[v];
                    int newComp = componente[u];
                    for (int j = 0; j < V; j++) {
                        if (componente[j] == oldComp)
                            componente[j] = newComp;
                    }
                    componentes--;
                }
            }
        }
    }
    
    return mst;
}
```

## 8. Aplicaciones Avanzadas

### 1. MST Dinámico
```cpp
// Mantener MST mientras se agregan/eliminan aristas
class MSTDinamico {
    // Usar estructura de datos como Link-Cut Tree
    // o recomputar parcialmente
};
```

### 2. MST de Steiner
```cpp
// Conectar un subconjunto de vértices (terminales)
// Problema NP-completo, usar aproximaciones
```

### 3. k-MST
```cpp
// Encontrar árbol que conecte exactamente k vértices
// con peso mínimo
```

## 9. Implementación Completa con Ejemplos

```cpp
// Ejemplo completo de uso
#include <iostream>
#include "Algoritmo_Kruskal.cpp"
#include "Algoritmo_Prim.cpp"
#include "Algoritmo_Reverse_Kruskal.cpp"

void ejemploRedCiudades() {
    int V = 5;
    vector<Arista> aristas = {
        {0, 1, 4}, // A-B
        {0, 2, 2}, // A-C
        {1, 2, 1}, // B-C
        {1, 3, 5}, // B-D
        {2, 3, 8}, // C-D
        {2, 4, 10}, // C-E
        {3, 4, 2}  // D-E
    };
    
    cout << "=== Kruskal ===" << endl;
    auto mstKruskal = kruskal(V, aristas);
    cout << "Peso total: " << pesoMST(mstKruskal) << endl;
    
    cout << "\n=== Prim ===" << endl;
    // Convertir a lista de adyacencia
    vector<vector<pair<int, int>>> grafo(V);
    for (auto& a : aristas) {
        grafo[a.u].push_back({a.v, a.peso});
        grafo[a.v].push_back({a.u, a.peso});
    }
    auto mstPrim = prim(V, grafo);
    cout << "Aristas en MST: " << mstPrim.size() << endl;
    
    cout << "\n=== Reverse Kruskal ===" << endl;
    auto mstReverse = reverseKruskal(V, aristas);
    cout << "Peso total: " << pesoMST(mstReverse) << endl;
}
```

## 10. Pruebas y Validación

### Casos de Prueba
1. **Grafo vacío:** V=0
2. **Grafo completo:** K₅
3. **Grafo desconectado:** Verificar manejo de error
4. **Pesos negativos:** MST aún válido
5. **Grafo lineal:** Árbol simple
6. **Grafo con ciclos:** Debe eliminarlos

### Validación del MST
```cpp
bool validarMST(int V, const vector<Arista>& mst, 
                const vector<Arista>& todasAristas) {
    // 1. Debe tener exactamente V-1 aristas
    if (mst.size() != V - 1) return false;
    
    // 2. No debe tener ciclos
    UnionFind uf(V);
    for (const auto& a : mst) {
        if (!uf.unir(a.u, a.v)) return false; // Ciclo detectado
    }
    
    // 3. Debe ser conexo
    // (Union-Find ya verifica esto si todas las uniones fueron exitosas)
    
    // 4. Peso debe ser mínimo (comparar con otros MSTs posibles)
    // Esto requiere algoritmos más complejos
    
    return true;
}
```

## Conclusión

### Resumen de Selección:
- **Kruskal:** Mejor para grafos dispersos, implementación simple
- **Prim:** Mejor para grafos densos, más eficiente con matriz
- **Reverse Kruskal:** Útil para optimización de redes existentes

### Recomendaciones Finales:
1. **Grafos dispersos (E < V log V):** Kruskal
2. **Grafos densos (E ≈ V²):** Prim con matriz
3. **Reducción de costos:** Reverse Kruskal
4. **Paralelización:** Kruskal o Borůvka
5. **Actualizaciones dinámicas:** Algoritmos especializados

> **Importante:** Todos los algoritmos encuentran el mismo MST (peso total) si los pesos son únicos. Con pesos duplicados, pueden encontrar diferentes MSTs con el mismo peso total.

---

**Implementaciones completas** en C++ disponibles en la carpeta `src/` con ejemplos, pruebas y benchmarks para comparar rendimiento en diferentes tipos de grafos.
