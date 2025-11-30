#include <iostream>      // Para cout y cin
#include <vector>        // Para listas de adyacencia antiguas (C++98 compatible)

using namespace std;     // Para evitar std::

/**************************************************************
   VARIABLES GLOBALES
**************************************************************/

vector<int> lista[100];   // Lista de adyacencia 
bool visitado[100];       // Marca si un nodo ya fue visitado
bool enRecursion[100];    // Para detectar ciclos dirigidos
int N;                    // Número de vértices
int E;                    // Número de aristas
bool esDirigido;          // Indica si el grafo es dirigido o no

/**************************************************************
   Reinicia todas las listas y arreglos de visita
**************************************************************/
void limpiarGrafo()
{
    int i;
    for(i = 0; i < 100; i++)
    {
        lista[i].clear();         // Borra lista de adyacencia
        visitado[i] = false;      // Borra visitas
        enRecursion[i] = false;   // Borra pila de recursión
    }
}

/**************************************************************
   Detecta ciclos en grafos dirigidos usando recursión
**************************************************************/
bool dfsDirigido(int u)
{
    visitado[u] = true;       // Marcamos el nodo como visitado
    enRecursion[u] = true;    // Lo agregamos a la pila de recursión

    int i;
    for(i = 0; i < lista[u].size(); i++)
    {
        int v = lista[u][i];  // Vecino v de u

        if(!visitado[v])      // Si v NO ha sido visitado
        {
            if(dfsDirigido(v))   // Llamada recursiva
                return true;     // Se detectó ciclo
        }
        else if(enRecursion[v])  // Si ya estaba en la pila ? ciclo
        {
            return true;
        }
    }

    enRecursion[u] = false;   // Sacamos a u de la pila
    return false;             // No hubo ciclo
}

/**************************************************************
   Detecta ciclos en grafos NO dirigidos
**************************************************************/
bool dfsNoDirigido(int u, int padre)
{
    visitado[u] = true;   // Marcamos como visitado

    int i;
    for(i = 0; i < lista[u].size(); i++)
    {
        int v = lista[u][i];   // Vecino de u

        if(!visitado[v])
        {
            if(dfsNoDirigido(v, u))  // Recursión
                return true;         // Ciclo encontrado
        }
        else if(v != padre)
        {
            // Si v ya fue visitado y NO es el padre ? ciclo
            return true;
        }
    }

    return false;  // No hay ciclo
}

/**************************************************************
   Se usa para comprobar si TODO el grafo es conexo
**************************************************************/
void dfsConectividad(int u)
{
    visitado[u] = true;  // Marcamos visitado

    int i;
    for(i = 0; i < lista[u].size(); i++)
    {
        int v = lista[u][i];
        if(!visitado[v])
            dfsConectividad(v);
    }
}

/**************************************************************
   Verifica si el grafo es un árbol
**************************************************************/
bool esArbol()
{
    int i;

    /**************** GRAFO DIRIGIDO ****************/
    if(esDirigido)
    {
        // 1. Detectar ciclos
        for(i = 0; i < N; i++)
        {
            visitado[i] = false;
            enRecursion[i] = false;
        }

        for(i = 0; i < N; i++)
        {
            if(!visitado[i])
                if(dfsDirigido(i))
                    return false;  // Tiene ciclo ? NO árbol
        }

        // 2. Verificar conectividad
        for(i = 0; i < N; i++)
            visitado[i] = false;

        dfsConectividad(0);   // Empezamos desde nodo 0

        for(i = 0; i < N; i++)
            if(!visitado[i])
                return false; // No es conexo ? NO árbol

        return true;          // Es árbol dirigido
    }

    /**************** GRAFO NO DIRIGIDO ****************/
    else
    {
        // 1. Detectar ciclos
        for(i = 0; i < N; i++)
            visitado[i] = false;

        if(dfsNoDirigido(0, -1))
            return false;   // Tiene ciclo ? NO árbol

        // 2. Verificar conectividad
        for(i = 0; i < N; i++)
            visitado[i] = false;

        dfsConectividad(0);

        for(i = 0; i < N; i++)
            if(!visitado[i])
                return false; // No es conexo ? NO árbol

        return true;          // Es árbol no dirigido
    }
}

/**************************************************************
   Captura N, E y las aristas
**************************************************************/
void capturarGrafo()
{
    limpiarGrafo();   // Borramos cualquier grafo previo

    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    cout << "¿Grafo dirigido? (1 = Si, 0 = No): ";
    cin >> esDirigido;

    cout << "\nIngrese las aristas (u v):\n";

    int i, u, v;

    for(i = 0; i < E; i++)
    {
        cout << "Arista " << i << ": ";
        cin >> u >> v;

        lista[u].push_back(v);  // Agregamos u?v

        if(!esDirigido)
            lista[v].push_back(u);  // Si NO es dirigido, agregamos v?u
    }
}

/**************************************************************
   FUNCIÓN PRINCIPAL (MENÚ)
**************************************************************/
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
            if(esArbol())
                cout << "\nEl grafo SI es un arbol.\n";
            else
                cout << "\nEl grafo NO es un arbol.\n";
        }

    } while(opcion != 0);

    return 0;
}

