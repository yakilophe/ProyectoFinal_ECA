#include <iostream>   // Para poder usar cin y cout (entrada y salida de datos)
#include <queue>      // Para poder usar la cola (queue) que necesitamos en BFS
#include <vector>     // Para usar vectores dinamicos, aqui lo usamos para llevar control de nodos visitados
#include <iomanip>    // Para setw, que nos sirve a alinear los numeros al imprimir la matriz
using namespace std;

const int MAXN = 50;    // Maximo numero de nodos que puede tener el grafo
const int NO_EDGE = 0;  // Convencion: 0 indica que no hay arista entre dos nodos

int main() {
    int n;               // Numero de nodos del grafo
    bool directed, weighted; // Variables para preguntar si el grafo es dirigido y si tiene pesos

    // Encabezado visual del programa
    cout << "========================================\n";
    cout << "                   BFS         \n";
    cout << "========================================\n";

    // Preguntamos al usuario si el grafo es dirigido
    cout << "El grafo es dirigido? (0=No, 1=Si): ";
    cin >> directed;

    // Preguntamos si el grafo es ponderado
    cout << "El grafo es ponderado? (0=No, 1=Si): ";
    cin >> weighted;

    // Pedimos el numero de nodos y verificamos que sea valido
    cout << "Ingrese el numero de nodos (max " << MAXN << "): ";
    cin >> n;
    if(n > MAXN || n <= 0){
        cout << "Numero de nodos invalido.\n";
        return 1; // Si el numero de nodos no es valido, salimos del programa
    }

    int mat[MAXN][MAXN];  // Declaramos la matriz de adyacencia
    char elementos[] = {'A','B','C','D','E','F','G','H','I','J',
                        'K','L','M','N','O','P','Q','R','S','T',
                        'U','V','W','X','Y','Z'}; // Letras que representan los nodos

    // Ingreso de la matriz de adyacencia
    cout << "\n=== Ingreso de la matriz de adyacencia ===\n";
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(weighted) {
                // Si el grafo es ponderado, pedimos el peso de la arista
                cout << "Peso de la arista " << elementos[i] << " -> " 
                     << elementos[j] << " (0 si no hay): ";
                cin >> mat[i][j];
            } else {
                // Si no es ponderado, solo preguntamos si existe la arista
                cout << "Hay arista " << elementos[i] << " -> " 
                     << elementos[j] << "? (0=No, 1=Si): ";
                cin >> mat[i][j];
            }

            // Si el grafo no es dirigido, hacemos que la arista inversa sea igual
            // Esto asegura que la matriz sea simetrica para grafos no dirigidos
            if(!directed && i != j) mat[j][i] = mat[i][j];
        }
    }

    // Mostramos la matriz de adyacencia ingresada para que el usuario la vea
    cout << "\n=== Matriz de adyacencia ingresada ===\n";
    cout << setw(4) << " ";  // Espacio inicial para alinear la primera columna
    for(int j = 0; j < n; ++j) cout << setw(4) << elementos[j]; // indice de columnas (letras A B C ...)
    cout << "\n";
    for(int i = 0; i < n; ++i) {
        cout << setw(4) << elementos[i]; // indice de filas (letras A B C ...)
        for(int j = 0; j < n; ++j)
            cout << setw(4) << mat[i][j]; // Mostramos cada valor de la matriz
        cout << "\n";
    }

    // Pedimos el nodo de inicio para BFS
    char origen;
    cout << "\nIngrese el nodo de inicio para BFS (letra): ";
    cin >> origen;
    int src = -1; // Indice del nodo de inicio
    for(int i = 0; i < n; ++i)
        if(elementos[i] == origen) src = i; // Buscamos la letra en el arreglo de nodos
    if(src == -1) { // Si la letra no corresponde a ningun nodo
        cout << "Nodo de inicio invalido\n";
        return 1; // Salimos del programa
    }

    // ===== BFS =====
    vector<bool> visitado(n,false); // Creamos un vector para marcar los nodos visitados
    queue<int> q;                   // Cola para mantener el orden de visita en BFS
    visitado[src] = true;           // Marcamos el nodo inicial como visitado
    q.push(src);                    // Lo agregamos a la cola para empezar BFS

    cout << "\n=== Recorrido BFS desde nodo " << origen << " ===\n";
    while(!q.empty()) {             // Mientras haya nodos pendientes en la cola
        int u = q.front(); q.pop(); // Sacamos el primer nodo de la cola
        cout << elementos[u] << " "; // Mostramos el nodo actual

        // Revisamos todos los vecinos del nodo actual
        for(int v = 0; v < n; ++v) {
            // Si hay arista entre u y v y v no ha sido visitado
            if(mat[u][v] != NO_EDGE && !visitado[v]) {
                visitado[v] = true; // Lo marcamos como visitado
                q.push(v);          // Lo agregamos a la cola para recorrerlo despues
            }
        }
    }
    cout << "\n========================================\n";

    return 0; // Fin del programa
}
