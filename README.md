# Algoritmos de Caminos Más Cortos: Dijkstra, Bellman-Ford, Floyd-Warshall

## Introducción
Los algoritmos de caminos más cortos encuentran la ruta mínima entre vértices en un grafo ponderado. Cada algoritmo tiene características específicas según el tipo de grafo y restricciones.

## 1. Algoritmo de Dijkstra

### Concepto
Encuentra el camino más corto desde un nodo origen a todos los demás nodos en grafos con pesos **no negativos**. Usa una cola de prioridad para seleccionar siempre el nodo con menor distancia temporal.

```cpp
// Implementación en C++ (src/Algoritmo_Dijkstra.cpp)
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<int> dijkstra(int n, vector<vector<pair<int, int>>>& grafo, int origen) {
    vector<int> distancias(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distancias[origen] = 0;
    pq.push({0, origen});
    
    while (!pq.empty()) {
        int distancia_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();
        
        if (distancia_actual > distancias[nodo_actual]) continue;
        
        for (auto& vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            int peso = vecino.second;
            int nueva_distancia = distancia_actual + peso;
            
            if (nueva_distancia < distancias[nodo_vecino]) {
                distancias[nodo_vecino] = nueva_distancia;
                pq.push({nueva_distancia, nodo_vecino});
            }
        }
    }
    return distancias;
}
```

**Características:**
- **Pesos:** Solo no negativos
- **Complejidad:** O((V + E) log V) con cola de prioridad
- **Tipo:** Algoritmo greedy
- **Aplicaciones:** Sistemas de navegación GPS, enrutamiento de redes

## 2. Algoritmo de Bellman-Ford

### Concepto
Encuentra el camino más corto desde un nodo origen a todos los demás, **incluso con pesos negativos**. Detecta ciclos negativos alcanzables.

```cpp
// Implementación en C++ (src/Algoritmo_BellmanFord.cpp)
#include <vector>
#include <climits>
using namespace std;

struct Arista {
    int origen, destino, peso;
};

vector<int> bellmanFord(int n, vector<Arista>& aristas, int origen) {
    vector<int> distancias(n, INT_MAX);
    distancias[origen] = 0;
    
    // Relajar todas las aristas V-1 veces
    for (int i = 0; i < n - 1; i++) {
        for (auto& arista : aristas) {
            if (distancias[arista.origen] != INT_MAX && 
                distancias[arista.origen] + arista.peso < distancias[arista.destino]) {
                distancias[arista.destino] = distancias[arista.origen] + arista.peso;
            }
        }
    }
    
    // Detectar ciclos negativos
    for (auto& arista : aristas) {
        if (distancias[arista.origen] != INT_MAX && 
            distancias[arista.origen] + arista.peso < distancias[arista.destino]) {
            // Ciclo negativo detectado
            return vector<int>(); // Vector vacío indica ciclo negativo
        }
    }
    
    return distancias;
}
```

**Características:**
- **Pesos:** Permite negativos
- **Complejidad:** O(V * E)
- **Detección:** Ciclos negativos alcanzables
- **Aplicaciones:** Arbitraje de divisas, análisis financiero

## 3. Algoritmo de Floyd-Warshall

### Concepto
Encuentra los caminos más cortos entre **todos los pares** de nodos. Trabaja con matrices de adyacencia y usa programación dinámica.

```cpp
// Implementación en C++ (src/Algoritmo_FloydWarshall.cpp)
#include <vector>
#include <climits>
using namespace std;

vector<vector<int>> floydWarshall(int n, vector<vector<int>>& grafo) {
    // Inicializar matriz de distancias
    vector<vector<int>> distancias = grafo;
    
    // Aplicar algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distancias[i][k] != INT_MAX && distancias[k][j] != INT_MAX &&
                    distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }
    
    // Detectar ciclos negativos
    for (int i = 0; i < n; i++) {
        if (distancias[i][i] < 0) {
            // Ciclo negativo detectado
            return vector<vector<int>>(); // Matriz vacía indica ciclo negativo
        }
    }
    
    return distancias;
}
```

**Características:**
- **Todos los pares:** Distancias entre todos los vértices
- **Complejidad:** O(V³)
- **Pesos:** Permite negativos (sin ciclos negativos)
- **Aplicaciones:** Planificación de rutas, análisis de redes

## Comparación de Algoritmos

### Tabla Comparativa

| Característica | Dijkstra | Bellman-Ford | Floyd-Warshall |
|---------------|----------|--------------|----------------|
| **Tipo** | Un origen a todos | Un origen a todos | Todos a todos |
| **Pesos negativos** | No permitido | Permitido (detecta ciclos) | Permitido (sin ciclos) |
| **Complejidad** | O((V+E) log V) | O(V * E) | O(V³) |
| **Estructura** | Grafo disperso | Lista de aristas | Matriz densa |
| **Óptimo para** | Grafos no negativos | Grafos con pesos negativos | Grafos pequeños |
| **Implementación** | Cola de prioridad | Relajación iterativa | Programación dinámica |

### Selección del Algoritmo

```
¿Necesitas distancias entre todos los pares?
├── Sí → ¿Grafo pequeño (V ≤ 500)?
│   ├── Sí → Floyd-Warshall
│   └── No → Dijkstra desde cada vértice
└── No → ¿Pesos negativos?
    ├── Sí → Bellman-Ford
    └── No → Dijkstra
```

## Aplicaciones Prácticas

### Dijkstra:
1. **GPS/Navegación:** Ruta más rápida entre dos puntos
2. **Redes de computadoras:** Enrutamiento OSPF (Open Shortest Path First)
3. **Sistemas de transporte:** Metro, autobuses

### Bellman-Ford:
1. **Finanzas:** Arbitraje de divisas (detección de oportunidades)
2. **Redes:** Protocolo RIP (Routing Information Protocol)
3. **Robótica:** Planificación de movimientos con restricciones

### Floyd-Warshall:
1. **Redes sociales:** Distancia social entre usuarios
2. **Transporte:** Tablas de distancias entre ciudades
3. **Procesamiento de imágenes:** Distancias transformadas

## Ejemplos Detallados

### Ejemplo 1: Dijkstra - Sistema de Metro
```
Estaciones: A, B, C, D, E
Tiempos de viaje (minutos):
A-B: 5, A-C: 10, B-D: 3, C-D: 1, D-E: 4

Desde A:
A → B: 5 min
A → C: 10 min
A → D: 8 min (A→B→D)
A → E: 12 min (A→B→D→E)
```

### Ejemplo 2: Bellman-Ford - Arbitraje de Divisas
```
Conversiones:
USD → EUR: 0.85
EUR → GBP: 0.88
GBP → USD: 1.42

Ciclo: 1 USD → 0.85 EUR → 0.748 GBP → 1.062 USD
Ganancia: 6.2% (ciclo negativo en logaritmos)
```

### Ejemplo 3: Floyd-Warshall - Red de Vuelos
```
Ciudades: NY, LON, PAR, TOK
Distancias (en matriz):
NY: [0, 5600, 5800, 10800]
LON: [5600, 0, 350, 9600]
...
```

## Optimizaciones y Variantes

### Dijkstra Optimizado
```cpp
// Usando Fibonacci Heap: O(E + V log V)
// Para grafos muy densos: O(V²) con matriz

// Camino reconstruido:
vector<int> reconstruir_camino(vector<int>& predecesores, int destino) {
    vector<int> camino;
    for (int v = destino; v != -1; v = predecesores[v]) {
        camino.push_back(v);
    }
    reverse(camino.begin(), camino.end());
    return camino;
}
```

### Bellman-Ford Mejorado (SPFA)
```cpp
// Shortest Path Faster Algorithm
// Mejora promedio: O(kE) donde k ≤ 2 en la práctica
```

### Floyd-Warshall con Reconstrucción de Caminos
```cpp
// Matriz de predecesores para reconstruir rutas
vector<vector<int>> next(n, vector<int>(n, -1));

// Inicialización
if (i != j && grafo[i][j] != INT_MAX) {
    next[i][j] = j;
}

// Durante el algoritmo
if (distancias[i][k] + distancias[k][j] < distancias[i][j]) {
    distancias[i][j] = distancias[i][k] + distancias[k][j];
    next[i][j] = next[i][k];
}
```

## Casos Especiales

### Grafos con Peso 0 o 1
- **BFS modificado:** O(V + E)
- **0-1 BFS:** Usa deque en lugar de priority queue

### Grafos Acíclicos Dirigidos (DAG)
- **Orden topológico + relajación:** O(V + E)
- Más eficiente que Dijkstra

### Grafos con Restricciones de Tiempo
- **Algoritmo de diferencia de restricciones:**
  - Transforma a problema de caminos más cortos
  - Usa Bellman-Ford

## Errores Comunes y Soluciones

### 1. Overflow en Suma de Pesos
```cpp
// Usar long long en lugar de int para distancias grandes
vector<long long> distancias(n, LLONG_MAX);
```

### 2. Grafos Desconectados
```cpp
// Verificar si hay camino
if (distancias[destino] == INT_MAX) {
    cout << "No hay camino disponible" << endl;
}
```

### 3. Ciclos Negativos no Alcanzables
```cpp
// En Bellman-Ford, solo ciclos alcanzables desde el origen importan
// Usar BFS/DFS para verificar alcanzabilidad primero
```

## Pruebas y Validación

### Casos de Prueba
1. **Grafo vacío:** 0 vértices, 0 aristas
2. **Grafo desconectado:** Componentes aislados
3. **Grafo completo:** Todos conectados
4. **Ciclos negativos:** Verificar detección
5. **Pesos grandes:** Evitar overflow
6. **Autobuces:** dist = 0 (permitido)

### Validación Cruzada
```cpp
// Comparar resultados de diferentes algoritmos
void validar(int n, vector<Arista>& aristas) {
    auto dist_dijkstra = dijkstra(n, aristas, 0);
    auto dist_bellman = bellmanFord(n, aristas, 0);
    
    // Para grafos sin pesos negativos, deben coincidir
    assert(dist_dijkstra == dist_bellman);
}
```

## Conclusión

### Resumen de Selección:
- **Dijkstra:** Grafos con pesos no negativos, eficiente
- **Bellman-Ford:** Pesos negativos, detección de ciclos
- **Floyd-Warshall:** Todos los pares, grafos pequeños

### Recomendaciones Finales:
1. **Navegación GPS:** Dijkstra con cola de prioridad
2. **Análisis financiero:** Bellman-Ford para detectar arbitraje
3. **Redes pequeñas:** Floyd-Warshall para análisis completo
4. **Grafos dinámicos:** Recalcular solo cuando sea necesario

> **Importante:** Siempre considere las restricciones de peso, tamaño del grafo y requisitos de rendimiento al seleccionar un algoritmo.

---

**Los algoritmos en C++** se encuentran en la carpeta `src/` con implementaciones completas, pruebas y ejemplos de uso para cada caso específico.
