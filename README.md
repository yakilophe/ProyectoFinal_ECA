# Algoritmos de Componentes Conexas en Grafos

## Introducción
Los componentes conexos son subgrafos donde cada par de vértices está conectado por un camino. En grafos no dirigidos, se llaman **componentes conexas**. En grafos dirigidos, existen **componentes fuertemente conexas** (SCC), donde cada vértice es alcanzable desde cualquier otro.

## Componentes Conexas (Grafos No Dirigidos)

### Definición
Un componente conexo es un subgrafo máximo donde existe un camino entre cualquier par de vértices.

```python
def componentes_conexas(grafo):
    visitado = set()
    componentes = []
    
    for vertice in grafo:
        if vertice not in visitado:
            # BFS o DFS para encontrar el componente
            componente = []
            pila = [vertice]
            
            while pila:
                nodo = pila.pop()
                if nodo not in visitado:
                    visitado.add(nodo)
                    componente.append(nodo)
                    
                    for vecino in grafo[nodo]:
                        if vecino not in visitado:
                            pila.append(vecino)
            
            componentes.append(componente)
    
    return componentes
```

**Ejemplo:**
```
Grafo no dirigido:
0---1   2---3
|       |   |
4       5   6

Componentes conexas:
1. [0, 1, 4]
2. [2, 3, 5, 6]
```

## Componentes Fuertemente Conexas (Grafos Dirigidos)

### Definición
Un componente fuertemente conexo es un subgrafo máximo donde para cada par de vértices u y v, existe un camino de u a v y de v a u.

### Algoritmo de Kosaraju

```python
def kosaraju(grafo):
    # Paso 1: DFS para orden de finalización
    visitado = set()
    orden = []
    
    def dfs_primera_pasada(nodo):
        visitado.add(nodo)
        for vecino in grafo.get(nodo, []):
            if vecino not in visitado:
                dfs_primera_pasada(vecino)
        orden.append(nodo)
    
    for nodo in grafo:
        if nodo not in visitado:
            dfs_primera_pasada(nodo)
    
    # Paso 2: Grafo transpuesto
    grafo_transpuesto = {}
    for nodo in grafo:
        for vecino in grafo[nodo]:
            if vecino not in grafo_transpuesto:
                grafo_transpuesto[vecino] = []
            grafo_transpuesto[vecino].append(nodo)
    
    # Paso 3: DFS en orden inverso
    visitado.clear()
    componentes = []
    
    def dfs_segunda_pasada(nodo, componente):
        visitado.add(nodo)
        componente.append(nodo)
        for vecino in grafo_transpuesto.get(nodo, []):
            if vecino not in visitado:
                dfs_segunda_pasada(vecino, componente)
    
    for nodo in reversed(orden):
        if nodo not in visitado:
            componente = []
            dfs_segunda_pasada(nodo, componente)
            componentes.append(componente)
    
    return componentes
```

### Algoritmo de Tarjan (Optimizado)

```python
def tarjan(grafo):
    indice = 0
    pila = []
    indices = {}
    lowlinks = {}
    en_pila = set()
    componentes = []
    
    def fuerte_conexo(nodo):
        nonlocal indice
        indices[nodo] = lowlinks[nodo] = indice
        indice += 1
        pila.append(nodo)
        en_pila.add(nodo)
        
        for vecino in grafo.get(nodo, []):
            if vecino not in indices:
                fuerte_conexo(vecino)
                lowlinks[nodo] = min(lowlinks[nodo], lowlinks[vecino])
            elif vecino in en_pila:
                lowlinks[nodo] = min(lowlinks[nodo], indices[vecino])
        
        if lowlinks[nodo] == indices[nodo]:
            componente = []
            while True:
                w = pila.pop()
                en_pila.remove(w)
                componente.append(w)
                if w == nodo:
                    break
            componentes.append(componente)
    
    for nodo in grafo:
        if nodo not in indices:
            fuerte_conexo(nodo)
    
    return componentes
```

## Comparación de Algoritmos

### Tabla Comparativa

| Algoritmo | Tipo | Complejidad | Ventajas | Desventajas |
|-----------|------|-------------|----------|-------------|
| **BFS/DFS** | No dirigido | O(V + E) | Simple, fácil implementación | Solo para no dirigidos |
| **Kosaraju** | Dirigido | O(V + E) | Fácil de entender | Dos pasadas DFS, grafo transpuesto |
| **Tarjan** | Dirigido | O(V + E) | Una pasada, eficiente | Más complejo de implementar |

## Aplicaciones Prácticas

### 1. Redes Sociales
- **Componentes conexas:** Grupos de amigos aislados
- **SCC:** Comunidades donde todos se siguen mutuamente

### 2. Compiladores
- **SCC en grafos de dependencia:** Detecta dependencias circulares
- **Optimización:** Identifica código que siempre se ejecuta junto

### 3. Redes de Computadoras
- **Componentes conexas:** Subredes aisladas
- **Análisis de conectividad:** Routers que pueden comunicarse

### 4. Bases de Datos
- **Transacciones:** Detecta deadlocks en grafos de espera
- **Integridad referencial:** Verifica consistencia de datos

### 5. Análisis Web
- **Páginas web:** Grupos de sitios mutuamente enlazados
- **Motor de búsqueda:** Identifica comunidades temáticas

## Ejemplos Detallados

### Ejemplo 1: Grafo No Dirigido
```
0---1   2   3---4
|   |       |   |
5   6       7---8

Componentes conexas:
1. [0, 1, 5, 6]
2. [2]
3. [3, 4, 7, 8]
```

### Ejemplo 2: Grafo Dirigido (SCC)
```
0 → 1 → 2
↑   ↓   ↓
3 ← 4   5
    ↓
    6 → 7

Componentes fuertemente conexas:
1. [0, 1, 3, 4]  (ciclo 0→1→4→3→0)
2. [2]
3. [5]
4. [6]
5. [7]
```

## Propiedades Matemáticas

### Teoría de Grafos
1. **Relación de equivalencia:** "Estar conectado" es una relación de equivalencia
2. **Partición:** Los componentes conexos particionan el conjunto de vértices
3. **Subgrafo inducido:** Cada componente es un subgrafo inducido maximal

### Propiedades de SCC
1. **Grafo condensado:** Los SCC forman un DAG (grafo acíclico dirigido)
2. **Orden topológico:** El grafo condensado tiene orden topológico
3. **Transitividad:** Si A→B y B→C son SCC, entonces todos están en el mismo SCC

## Algoritmos Especializados

### Para Grafos No Dirigidos

**Union-Find (Disjoint Set Union):**
```python
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1
    
    def componentes(self):
        componentes = {}
        for i in range(len(self.parent)):
            root = self.find(i)
            if root not in componentes:
                componentes[root] = []
            componentes[root].append(i)
        return list(componentes.values())
```

### Para Grafos Dirigidos

**Algoritmo de Gabow:**
- Variante de Tarjan
- Usa dos pilas en lugar de una
- Misma complejidad O(V + E)

## Casos de Estudio

### Caso 1: Análisis de Redes Sociales
```
Usuarios de Twitter:
A sigue a B, B sigue a C, C sigue a A  → SCC [A, B, C]
D sigue a E, E no sigue a D            → No son SCC
F no sigue a nadie                     → Componente [F]
```

### Caso 2: Dependencias de Software
```
Paquetes:
numpy → scipy → matplotlib
↑           ↓
pandas ←------
TensorFlow (aislado)

SCC: [numpy, scipy, pandas, matplotlib] si hay dependencias circulares
```

## Optimización y Consideraciones

### Mejores Prácticas
1. **Grafos grandes:** Usar Tarjan sobre Kosaraju
2. **Memoria limitada:** DFS iterativo en lugar de recursivo
3. **Actualizaciones dinámicas:** Union-Find para grafos no dirigidos
4. **Grafos dispersos:** Listas de adyacencia
5. **Grafos densos:** Matrices de adyacencia

### Complejidades
- **Tiempo:** O(V + E) para todos los algoritmos
- **Espacio:** O(V) para Tarjan, O(V + E) para Kosaraju
- **Union-Find:** O(α(n)) por operación (casi constante)

## Problemas Relacionados

### 1. Número de Componentes Conexas
```python
def contar_componentes(grafo):
    return len(componentes_conexas(grafo))
```

### 2. Componente Conexa Más Grande
```python
def componente_mas_grande(grafo):
    componentes = componentes_conexas(grafo)
    return max(componentes, key=len, default=[])
```

### 3. Verificar Si Todo Está Conectado
```python
def esta_conectado(grafo):
    componentes = componentes_conexas(grafo)
    return len(componentes) == 1
```

### 4. Puntos de Articulación (Cut Vertices)
- Vértices cuya remoción aumenta el número de componentes
- Algoritmo de Tarjan modificado

### 5. Puentes (Bridges)
- Aristas cuya remoción aumenta el número de componentes
- DFS con números de descubrimiento

## Conclusión

Los algoritmos de componentes conexas son fundamentales para:
1. **Análisis de redes:** Identificar comunidades
2. **Optimización:** Reducir problemas grandes a subproblemas
3. **Verificación:** Validar conectividad en sistemas
4. **Clustering:** Agrupar datos relacionados

> **Selección de algoritmo:** Use BFS/DFS para grafos no dirigidos, Tarjan para SCC en grafos dirigidos, y Union-Find para problemas dinámicos.

---

**Implemente estos algoritmos** para analizar la estructura de conectividad en sus grafos y optimizar algoritmos basados en componentes.
