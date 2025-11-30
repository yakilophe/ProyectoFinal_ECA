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
    
    int V, E; // 'V' es la cantidad de nodos (vertices), 'E' es la cantidad de aristas (conexiones).
    int tipo_grafo; 

    // --- MENU DE TITULO ---
    cout << "=======================================================" << endl;
    cout << "         VERIFICACION DE GRAFO BIPARTITO" << endl;
    cout << "=======================================================" << endl;
    cout << "    (Algoritmo 3: Basado en Potencias de la Matriz)" << endl;
    cout << "\n";


    // 1. PREGUNTAR SI ES PONDERADO O NO 
    cout << "1. Su grafo es Ponderado (tiene pesos) o No Ponderado?" << endl;
    cout << "[1] No Ponderado" << endl;
    cout << "[2] Ponderado" << endl;
    cout << "Opcion: ";
    cin >> tipo_grafo; // Leemos la respuesta del usuario.
    
    bool es_ponderado = (tipo_grafo == 2); // 'true' si es ponderado, 'false' si no.
    
    // --- CONFIGURACION DEL GRAFO ---
    cout << "\n================================================" << endl;
    cout << "           CONFIGURACION DEL GRAFO" << endl;
    cout << "================================================" << endl;
    
    // 2. SOLICITAR NUMERO DE NODOS (V)
    do {
        cout << "Introduce el numero de vertices (nodos) [Maximo " << MAX_NODES << "]: ";
        cin >> V;
        // Revisamos que el numero este dentro de los limites que definimos.
        if (V <= 0 || V > MAX_NODES) cout << "[ERROR] El numero de nodos debe ser entre 1 y " << MAX_NODES << ".\n" << endl;
    } while (V <= 0 || V > MAX_NODES);

    cout << "Introduce el numero de aristas (conexiones): ";
    cin >> E;

    // 3. CREAR LA MATRIZ DE ADYACENCIA
    // Creamos una tabla cuadrada (matriz) de VxV, donde los 0 indican que no hay conexion.
    vector< vector<int> > matriz_adyacencia(V, vector<int>(V, 0));

    // 4. LEER LAS CONEXIONES (ARISTAS)
    cout << "Introduce las aristas (u v). PUEDES USAR NUMEROS DEL 1 AL " << V << ":" << endl;
    cout << " (ejemplo: " << (es_ponderado ? "1 2 5.5" : "1 2") << ")" << endl; 
    
    for (int i = 0; i < E; i++) {
        int u, v; // u es el nodo de inicio, v es el nodo de llegada.
        double peso = 0; 

        cout << "Arista " << i + 1 << ": ";
        cin >> u >> v; // Leemos los dos nodos conectados.
        
        if (es_ponderado) {
            cin >> peso; // Si es ponderado, leemos el peso (que sera ignorado en el analisis).
        }
        
        int u_idx = u - 1; // Adaptamos el numero del usuario (ej. 1) a la posicion de la matriz (ej. 0).
        int v_idx = v - 1; 

        if (u_idx >= 0 && u_idx < V && v_idx >= 0 && v_idx < V) {
            // Marcamos la conexion con un 1 en la matriz A.
            matriz_adyacencia[u_idx][v_idx] = 1; 
            matriz_adyacencia[v_idx][u_idx] = 1; // Como es NO Dirigido, la conexion va en ambos sentidos.
        } else {
            cout << "[ERROR]: Los nodos ingresados no existen. Deben ser entre 1 y " << V << "." << endl;
            i--; // Hacemos que el bucle repita esta arista porque el dato fue invalido.
        }
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
