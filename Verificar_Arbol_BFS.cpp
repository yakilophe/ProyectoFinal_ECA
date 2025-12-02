#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/***************************************************************
   VARIABLES GLOBALES
***************************************************************/
vector<int> lista[100]; 
int N;
int E;
bool esDirigido;
bool visitado[100];
int indegreeArr[100];

/***************************************************************
   Limpiar grafo
***************************************************************/
void limpiar()
{
    for(int i = 0; i < 100; i++)
    {
        lista[i].clear();
        visitado[i] = false;
        indegreeArr[i] = 0;
    }
}

/***************************************************************
   BFS normal
***************************************************************/
void bfs(int inicio)
{
    queue<int> q;         
    q.push(inicio);       
    visitado[inicio] = true;

    while(!q.empty())     
    {
        int u = q.front();
        q.pop();

        int i;
        for(i = 0; i < lista[u].size(); i++)   
        {
            int v = lista[u][i];

            if(!visitado[v])
            {
                visitado[v] = true;
                q.push(v);
            }
        }
    }
}

/***************************************************************
   Árbol NO dirigido
***************************************************************/
bool esArbolNoDirigido()
{
    if(E != N - 1)
        return false;

    for(int i = 0; i < N; i++)
        visitado[i] = false;

    bfs(0);

    for(int i = 0; i < N; i++)
        if(!visitado[i])
            return false;

    return true;
}

/***************************************************************
   Árbol dirigido
***************************************************************/
bool esArbolDirigido()
{
    int raiz = -1;
    int conteoRaices = 0;

    for(int i = 0; i < N; i++)
    {
        if(indegreeArr[i] == 0)
        {
            raiz = i;
            conteoRaices++;
        }
    }

    if(conteoRaices != 1)
        return false;

    int correctos = 0;

    for(int i = 0; i < N; i++)
        if(i != raiz && indegreeArr[i] == 1)
            correctos++;

    if(correctos != N - 1)
        return false;

    for(int i = 0; i < N; i++)
        visitado[i] = false;

    bfs(raiz);

    for(int i = 0; i < N; i++)
        if(!visitado[i])
            return false;

    return true;
}

/***************************************************************
   Cargar grafos predefinidos
***************************************************************/
void cargarGrafoPredefinido(int opcion)
{
    limpiar();

    if(opcion == 1)   // No dirigido y NO ponderado
    {
        esDirigido = false;
        N = 5;
        E = 12;

        int conexiones[][2] = {
            {0,1},{0,4},{0,3},
            {1,0},{1,3},{1,2},
            {2,1},{2,3},
            {3,2},{3,1},{3,0},
            {4,0}
        };

        for(int i = 0; i < E; i++)
        {
            int u = conexiones[i][0];
            int v = conexiones[i][1];
            lista[u].push_back(v);
            lista[v].push_back(u);
        }

        cout << "\nGrafo NO dirigido y NO ponderado cargado.\n";
    }

    else if(opcion == 2) // Dirigido y NO ponderado
    {
        esDirigido = true;
        N = 5;
        E = 6;

        int conexiones[][2] = {
            {1,0},{0,3},{1,2},
            {3,2},{3,1},{4,0}
        };

        for(int i = 0; i < E; i++)
        {
            int u = conexiones[i][0];
            int v = conexiones[i][1];
            lista[u].push_back(v);
            indegreeArr[v]++;
        }

        cout << "\nGrafo DIRIGIDO y NO ponderado cargado.\n";
    }

    else if(opcion == 3) // No dirigido y ponderado
    {
        esDirigido = false;
        N = 5;
        E = 12;

        int datos[][3] = {
            {0,1,4},{0,4,6},{0,3,9},
            {1,0,4},{1,3,8},{1,2,7},
            {2,1,7},{2,3,5},
            {3,2,5},{3,1,8},{3,0,9},
            {4,0,6}
        };

        for(int i = 0; i < E; i++)
        {
            int u = datos[i][0];
            int v = datos[i][1];
            lista[u].push_back(v);
            lista[v].push_back(u);
        }

        cout << "\nGrafo NO dirigido y PONDERADO cargado (pesos ignorados).\n";
    }

    else if(opcion == 4) // Dirigido y ponderado
    {
        esDirigido = true;
        N = 5;
        E = 6;

        int datos[][3] = {
            {1,0,3},{0,3,12},{1,2,18},
            {3,2,15},{3,1,9},{4,0,6}
        };

        for(int i = 0; i < E; i++)
        {
            int u = datos[i][0];
            int v = datos[i][1];
            lista[u].push_back(v);
            indegreeArr[v]++;
        }

        cout << "\nGrafo DIRIGIDO y PONDERADO cargado (pesos ignorados).\n";
    }
}

/***************************************************************
   Capturar grafo manual
***************************************************************/
void capturarGrafo()
{
    limpiar();

    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    cout << "¿Es dirigido? (1 = Si, 0 = No): ";
    cin >> esDirigido;

    cout << "\nIngrese las aristas (u v):\n";

    for(int i = 0; i < E; i++)
    {
        int u, v;
        cout << "Arista " << i << ": ";
        cin >> u >> v;

        lista[u].push_back(v);

        if(esDirigido)
            indegreeArr[v]++;
        else
            lista[v].push_back(u);
    }
}

/***************************************************************
   MAIN
***************************************************************/
int main()
{
    int opcion;

    do {
        cout << "\n====== MENU PRINCIPAL ======\n";
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
