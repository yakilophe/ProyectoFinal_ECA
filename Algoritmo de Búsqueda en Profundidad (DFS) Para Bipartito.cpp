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
            cout << "\n[CONFLICTO ENCONTRADO]: Los nodos " << (u + 1) << " y " << (vecino + 1) 
                 << " estan conectados y ambos pertenecen al color " << color_actual << " (" << (color_actual == 0 ? "Grupo A" : "Grupo B") 
                 << ")." << endl;
            return false; 
        }
        // Caso C: El vecino YA esta coloreado con el color opuesto. (Esta bien, continuamos).
    }
    
    // Si terminamos el recorrido sin conflictos, esta porcion es bipartita.
    return true; 
}


// ***************************************************************
// FUNCION PRINCIPAL DEL PROGRAMA (ENTRADA, SALIDA Y MENU)
// ***************************************************************
int main() {
    // setlocale(LC_ALL, ""); // Eliminado
    
    int V, E;
    int tipo_grafo; 
    
    // --- MENU DE TITULO ---
    cout << "=======================================================" << endl;
    cout << "         VERIFICACION DE GRAFO BIPARTITO" << endl;
    cout << "=======================================================" << endl;
    cout << "(El algoritmo funciona para Grafos NO DIRIGIDOS)" << endl;
    cout << "\n";


    // 1. PREGUNTAR SI ES PONDERADO O NO 
    cout << "1. Su grafo es Ponderado (tiene pesos) o No Ponderado?" << endl;
    cout << "[1] No Ponderado" << endl;
    cout << "[2] Ponderado" << endl;
    cout << "Opcion: ";
    cin >> tipo_grafo;
    
    bool es_ponderado = (tipo_grafo == 2);
    
    if (es_ponderado) {
        cout << "\n[NOTA]: Los pesos se ignoraran para la verificacion de biparticion." << endl;
    }


    // --- CONFIGURACION DEL GRAFO ---
    cout << "\n================================================" << endl;
    cout << "           CONFIGURACION DEL GRAFO" << endl;
    cout << "================================================" << endl;
    
    // 2. SOLICITAR NUMERO DE NODOS (V)
    do {
        cout << "Introduce el numero de vertices (nodos): ";
        cin >> V;
        if (V <= 0) cout << "[ERROR] Debe haber al menos 1 nodo.\n" << endl;
    } while (V <= 0);

    cout << "Introduce el numero de aristas (conexiones): ";
    cin >> E;

    // 3. CREAR LA ESTRUCTURA PRINCIPAL (LISTA DE ADYACENCIA)
    vector< vector<int> > grafo_adyacencia(V);

    // 4. LEER LAS CONEXIONES (ARISTAS)
    cout << "Introduce las aristas (u v). PUEDES USAR NUMEROS DEL 1 AL " << V << ":" << endl;
    cout << " (ejemplo: " << (es_ponderado ? "1 2 5.5" : "1 2") << ")" << endl;
    
    for (int i = 0; i < E; i++) {
        int u, v;
        double peso = 0; 

        cout << "Arista " << i + 1 << ": ";
        cin >> u >> v;
        
        if (es_ponderado) {
            cin >> peso;
        }
        
        u = u - 1; // Ajuste a indice 0
        v = v - 1; // Ajuste a indice 0

        if (u >= 0 && u < V && v >= 0 && v < V) {
            grafo_adyacencia[u].push_back(v); 
            grafo_adyacencia[v].push_back(u); 
        } else {
            cout << "[ERROR]: Los nodos ingresados no existen. Deben ser entre 1 y " << V << "." << endl;
            i--; 
        }
    }

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
        cout << "EXPLICACION: El algoritmo encontro un CONFLICTO, lo que indica que el grafo contiene al menos un ciclo impar que impide el coloreado con solo dos colores." << endl;
    }

    return 0; // El programa termina correctamente.
}
