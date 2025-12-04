#include <iostream>
#include <vector>

// Declaraciones de funciones existentes (asumidas en el scope global)
extern int matriz[100][100];
extern int n;
extern void inicializarMatriz();
extern void imprimirLista();

// --- Funciones de Simulación ---

// Función que simula la creación de un grafo NO PONDERADO
void crearGrafoNoPonderadoSimulacion(int num_nodos, const std::vector<std::pair<int, int>>& aristas) {
    n = num_nodos;
    inicializarMatriz();
    
    std::cout << "--- CREANDO GRAFO NO PONDERADO (N=" << n << ") ---\n";

    for (const auto& arista : aristas) {
        int a = arista.first;
        int b = arista.second;
        
        // Marcamos la conexión en ambos sentidos porque es NO dirigido
        matriz[a][b] = 1;
        matriz[b][a] = 1;
        std::cout << "  Arista agregada: (" << a << ", " << b << ")\n";
    }
}

// Función que simula la creación de un grafo PONDERADO
void crearGrafoPonderadoSimulacion(int num_nodos, const std::vector<std::tuple<int, int, int>>& aristas) {
    n = num_nodos;
    inicializarMatriz();
    
    std::cout << "--- CREANDO GRAFO PONDERADO (N=" << n << ") ---\n";

    for (const auto& arista : aristas) {
        int a = std::get<0>(arista);
        int b = std::get<1>(arista);
        int peso = std::get<2>(arista);
        
        // Guardamos el peso en ambas posiciones
        matriz[a][b] = peso;
        matriz[b][a] = peso;
        std::cout << "  Arista agregada: (" << a << ", " << b << ", peso=" << peso << ")\n";
    }
}


// Función principal de prueba
void simularPruebas() {
    std::cout << "\n============================================\n";
    std::cout << "          EJECUCIÓN DE PRUEBAS SIMULADAS    \n";
    std::cout << "============================================\n";

    // -------------------------------------------------------------------
    // PRUEBA 1: Grafo NO PONDERADO
    // Nodos: 4 (0, 1, 2, 3). Aristas: (0, 1), (1, 2), (3, 0).
    // El nodo 2 tiene un solo vecino.
    // -------------------------------------------------------------------
    std::vector<std::pair<int, int>> aristas_no_ponderadas = {
        {0, 1},
        {1, 2},
        {3, 0}
    };
    crearGrafoNoPonderadoSimulacion(4, aristas_no_ponderadas);
    imprimirLista();
    
    // -------------------------------------------------------------------
    // PRUEBA 2: Grafo PONDERADO
    // Nodos: 3 (0, 1, 2). Aristas: (0, 1, peso=5), (1, 2, peso=10).
    // -------------------------------------------------------------------
    std::vector<std::tuple<int, int, int>> aristas_ponderadas = {
        std::make_tuple(0, 1, 5),
        std::make_tuple(1, 2, 10)
    };
    crearGrafoPonderadoSimulacion(3, aristas_ponderadas);
    imprimirLista();
    
    std::cout << "\n============================================\n";
    std::cout << "          FIN DE PRUEBAS SIMULADAS          \n";
    std::cout << "============================================\n";
}

// NOTA: Para ejecutar esta prueba, llama a simularPruebas() en tu main()
// o renombra este archivo a main.cpp si solo quieres ejecutar las pruebas.
