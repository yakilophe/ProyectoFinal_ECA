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
// FUNCION PRINCIPAL DEL PROGRAMA (ENTRADA, SALIDA Y MENU)
// ***************************************************************
int main() {
    // setlocale(LC_ALL, ""); // Eliminado
    
    int V, E;
    int opcion_ponderacion;
    bool es_ponderado = false;

    // --- MENU DE TITULO ---
    cout << "===============================================" << endl;
    cout << "        VERIFICACION DE GRAFO BIPARTITO      " << endl;
    cout << "===============================================" << endl;
    cout << "  (El algoritmo funciona para Grafos NO DIRIGIDOS)" << endl;
    cout << "-----------------------------------------------" << endl;

    // --- MENU DE PONDERACION CON VALIDACION ---
    // Este ciclo 'do-while' repite la pregunta si el usuario no escribe 1 o 2.
    do {
        cout << "1. Su grafo es Ponderado (tiene pesos) o No Ponderado?" << endl;
        cout << "    [1] No Ponderado" << endl;
        cout << "    [2] Ponderado" << endl;
        cout << "    Opcion: ";
        cin >> opcion_ponderacion;

        // Si la opcion NO es 1 Y TAMPOCO es 2, mostramos error.
        if (opcion_ponderacion != 1 && opcion_ponderacion != 2) {
            cout << "\n[ERROR] Opcion invalida. Por favor ingrese 1 o 2.\n" << endl;
        }

    // El ciclo se repite MIENTRAS la opcion sea diferente de 1 y de 2.
    } while (opcion_ponderacion != 1 && opcion_ponderacion != 2);
    
    // Una vez validada la opcion, configuramos el modo.
    if (opcion_ponderacion == 2) {
        es_ponderado = true;
        cout << "\n[NOTA]: Los pesos se ignoraran para la verificacion de biparticion." << endl;
    }

    // --- LECTURA DEL GRAFO ---
    cout << "\n===============================================" << endl;
    cout << "            CONFIGURACION DEL GRAFO            " << endl;
    cout << "===============================================" << endl;
    
    // 1. SOLICITAR NUMERO DE NODOS (VALIDADO)
    // Nos aseguramos de que al menos haya 1 nodo.
    do {
        cout << "Introduce el numero de vertices (nodos): ";
        cin >> V;
        if (V <= 0) cout << "[ERROR] Debe haber al menos 1 nodo." << endl;
    } while (V <= 0);

    cout << "Introduce el numero de aristas (conexiones): ";
    cin >> E;

    // 2. CREAR LA ESTRUCTURA
    // Lista de adyacencia (lista de listas que almacena las conexiones).
    vector< vector<int> > grafo_adyacencia(V);

    // 3. LEER LAS CONEXIONES (ARISTAS)
    cout << "Introduce las aristas (u v). PUEDES USAR NUMEROS DEL 1 AL " << V << ":" << endl;
    if (es_ponderado) {
           cout << " (ejemplo: 1 2 5.5)" << endl;
    } else {
           cout << " (ejemplo: 1 2)" << endl;
    }
    
    for (int i = 0; i < E; i++) {
        int u, v;
        double peso = 0; 

        cout << "Arista " << i + 1 << ": ";
        cin >> u >> v;

        if (es_ponderado) {
            cin >> peso; // Leemos el peso si el usuario dijo que es ponderado.
        }
        
        // --- AJUSTE "HUMANO" ---
        // Restamos 1 porque la gente cuenta desde 1, pero la computadora cuenta desde 0.
        u = u - 1;
        v = v - 1;

        // --- PROTECCION CONTRA ERRORES ---
        // Verificamos si los nodos ingresados existen realmente.
        if (u >= 0 && u < V && v >= 0 && v < V) {
            // Agregamos la conexion en ambos sentidos (Grafo No Dirigido).
            grafo_adyacencia[u].push_back(v);
            grafo_adyacencia[v].push_back(u); 
        } else {
            cout << "[ERROR]: Los nodos ingresados no existen. Deben ser entre 1 y " << V << "." << endl;
            // Restamos 1 al contador 'i' para que el programa vuelva a pedir esta misma arista.
            i--; 
        }
    }

    // 4. EJECUTAR EL ALGORITMO Y MOSTRAR RESULTADO
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
