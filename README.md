# Algoritmos para Grafos Bipartitos

## Introducción
Un grafo bipartito es aquel cuyos vértices pueden dividirse en dos conjuntos disjuntos U y V, tal que cada arista conecta un vértice de U con uno de V. No contiene ciclos de longitud impar.

## 1. Propiedades y Definiciones

### Características Fundamentales
Un grafo G = (V, E) es bipartito si cumple:

1. **Coloreable con 2 colores** (2-colorable)
2. **No contiene ciclos de longitud impar**
3. **Puede dividirse en dos conjuntos independientes**
4. **La matriz de adyacencia tiene estructura especial**

### Condiciones Equivalentes
```
Teorema: Un grafo es bipartito ⇔ es 2-coloreable
Teorema: Un grafo es bipartito ⇔ no tiene ciclos impares
```

## 2. Algoritmo BFS para Verificar Bipartito

### Concepto
Usa BFS para asignar colores (0 y 1) alternadamente a los vértices. Si se encuentra una arista entre vértices del mismo color, el grafo no es bipartito.

```cpp
// src/Algoritmo_BFS_Bipartito.cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool esBipartitoBFS(int V, vector<vector<int>>& grafo) {
    if (V == 0) return true;
    
    vector<int> color(V, -1); // -1 = no coloreado, 0/1 = colores
    queue<int> q;
    
    for (int inicio = 0; inicio < V; inicio++) {
        if (color[inicio] == -1) {
            // Nuevo componente conexo
            color[inicio] = 0;
            q.push(inicio);
            
            while (!q.empty()) {
                int actual = q.front();
                q.pop();
                
                for (int vecino : grafo[actual]) {
                    if (color[vecino] == -1) {
                        // Colorear con color opuesto
                        color[vecino] = 1 - color[actual];
                        q.push(vecino);
                    } 
                    // Si el vecino tiene el mismo color, no es bipartito
                    else if (color[vecino] == color[actual]) {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

// Función para obtener la bipartición si existe
pair<vector<int>, vector<int>> obtenerBiparticionBFS(int V, vector<vector<int>>& grafo) {
    vector<int> conjuntoA, conjuntoB;
    
    if (!esBipartitoBFS(V, grafo)) {
        return {{}, {}}; // No es bipartito
    }
    
    vector<int> color(V, -1);
    queue<int> q;
    
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);
            
            while (!q.empty()) {
                int actual = q.front();
                q.pop();
                
                // Agregar al conjunto correspondiente
                if (color[actual] == 0) {
                    conjuntoA.push_back(actual);
                } else {
                    conjuntoB.push_back(actual);
                }
                
                for (int vecino : grafo[actual]) {
                    if (color[vecino] == -1) {
                        color[vecino] = 1 - color[actual];
                        q.push(vecino);
                    }
                }
            }
        }
    }
    
    return {conjuntoA, conjuntoB};
}
```

### Características BFS:
- **Complejidad:** O(V + E)
- **Ventaja:** Detecta ciclos impares rápidamente
- **Ideal para:** Grafos con muchos componentes conexos

## 3. Algoritmo DFS para Verificar Bipartito

### Concepto
Versión recursiva o iterativa usando DFS para el coloreo 2-color.

```cpp
// src/Algoritmo_DFS_Bipartito.cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Versión recursiva
bool DFS_Bipartito(int nodo, int colorActual, vector<vector<int>>& grafo, vector<int>& color) {
    color[nodo] = colorActual;
    
    for (int vecino : grafo[nodo]) {
        if (color[vecino] == -1) {
            if (!DFS_Bipartito(vecino, 1 - colorActual, grafo, color)) {
                return false;
            }
        } 
        else if (color[vecino] == colorActual) {
            return false;
        }
    }
    return true;
}

bool esBipartitoDFS_Recursivo(int V, vector<vector<int>>& grafo) {
    vector<int> color(V, -1);
    
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            if (!DFS_Bipartito(i, 0, grafo, color)) {
                return false;
            }
        }
    }
    return true;
}

// Versión iterativa con pila
bool esBipartitoDFS_Iterativo(int V, vector<vector<int>>& grafo) {
    vector<int> color(V, -1);
    stack<pair<int, int>> pila; // (nodo, color)
    
    for (int inicio = 0; inicio < V; inicio++) {
        if (color[inicio] == -1) {
            pila.push({inicio, 0});
            
            while (!pila.empty()) {
                auto [actual, colorActual] = pila.top();
                pila.pop();
                
                if (color[actual] == -1) {
                    color[actual] = colorActual;
                    
                    for (int vecino : grafo[actual]) {
                        if (color[vecino] == -1) {
                            pila.push({vecino, 1 - colorActual});
                        } 
                        else if (color[vecino] == colorActual) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

// Detección de ciclo impar con DFS
vector<int> encontrarCicloImpar(int V, vector<vector<int>>& grafo) {
    vector<int> color(V, -1);
    vector<int> padre(V, -1);
    
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            stack<pair<int, int>> pila;
            pila.push({i, 0});
            color[i] = 0;
            
            while (!pila.empty()) {
                auto [actual, colorActual] = pila.top();
                pila.pop();
                
                for (int vecino : grafo[actual]) {
                    if (color[vecino] == -1) {
                        color[vecino] = 1 - colorActual;
                        padre[vecino] = actual;
                        pila.push({vecino, color[vecino]});
                    } 
                    else if (color[vecino] == colorActual) {
                        // Ciclo impar encontrado
                        vector<int> ciclo;
                        ciclo.push_back(vecino);
                        
                        // Reconstruir ciclo
                        int nodo = actual;
                        while (nodo != vecino) {
                            ciclo.push_back(nodo);
                            nodo = padre[nodo];
                        }
                        ciclo.push_back(vecino); // Cerrar ciclo
                        
                        return ciclo;
                    }
                }
            }
        }
    }
    
    return {}; // No hay ciclo impar
}
```

### Características DFS:
- **Complejidad:** O(V + E)
- **Ventaja:** Menor sobrecarga para grafos profundos
- **Ideal para:** Encontrar ciclos impares específicos

## 4. Algoritmo con Potencias de Matriz de Adyacencia

### Concepto Matemático
Para un grafo bipartito, la matriz de adyacencia A tiene la propiedad de que:
- A² tiene ceros en la diagonal (para grafos sin bucles)
- Los ciclos corresponden a trazas de potencias de A

```cpp
// src/Algoritmo_Bipartito_Potencias_MatrizAdyacencia.cpp
#include <iostream>
#include <vector>
using namespace std;

// Multiplicación de matrices
vector<vector<int>> multiplicarMatrices(const vector<vector<int>>& A, 
                                        const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> resultado(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return resultado;
}

// Verificar bipartito usando potencias de matriz
bool esBipartitoMatriz(int V, const vector<vector<int>>& matriz) {
    // Teorema: Un grafo es bipartito si y solo si
    // no contiene ciclos de longitud impar
    
    // Para grafos pequeños, podemos verificar A³, A⁵, etc.
    // Un método más práctico: verificar si la matriz puede reordenarse
    // en forma de bloques
    
    // Método 1: Verificar si hay ciclos de longitud 3 (triángulos)
    vector<vector<int>> A2 = multiplicarMatrices(matriz, matriz);
    vector<vector<int>> A3 = multiplicarMatrices(A2, matriz);
    
    // Si hay un ciclo de longitud 3, A³ tendrá entradas positivas en la diagonal
    for (int i = 0; i < V; i++) {
        if (A3[i][i] != 0) {
            return false; // Ciclo impar encontrado
        }
    }
    
    return true;
}

// Método alternativo: estructura de bloques
bool esBipartitoPorEstructura(int V, const vector<vector<int>>& matriz) {
    // Intentar encontrar permutación que ponga la matriz en forma:
    // [ 0  B ]
    // [ Bᵀ 0 ]
    
    vector<int> color(V, -1);
    
    // Usar BFS/DFS para colorear
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            
            // BFS simple
            vector<int> actuales = {i};
            while (!actuales.empty()) {
                vector<int> siguientes;
                
                for (int u : actuales) {
                    for (int v = 0; v < V; v++) {
                        if (matriz[u][v] != 0) {
                            if (color[v] == -1) {
                                color[v] = 1 - color[u];
                                siguientes.push_back(v);
                            } 
                            else if (color[v] == color[u]) {
                                return false;
                            }
                        }
                    }
                }
                
                actuales = siguientes;
            }
        }
    }
    
    // Verificar que la matriz tenga la estructura correcta
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matriz[i][j] != 0 && color[i] == color[j]) {
                return false;
            }
        }
    }
    
    return true;
}
```

### Características Matriciales:
- **Complejidad:** O(V³) para multiplicación naïve
- **Ventaja:** Enfoque teórico elegante
- **Aplicación:** Análisis espectral de grafos
- **Limitación:** Impracticable para grafos grandes

## 5. Comparación de Algoritmos

### Tabla Comparativa

| Algoritmo | Complejidad | Ventajas | Desventajas | Caso Ideal |
|-----------|------------|----------|-------------|------------|
| **BFS** | O(V + E) | Simple, detecta ciclos rápidamente | Usa cola explícita | Grafos anchos |
| **DFS Recursivo** | O(V + E) | Código conciso, natural para backtracking | Posible stack overflow | Grafos profundos |
| **DFS Iterativo** | O(V + E) | Sin riesgo de stack overflow | Implementación más compleja | Grafos muy profundos |
| **Matricial** | O(V³) | Enfoque matemático elegante | Impracticable para V grandes | Análisis teórico |

### Selección del Algoritmo
```
¿Tamaño del grafo?
├── Grande (V > 1000) → BFS o DFS Iterativo
├── Mediano → Cualquier BFS/DFS
└── Pequeño y análisis teórico → Método matricial

¿Necesitas encontrar el ciclo impar?
├── Sí → DFS con reconstrucción de camino
└── No → BFS simple
```

## 6. Aplicaciones Prácticas

### 1. Problemas de Asignación
- **Matching bipartito:** Emparejamiento máximo
- **Scheduling:** Asignar tareas a trabajadores
- **Asignación de recursos:** Recursos a consumidores

### 2. Redes Sociales
- **Relaciones:** Hombres-mujeres en redes de citas
- **Recomendaciones:** Usuarios-productos
- **Comunidades:** Detectar estructuras bipartitas

### 3. Sistemas de Recomendación
- **Usuario-ítem:** Matriz de preferencias
- **Colaborativo:** Filtrado basado en usuarios

### 4. Teoría de Juegos
- **Juegos de suma cero:** Representación como grafo bipartito
- **Equilibrios:** Encontrar estrategias óptimas

## 7. Ejemplos Detallados

### Ejemplo 1: Grafo Bipartito
```
V = 6
Aristas: (0,3), (0,4), (1,3), (1,5), (2,4), (2,5)

Conjunto U: {0,1,2}
Conjunto V: {3,4,5}

Grafo:
0---3
|   |
1---4
|   |
2---5
```

### Ejemplo 2: Grafo No Bipartito (ciclo impar)
```
V = 5
Aristas: (0,1), (1,2), (2,3), (3,4), (4,0)

Ciclo impar de longitud 5: 0-1-2-3-4-0
```

### Ejemplo 3: Grafo Completo Bipartito K₃,₃
```
V = 6
Conjunto U: {0,1,2}
Conjunto V: {3,4,5}
Todas las aristas U-V existen

Es bipartito (K_{m,n} siempre es bipartito)
```

## 8. Algoritmos Avanzados

### Detección de Componentes Bipartitas Múltiples
```cpp
vector<vector<int>> encontrarComponentesBipartitas(int V, vector<vector<int>>& grafo) {
    vector<int> color(V, -1);
    vector<vector<int>> componentes;
    
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            vector<int> componente;
            queue<int> q;
            
            color[i] = 0;
            q.push(i);
            componente.push_back(i);
            
            bool esBipartito = true;
            
            while (!q.empty()) {
                int actual = q.front();
                q.pop();
                
                for (int vecino : grafo[actual]) {
                    if (color[vecino] == -1) {
                        color[vecino] = 1 - color[actual];
                        q.push(vecino);
                        componente.push_back(vecino);
                    } 
                    else if (color[vecino] == color[actual]) {
                        esBipartito = false;
                    }
                }
            }
            
            if (esBipartito) {
                componentes.push_back(componente);
            }
        }
    }
    
    return componentes;
}
```

### Máximo Matching Bipartito (Algoritmo de Hopcroft-Karp)
```cpp
// Implementación simplificada
class MatchingBipartito {
private:
    int U, V;
    vector<vector<int>> grafo;
    
public:
    MatchingBipartito(int u, int v) : U(u), V(v) {
        grafo.resize(U);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
    }
    
    int maxMatching() {
        vector<int> parejaU(U, -1);
        vector<int> parejaV(V, -1);
        vector<int> distancia(U);
        int matching = 0;
        
        while (bfs(parejaU, parejaV, distancia)) {
            for (int u = 0; u < U; u++) {
                if (parejaU[u] == -1 && dfs(u, parejaU, parejaV, distancia)) {
                    matching++;
                }
            }
        }
        
        return matching;
    }
    
private:
    bool bfs(vector<int>& parejaU, vector<int>& parejaV, vector<int>& distancia) {
        queue<int> q;
        
        for (int u = 0; u < U; u++) {
            if (parejaU[u] == -1) {
                distancia[u] = 0;
                q.push(u);
            } else {
                distancia[u] = INT_MAX;
            }
        }
        
        bool encontrado = false;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : grafo[u]) {
                if (parejaV[v] != -1) {
                    if (distancia[parejaV[v]] == INT_MAX) {
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
    
    bool dfs(int u, vector<int>& parejaU, vector<int>& parejaV, vector<int>& distancia) {
        for (int v : grafo[u]) {
            if (parejaV[v] == -1 || 
                (distancia[parejaV[v]] == distancia[u] + 1 && 
                 dfs(parejaV[v], parejaU, parejaV, distancia))) {
                parejaU[u] = v;
                parejaV[v] = u;
                return true;
            }
        }
        distancia[u] = INT_MAX;
        return false;
    }
};
```

## 9. Optimizaciones y Consideraciones

### Grafos Muy Grandes
```cpp
// Para grafos con millones de vértices:
// 1. Usar representación comprimida
// 2. Procesar por chunks
// 3. Paralelizar BFS/DFS

bool esBipartitoEficiente(int V, const vector<pair<int, int>>& aristas) {
    vector<int> padre(V);
    vector<int> rango(V, 0);
    
    // Inicializar DSU
    for (int i = 0; i < V; i++) padre[i] = i;
    
    // Procesar aristas en paralelo si es posible
    vector<int> color(V, -1);
    
    // BFS optimizado
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            if (!bfsComponente(i, aristas, color)) {
                return false;
            }
        }
    }
    
    return true;
}
```

### Grafos con Pesos (Bipartito Perfecto)
```cpp
// Problema de asignación (Hungarian Algorithm)
// Encontrar matching perfecto de peso mínimo/máximo

int asignacionOptima(int n, const vector<vector<int>>& costos) {
    // Implementación del algoritmo húngaro
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
    
    return -v[0]; // Costo óptimo
}
```

## 10. Implementación Completa

```cpp
// Sistema completo de verificación bipartita
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class VerificadorBipartito {
private:
    int V;
    vector<vector<int>> grafo;
    
public:
    VerificadorBipartito(int vertices) : V(vertices) {
        grafo.resize(V);
    }
    
    void agregarArista(int u, int v) {
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    
    // Método principal
    bool esBipartito() {
        return esBipartitoBFS(V, grafo);
    }
    
    // Obtener bipartición
    pair<vector<int>, vector<int>> obtenerBiparticion() {
        return obtenerBiparticionBFS(V, grafo);
    }
    
    // Encontrar ciclo impar si existe
    vector<int> encontrarCicloImpar() {
        return ::encontrarCicloImpar(V, grafo);
    }
    
    // Verificar matching máximo
    int maxMatching() {
        // Primero verificar que sea bipartito
        if (!esBipartito()) return -1;
        
        // Obtener bipartición
        auto [conjuntoA, conjuntoB] = obtenerBiparticion();
        
        // Construir grafo dirigido para Hopcroft-Karp
        MatchingBipartito matcher(conjuntoA.size(), conjuntoB.size());
        
        // Mapear vértices a índices
        unordered_map<int, int> mapaA, mapaB;
        for (int i = 0; i < conjuntoA.size(); i++) {
            mapaA[conjuntoA[i]] = i;
        }
        for (int i = 0; i < conjuntoB.size(); i++) {
            mapaB[conjuntoB[i]] = i;
        }
        
        // Agregar aristas al matcher
        for (int u : conjuntoA) {
            for (int v : grafo[u]) {
                if (mapaB.find(v) != mapaB.end()) {
                    matcher.agregarArista(mapaA[u], mapaB[v]);
                }
            }
        }
        
        return matcher.maxMatching();
    }
};
```

## Conclusión

### Resumen de Métodos:
- **BFS:** Mejor para detección rápida en grafos anchos
- **DFS:** Mejor para encontrar ciclos impares específicos
- **Matricial:** Interés teórico, práctico solo para grafos pequeños

### Aplicaciones Clave:
1. **Emparejamiento:** Asignación óptima de recursos
2. **Scheduling:** Planificación de tareas
3. **Análisis de redes:** Detectar estructuras bipartitas
4. **Optimización:** Problemas de cobertura y partición

### Recomendaciones:
1. **Verificación simple:** Usar BFS
2. **Encontrar ciclo impar:** Usar DFS con reconstrucción
3. **Matching máximo:** Hopcroft-Karp para grafos bipartitos
4. **Grafos grandes:** BFS iterativo o paralelo

> **Teorema importante:** Un grafo es bipartito si y solo si no contiene ciclos de longitud impar. Esta propiedad es la base de todos los algoritmos de verificación.

---

**Implementaciones completas** en C++ disponibles en la carpeta `src/` con ejemplos de uso, pruebas para diferentes tipos de grafos, y algoritmos para problemas relacionados como matching máximo y coloración.
