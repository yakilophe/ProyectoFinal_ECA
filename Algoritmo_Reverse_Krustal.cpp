#include <iostream>
#include <algorithm>   // Para sort()
using namespace std;

/***********************************************************
   ESTRUCTURA PARA GUARDAR UNA ARISTA
***********************************************************/
struct Arista {
    int u;   // nodo 1
    int v;   // nodo 2
    int w;   // peso
};

/***********************************************************
   VARIABLES GLOBALES
***********************************************************/
Arista aristas[300];   // aristas originales
bool eliminar[300];    // marca si la arista sera borrada
bool visitado[100];    // para DFS

int N, E;              // vertices y aristas

/***********************************************************
   DFS para verificar si el grafo sigue conectado sin una arista
***********************************************************/
void dfs(int u, bool matriz[100][100])
{
    visitado[u] = true;

    int v;
    for(v = 0; v < N; v++)
    {
        // Si existe conexi�n y no fue visitado, avanzar
        if(matriz[u][v] && !visitado[v])
            dfs(v, matriz);
    }
}

/***********************************************************
   COMPARADOR PARA ORDENAR ARISTAS DE MAYOR A MENOR PESO
***********************************************************/
bool ordenarDesc(const Arista &A, const Arista &B)
{
    return A.w > B.w;        // mayor primero
}

/***********************************************************
   Reverse-Kruskal (Reverse Delete Algorithm)
***********************************************************/
void ejecutarReverseKruskal()
{
    // Ordenamos aristas de mayor a menor
    sort(aristas, aristas + E, ordenarDesc);

    // Inicialmente ninguna esta eliminada
    int i;
    for(i = 0; i < E; i++)
        eliminar[i] = false;

    /*********************************************************
       MATRIZ DE ADYACENCIA TEMPORAL:
       Aqu� a�adimos TODAS las aristas primero.
    *********************************************************/
    bool matriz[100][100];
    int u, v;

    for(u = 0; u < N; u++)
        for(v = 0; v < N; v++)
            matriz[u][v] = false;

    // Colocar todas las aristas
    for(i = 0; i < E; i++)
    {
        matriz[ aristas[i].u ][ aristas[i].v ] = true;
        matriz[ aristas[i].v ][ aristas[i].u ] = true;
    }

    /*********************************************************
       PROCESO PRINCIPAL:
       Intentamos ELIMINAR aristas en orden DESCENDENTE.
       - Quitamos una arista.
       - Verificamos si el grafo sigue conectado.
       - Si se desconecta, devolvemos la arista.
    *********************************************************/
    for(i = 0; i < E; i++)
    {
        int a = aristas[i].u;
        int b = aristas[i].v;

        // Eliminamos temporalmente
        matriz[a][b] = false;
        matriz[b][a] = false;

        // Limpiar visitados para DFS
        int k;
        for(k = 0; k < N; k++)
            visitado[k] = false;

        // Hacemos DFS desde cualquier nodo (0)
        dfs(0, matriz);

        // Revisar si todos fueron alcanzados
        bool conectado = true;
        for(k = 0; k < N; k++)
        {
            if(!visitado[k])
            {
                conectado = false;
                break;
            }
        }

        // Si se desconect�, la arista NO puede eliminarse
        if(!conectado)
        {
            matriz[a][b] = true;
            matriz[b][a] = true;
        }
        else
        {
            eliminar[i] = true;  // queda eliminada
        }
    }

    /*********************************************************
       MOSTRAR RESULTADOS DEL MST
    *********************************************************/
    cout << "\n======= MST OBTENIDO (Reverse Kruskal) =======\n";

    int total = 0;

    for(i = 0; i < E; i++)
    {
        if(!eliminar[i])
        {
            cout << aristas[i].u << " -- " << aristas[i].v
                 << "  (peso = " << aristas[i].w << ")\n";

            total += aristas[i].w;
        }
    }

    cout << "\nPeso total del MST = " << total << "\n";
}

/***********************************************************
   Captura del grafo (SIEMPRE NO DIRIGIDO)
***********************************************************/
void capturarGrafo()
{
    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    cout << "\nIngrese (u v peso):\n";

    int i;
    for(i = 0; i < E; i++)
    {
        cout << "Arista " << i << ": ";
        cin >> aristas[i].u >> aristas[i].v >> aristas[i].w;
    }

    cout << "\nGrafo cargado!!.\n";
}

/***********************************************************
   MENU PRINCIPAL
***********************************************************/
int main()
{
    int opcion;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Capturar grafo\n";
        cout << "2. Ejecutar Reverse-Kruskal\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1)
            capturarGrafo();
        else if(opcion == 2)
            ejecutarReverseKruskal();

    } while(opcion != 0);

    return 0;
}

