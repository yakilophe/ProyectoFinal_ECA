#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int n;                      // número de nodos
int matriz[50][50];         // matriz de adyacencia (0/1)
char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// Variables Tarjan
int ids[50], low[50];
bool enPila[50];
stack<int> pila;
int idActual = 0;
int sccCount = 0;

// --------------------------------------------------------------
void tarjan(int u) {
    ids[u] = low[u] = idActual++;
    pila.push(u);
    enPila[u] = true;

    // Revisar conexiones del nodo u
    for(int v = 0; v < n; v++) {
        if(matriz[u][v] == 1) {  // hay arista u -> v
            if(ids[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if(enPila[v]) {
                low[u] = min(low[u], ids[v]);
            }
        }
    }

    // ¿u es raíz de una SCC?
    if(ids[u] == low[u]) {
        cout << "\nComponente #" << ++sccCount << ": ";
        while(true) {
            int v = pila.top();
            pila.pop();
            enPila[v] = false;

            cout << elementos[v] << " ";
            if(v == u) break;
        }
        cout << endl;
    }
}
// --------------------------------------------------------------

int main() {
    cout << "===== TARJAN - SCC (con matriz de adyacencia) =====\n\n";

    cout << "Ingrese el numero de vertices (max 26): ";
    cin >> n;

    if(n > 26) {
        cout << "Maximo permitido: 26\n";
        return 1;
    }

    cout << "\nIngrese la matriz de adyacencia \n";
    

    for(int i = 0; i < n; i++) {
        cout << "Fila para el nodo " << elementos[i] << ": ";
        for(int j = 0; j < n; j++) {
            cin >> matriz[i][j];
        }
    }

    // Inicializar Tarjan
    for(int i = 0; i < n; i++) {
        ids[i] = -1;
        low[i] = 0;
        enPila[i] = false;
    }

    // Ejecutar Tarjan
    for(int i = 0; i < n; i++) {
        if(ids[i] == -1) tarjan(i);
    }



    return 0;
}

