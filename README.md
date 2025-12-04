# Repositorio de Algoritmos de Grafos
## Proyecto Final - Estructuras Computacionales Avanzadas
### Fecha de entrega: 4 de diciembre de 2025

![GIF relacionado con grafos](https://th.bing.com/th/id/R.18a4949fc9c8067172d3b96e302e7097?rik=%2fLZCQFlB6A7KlQ&pid=ImgRaw&r=0)

<div align="center" style="margin: 30px 0;">
  <a href="https://github.com/yakilophe/ProyectoFinal_ECA.git" style="background-color: #FF69B4; color: white; padding: 12px 25px; text-decoration: none; border-radius: 6px; font-weight: bold; margin: 8px; display: inline-block; border: none;">
    Repositorio Principal
  </a>
  
  <a href="https://github.com/yakilophe/ProyectoFinal_ECA/commits" style="background-color: #FF69B4; color: white; padding: 12px 25px; text-decoration: none; border-radius: 6px; font-weight: bold; margin: 8px; display: inline-block; border: none;">
    Historial de Commits
  </a>
  
  <a href="https://raw.githack.com/yakilophe/ProyectoFinal_ECA/Testeo-InterfazWeb/scrumtablero.html" style="background-color: #FF69B4; color: white; padding: 12px 25px; text-decoration: none; border-radius: 6px; font-weight: bold; margin: 8px; display: inline-block; border: none;">
    Tablero Scrum Interactivo
  </a>
  
  <a href="https://github.com/yakilophe/ProyectoFinal_ECA/blob/main/proyecto_estructura_3er.pdf" style="background-color: #FF69B4; color: white; padding: 12px 25px; text-decoration: none; border-radius: 6px; font-weight: bold; margin: 8px; display: inline-block; border: none;">
    Documentación PDF
  </a>
</div>

---

## Integrantes del equipo

| Nombre                        | Rol asignado   | Responsabilidades principales |
|-------------------------------|----------------|-------------------------------|
| Norma Yakelin Herrada López   | Scrum Master   | Facilitar el equipo, gestionar tablero (GitHub), eliminar impedimentos, asegurar metodología ágil. |
| Gustavo Trueba Cardoso        | Product Owner  | Definir y priorizar historias de usuario, validar criterios de aceptación (Big-O, pruebas). |
| Luis Octavio Delgado Ramírez  | Developer      | Implementación de código fuente, refactorización y escritura de pruebas unitarias. |
| Valeria Itzel Trinidad González | Developer    | Implementación de código fuente, refactorización y escritura de pruebas unitarias. |
| Ángel Joshua González Bennetts| Developer      | Implementación de código fuente, documentación técnica y análisis de complejidad. |

---

## Metodología - Scrum

El proyecto se desarrolló con metodología ágil Scrum en un sprint de una semana, usando GitHub Projects como tablero de seguimiento.

**Equipo Scrum:**
- Scrum Master: Norma Yakelin Herrada López
- Product Owner: Gustavo Trueba Cardoso
- Developers: Luis Octavio Delgado, Valeria Itzel Trinidad, Ángel Joshua González

**Duración del sprint:** 27 de noviembre - 3 de diciembre 2025

**Objetivo:** Implementar, probar y documentar algoritmos de grafos en C++ con buenas prácticas, pruebas automatizadas y documentación técnica.

---

## Estructura del repositorio

```
ProyectoFinal_ECA/
├── README.md
├── proyecto_estructura_3er.pdf   # Documentación completa del proyecto
├── docs/                         # Documentación adicional
├── src/                          # Código fuente principal
│   ├── 1-representacion-grafos/  # Matriz de adyacencia, lista, incidencia
│   ├── 2-algoritmos-recorrido/   # BFS, DFS
│   ├── 3-componentes-conexas/    # BFS, DFS, Union-Find, Gabow, Kosaraju, Tarjan
│   ├── 4-caminos-cortos/         # Backtracking con poda, Bellman-Ford, Floyd-Warshall
│   ├── 5-verificacion-arbol/     # DFS, BFS y grados, DFS con N-1
│   ├── 6-arbol-expansion/        # Kruskal, Prim, Reverse-Kruskal
│   ├── 7-grafo-bipartito/        # BFS, multiplicación de matrices, DFS
│   └── 8-pareo-matching/         # Edmonds, Greedy, Hopcroft-Karp, Húngaro, Random Greedy
├── Testeo-InterfazWeb/           # Rama con interfaz web y tablero Scrum
│   ├── scrumtablero.html         # Tablero Scrum interactivo
│   ├── index.html                # Interfaz principal
│   └── tests/                    # Pruebas web
├── testeo/                       # Rama dedicada a pruebas en C++
│   ├── test-bfs.cpp
│   ├── test-dfs.cpp
│   ├── test-dijkstra.cpp
│   ├── test-kruskal.cpp
│   ├── test-bipartito.cpp
│   └── ...
├── .github/workflows/            # CI/CD
└── Makefile / CMakeLists.txt     # Sistema de compilación
```

---

## Acceso directo a las páginas web

**Tablero Scrum (vista funcional):**  
https://raw.githack.com/yakilophe/ProyectoFinal_ECA/Testeo-InterfazWeb/scrumtablero.html

**Rama principal (main):**  
https://github.com/yakilophe/ProyectoFinal_ECA

**Rama de testeo e interfaz web:**  
https://github.com/yakilophe/ProyectoFinal_ECA/tree/Testeo-InterfazWeb

**Historial de commits completo:**  
https://github.com/yakilophe/ProyectoFinal_ECA/commits

**Documentación PDF:**  
https://github.com/yakilophe/ProyectoFinal_ECA/blob/main/proyecto_estructura_3er.pdf

---

## Algoritmos implementados

### 1. Representación de grafos
- Matriz de adyacencia (no dirigido, ponderado/no ponderado)
- Visualización como lista de adyacencia (no dirigido, ponderado/no ponderado)
- Matriz de incidencia (dirigido/no dirigido, ponderado/no ponderado)

### 2. Algoritmos de recorrido
- BFS (Breadth-First Search)
- DFS (Depth-First Search)

### 3. Componentes conexas
- Con BFS
- Con DFS
- Con Union-Find
- Gabow
- Kosaraju
- Tarjan

### 4. Caminos más cortos
- Backtracking con poda
- Bellman-Ford
- Floyd-Warshall

### 5. Verificación de árbol
- DFS
- BFS y grados
- DFS, grados y N-1

### 6. Árbol de expansión
- Kruskal
- Prim
- Reverse-Kruskal

### 7. Grafo bipartito
- BFS
- Multiplicación de matrices
- DFS

### 8. Pareo (Matching)
- Edmonds (Blossom)
- Greedy
- Hopcroft-Karp
- Húngaro (Kuhn-Munkres)
- Random Greedy

---

## Análisis de complejidad (Big-O)

| Algoritmo / Estructura          | Tiempo         | Espacio       |
|---------------------------------|----------------|---------------|
| Matriz de adyacencia           | O(N²)          | O(N²)         |
| Lista de adyacencia (visual.)  | O(N²)          | O(N²)         |
| Matriz de incidencia           | O(V×E)         | O(V×E)        |
| BFS/DFS (con matriz)           | O(N²)          | O(N²)         |
| Componentes conexas (BFS/DFS)  | O(N²)          | O(N²)         |
| Union-Find                     | O(N²)          | O(N²)         |
| Gabow / Kosaraju / Tarjan      | O(N²)          | O(N²)         |
| Backtracking con poda          | O(N!)          | O(N²)         |
| Bellman-Ford                   | O(N³)          | O(N²)         |
| Floyd-Warshall                 | O(N³)          | O(N²)         |
| Verificación árbol (DFS/BFS)   | O(V+E)         | O(V+E)        |
| Kruskal                        | O(E log E)     | O(V+E)        |
| Prim                           | O(V²)          | O(V²)         |
| Reverse-Kruskal                | O(E²)          | O(V²)         |
| Bipartito (BFS/DFS)            | O(V+E)         | O(V+E)        |
| Bipartito (mult. matrices)     | O(V⁴)          | O(V²)         |
| Edmonds (Blossom)              | O(V³)          | O(V+E)        |
| Greedy matching                | O(E)           | O(V+E)        |
| Hopcroft-Karp                  | O(E√V)         | O(V+E)        |
| Húngaro                        | O(V³)          | O(V²)         |

---

## Análisis y discusión

La implementación se realizó principalmente con matrices de adyacencia, lo que facilita la verificación de conexiones en O(1), pero eleva la complejidad en grafos dispersos para recorridos y componentes conexas a O(N²).

El uso de Scrum permitió organizar el trabajo en un tiempo limitado, con roles definidos, ceremonias regulares y seguimiento visual mediante GitHub Projects. La integración de pruebas unitarias y documentación técnica aseguró la calidad del código entregado.

---

## Conclusiones

- Se implementaron más de 20 algoritmos de grafos en C++ con análisis de complejidad.
- La metodología ágil Scrum fue efectiva para coordinar al equipo y cumplir los objetivos en una semana.
- La estructura modular del repositorio (rama src/ por categorías y rama testeo/ para pruebas) facilita el mantenimiento y la extensión futura.
- El análisis de Big-O realizado para cada algoritmo proporciona una guía clara sobre su aplicabilidad y limitaciones en diferentes contextos.

---

## Referencias

1. Aprende con IA. (2025). Entendiendo grafos bipartitos [Video]. YouTube.
2. UCAM Universidad Católica de Murcia. (2016). Matemática Discreta - Grafo bipartido [Video]. YouTube.
3. Universitat Politècnica de València. (2011). Problema de emparejamientos [Video]. YouTube.
4. Usha's EduVids. (2024). Graph Matching, Maximal Matching, Maximum matching, Perfect Matching [Video]. YouTube.
5. OptWhiz. (2022). Can we assign everyone a job? (maximum matchings) | Bipartite Matchings [Video]. YouTube.
6. Varun Sir. (s.f.). BFS & DFS | Breadth First Search | Depth First Search [Video]. YouTube.
7. WilliamFiset. (2020). Tarjan's Strongly Connected Component (SCC) Algorithm [Video]. YouTube.
8. The code bit. (2025). Gabow's Algorithm Explained [Video]. YouTube.
9. Potato Coders. (2020). Union Find in 5 minutes [Video]. YouTube.
10. HeadEasy. (2023). Kosaraju's Algorithm | Strongly Connected Components [Video]. YouTube.
11. Juan Villalpando. (2021). Método Kruskal y Prim; Árbol Recubridor Mínimo y Máximo [Video]. YouTube.
12. Balvin, J. (2022). Árbol de Expansión Mínima (Prim + Kruskal) [Video]. YouTube.
13. Rodríguez, F. (2020). Grafos: Árbol parcial mínimo con algoritmo de Prim [Video]. YouTube.
14. Estudiante Digital. (2021). Árbol de Expansión Mínima - Algoritmo de Kruskal [Video]. YouTube.

---

<div align="center">
  <p><strong>Repositorio principal:</strong> <a href="https://github.com/yakilophe/ProyectoFinal_ECA">https://github.com/yakilophe/ProyectoFinal_ECA</a></p>
  <p><strong>Tablero Scrum (Vista Web):</strong> <a href="https://raw.githack.com/yakilophe/ProyectoFinal_ECA/Testeo-InterfazWeb/scrumtablero.html">Ver Tablero Interactivo</a></p>
  <p><strong>Documentación completa:</strong> <a href="https://github.com/yakilophe/ProyectoFinal_ECA/blob/main/proyecto_estructura_3er.pdf">Descargar PDF</a></p>
</div>

*Proyecto desarrollado como parte de la materia Estructuras Computacionales Avanzadas, 2025.*
