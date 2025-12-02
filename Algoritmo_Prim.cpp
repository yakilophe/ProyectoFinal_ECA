#include <iostream>                                                     // incluye la libreria estándar para entrada y salida
using namespace std;                                                    // evita escribir std:: en cada uso

// ===============================================================
//  ARREGLOS PARA REPRESENTAR EL GRAFO
// ===============================================================
int adyNodo[100][100];                                                  // adyNodo[u][k] guarda el k-esimo vecino de u
int adyPeso[100][100];                                                  // adyPeso[u][k] guarda el peso correspondiente
int grado[100];                                                         // grado[u] indica cuantos vecinos tiene u

int N, E;                                                               // N = numero de vertices, E = numero de aristas

// ===============================================================
//  ARREGLOS USADOS POR EL ALGORITMO DE PRIM
// ===============================================================
int dist[100];                                                          // dist[v] almacena el peso minimo para alcanzar v
bool visitado[100];                                                     // visitado[v] indica si v ya esta en el MST
int padre[100];                                                         // padre[v] indica desde que nodo llega v al MST

// ===============================================================
//  LIMPIAR TODO EL GRAFO
// ===============================================================
void limpiarGrafo()                                                     // funcion que borra totalmente el grafo
{
    int i, j;                                                           // indices para ciclos
    for(i = 0; i < 100; i++)                                            // recorre todos los posibles nodos
    {
        grado[i] = 0;                                                   // resetea el numero de vecinos del nodo i
        for(j = 0; j < 100; j++)                                        // recorre posibles posiciones de vecinos
        {
            adyNodo[i][j] = 0;                                          // limpia el vecino j del nodo i
            adyPeso[i][j] = 0;                                          // limpia el peso j del nodo i
        }
    }
}

// ===============================================================
//  CAPTURA MANUAL DEL GRAFO
// ===============================================================
void capturarGrafo()                                                    // permite ingresar el grafo manualmente
{
    cout << "\nNumero de vertices: ";                     // solicita numero de vertices
    cin >> N;                                                           // lee N

    cout << "Numero de aristas: ";                      // solicita numero de aristas
    cin >> E;                                                           // lee E

    limpiarGrafo();                                                     // limpia el grafo antes de cargar datos

    cout << "\nIngrese cada arista como: u v peso\n";    // indica el formato de entrada

    int i, u, v, w;                                                     // variables para lectura

    for(i = 0; i < E; i++)                                              // lee cada arista del usuario
    {
        cout << "Arista " << i << ": ";                        // muestra numero de arista
        cin >> u >> v >> w;                                             // lee los datos u, v, w

        adyNodo[u][ grado[u] ] = v;                                     // agrega v como vecino de u
        adyPeso[u][ grado[u] ] = w;                                     // agrega el peso correspondiente
        grado[u]++;                                                     // incrementa grado de u

        adyNodo[v][ grado[v] ] = u;                                     // agrega u como vecino de v (grafo no dirigido)
        adyPeso[v][ grado[v] ] = w;                                     // agrega el peso correspondiente
        grado[v]++;                                                     // incrementa grado de v
    }

    cout << "\nGrafo cargado correctamente.\n";             // confirma carga
}

// ===============================================================
//  CARGA PREDEFINIDA DEL GRAFO (NO DIRIGIDO)
// ===============================================================
void cargarGrafoPredef()                                                // carga el grafo predefinido
{
    limpiarGrafo();                                                     // limpia todo antes de cargar

    N = 5;                                                              // establece numero de vertices
    E = 6;                                                              // establece numero de aristas

    int A[6][3] = {                                                     // matriz con aristas predefinidas
        {0,1,4},                                                        // arista: 0 - 1 peso 4
        {0,4,6},                                                        // arista: 0 - 4 peso 6
        {1,2,7},                                                        // arista: 1 - 2 peso 7
        {2,3,5},                                                        // arista: 2 - 3 peso 5
        {1,3,12},                                                       // arista: 1 - 3 peso 12
        {3,4,8}                                                         // arista: 3 - 4 peso 8
    };

    for(int i = 0; i < 6; i++)                                          // recorre cada arista
    {
        int u = A[i][0];                                               // obtiene nodo u
        int v = A[i][1];                                               // obtiene nodo v
        int w = A[i][2];                                               // obtiene el peso w

        adyNodo[u][grado[u]] = v;                                      // inserta v como vecino de u
        adyPeso[u][grado[u]] = w;                                      // inserta peso
        grado[u]++;                                                    // aumenta grado de u

        adyNodo[v][grado[v]] = u;                                      // inserta u como vecino de v
        adyPeso[v][grado[v]] = w;                                      // inserta peso
        grado[v]++;                                                    // aumenta grado de v
    }

    cout << "\nGrafo predefinido NO dirigido ponderado cargado.\n"; // confirma carga
}

// ===============================================================
//  ALGORITMO DE PRIM
// ===============================================================
void ejecutarPrim()                                                     // inicia calculo del MST
{
    int i;                                                              // indice

    for(i = 0; i < N; i++)                                              // inicializa todos los arreglos
    {
        dist[i] = 999999;                                               // valor muy grande (infinito)
        visitado[i] = false;                                            // aun no esta en el MST
        padre[i] = -1;                                                  // sin padre asignado
    }

    dist[0] = 0;                                                        // arranca desde el nodo 0

    for(int iter = 0; iter < N; iter++)                                 // agrega N nodos al MST
    {
        int u = -1;                                                     // nodo seleccionado
        int mejor = 999999;                                             // mejor peso encontrado

        for(i = 0; i < N; i++)                                          // busca nodo no visitado de menor dist
        {
            if(!visitado[i] && dist[i] < mejor)                         // verifica mejor opcion
            {
                mejor = dist[i];                                        // actualiza mejor peso
                u = i;                                                  // selecciona este nodo
            }
        }

        visitado[u] = true;                                             // marca nodo como parte del MST

        for(int k = 0; k < grado[u]; k++)                               // revisa vecinos de u
        {
            int v = adyNodo[u][k];                                      // vecino v
            int w = adyPeso[u][k];                                      // peso de u a v

            if(!visitado[v] && w < dist[v])                             // mejora posible?
            {
                dist[v] = w;                                            // actualiza mejor peso
                padre[v] = u;                                           // guarda padre
            }
        }
    }

    cout << "\n=========== MST OBTENIDO (Prim) ===========\n";   // encabezado MST

    int total = 0;                                                      // suma de pesos del MST

    for(i = 1; i < N; i++)                                              // imprime aristas del MST
    {
        cout << padre[i] << " -- " << i                               // muestra arista
             << "   (peso = " << dist[i] << ")\n";                   // muestra peso correspondiente

        total += dist[i];                                               // acumula peso
    }

    cout << "\nPeso total del MST = " << total << "\n";          // imprime peso total
}

// ===============================================================
//  MENU PRINCIPAL
// ===============================================================
int main()                                                              // funcion principal
{
    int opcion;                                                         // almacena opcion del menu

    do {
        cout << "\n========== MENU ==========\n";              // imprime menu
        cout << "1. Capturar grafo manualmente\n";                  // opcion 1
        cout << "2. Cargar grafo NO dirigido ponderado\n";           // opcion 2
        cout << "3. Ejecutar Prim\n";                               // opcion 3
        cout << "0. Salir\n";                                        // opcion 0
        cout << "Opcion: ";                                           // pide opcion
        cin >> opcion;                                                  // lee opcion

        if(opcion == 1)                                                 // si selecciona 1
            capturarGrafo();                                            // llama captura manual
        else if(opcion == 2)                                            // si selecciona 2
            cargarGrafoPredef();                                        // carga grafo predefinido
        else if(opcion == 3)                                            // si selecciona 3
            ejecutarPrim();                                             // ejecuta Prim

    } while(opcion != 0);                                               // repite hasta elegir salir

    return 0;                                                           // fin del programa
}
