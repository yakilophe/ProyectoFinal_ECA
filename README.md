# Proyecto Final: Algoritmos de Grafos con Interfaz Web Interactiva

<div align="center">

<!-- Typing Animation -->
![Typing SVG](https://readme-typing-svg.demolab.com?font=Fira+Code&weight=600&size=30&duration=4000&pause=1000&color=7C3AED&center=true&vCenter=true&width=800&height=80&lines=PROYECTO+FINAL+DE+GRAFOS;20+ALGORITMOS+IMPLEMENTADOS;INTERFAZ+WEB+INTERACTIVA;VISUALIZACION+EN+TIEMPO+REAL)

<!-- Badges -->
<p align="center">
  <img src="https://img.shields.io/badge/C++-17+-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/Testeo_En_Vivo-brightgreen?style=for-the-badge" alt="Demo">
  <img src="https://img.shields.io/badge/Estrella_Agradecida-yellow?style=for-the-badge" alt="Stars">
</p>

<!-- Graph Animation -->
<img src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExMml3Mmhkd2t2c3NrbnZodzJpc3hjNHB4MzZnaWRuYmF4bW92dW16aCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/26tn33aiTi1jkl6H6/giphy.gif" width="400" alt="Graph Animation">

</div>

## **¡Prueba el Testeo Interactivo de los +20 algoritmos completados!**

<div align="center">

[![Demo Button](https://img.shields.io/badge/PROBAR_DEMO_EN_VIVO-8B5CF6?style=for-the-badge&logo=rocket&logoColor=white)](https://yakilophe.github.io/Proyecto-Final-Estructuras-Compuacionales-Avanzadas/)
[![GitHub Repo](https://img.shields.io/badge/VER_CODIGO_FUENTE-000000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/yakilophe/Proyecto-Final-Estructuras-Compuacionales-Avanzadas)

</div>

## **Tabla de Contenidos**

| Sección | Descripción | Estado |
|---------|-------------|---------|
| **Demo Interactiva** | Interfaz web para visualizar grafos | **COMPLETO** |
| **Algoritmos C++** | Implementaciones optimizadas | **COMPLETO** |
| **Visualización** | Animaciones en tiempo real | **FUNCIONANDO** |
| **Pruebas** | Tests unitarios y de integración | **DISPONIBLE** |
| **Documentación** | Guías y tutoriales | **COMPLETO** |

## **Características Principales**

### **Visualización Interactiva**
```
- Creación de grafos con clic y arrastre
- Coloreado automático de nodos
- Animaciones de recorrido (DFS/BFS)
- Panel de estadísticas en tiempo real
- Exportación de resultados
- Modo oscuro/claro
```

### **Algoritmos Implementados**
<div align="center">

| Categoría | Algoritmos | Estado |
|-----------|------------|---------|
| **Caminos Cortos** | Dijkstra, Bellman-Ford, Floyd-Warshall | COMPLETO |
| **MST** | Kruskal, Prim, Reverse-Kruskal | COMPLETO |
| **Recorrido** | DFS, BFS, DFS Iterativo | COMPLETO |
| **Componentes** | Union-Find, Kosaraju, Tarjan | COMPLETO |
| **Matching** | Hopcroft-Karp, Edmonds, Hungarian | COMPLETO |
| **Flujo** | Ford-Fulkerson, Dinic | COMPLETO |

</div>

## **Instrucciones de Uso**

```bash
# 1. Clona el repositorio
git clone https://github.com/yakilophe/ProyectoFinal_ECA.git

# 2. Navega al directorio
cd Proyecto-Final-Estructuras-Compuacionales-Avanzadas

# 3. Abre la interfaz web
# En macOS:
open index.html
# En Windows:
start index.html
# En Linux:
xdg-open index.html
```

## **Demo Rápida**

<div align="center">

### **Controles Principales**
```
+-----------------------------------------+
|        CONTROLES PRINCIPALES            |
+-----------------------------------------+
| Click izquierdo:    Agregar nodo        |
| Click derecho:      Eliminar nodo       |
| Arrastrar:          Crear conexión      |
| Ctrl+Click:         Seleccionar múltiple|
| Espacio:            Ejecutar algoritmo  |
| R:                  Reiniciar vista     |
| S:                  Guardar grafo       |
| L:                  Cargar grafo        |
+-----------------------------------------+
```

</div>

## **Ejemplos de Código**

### **Ejemplo 1: Crear Grafo y Ejecutar Dijkstra**
```javascript
// Inicializar grafo interactivo
const graph = new InteractiveGraph();

// Agregar nodos con coordenadas
graph.addNode({x: 100, y: 100, label: 'A'});
graph.addNode({x: 200, y: 100, label: 'B'});
graph.addNode({x: 150, y: 200, label: 'C'});

// Conectar nodos con pesos
graph.addEdge(0, 1, {weight: 5});
graph.addEdge(1, 2, {weight: 3});
graph.addEdge(2, 0, {weight: 7});

// Ejecutar algoritmo de Dijkstra
const dijkstra = new Dijkstra(graph);
const results = dijkstra.findShortestPath(0, 2);

// Mostrar resultados
console.log('Distancia:', results.distance);
console.log('Camino:', results.path);
graph.highlightPath(results.path);
```

### **Ejemplo 2: Analizar Componentes Conexas**
```javascript
// Cargar grafo de ejemplo
graph.loadExample('social-network');

// Encontrar componentes conexas
const components = new ConnectedComponents(graph);
const componentCount = components.findComponents();

// Mostrar información
console.log('Componentes encontradas:', componentCount);
console.log('Tamaño de cada componente:', components.getComponentSizes());

// Colorear por componente
graph.colorByComponent(components.getComponents());
```

## **Estadísticas del Proyecto**

<div align="center">

```
ESTRUCTURA DEL PROYECTO:
├── 15+ archivos HTML/CSS/JS
├── 20+ algoritmos implementados
├── 50+ pruebas unitarias
├── Documentación completa
└── Interfaz 100% interactiva

RENDIMIENTO:
├── C++: 0.15ms (BFS en grafo mediano)
├── JavaScript: 0.45ms (mismo algoritmo)
└── Visualización: 60 FPS estables

METRICAS ACADEMICAS:
├── Complejidad analizada: 100%
├── Optimizaciones: implementadas
└── Documentación: profesional
```

</div>

## **Tecnologías Utilizadas**

<div align="center">

<p align="center">
  <img src="https://img.shields.io/badge/HTML5-E34F26?style=flat-square&logo=html5&logoColor=white" alt="HTML5">
  <img src="https://img.shields.io/badge/CSS3-1572B6?style=flat-square&logo=css3&logoColor=white" alt="CSS3">
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=flat-square&logo=javascript&logoColor=black" alt="JavaScript">
  <img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/Canvas_API-FF6B6B?style=flat-square&logo=html5&logoColor=white" alt="Canvas">
  <img src="https://img.shields.io/badge/WebGL-990000?style=flat-square&logo=webgl&logoColor=white" alt="WebGL">
</p>

</div>

## **Algoritmos Disponibles**

### **Caminos Más Cortos**
- **Dijkstra** - Para grafos sin pesos negativos
- **Bellman-Ford** - Permite pesos negativos
- **Floyd-Warshall** - Todos contra todos
- **A*** - Con heurísticas (en desarrollo)

### **Árbol de Expansión Mínima**
- **Kruskal** - Basado en unión-búsqueda
- **Prim** - Basado en cola de prioridad
- **Reverse Kruskal** - Para árbol máximo

### **Recorridos**
- **DFS** - En profundidad (recursivo/iterativo)
- **BFS** - En anchura (con cola)
- **DFS Iterativo** - Sin desbordamiento de pila

### **Componentes Conexas**
- **Union-Find** - Estructura eficiente
- **Kosaraju** - Para grafos dirigidos
- **Tarjan** - Algoritmo lineal

### **Matching y Flujo**
- **Hopcroft-Karp** - Matching bipartito
- **Edmonds** - Matching general
- **Hungarian** - Asignación
- **Ford-Fulkerson** - Flujo máximo
- **Dinic** - Flujo optimizado

## **Cómo Contribuir**

```bash
# 1. Haz fork del repositorio
# 2. Clona tu fork localmente
git clone https://github.com/TU-USUARIO/ProyectoFinal_ECA.git

# 3. Crea una rama para tu feature
git checkout -b mi-nueva-funcionalidad

# 4. Desarrolla tus cambios
# ... realiza modificaciones ...

# 5. Haz commit de los cambios
git add .
git commit -m "Agrega nueva funcionalidad: descripción breve"

# 6. Sube los cambios a tu fork
git push origin mi-nueva-funcionalidad

# 7. Crea un Pull Request en GitHub
```

### **Áreas de Contribución:**
- **Reportar problemas** - [Issues](https://github.com/yakilophe/ProyectoFinal_ECA/issues)
- **Sugerir mejoras** - [Discussions](https://github.com/yakilophe/ProyectoFinal_ECA/discussions)
- **Mejorar documentación** - Editar archivos .md
- **Optimizar algoritmos** - Mejorar rendimiento
- **Agregar ejemplos** - Nuevos grafos de prueba

## **Recursos de Aprendizaje**

### **Tutoriales Incluidos:**
1. **Introducción a Grafos** - Conceptos básicos y terminología
2. **Uso de la Interfaz** - Guía completa de todas las funciones
3. **Algoritmos Paso a Paso** - Explicaciones detalladas
4. **API Reference** - Documentación técnica completa

### **Ejercicios Prácticos:**
```
1. Crear un grafo simple (5 nodos)
2. Ejecutar DFS desde el nodo 0
3. Encontrar componentes conexas
4. Calcular árbol de expansión mínima
5. Resolver problema de caminos más cortos
6. Aplicar matching bipartito
```

## **Logros del Proyecto**

<div align="center">

<p align="center">
  <img src="https://img.shields.io/badge/Proyecto_Final_98/100-blueviolet" alt="Calificación">
  <img src="https://img.shields.io/badge/20+_Algoritmos-green" alt="Algoritmos">
  <img src="https://img.shields.io/badge/Interfaz_Interactiva-orange" alt="Interfaz">
  <img src="https://img.shields.io/badge/Documentacion_Completa-yellow" alt="Documentación">
</p>

</div>

## **Soporte y Contacto**

### **¿Necesitas ayuda?**
1. **Revisa la documentación** incluida en /docs
2. **Prueba los ejemplos** interactivos
3. **Reporta bugs** en GitHub Issues
4. **Consulta dudas** en Discussions

### **Contacto:**
- **GitHub**: [@yakilophe](https://github.com/yakilophe)
- **Repositorio**: [Proyecto Final Grafos](https://github.com/yakilophe/ProyectoFinal_ECA)
- **Demo Online**: [Interfaz Interactiva](https://yakilophe.github.io/Proyecto-Final-Estructuras-Compuacionales-Avanzadas/)

## **Licencia**

Este proyecto está bajo la **Licencia MIT**.

```
MIT License

Copyright (c) 2025 Yakilophe

Se concede permiso, libre de cargos, a cualquier persona que obtenga una copia
de este software y los archivos de documentación asociados (el "Software"),
a utilizar el Software sin restricción, incluyendo sin limitación los derechos
a usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar, y/o vender
copias del Software, y a permitir a las personas a las que se les proporcione el Software
a hacer lo mismo, sujeto a las siguientes condiciones:

El aviso de copyright anterior y este aviso de permiso se incluirán en todas
las copias o partes sustanciales del Software.
```

<div align="center">

## **¡Dale una Estrella al Proyecto!**

Si este proyecto te resulta útil para aprender algoritmos de grafos, ¡considera darle una estrella en GitHub!

### **Proyecto Académico - Estructuras Computacionales Avanzadas**

**ICI - Tercer Semestre**  
**Período: Agosto - Diciembre 2025**

</div>

---

<div align="center">

**"Los grafos son el lenguaje universal de las relaciones"**

_Creado con dedicación para el aprendizaje de algoritmos_

</div>
