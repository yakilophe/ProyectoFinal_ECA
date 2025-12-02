#include <iostream>  // Libreria para la entrada y salida de datos (pedirle cosas al usuario y mostrar resultados)
#include <vector>    // Libreria clave para usar listas flexibles (para guardar el grafo y la lista de colores)

using namespace std; 

// ***************************************************************
// FUNCION RECURSIVA CENTRAL: VERIFICACION DE BIPARTITO (DFS)
// ***************************************************************

// La funcion DFS_Bipartito verifica si el grafo puede colorearse con solo dos colores.
// Utiliza la recursion (profundidad) para explorar el grafo.
// Retorna 'true' si es bipartito, 'false' en caso de conflicto.
bool DFS_Bipartito(int u,             // 'u' es el nodo actual que estamos coloreando
                   int color_actual,  // El color que debemos asignar a 'u' (1 o 0)
                   vector< vector<int> >& grafo, // La lista de adyacencia (las conexiones)
                   vector<int>& color)  // La lista de colores: -1 (no coloreado), 0 (Grupo A), 1 (Grupo B)
{
    // 1. ASIGNAR COLOR AL NODO ACTUAL
    color[u] = color_actual;

    // 2. RECORRER VECINOS Y COMPROBAR LA REGLA BIPARTITA
    for (size_t i = 0; i < grafo[u].size(); ++i) {
        
        int vecino = grafo[u][i]; 
        
        // Caso A: El vecino NO ha sido coloreado.
        if (color[vecino] == -1) {
            
            // Asignamos el color OPUESTO (1 - color_actual) y nos sumergimos recursivamente.
            if (!DFS_Bipartito(vecino, 1 - color_actual, grafo, color)) {
                return false; // Conflicto detectado en la rama profunda.
            }
        }
        // Caso B: El vecino YA esta coloreado con el MISMO color.
        else if (color[vecino] == color_actual) {
            
            // ¡VIOLACION DE LA REGLA! El grafo no es bipartito.
            cout << "\n[CONFLICTO ENCONTRADO]: Los nodos " << u << " y " << vecino
                 << " estan conectados y ambos pertenecen al color " << color_actual 
                 << " (" << (color_actual == 0 ? "Grupo A" : "Grupo B") << ")." << endl;
            return false; 
        }
        // Caso C: El vecino YA esta coloreado con el color opuesto. (Esta bien, continuamos).
    }
    
    // Si terminamos el recorrido sin conflictos, esta porcion es bipartita.
    return true; 
}

// ***************************************************************
// FUNCION PARA MOSTRAR MATRIZ DE ADYACENCIA
// ***************************************************************
void mostrarMatrizAdyacencia(vector< vector<int> >& matriz, int V) {
    cout << "\nMATRIZ DE ADYACENCIA:\n\n";
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

    cout << "=======================================================" << endl;
    cout << "         VERIFICACION DE GRAFO BIPARTITO (DFS)" << endl;
    cout << "=======================================================\n";

    cout << "1. Usar grafo NO dirigido NO ponderado (predefinido)" << endl;
    cout << "2. Usar grafo NO dirigido PONDERADO (predefinido)" << endl;
    cout << "3. Ingresar grafo manualmente" << endl;
    cout << "4. Salir" << endl;
    cout << "Opcion: ";
    cin >> opcion_menu;

    if (opcion_menu == 4) return 0;

    vector< vector<int> > grafo_adyacencia;
    vector< vector<int> > matriz_adyacencia;

    // ----- GRAFOS PREDEFINIDOS -----
    if (opcion_menu == 1 || opcion_menu == 2) {
        V = 5;
        grafo_adyacencia.assign(V, vector<int>());
        matriz_adyacencia.assign(V, vector<int>(V, 0));

        // TUS CONEXIONES EXACTAS
        int conexiones[][2] = {
            {0,1},{0,4},{0,3},
            {1,0},{1,3},{1,2},
            {2,1},{2,3},
            {3,2},{3,1},{3,0},
            {4,0}
        };

        int total = 12;

        for (int i = 0; i < total; i++) {
            int u = conexiones[i][0];
            int v = conexiones[i][1];
            grafo_adyacencia[u].push_back(v);
            matriz_adyacencia[u][v] = 1;
        }

        if (opcion_menu == 2) {
            cout << "\n[NOTA]: Los pesos se ignoran para la verificacion de biparticion.\n";
        }
    }

    // ----- INGRESO MANUAL -----
    if (opcion_menu == 3) {
        do {
            cout << "Introduce el numero de vertices (nodos): ";
            cin >> V;
            if (V <= 0) cout << "[ERROR] Debe haber al menos 1 nodo.\n" << endl;
        } while (V <= 0);

        cout << "Introduce el numero de aristas (conexiones): ";
        cin >> E;

        grafo_adyacencia.assign(V, vector<int>());
        matriz_adyacencia.assign(V, vector<int>(V, 0));

        cout << "Introduce las aristas (u v). PUEDES USAR NUMEROS DEL 0 AL " << V-1 << ":" << endl;
        cout << " (ejemplo: 0 1)" << endl;
        
        for (int i = 0; i < E; i++) {
            int u, v;
            cout << "Arista " << i + 1 << ": ";
            cin >> u >> v;

            if (u >= 0 && u < V && v >= 0 && v < V) {
                grafo_adyacencia[u].push_back(v);
                grafo_adyacencia[v].push_back(u);
                matriz_adyacencia[u][v] = 1;
                matriz_adyacencia[v][u] = 1;
            } else {
                cout << "[ERROR]: Los nodos ingresados no existen.\n";
                i--; 
            }
        }
    }

    // MOSTRAR MATRIZ
    mostrarMatrizAdyacencia(matriz_adyacencia, V);

    // --- PREPARACION PARA EL BIPARTITO ---
    vector<int> color(V, -1);
    bool es_bipartito = true;

    // 5. ITERAR SOBRE TODOS LOS NODOS (Maneja grafos disconexos)
    for (int i = 0; i < V; ++i) {
        if (color[i] == -1) {
            if (!DFS_Bipartito(i, 0, grafo_adyacencia, color)) {
                es_bipartito = false;
                break; 
            }
        }
    }

    // --- RESULTADO ---
    cout << "\n=======================================================" << endl;
    cout << "                       RESULTADO" << endl;
    cout << "=======================================================" << endl;
    
    if (es_bipartito) {
        cout << "\n[EXITO] El grafo ES BIPARTITO." << endl;
        cout << "EXPLICACION: Fue posible dividir todos los nodos en dos grupos (A y B) sin conexiones internas." << endl;
    } else {
        cout << "\n[FALLO] El grafo NO ES BIPARTITO." << endl;
        cout << "EXPLICACION: El algoritmo encontro un CONFLICTO, lo que indica que el grafo contiene al menos un ciclo impar." << endl;
    }

    return 0; // El programa termina correctamente.
}
