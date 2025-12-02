#include <iostream>                                   // incluye libreria para entrada/salida
#include <algorithm>                                  // incluye algoritmo para sort
using namespace std;                                  // usa el espacio de nombres std

struct Arista {                                       // estructura para aristas del grafo
    int u;                                            // nodo u
    int v;                                            // nodo v
    int w;                                            // peso de la arista
};                                                    // fin estructura

Arista aristas[300];                                  // arreglo de aristas
bool eliminar[300];                                   // marca si una arista se eliminara
bool visitado[100];                                   // arreglo de visita para DFS

int N, E;                                             // N = vertices, E = aristas

void dfs(int u, bool matriz[100][100])                // DFS para verificar conectividad
{                                                     // inicio funcion
    visitado[u] = true;                               // marcar nodo como visitado

    for(int v = 0; v < N; v++)                        // recorrer todos los posibles nodos v
    {
        if(matriz[u][v] && !visitado[v])              // si hay conexion y no visitado
            dfs(v, matriz);                           // continuar DFS
    }
}                                                     // fin DFS

bool ordenarDesc(const Arista &A, const Arista &B)    // comparador para ordenar pesos desc
{
    return A.w > B.w;                                 // true si A pesa mas que B
}

void ejecutarReverseKruskal()                         // algoritmo Reverse Delete
{
    sort(aristas, aristas + E, ordenarDesc);          // ordenar aristas de mayor a menor

    for(int i = 0; i < E; i++)                        // inicialmente ninguna eliminada
        eliminar[i] = false;

    bool matriz[100][100];                            // matriz de adyacencia temporal

    for(int i = 0; i < N; i++)                        // limpiar matriz
        for(int j = 0; j < N; j++)
            matriz[i][j] = false;

    for(int i = 0; i < E; i++)                        // agregar todas las aristas
    {
        matriz[ aristas[i].u ][ aristas[i].v ] = true; // u-v
        matriz[ aristas[i].v ][ aristas[i].u ] = true; // v-u
    }

    for(int i = 0; i < E; i++)                        // recorrer aristas en orden descendente
    {
        int a = aristas[i].u;                         // extremo a
        int b = aristas[i].v;                         // extremo b

        matriz[a][b] = false;                         // quitar arista temporalmente
        matriz[b][a] = false;

        for(int k = 0; k < N; k++)                    // limpiar marcas del DFS
            visitado[k] = false;

        dfs(0, matriz);                               // correr DFS desde nodo 0

        bool conectado = true;                        // verificar conectividad

        for(int k = 0; k < N; k++)                    // si algun nodo no fue visitado
        {
            if(!visitado[k])
            {
                conectado = false;                   // grafo se desconecto
                break;
            }
        }

        if(!conectado)                                // si desconecto, restaurar arista
        {
            matriz[a][b] = true;
            matriz[b][a] = true;
        }
        else                                          // si sigue conectado, eliminarla
        {
            eliminar[i] = true;
        }
    }

    cout << "\n======= MST OBTENIDO (Reverse Kruskal) =======\n";

    int total = 0;                                    // acumulador del peso total

    for(int i = 0; i < E; i++)                        // mostrar aristas del MST
    {
        if(!eliminar[i])                              // si no fue eliminada
        {
            cout << aristas[i].u << " -- " << aristas[i].v
                 << "  (peso = " << aristas[i].w << ")\n";
            total += aristas[i].w;                    // sumar peso
        }
    }

    cout << "\nPeso total del MST = " << total << "\n";
}

void capturarGrafo()                                  // captura manual del grafo
{
    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    cout << "\nIngrese (u v peso):\n";

    for(int i = 0; i < E; i++)
    {
        cout << "Arista " << i << ": ";
        cin >> aristas[i].u >> aristas[i].v >> aristas[i].w;
    }

    cout << "\nGrafo cargado.\n";
}

void cargarGrafoPredefinido(int tipo)                 // cargar opciones predefinidas
{
    if(tipo == 1)                                     // grafo no dirigido PONDERADO
    {
        N = 5;
        E = 6;

        int datos[6][3] = {
            {0,1,4},
            {0,4,6},
            {0,3,9},
            {1,3,8},
            {1,2,7},
            {2,3,5}
        };

        for(int i = 0; i < E; i++)
        {
            aristas[i].u = datos[i][0];
            aristas[i].v = datos[i][1];
            aristas[i].w = datos[i][2];
        }

        cout << "\nGrafo NO dirigido y PONDERADO cargado.\n";
    }
    else if(tipo == 2)                                // grafo dirigido PONDERADO
    {
        N = 5;
        E = 6;

        int datos[6][3] = {
            {1,0,3}, {0,3,12}, {1,2,18},
            {3,2,15}, {3,1,9}, {4,0,6}
        };

        for(int i = 0; i < E; i++)
        {
            aristas[i].u = datos[i][0];
            aristas[i].v = datos[i][1];
            aristas[i].w = datos[i][2];
        }

        cout << "\nGrafo DIRIGIDO y PONDERADO cargado.\n";
    }
    else
    {
        cout << "\nOpcion de grafo predefinido invalida.\n";
    }
}

void menuGrafosPredef()                               // menu para grafos predefinidos
{
    int opcion;

    cout << "\nGRAFOS PREDEFINIDOS:\n";
    cout << "1. No dirigido y ponderado\n";
    cout << "2. Dirigido y ponderado\n";
    cout << "3. Ingresar grafo manualmente\n";
    cout << "\nElija una opcion: ";
    cin >> opcion;

    if(opcion == 1 || opcion == 2)
        cargarGrafoPredefinido(opcion);
    else if(opcion == 3)
        capturarGrafo();
    else
        cout << "\nOpcion invalida.\n";
}

int main()
{
    int opcion;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Seleccionar grafo predefinido o manual\n";
        cout << "2. Ejecutar Reverse-Kruskal\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1)
            menuGrafosPredef();
        else if(opcion == 2)
            ejecutarReverseKruskal();

    } while(opcion != 0);

    return 0;
}
