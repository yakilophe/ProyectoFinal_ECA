#include <iostream>
#include <vector>
#include <utility> // para std::pair
#include <tuple>   // para std::tuple
#include <list>    // opcional, pero mejor usar vector<vector> para grafos


using AristaPeso = std::pair<int, int>;
extern std::vector<std::vector<AristaPeso>> lista_adyacencia;
extern int n;
extern void inicializarLista();
extern void imprimirLista();


// --- Funciones de Simulación ---

/**
 * Simula la creación de un grafo NO PONDERADO (peso = 1)
 * Las aristas se añaden simétricamente.
 */
void crearGrafoNoPonderadoSimulacion(int num_nodos, const std::vector<std::pair<int, int>>& aristas) {
    n = num_nodos;
    // Inicializar el contenedor global (la lista de adyacencia)
    lista_adyacencia.assign(n, std::vector<AristaPeso>());
    
    std::cout << "--- CREANDO GRAFO NO PONDERADO (N=" << n << ") ---\n";

    for (const auto& arista : aristas) {
        int u = arista.first;
        int v = arista.second;
        
        // El peso siempre es 1 en NO ponderado
        int peso = 1; 

        // Añadir u -> v
        lista_adyacencia[u].push_back({v, peso});
        // Añadir v -> u (es NO dirigido)
        lista_adyacencia[v].push_back({u, peso});
        
        std::cout << "  Arista agregada: (" << u << ", " << v << ")\n";
    }
}

/**
 * Simula la creación de un grafo PONDERADO (peso > 1)
 * Las aristas se añaden simétricamente con el peso especificado.
 */
void crearGrafoPonderadoSimulacion(int num_nodos, const std::vector<std::tuple<int, int, int>>& aristas) {
    n = num_nodos;
    // Inicializar el contenedor global
    lista_adyacencia.assign(n, std::vector<AristaPeso>());

    std::cout << "--- CREANDO GRAFO PONDERADO (N=" << n << ") ---\n";

    for (const auto& arista : aristas) {
        int u = std::get<0>(arista);
        int v = std::get<1>(arista);
        int peso = std::get<2>(arista);
        
        // Añadir u -> v
        lista_adyacencia[u].push_back({v, peso});
        // Añadir v -> u (es NO dirigido)
        lista_adyacencia[v].push_back({u, peso});
        
        std::cout << "  Arista agregada: (" << u << ", " << v << ", peso=" << peso << ")\n";
    }
}


// Función principal de prueba
void simularPruebasLista() {
    std::cout << "\n============================================\n";
    std::cout << "  EJECUCIÓN DE PRUEBAS SIMULADAS (LISTA DE ADYACENCIA) \n";
    std::cout << "============================================\n";

    // -------------------------------------------------------------------
    // PRUEBA 1: Grafo NO PONDERADO
    // Nodos: 4. Aristas: (0, 1), (1, 2), (3, 0). 
    // Nodo 2 tiene un solo vecino.
    // -------------------------------------------------------------------
    std::vector<std::pair<int, int>> aristas_no_ponderadas = {
        {0, 1},
        {1, 2},
        {3, 0}
    };
    crearGrafoNoPonderadoSimulacion(4, aristas_no_ponderadas);
    std::cout << "\n--- Resultado Esperado: Grafo NO Ponderado ---\n";
    imprimirLista();
    
    // -------------------------------------------------------------------
    // PRUEBA 2: Grafo PONDERADO
    // Nodos: 3. Aristas: (0, 1, peso=5), (1, 2, peso=10).
    // -------------------------------------------------------------------
    std::vector<std::tuple<int, int, int>> aristas_ponderadas = {
        std::make_tuple(0, 1, 5),
        std::make_tuple(1, 2, 10)
    };
    crearGrafoPonderadoSimulacion(3, aristas_ponderadas);
    std::cout << "\n--- Resultado Esperado: Grafo Ponderado ---\n";
    imprimirLista();
    
    std::cout << "\n============================================\n";
    std::cout << "          FIN DE PRUEBAS SIMULADAS          \n";
    std::cout << "============================================\n";
}
