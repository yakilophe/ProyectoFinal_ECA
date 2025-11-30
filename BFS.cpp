#include <iostream> 
#include <vector> 
#include <queue> 
using namespace std;

int main() { 
int n; 
// n�mero de nodos 
cout << "Ingresa el n�mero de nodos del grafo: "; 
cin >> n;

// Crear matriz de adyacencia
vector<vector<int> > grafo(n, vector<int>(n, 0));

cout << "Ingresa la matriz de adyacencia (" << n << "x" << n << "): "; for(int i = 0; i < n; i++) { for(int j = 0; j < n; j++) { cin >> grafo[i][j]; } }

int inicio;
cout << "Ingresa el nodo inicial para recorrer en BFS: "; cin >> inicio;

vector<bool> visitado(n, false);
queue<int> q;

// BFS
visitado[inicio] = true;
q.push(inicio);

cout << "Recorrido BFS: ";

while(!q.empty()) {
    int nodo = q.front();
    q.pop();

    cout << nodo << " ";

    // Revisar vecinos
    for(int v = 0; v < n; v++) {
        if (grafo[nodo][v] == 1 && !visitado[v]) {
            visitado[v] = true;
            q.push(v);
        }
    }
}

cout << endl;
return 0;

}
 
// So hi

