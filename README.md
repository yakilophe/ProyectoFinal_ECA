# Algoritmos BFS y DFS: Recorrido de Grafos

## Introducción
Los algoritmos de BFS (Breadth-First Search) y DFS (Depth-First Search) son métodos fundamentales para recorrer grafos. BFS explora nivel por nivel, mientras que DFS profundiza en cada rama antes de retroceder.

## Breadth-First Search (BFS)

### Concepto
BFS explora todos los vecinos de un nodo antes de pasar a los vecinos de los vecinos. Utiliza una cola (estructura FIFO) para mantener el orden de exploración.

```python
def BFS(grafo, inicio):
    visitado = set()
    cola = deque([inicio])
    visitado.add(inicio)
    
    while cola:
        nodo = cola.popleft()
        print(nodo)  # Procesar nodo
        
        for vecino in grafo[nodo]:
            if vecino not in visitado:
                visitado.add(vecino)
                cola.append(vecino)
```

**Características:**
- **Estructura:** Cola (FIFO)
- **Complejidad:** O(V + E) en tiempo y espacio
- **Ventajas:** Encuentra el camino más corto en grafos no ponderados
- **Desventajas:** Requiere más memoria que DFS
- **Aplicaciones:** Redes sociales, navegación web, GPS

## Depth-First Search (DFS)

### Concepto
DFS explora tan lejos como sea posible a lo largo de cada rama antes de retroceder. Puede implementarse con una pila (iterativo) o recursión.

```python
def DFS_iterativo(grafo, inicio):
    visitado = set()
    pila = [inicio]
    
    while pila:
        nodo = pila.pop()
        if nodo not in visitado:
            visitado.add(nodo)
            print(nodo)  # Procesar nodo
            
            for vecino in reversed(grafo[nodo]):
                if vecino not in visitado:
                    pila.append(vecino)

# Versión recursiva
def DFS_recursivo(grafo, nodo, visitado=None):
    if visitado is None:
        visitado = set()
    
    visitado.add(nodo)
    print(nodo)  # Procesar nodo
    
    for vecino in grafo[nodo]:
        if vecino not in visitado:
            DFS_recursivo(grafo, vecino, visitado)
```

**Características:**
- **Estructura:** Pila (LIFO) o recursión
- **Complejidad:** O(V + E) en tiempo, O(V) en espacio
- **Ventajas:** Menor uso de memoria, útil para backtracking
- **Desventajas:** Puede no encontrar el camino más corto
- **Aplicaciones:** Laberintos, juegos de puzzles, compiladores

## Comparación BFS vs DFS

### Orden de Visita
```
Grafo: A conectado con B y C, B con D, C con E

BFS: A → B → C → D → E  (nivel por nivel)
DFS: A → B → D → C → E  (profundidad primero)
```

### Tabla Comparativa

| Característica | BFS | DFS |
|---------------|-----|-----|
| **Estructura** | Cola (FIFO) | Pila (LIFO) / Recursión |
| **Memoria** | O(V) (peor caso) | O(V) (altura del árbol) |
| **Camino más corto** | Sí (no ponderado) | No garantizado |
| **Complejidad** | O(V + E) | O(V + E) |
| **Conexidad** | Detecta componentes conexos | Detecta componentes conexos |
| **Ciclos** | Detecta en grafos no dirigidos | Detecta en grafos dirigidos y no dirigidos |
| **Óptimo para** | Camino más corto, niveles | Backtracking, orden topológico |

### Ejemplo Práctico: Recorrido de Grafo
```
Grafo de ejemplo:
     A
    / \
   B   C
  /   / \
 D   E   F
```

**Recorrido BFS:** A → B → C → D → E → F  
**Recorrido DFS:** A → B → D → C → E → F

## Aplicaciones Específicas

### BFS (Breadth-First Search)
1. **Redes sociales:** Encontrar conexiones de menor grado
2. **Navegación web:** Crawlers de motores de búsqueda
3. **GPS:** Ruta más corta en mapas
4. **Broadcast en redes:** Difusión de paquetes
5. **Puzzles:** Solución de menor número de movimientos

### DFS (Depth-First Search)
1. **Juegos de puzzles:** Backtracking (Sudoku, N-Queens)
2. **Compiladores:** Análisis sintáctico
3. **Sistemas de archivos:** Recorrido de directorios
4. **Redes:** Detección de ciclos
5. **Grafos dirigidos:** Orden topológico, componentes fuertemente conexos

## Complejidad y Optimización

### Análisis de Complejidad
- **Tiempo:** O(V + E) para ambos algoritmos
- **Espacio BFS:** O(V) (todos los nodos de un nivel)
- **Espacio DFS:** O(V) (altura del árbol de recursión)

### Consideraciones de Implementación

**BFS óptimo cuando:**
- Necesitas el camino más corto
- El grafo es ancho pero poco profundo
- Memoria no es una restricción crítica

**DFS óptimo cuando:**
- Necesitas explorar todas las posibilidades
- El grafo es profundo pero estrecho
- Memoria es limitada
- Buscas soluciones con backtracking

## Visualización del Proceso

### BFS: Exploración por Niveles
```
Nivel 0: [A]
Nivel 1: [B, C]
Nivel 2: [D, E, F]
```

### DFS: Exploración por Ramas
```
Rama 1: A → B → D (retrocede)
Rama 2: A → C → E → F (retrocede)
```

## Casos de Uso Comunes

### Problemas para BFS:
1. **Six Degrees of Separation:** Encontrar conexiones mínimas
2. **Word Ladder:** Transformar palabras cambiando una letra
3. **Maze Solver:** Salida más cercana en laberinto

### Problemas para DFS:
1. **Sudoku Solver:** Backtracking para llenar celdas
2. **Tree Traversal:** In-order, pre-order, post-order
3. **Connected Components:** Encontrar grupos conectados

## Conclusión

**BFS** es ideal cuando necesitas encontrar el camino más corto o trabajar con niveles de conexión. **DFS** es mejor para problemas que requieren exploración exhaustiva o backtracking. La elección depende del problema específico y de las restricciones de memoria.

> **Nota:** Ambos algoritmos son la base para algoritmos más complejos como Dijkstra (BFS con pesos) y algoritmos de componentes conexos.

---

**Implementa ambos algoritmos** para entender sus diferencias prácticas y selecciona el más adecuado según el problema a resolver.
