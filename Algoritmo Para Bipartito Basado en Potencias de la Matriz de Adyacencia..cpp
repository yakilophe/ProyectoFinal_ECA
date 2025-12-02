#include <iostream>  // Necesario para que el programa pueda 'hablar' con el usuario (pedir datos y mostrar resultados).
#include <vector>    // Necesario para crear listas flexibles (matrices) que crecen con el grafo.

using namespace std;

// Este es un limite de seguridad para que la computadora no se tarde demasiado.
// Este algoritmo es lento, asi que limitamos el grafo a 10 nodos.
const int MAX_NODES = 10; 

// ***************************************************************
// FUNCIONES DE MATRIZ (LAS MATEMATICAS DEL ALGORITMO)
// ***************************************************************

// 1. FUNCION PARA MULTIPLICAR DOS MATRICES Cuadradas (A * B)
// En terminos de grafos, si A es el 'mapa de caminos de longitud 1',
// esta funcion combina dos mapas (A y B) para crear un mapa de caminos mas largos.
vector< vector<int> > multiplicar_matrices(const vector< vector<int> >& A, 
                                          const vector< vector<int> >& B, 
                                          int V) 
{
    // C es la matriz (el nuevo mapa de caminos) donde guardaremos el resultado.
    vector< vector<int> > C(V, vector<int>(V, 0)); 
    
    // Estos tres ciclos son la forma estandar en que se multiplican las matrices.
    // Es como revisar todas las combinaciones posibles de caminos intermedios.
    for (int i = 0; i < V; ++i) { // 'i' es el nodo de INICIO del camino.
        for (int j = 0; j < V; ++j) { // 'j' es el nodo de LLEGADA del camino.
            for (int k = 0; k < V; ++k) { // 'k' es el nodo INTERMEDIO por el que pasamos.
                // Aqui acumulamos la cantidad de formas de ir de 'i' a 'j' pasando por 'k'.
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C; // Devolvemos el nuevo mapa de caminos.
}

// 2. FUNCION PRINCIPAL DE VERIFICACION DE BIPARTITO (USANDO MATRIZ)
// REGLA: Un grafo NO es bipartito si tiene un ciclo (un camino que vuelve al inicio) 
// de longitud IMPAR (como 3, 5, 7, etc.).
bool verificar_bipartito_matriz(const vector< vector<int> >& matriz_adyacencia, int V) 
{
    // Empezamos con la matriz de adyacencia (A^1), que son los caminos de longitud 1 (las aristas).
    vector< vector<int> > potencia_actual = matriz_adyacencia;
    
    // Bucle para buscar CICLOS IMPARES: 3 (triangulo), 5, 7, y asi hasta el numero de nodos.
    for (int k = 3; k <= V; k += 2) { 
        
        // Para llegar a la potencia impar 'A^k', necesitamos multiplicar dos veces la matriz.
        
        // Multiplicacion 1: Nos lleva a una longitud PAR (k-1). No la revisamos.
        // Ejemplo: Si buscamos A^3, aqui calculamos A^2.
        potencia_actual = multiplicar_matrices(potencia_actual, matriz_adyacencia, V);
        
        // Multiplicacion 2: Nos lleva a la longitud IMPAR 'k'. Esta es la que revisamos.
        // Ejemplo: Si buscamos A^3, aqui finalmente calculamos A^3.
        potencia_actual = multiplicar_matrices(potencia_actual, matriz_adyacencia, V);

        cout << " -> Verificando ciclos de longitud IMPAR: " << k << endl;
        
        // Verificamos la DIAGONAL PRINCIPAL (donde la fila 'i' es igual a la columna 'i').
        // Si (A^k)[i][i] es mayor que 0, significa que existe un camino de longitud 'k' 
        // que va del nodo 'i' a si mismo. ¡Esto es un ciclo!
        for (int i = 0; i < V; ++i) {
            if (potencia_actual[i][i] > 0) {
                // Si encontramos un ciclo de longitud impar, ¡el grafo NO es bipartito!
                cout << "[CONFLICTO]: Se encontro un ciclo de longitud impar " << k << " que pasa por el nodo " << (i + 1) << "." << endl;
                return false; // Salimos de la funcion, el resultado es NO bipartito.
            }
        }
    }

    // Si el programa termina el bucle sin encontrar ningun ciclo impar, ¡el grafo ES bipartito!
    return true;
}


// ***************************************************************
// FUNCION PRINCIPAL DEL PROGRAMA (EL QUE INICIA TODO)
// ***************************************************************
int main() {
    // setlocale(LC_ALL, ""); // Eliminado
    
    // Nuevo comportamiento: el programa inicia con un menú.
    // Opciones:
    // 1) Usar grafo NO dirigido y NO ponderado (predefinido)
    // 2) Usar grafo NO dirigido y PONDERADO (predefinido)
    // 3) Ingresar grafo manualmente
    // 4) Salir
    //
    // IMPORTANTE: NO se modifica ninguna de las funciones ni comentarios del algoritmo.
    // Solo se controla la forma en que se obtiene la matriz de adyacencia para que
    // pueda usarse el algoritmo tal cual.
    
    int opcion_menu = 0;
    cout << "=======================================================" << endl;
    cout << "         VERIFICACION DE GRAFO BIPARTITO" << endl;
    cout << "=======================================================" << endl;
    cout << "Seleccione una opcion:" << endl;
    cout << "1. Usar grafo NO dirigido y NO ponderado (predefinido)" << endl;
    cout << "2. Usar grafo NO dirigido y PONDERADO (predefinido)" << endl;
    cout << "3. Ingresar grafo manualmente" << endl;
    cout << "4. Salir" << endl;
    cout << "Opcion: ";
    cin >> opcion_menu;
    
    // Variables que necesita el algoritmo original
    int V = 0, E = 0;
    vector< vector<int> > matriz_adyacencia;

    if (opcion_menu == 4) {
        cout << "\n[PROGRAMA TERMINADO]\n";
        return 0;
    }
    
    if (opcion_menu == 1) {
        // Grafo NO dirigido y NO ponderado (predefinido)
        V = 5;
        matriz_adyacencia.assign(V, vector<int>(V, 0));
        // Tus conexiones (no duplicamos 1-0 y 0-1 porque es no dirigido)
        matriz_adyacencia[0][1] = matriz_adyacencia[1][0] = 1;
        matriz_adyacencia[0][4] = matriz_adyacencia[4][0] = 1;
        matriz_adyacencia[0][3] = matriz_adyacencia[3][0] = 1;
        matriz_adyacencia[1][3] = matriz_adyacencia[3][1] = 1;
        matriz_adyacencia[1][2] = matriz_adyacencia[2][1] = 1;
        matriz_adyacencia[2][3] = matriz_adyacencia[3][2] = 1;
        cout << "\n[GRAFO CARGADO]: No dirigido NO ponderado\n";
    }
    else if (opcion_menu == 2) {
        // Grafo NO dirigido y PONDERADO (predefinido)
        // Los pesos los ignoramos para el analisis (tu algoritmo usa solo la matriz de adyacencia binaria)
        V = 5;
        matriz_adyacencia.assign(V, vector<int>(V, 0));
        matriz_adyacencia[0][1] = matriz_adyacencia[1][0] = 1;
        matriz_adyacencia[0][4] = matriz_adyacencia[4][0] = 1;
        matriz_adyacencia[0][3] = matriz_adyacencia[3][0] = 1;
        matriz_adyacencia[1][3] = matriz_adyacencia[3][1] = 1;
        matriz_adyacencia[1][2] = matriz_adyacencia[2][1] = 1;
        matriz_adyacencia[2][3] = matriz_adyacencia[3][2] = 1;
        cout << "\n[GRAFO CARGADO]: No dirigido PONDERADO (pesos ignorados para analisis)\n";
    }
    else if (opcion_menu == 3) {
        // Ingreso manual: el usuario decide nodos y aristas (se usará la lógica original)
        // NOTA: para mantener consistencia con tus definiciones usamos numeración 0..V-1
        do {
            cout << "Introduce el numero de vertices (nodos) [Maximo " << MAX_NODES << "]: ";
            cin >> V;
            if (V <= 0 || V > MAX_NODES) cout << "[ERROR] El numero de nodos debe ser entre 1 y " << MAX_NODES << ".\n" << endl;
        } while (V <= 0 || V > MAX_NODES);

        cout << "Introduce el numero de aristas (conexiones): ";
        cin >> E;

        matriz_adyacencia.assign(V, vector<int>(V, 0));

        cout << "Introduce las aristas (u v). PUEDES USAR NUMEROS DEL 0 AL " << (V-1) << ":" << endl;
        cout << " (ejemplo: 0 1)" << endl; 
        
        for (int i = 0; i < E; i++) {
            int u, v; // u es el nodo de inicio, v es el nodo de llegada.
            cout << "Arista " << i + 1 << ": ";
            cin >> u >> v; // Leemos los dos nodos conectados.

            int u_idx = u; // Ya asume 0-based
            int v_idx = v; 

            if (u_idx >= 0 && u_idx < V && v_idx >= 0 && v_idx < V) {
                // Marcamos la conexion con un 1 en la matriz A.
                matriz_adyacencia[u_idx][v_idx] = 1; 
                matriz_adyacencia[v_idx][u_idx] = 1; // Como es NO Dirigido, la conexion va en ambos sentidos.
            } else {
                cout << "[ERROR]: Los nodos ingresados no existen. Deben ser entre 0 y " << (V-1) << "." << endl;
                i--; // Hacemos que el bucle repita esta arista porque el dato fue invalido.
            }
        }
    }
    else {
        cout << "\n[OPCION NO VALIDA]\n";
        return 0;
    }

    // --- ANALISIS DE BIPARTITO ---
    cout << "\n=======================================================" << endl;
    cout << "                 ANALISIS DE MATRIZ" << endl;
    cout << "=======================================================" << endl;
    // Llamamos a la funcion principal que hara todas las multiplicaciones de matriz.
    bool es_bipartito = verificar_bipartito_matriz(matriz_adyacencia, V);

    // --- RESULTADO ---
    cout << "\n=======================================================" << endl;
    cout << "                       RESULTADO" << endl;
    cout << "=======================================================" << endl;
    
    if (es_bipartito) {
        cout << "\n[EXITO] El grafo ES BIPARTITO." << endl;
        cout << "EXPLICACION: No se encontraron caminos que regresen a un nodo despues de un numero IMPAR de pasos (ciclos impares)." << endl;
    } else {
        cout << "\n[FALLO] El grafo NO ES BIPARTITO." << endl;
        cout << "EXPLICACION: La multiplicacion de matrices confirmo la existencia de un ciclo de longitud impar (3, 5, 7, etc.), lo que viola la propiedad de biparticion." << endl;
        
    }

    return 0; // El programa termina correctamente.
}
