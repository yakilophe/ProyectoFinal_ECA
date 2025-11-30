#include <iostream> 
#include <vector> 
using namespace std;

void dfs(int nodo, vector<vector<int> >& grafo, vector<bool>& visitado) 
{ visitado[nodo] = true; cout << nodo << " ";

for (int v = 0; v < grafo.size(); v++) {
    if (grafo[nodo][v] == 1 && !visitado[v]) {
        dfs(v, grafo, visitado);
    }
}

}

int main() { 
int n; 
// número de nodos 
cout << "Ingresa el número de nodos del grafo: "; 
cin >> n;

// Crear matriz de adyacencia
vector<vector<int>
> grafo(n, vector<int>(n, 0));

cout << "Ingresa la matriz de adyacencia (" << n << "x" << n << "): "; for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) { cin >> grafo[i][j]; } }

int inicio;
cout << "Ingresa el nodo inicial para recorrer en DFS: "; cin >> inicio;

vector<bool> visitado(n, false);

cout << "Recorrido DFS: "; dfs(inicio, grafo, visitado); cout << endl;
return 0;

}
