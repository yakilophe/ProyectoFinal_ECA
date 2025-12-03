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
            return true;             // Si v ya fue visitado y NO es el padre ? ciclo
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
   Carga uno de los grafos predefinidos del menú
**************************************************************/
void cargarGrafoPredefinido(int opcion)
{
    limpiarGrafo();

    if(opcion == 1)   // No dirigido y NO ponderado
    {
        N = 5;
        E = 12;
        esDirigido = false;

        int conexiones[][2] = {
            {0,1},{0,4},{0,3},
            {1,0},{1,3},{1,2},
            {2,1},{2,3},
            {3,2},{3,1},{3,0},
            {4,0}
        };

        for(int i=0; i<E; i++)
        {
            int u = conexiones[i][0];
            int v = conexiones[i][1];
            lista[u].push_back(v);
            lista[v].push_back(u);
        }

        cout << "\nGrafo NO dirigido y NO ponderado cargado.\n";
    }

    else if(opcion == 2)   // Dirigido y NO ponderado
    {
        N = 5;
        E = 6;
        esDirigido = true;

        int datos[][2] = {
            {1,0},{0,3},{1,2},
            {3,2},{3,1},{4,0}
        };

        for(int i=0; i<E; i++)
            lista[ datos[i][0] ].push_back( datos[i][1] );

        cout << "\nGrafo DIRIGIDO y NO ponderado cargado.\n";
    }

    else if(opcion == 3)  // No dirigido y PONDERADO (pero ignoramos pesos)
    {
        N = 5;
        E = 12;
        esDirigido = false;

        int datos[][3] = {
            {0,1,4},{0,4,6},{0,3,9},
            {1,0,4},{1,3,8},{1,2,7},
            {2,1,7},{2,3,5},
            {3,2,5},{3,1,8},{3,0,9},
            {4,0,6}
        };

        for(int i=0; i<E; i++)
        {
            int u = datos[i][0], v = datos[i][1];
            lista[u].push_back(v);
            lista[v].push_back(u);
        }

        cout << "\nGrafo NO dirigido y PONDERADO cargado (pesos ignorados).\n";
    }

    else if(opcion == 4)   // Dirigido y PONDERADO (pesos ignorados)
    {
        N = 5;
        E = 6;
        esDirigido = true;

        int datos[][3] = {
            {1,0,3},{0,3,12},{1,2,18},
            {3,2,15},{3,1,9},{4,0,6}
        };

        for(int i=0; i<E; i++)
            lista[ datos[i][0] ].push_back( datos[i][1] );

        cout << "\nGrafo DIRIGIDO y PONDERADO cargado (pesos ignorados).\n";
    }
}

/**************************************************************
   Captura N, E y las aristas (modo manual)
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
        cout << "1. Seleccionar grafo (predefinido o manual)\n";
        cout << "2. Verificar si es arbol\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1)
        {
            int g;
            cout << "\nGRAFOS PREDEFINIDOS:\n";
            cout << "1. No dirigido y no ponderado\n";
            cout << "2. Dirigido y no ponderado\n";
            cout << "3. No dirigido y ponderado\n";
            cout << "4. Dirigido y ponderado\n";
            cout << "5. Ingresar grafo manualmente\n";
            cout << "\nElija una opcion: ";
            cin >> g;

            if(g >= 1 && g <= 4)
                cargarGrafoPredefinido(g);
            else if(g == 5)
                capturarGrafo();
            else
                cout << "\nOpcion invalida.\n";
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
