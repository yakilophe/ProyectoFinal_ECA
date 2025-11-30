#include <iostream>
#include <stack>
using namespace std;

int n;                     // Número de nodos
int matriz[50][50];        // Matriz de adyacencia
char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

int pre[50];               // Numeración de preorden
int preCont = 0;

stack<int> S;              // Pila principal
stack<int> P;              // Pila auxiliar (para detectar raíces)


// ======================================================
//           DFS de Gabow
// ======================================================
void gabowDFS(int u) {
    pre[u] = preCont++;
    S.push(u);
    P.push(u);

    // Recorrer vecinos
    for (int v = 0; v < n; v++) {
        if (matriz[u][v] == 1) {   // Existe arista u ? v

            if (pre[v] == -1) {
                // No visitado
                gabowDFS(v);
            } 
            else if (pre[v] < pre[u]) {
                // Ajustamos pila P
                while (!P.empty() && pre[P.top()] > pre[v]) {
                    P.pop();
                }
            }
        }
    }

    // ¿u es raíz de una SCC?
    if (!P.empty() && P.top() == u) {
        cout << "\nComponente fuertemente conexa: ";

        int v;
        do {
            v = S.top();
            S.pop();
            cout << elementos[v] << " ";
        } while (v != u);

        cout << endl;
        P.pop();
    }
}


// ======================================================
//                        MAIN
// ======================================================
int main() {
    cout << "===== GABOW - SCC con Matriz de Adyacencia =====\n\n";

    cout << "Ingrese el numero de vertices (max 26): ";
    cin >> n;

    if (n > 26) {
        cout << "Maximo permitido: 26\n";
        return 1;
    }

    cout << "\nIngrese la matriz de adyacencia (0 = no hay arista, 1 = hay arista)\n";
    cout << "(Por ejemplo para A: 0 1 0 1 ...)\n\n";

    for (int i = 0; i < n; i++) {
        cout << "Fila para el nodo " << elementos[i] << ": ";
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];
        }
    }

    // Inicializar preorden
    for (int i = 0; i < n; i++) {
        pre[i] = -1;
    }

    // Ejecutar Gabow
    for (int i = 0; i < n; i++) {
        if (pre[i] == -1)
            gabowDFS(i);
    }

    return 0;
}

