#include <iostream>
using namespace std;

/**************************************************************
   REPRESENTACIÓN DEL GRAFO:
   - adyNodo[u][k]  guarda el k-ésimo vecino de u
   - adyPeso[u][k]  guarda el peso correspondiente
   - grado[u]       dice cuántos vecinos tiene u

   Se usa esta forma porque funciona en compiladores viejos
   sin usar vector ni pair.
**************************************************************/
int adyNodo[100][100];
int adyPeso[100][100];
int grado[100];

int N, E;   // número de vértices y aristas

/**************************************************************
   Arreglos usados por el algoritmo de Prim:
   - dist[]   almacena el peso mínimo para conectar cada nodo al MST
   - padre[]  almacena desde qué nodo llega
   - visitado[] marca si ya se agregó al MST
**************************************************************/
int dist[100];
bool visitado[100];
int padre[100];

/**************************************************************
   Limpia completamente el grafo:
   - Borra la lista de vecinos
   - Reinicia grados
**************************************************************/
void limpiarGrafo()
{
    int i, j;
    for(i = 0; i < 100; i++)
    {
        grado[i] = 0;  // sin vecinos

        for(j = 0; j < 100; j++)
        {
            // Todo en 0 para evitar basura
            adyNodo[i][j] = 0;
            adyPeso[i][j] = 0;
        }
    }
}

/**************************************************************
   Permite capturar un grafo NO dirigido con pesos.
   El usuario proporciona: (u v peso)
   Se agrega en ambos sentidos porque el grafo es NO dirigido.
**************************************************************/
void capturarGrafo()
{
    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    limpiarGrafo();

    cout << "\nIngrese cada arista como: u v peso\n";

    int i, u, v, w;

    for(i = 0; i < E; i++)
    {
        cout << "Arista " << i << ": ";
        cin >> u >> v >> w;

        // Se guarda el vecino para u
        adyNodo[u][ grado[u] ] = v;
        adyPeso[u][ grado[u] ] = w;
        grado[u]++;

        // Se guarda el vecino para v (gráfo NO dirigido)
        adyNodo[v][ grado[v] ] = u;
        adyPeso[v][ grado[v] ] = w;
        grado[v]++;
    }

    cout << "\nGrafo cargado correctamente.\n";
}

/**************************************************************
   Algoritmo de Prim:
   1. Inicia desde el nodo 0.
   2. Siempre elige el nodo NO visitado con menor peso dist[].
   3. Actualiza el MST agregando ese nodo.
   4. Intenta mejorar las distancias de sus vecinos.
**************************************************************/
void ejecutarPrim()
{
    int i;

    /**********************************************************
       Inicialización básica:
       - dist[] se llena con un valor muy grande (simulación de infinito)
       - visitado[] en false, nadie en el MST
       - padre[] sin definir
    **********************************************************/
    for(i = 0; i < N; i++)
    {
        dist[i] = 999999;    // infinito
        visitado[i] = false; // aún no en el MST
        padre[i] = -1;       // sin padre
    }

    // Comenzamos desde el nodo 0
    dist[0] = 0;

    /**********************************************************
       Se agregan N nodos al MST, uno por iteración.
       En cada iteración:
       - Se selecciona el nodo NO visitado con menor dist[]
       - Se marca como visitado
       - Se relajan las distancias de sus vecinos
    **********************************************************/
    int iter;
    for(iter = 0; iter < N; iter++)
    {
        int u = -1;
        int mejor = 999999;

        /**********************************************************
            BÚSQUEDA DEL NODO DE MENOR DIST NO VISITADO
        **********************************************************/
        for(i = 0; i < N; i++)
        {
            if(!visitado[i] && dist[i] < mejor)
            {
                mejor = dist[i];
                u = i;   // nodo con menor costo actual
            }
        }

        // Se agrega al MST
        visitado[u] = true;

        /**********************************************************
           RELAJACIÓN:
           Se revisan todos los vecinos de u:
           Si un vecino v NO está visitado y el peso w es menor
           que la mejor distancia actual dist[v], se actualiza.
        **********************************************************/
        int k;
        for(k = 0; k < grado[u]; k++)
        {
            int v = adyNodo[u][k];
            int w = adyPeso[u][k];

            if(!visitado[v] && w < dist[v])
            {
                dist[v] = w;    // mejor peso encontrado
                padre[v] = u;   // u es el padre de v en el MST
            }
        }
    }

    /**************************************************************
       Se imprime el MST construido:
       Las aristas están dadas por padre[v] -- v
       excepto v = 0 (que es la raíz)
    **************************************************************/
    cout << "\n=========== MST OBTENIDO (Prim) ===========\n";

    int total = 0;

    for(i = 1; i < N; i++)
    {
        cout << padre[i] << " -- " << i
             << "   (peso = " << dist[i] << ")\n";

        total += dist[i];
    }

    cout << "\nPeso total del MST = " << total << "\n";
}

/**************************************************************
   Menú principal
**************************************************************/
int main()
{
    int opcion;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Capturar grafo\n";
        cout << "2. Ejecutar Prim\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1)
            capturarGrafo();
        else if(opcion == 2)
            ejecutarPrim();

    } while(opcion != 0);

    return 0;
}