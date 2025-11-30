#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

const int MAXN = 50;
const int NO_EDGE = 0;

// =====================================================
// Funcion para leer si el grafo es dirigido, ponderado y el numero de nodos
// =====================================================
void leerParametros(bool &directed, bool &weighted, int &n) {

    cout << "El grafo es dirigido? (0=No, 1=Si): ";
    cin >> directed;        // Leo si el grafo es dirigido

    cout << "El grafo es ponderado? (0=No, 1=Si): ";
    cin >> weighted;        // Leo si tiene pesos o no

    cout << "Ingrese el numero de nodos (max " << MAXN << "): ";
    cin >> n;               // Leo el numero de nodos

    // Validacion para evitar valores invalidos
    if(n <= 0 || n > MAXN) {
        cout << "Numero de nodos invalido.\n";
        exit(1);            // Si es invalido, cierro el programa
    }
}

// =====================================================
// Funcion para leer matriz NO ponderada (solo ceros y unos)
// =====================================================
void leerMatrizNoPonderada(int mat[MAXN][MAXN], int n, bool directed, char elementos[]) {

    cout << "\n=== Ingrese la matriz 0/1 ===\n";

    // Leo la matriz completa desde teclado
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> mat[i][j];

    // Si el grafo no es dirigido, hago la matriz simetrica
    // Esto asegura que si hay arista i->j, tambien exista j->i
    if(!directed) {
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                mat[j][i] = mat[i][j];
    }
}

// =====================================================
// Funcion para leer lista de adyacencia con pesos y convertirla a matriz
// =====================================================
void leerGrafoPonderado(int mat[MAXN][MAXN], int n, bool directed, char elementos[]) {

    vector<pair<int,int> > adj[MAXN];   // Lista de adyacencia (nodo vecino, peso)

    cout << "\n=== Ingrese lista de adyacencia con pesos ===\n";
    cout << "(vecino peso) por cada nodo\n";
    cout << "Ejemplo: si nodo A tiene 2 vecinos, se ingresa: 2   1 5   3 7\n\n";

    for(int i=0;i<n;i++){

        int num;
        cout << "Nodo " << elementos[i] << ": ";
        cin >> num;    // Cantidad de vecinos de este nodo

        // Leo cada vecino y su peso
        for(int k=0;k<num;k++){
            int v,w;
            cin >> v >> w;

            adj[i].push_back(make_pair(v,w));   // Guardo la arista i->v con peso w

            if(!directed)
                adj[v].push_back(make_pair(i,w));   // Si no es dirigido, agrego v->i tambien
        }
    }

    // Inicializo la matriz en 0
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j] = NO_EDGE;

    // Paso de la lista de adyacencia a la matriz final
    for(int i=0;i<n;i++)
        for(size_t k=0;k<adj[i].size();k++)
            mat[i][ adj[i][k].first ] = adj[i][k].second;
}

// =====================================================
// Funcion para mostrar la matriz en forma bonita
// =====================================================
void mostrarMatriz(int mat[MAXN][MAXN], int n, char elementos[]) {

    cout << "\n=== Matriz de Adyacencia ===\n";

    cout << setw(4) << " ";            // Espacio inicial para alinear columnas
    for(int j=0;j<n;j++)
        cout << setw(4) << elementos[j];  // Imprimo encabezado con letras A, B, C...
    cout << "\n";

    // Recorro filas
    for(int i=0;i<n;i++){
        cout << setw(4) << elementos[i];  // Etiqueta de la fila

        // Recorro columnas
        for(int j=0;j<n;j++)
            cout << setw(4) << mat[i][j]; // Valor en posicion i,j

        cout << "\n";
    }
}

// =====================================================
// Funcion para buscar el indice (numero) de un nodo segun su letra
// =====================================================
int buscarIndiceNodo(char origen, int n, char elementos[]) {

    // Busco en el arreglo de letras hasta encontrarlo
    for(int i=0;i<n;i++)
        if(elementos[i] == origen)
            return i;

    return -1;   // Si no existe, regreso -1
}

// =====================================================
// Funcion BFS (recorrido por niveles)
// =====================================================
void BFS(int src, int n, int mat[MAXN][MAXN], char elementos[]) {

    vector<bool> visitado(n,false);   // Vector para marcar nodos visitados
    queue<int> q;                     // Cola usada en BFS

    visitado[src] = true;             // Marco nodo inicial como visitado
    q.push(src);                      // Lo pongo en la cola

    cout << "\n=== Recorrido BFS ===\n";

    // Mientras la cola no este vacia
    while(!q.empty()) {

        int u = q.front();   // Tomo el primer elemento de la cola
        q.pop();             // Lo quito de la cola

        cout << elementos[u] << " ";    // Muestro el nodo visitado

        // Recorro todos los posibles vecinos
        for(int v=0;v<n;v++) {

            // Si hay arista u->v y aun no lo he visitado
            if(mat[u][v] != NO_EDGE && !visitado[v]) {

                visitado[v] = true;    // Marco v como visitado
                q.push(v);             // Lo agrego a la cola para visitarlo despues
            }
        }
    }

    cout << "\n========================================\n";
}

// =====================================================
// MAIN
// =====================================================
int main() {

    cout << "========================================\n";
    cout << "                BFS                     \n";
    cout << "========================================\n";

    bool directed, weighted;   // Para saber si el grafo es dirigido y ponderado
    int n;                     // Numero de nodos

    leerParametros(directed, weighted, n);  // Leo datos iniciales

    int mat[MAXN][MAXN];      // Matriz de adyacencia

    // Letras de cada nodo. Solo usare las primeras n.
    char elementos[] = {
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    // Si es ponderado leo lista con pesos,
    // si no, leo matriz 0/1
    if(weighted)
        leerGrafoPonderado(mat, n, directed, elementos);
    else
        leerMatrizNoPonderada(mat, n, directed, elementos);

    // Muestro la matriz final
    mostrarMatriz(mat, n, elementos);

    // Pido nodo inicial
    char inicio;
    cout << "\nNodo de inicio para BFS (A-Z): ";
    cin >> inicio;

    // Lo convierto a indice
    int src = buscarIndiceNodo(inicio, n, elementos);

    if(src == -1){        // Si no existe, error
        cout << "Nodo invalido.\n";
        return 1;
    }

    // Ejecuto BFS desde el nodo solicitado
    BFS(src, n, mat, elementos);

    return 0;
}
