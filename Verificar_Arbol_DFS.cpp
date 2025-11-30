#include <iostream>       // Entrada y salida
#include <vector>         // Listas de adyacencia
using namespace std;      // Para no escribir std::

/************************************************************
   VARIABLES GLOBALES
************************************************************/
vector<int> lista[100];   // Lista de adyacencia
bool visitado[100];       // Para DFS
bool enProceso[100];      // Para ciclos dirigidos
int indegree[100];        // Grado de entrada
int N, E;                 // Vértices y aristas
bool esDirigido;          // Tipo de grafo
int aristasDFS;           // Cuenta aristas del árbol DFS

/************************************************************
   LIMPIAR DATOS
************************************************************/
void limpiar()
{
    int i;
    for(i = 0; i < 100; i++)
    {
        lista[i].clear();
        visitado[i] = false;
        enProceso[i] = false;
        indegree[i] = 0;
    }
    aristasDFS = 0;  // reiniciamos contador
}

/************************************************************
   DFS PARA GRAFO NO DIRIGIDO
   Cuenta aristas del árbol DFS, si pasa de N-1 = ciclo
************************************************************/
void dfsNoDirigido(int u, int padre)
{
    visitado[u] = true;       // Marcamos nodo visitado

    int i;
    for(i = 0; i < lista[u].size(); i++)
    {
        int v = lista[u][i];  // Vecino de u

        if(!visitado[v])
        {
            aristasDFS++;      // Arista válida del árbol DFS
            dfsNoDirigido(v, u);
        }
        else if(v != padre)
        {
            // Si está visitado y NO es el padre ? ciclo
            aristasDFS = 999999; // Marcamos ciclo explícito
        }
    }
}

/************************************************************
   DFS PARA GRAFO DIRIGIDO
   Detecta ciclos
************************************************************/
bool dfsDirigido(int u)
{
    visitado[u] = true;
    enProceso[u] = true; // Nodo está en el stack

    int i;
    for(i = 0; i < lista[u].size(); i++)
    {
        int v = lista[u][i];

        if(!visitado[v])
        {
            if(dfsDirigido(v))
                return true;   // Ciclo detectado
        }
        else if(enProceso[v])
        {
            return true;       // Ciclo dirigido
        }
    }

    enProceso[u] = false; // Lo sacamos del stack
    return false;
}

/************************************************************
   VERIFICAR ARBOL NO DIRIGIDO (nuevo método DFS)
************************************************************/
bool esArbolNoDirigido()
{
    int i;

    // 1. DFS para contar aristas del árbol DFS
    dfsNoDirigido(0, -1);

    // 2. Si detectamos ciclo
    if(aristasDFS == 999999)
        return false;

    // 3. Si las aristas del DFS no son N-1 = no es árbol
    if(aristasDFS != N - 1)
        return false;

    // 4. Verificar que todos fueron visitados (conexo)
    for(i = 0; i < N; i++)
        if(!visitado[i])
            return false;

    return true;
}

/************************************************************
   VERIFICAR ARBOL DIRIGIDO (nuevo método DFS)
************************************************************/
bool esArbolDirigido()
{
    int i;

    // 1. Buscar raíz (indegree = 0)
    int raiz = -1;
    int cantidadRaices = 0;

    for(i = 0; i < N; i++)
    {
        if(indegree[i] == 0)
        {
            raiz = i;
            cantidadRaices++;
        }
        else if(indegree[i] > 1)
        {
            return false; // Nodo con más de un padre = NO árbol
        }
    }

    if(cantidadRaices != 1)
        return false;

    // 2. DFS para detectar ciclos dirigidos
    if(dfsDirigido(raiz))
        return false;

    // 3. Verificar que todos los nodos se visitan desde la raíz
    for(i = 0; i < N; i++)
        if(!visitado[i])
            return false;

    // 4. Propiedad del árbol dirigido: E = N - 1
    if(E != N - 1)
        return false;

    return true;
}

/************************************************************
   CAPTURAR EL GRAFO
************************************************************/
void capturarGrafo()
{
    limpiar(); // Borra el grafo anterior

    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    cout << "¿Es dirigido? (1 = Si, 0 = No): ";
    cin >> esDirigido;

    cout << "\nIngrese aristas (u v):\n";

    int i, u, v;
    for(i = 0; i < E; i++)
    {
        cout << "Arista " << i << ": ";
        cin >> u >> v;

        lista[u].push_back(v);

        if(esDirigido)
        {
            indegree[v]++;
        }
        else
        {
            lista[v].push_back(u);
        }
    }
}

/************************************************************
   MAIN (MENU)
************************************************************/
int main()
{
    int opcion;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Capturar grafo\n";
        cout << "2. Verificar si es arbol\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1)
        {
            capturarGrafo();
        }
        else if(opcion == 2)
        {
            if(esDirigido)
            {
                if(esArbolDirigido())
                    cout << "\nEl grafo SI es un arbol dirigido.\n";
                else
                    cout << "\nEl grafo NO es un arbol dirigido.\n";
            }
            else
            {
                if(esArbolNoDirigido())
                    cout << "\nEl grafo SI es un arbol.\n";
                else
                    cout << "\nEl grafo NO es un arbol.\n";
            }
        }

    } while(opcion != 0);

    return 0;
}
