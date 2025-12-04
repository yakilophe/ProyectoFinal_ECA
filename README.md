# Representación de Grafos: Matrices y Listas

## Introducción
Los grafos son estructuras fundamentales en ciencia de computación, utilizados para modelar relaciones entre objetos. Su representación eficiente es crucial para el rendimiento de algoritmos. Aquí exploramos tres métodos principales:

## Métodos de Representación

### 1. Matriz de Adyacencia
Una matriz cuadrada donde cada celda `[i][j]` indica la existencia (y peso) de una arista entre los vértices `i` y `j`.

```python
# Ejemplo: Grafo no dirigido con 4 vértices
    0  1  2  3
0  [0, 1, 0, 1]
1  [1, 0, 1, 0]
2  [0, 1, 0, 1]
3  [1, 0, 1, 0]
```

**Características:**
- **Ventajas:** Consulta O(1) de adyacencia
- **Desventajas:** O(V²) en espacio
- **Ideal para:** Grafos densos

### 2. Lista de Adyacencia
Cada vértice mantiene una lista de sus vecinos directos.

```python
# Mismo grafo representado como lista
0: [1, 3]
1: [0, 2]
2: [1, 3]
3: [0, 2]
```

**Características:**
- **Ventajas:** Espacio O(V + E)
- **Desventajas:** Consulta O(deg(v)) de adyacencia
- **Ideal para:** Grafos dispersos

### 3. Matriz de Incidencia
Matriz V × E donde cada fila representa un vértice y cada columna una arista.

```python
# Vértices: 0,1,2,3 | Aristas: (0,1), (1,2), (2,3), (3,0)
   e1 e2 e3 e4
0 [ 1, 0, 0, 1 ]
1 [ 1, 1, 0, 0 ]
2 [ 0, 1, 1, 0 ]
3 [ 0, 0, 1, 1 ]
```

**Características:**
- **Ventajas:** Representa múltiples aristas fácilmente
- **Desventajas:** Espacio O(V × E), ineficiente para grafos densos

## Comparación Visual

```
Densidad del Grafo  ->  Método Recomendado
   Baja             ->  Lista de Adyacencia
   Media/Alta       ->  Matriz de Adyacencia
   Multigrafo       ->  Matriz de Incidencia
```

## Aplicaciones Prácticas

| Representación        | Casos de Uso Típicos                     |
|----------------------|------------------------------------------|
| Matriz Adyacencia    | Algoritmos Floyd-Warshall, grafos pequeños |
| Lista Adyacencia     | BFS/DFS, grafos de redes sociales        |
| Matriz Incidencia    | Teoría de grafos, análisis de circuitos  |

## Animación Conceptual
Cada representación transforma la misma estructura de grafo, optimizando diferentes operaciones según las necesidades del algoritmo.

> Nota: La elección de representación impacta directamente en la eficiencia temporal y espacial de tus algoritmos gráficos.

---

**Explora cada implementación** en los archivos correspondientes para ver ejemplos de código y análisis de complejidad detallados.
