#include <iostream>      // Para entrada/salida
#include <vector>        // Para listas de adyacencia antiguas
#include <queue>         // Para BFS clásico
using namespace std;     // Para no usar std::

/***************************************************************
   VARIABLES GLOBALES
***************************************************************/
vector<int> lista[100];   // Lista de adyacencia NO ponderada
int N;                    // Número de vértices
int E;                    // Número de aristas
bool esDirigido;          // Indica si es dirigido
bool visitado[100];       // Para BFS o DFS
int indegree[100];        // Grado de entrada (solo dirigido)

/***************************************************************
   Limpia TODO el grafo para poder capturar otro
***************************************************************/
void limpiar()
{
    int i;
    for(i = 0; i < 100; i++)
    {
        lista[i].clear();     // Vacía la lista del nodo i
        visitado[i] = false;  // Marca como no visitado
        indegree[i] = 0;      // Reinicia indegree
    }
}

/***************************************************************
   Recorre desde el nodo 0 y marca nodos visitados
***************************************************************/
void bfs(int inicio)
{
    queue<int> q;         // Cola de nodos
    q.push(inicio);       // Empieza en el nodo elegido
    visitado[inicio] = true;

    while(!q.empty())     // Mientras haya nodos por recorrer
    {
        int u = q.front();
        q.pop();

        int i;
        for(i = 0; i < lista[u].size(); i++)
        {
            int v = lista[u][i];   // Vecino v de u
            if(!visitado[v])       // Si no está visitado
            {
                visitado[v] = true;
                q.push(v);         // Lo agregamos a la cola
            }
        }
    }
}

/***************************************************************
   Usa BFS + propiedad E = N-1
***************************************************************/
bool esArbolNoDirigido()
{
    int i;

    // -------- Verificar propiedad E = N - 1 --------
    if(E != N - 1)
        return false;  // Si no se cumple ? NO es árbol

    // -------- Verificar conectividad con BFS --------
    for(i = 0; i < N; i++)
        visitado[i] = false;

    bfs(0);  // Recorremos desde el nodo 0

    // Si algún nodo sigue sin visitarse ? no es árbol
    for(i = 0; i < N; i++)
        if(!visitado[i])
            return false;

    return true;  // Cumple propiedades ? es árbol
}

/***************************************************************
   Usa indegree y un BFS desde la raíz
***************************************************************/
bool esArbolDirigido()
{
    int i;

    // 1. Buscar nodo RAÍZ (indegree = 0)
    int raiz = -1;
    int contadorRaices = 0;

    for(i = 0; i < N; i++)
    {
        if(indegree[i] == 0)
        {
            raiz = i;
            contadorRaices++;
        }
    }

    // Si NO hay raíz o hay más de una ? NO es árbol
    if(contadorRaices != 1)
        return false;

    // 2. Verificar que TODOS los demás nodos tengan indegree = 1
    int nodosCorrectos = 0;

    for(i = 0; i < N; i++)
        if(i != raiz && indegree[i] == 1)
            nodosCorrectos++;

    // Debe haber N-1 nodos con indegree=1
    if(nodosCorrectos != N - 1)
        return false;

    // 3. Usar BFS para verificar conectividad desde la raíz
    for(i = 0; i < N; i++)
        visitado[i] = false;

    bfs(raiz);

    for(i = 0; i < N; i++)
        if(!visitado[i])
            return false;

    return true;   // Cumple todo ? es árbol dirigido
}

/***************************************************************
   Guardamos el grafo introducido por el usuario
***************************************************************/
void capturarGrafo()
{
    limpiar();     // Siempre reiniciar todo

    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    cout << "¿Es dirigido? (1 = Si, 0 = No): ";
    cin >> esDirigido;

    cout << "\nIngrese las aristas (u v):\n";

    int i, u, v;

    for(i = 0; i < E; i++)
    {
        cout << "Arista " << i << ": ";
        cin >> u >> v;

        lista[u].push_back(v);  // Agregar arista u ? v

        if(esDirigido)
            indegree[v]++;      // En dirigido se suma indegree
        else
            lista[v].push_back(u); // En NO dirigido agregamos v ? u
    }
}

/***************************************************************
   MAIN
***************************************************************/
int main()
{
    int opcion;

    do {
        cout << "\n====== MENU ======\n";
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
