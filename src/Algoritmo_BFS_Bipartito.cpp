#include <iostream>  // Necesario para leer datos y escribir resultados en la pantalla
#include <vector>    // Necesario para usar listas que guardan las conexiones y los colores
#include <queue>     // Necesario para usar la 'cola', que organiza la forma en que exploramos el grafo
#include <algorithm> // Contiene funciones utiles para manipular colecciones
#include <utility>   // Proporciona la estructura 'pair' (par), usada para representar las aristas (u, v)
#include <limits>    // Contiene informacion sobre limites, esencial para manejar errores de entrada

using namespace std; 

// ***************************************************************
// FUNCION PRINCIPAL DEL ALGORITMO: VERIFICACION DE GRAFO BIPARTITO
// ***************************************************************

// La funcion 'esBipartito' intenta colorear el grafo con solo dos colores.
// Si lo logra, es bipartito (true). Si encuentra un conflicto, no lo es (false).
bool esBipartito(vector< vector<int> >& grafo, int V) {
	
    // 1. PREPARACION DEL COLOREO
    // Creamos la lista de colores: -1 (sin color); 0 (Color A); 1 (Color B).
    vector<int> color(V, -1);

    // 2. ITERACION SOBRE TODOS LOS NODOS
    // Recorremos todos los nodos. Esto asegura que visitemos todas las partes 
    // del grafo, incluso si estan desconectadas.
    for (int inicio = 0; inicio < V; inicio++) {
        
        // Si el nodo 'inicio' no tiene color (-1), iniciamos un nuevo chequeo en esta parte.
        if (color[inicio] == -1) {
            
            // ************ INICIO DEL ALGORITMO BFS (COLOREO POR NIVELES) ************
            
            queue<int> cola; // Cola para organizar el recorrido
            cola.push(inicio);
            color[inicio] = 0; // Asignamos el primer color (Color A) al nodo de inicio

            // Mientras haya nodos en la cola para visitar, continuamos el proceso.
            while (!cola.empty()) {
                
                // Sacamos el nodo actual ('u') de la cola para procesarlo.
                int u = cola.front();
                cola.pop();

                // Revisamos a todos los "vecinos" (nodos conectados) del nodo actual 'u'.
                // Usamos size_t solo porque es el tipo correcto para contar elementos, pero es como un contador normal.
                for (size_t i = 0; i < grafo[u].size(); ++i) { 
                    int vecino = grafo[u][i];

                    // CONDICION 1: VECINO SIN COLOREAR
                    if (color[vecino] == -1) {
                        // Le asignamos el color opuesto al nodo actual.
                        // Esto garantiza la alternancia de colores (A, B, A, B...).
                        color[vecino] = 1 - color[u];
                        
                        // Anadimos el vecino a la cola para seguir el recorrido.
                        cola.push(vecino);
                    }
                    // CONDICION 2: ¡CONFLICTO DE COLORES!
                    // Si el vecino ya esta coloreado y su color es IGUAL al del nodo 'u'.
                    else if (color[vecino] == color[u]) {
                        // El grafo NO es bipartito (hay dos nodos conectados con el mismo color).
                        return false; 
                    }
                    // CONDICION 3: Vecino ya coloreado con el color opuesto (todo bien), pasamos al siguiente.
                }
            }
            // ************ FIN DEL ALGORITMO BFS ************
        }
    }
    
    // Si el algoritmo completo todo el recorrido sin encontrar conflictos, el grafo ES bipartito.
    return true;
}

// ***************************************************************
// FUNCION PARA MOSTRAR LA MATRIZ DE ADYACENCIA
// ***************************************************************
void mostrarMatriz(const vector< vector<int> >& grafo, int V) {

    vector< vector<int> > matriz(V, vector<int>(V, 0));

    for (int i = 0; i < V; i++) {
        for (size_t j = 0; j < grafo[i].size(); j++) {
            int v = grafo[i][j];
            matriz[i][v] = 1;
        }
    }

    cout << "\n===============================================" << endl;
    cout << "               MATRIZ DE ADYACENCIA" << endl;
    cout << "===============================================" << endl;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

// ***************************************************************
// FUNCION PRINCIPAL DEL PROGRAMA (ENTRADA, SALIDA Y MENU)
// ***************************************************************
int main() {
    // setlocale(LC_ALL, ""); // Eliminado
    
    int V, E;
    int opcion_menu;

    cout << "===============================================" << endl;
    cout << "        VERIFICACION DE GRAFO BIPARTITO      " << endl;
    cout << "===============================================" << endl;

    cout << "1. Usar grafo NO dirigido NO ponderado (predefinido)" << endl;
    cout << "2. Usar grafo NO dirigido PONDERADO (predefinido)" << endl;
    cout << "3. Ingresar grafo manualmente" << endl;
    cout << "4. Salir" << endl;
    cout << "Opcion: ";
    cin >> opcion_menu;

    if (opcion_menu == 4) return 0;

    vector< vector<int> > grafo_adyacencia;

    // ----- GRAFO 1 PREDEFINIDO -----
    if (opcion_menu == 1 || opcion_menu == 2) {
        V = 5;
        grafo_adyacencia.assign(V, vector<int>());

        grafo_adyacencia[0].push_back(1);
        grafo_adyacencia[1].push_back(0);

        grafo_adyacencia[0].push_back(4);
        grafo_adyacencia[4].push_back(0);

        grafo_adyacencia[0].push_back(3);
        grafo_adyacencia[3].push_back(0);

        grafo_adyacencia[1].push_back(3);
        grafo_adyacencia[3].push_back(1);

        grafo_adyacencia[1].push_back(2);
        grafo_adyacencia[2].push_back(1);

        grafo_adyacencia[2].push_back(3);
        grafo_adyacencia[3].push_back(2);

        if (opcion_menu == 2) {
            cout << "\n[NOTA]: Los pesos se ignoran para la verificacion de biparticion.\n";
        }
    }

    // ----- INGRESO MANUAL (DESDE 0) -----
    if (opcion_menu == 3) {
        do {
            cout << "Introduce el numero de vertices (nodos): ";
            cin >> V;
            if (V <= 0) cout << "[ERROR] Debe haber al menos 1 nodo." << endl;
        } while (V <= 0);

        cout << "Introduce el numero de aristas (conexiones): ";
        cin >> E;

        grafo_adyacencia.assign(V, vector<int>());

        cout << "Introduce las aristas (u v). PUEDES USAR NUMEROS DEL 0 AL " << (V - 1) << ":" << endl;
        cout << " (ejemplo: 0 1)" << endl;
        
        for (int i = 0; i < E; i++) {
            int u, v;
            cout << "Arista " << i + 1 << ": ";
            cin >> u >> v;

            if (u >= 0 && u < V && v >= 0 && v < V) {
                grafo_adyacencia[u].push_back(v);
                grafo_adyacencia[v].push_back(u); 
            } else {
                cout << "[ERROR]: Los nodos ingresados no existen. Deben ser entre 0 y " << (V - 1) << "." << endl;
                i--; 
            }
        }
    }

    // ----- MOSTRAR MATRIZ -----
    mostrarMatriz(grafo_adyacencia, V);

    cout << "\n===============================================" << endl;
    cout << "                RESULTADO                      " << endl;
    cout << "===============================================" << endl;

    if (esBipartito(grafo_adyacencia, V)) {
        cout << "[EXITO] El grafo ES bipartito." << endl;
        cout << "EXPLICACION: Fue posible dividir todos los nodos en dos grupos (A y B) sin conexiones internas." << endl;
    }
    else {
        cout << "[FALLA] El grafo NO es bipartito." << endl;
        cout << "EXPLICACION: El grafo contiene un ciclo impar (un camino cerrado impar) que impide la division." << endl;
    }

    return 0; // El programa termina correctamente.
}
