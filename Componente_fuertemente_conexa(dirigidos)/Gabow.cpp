#include <iostream>
#include <stack>
#include <iomanip>
using namespace std;

const int MAXN = 50;

int n;                     
int matriz[MAXN][MAXN];    
int pre[MAXN];             
int preCont = 0;           

stack<int> S;             
stack<int> P;              

char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// ======================================================
// LEER MATRIZ DE ADYACENCIA
// ======================================================
void leerMatriz() {
    cout << "\nIngrese la matriz de adyacencia (0 = no, 1 = si)\n";

    for (int i = 0; i < n; i++) {
        cout << "Fila para nodo " << elementos[i] << ": ";
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];
        }
    }
}

// ======================================================
// OPCIONAL: IMPRIMIR MATRIZ
// ======================================================
void imprimirMatriz() {
    cout << "\n=== Matriz ingresada ===\n\n";

    cout << setw(4) << " ";
    for (int j = 0; j < n; j++)
        cout << setw(4) << elementos[j];
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << setw(4) << elementos[i];
        for (int j = 0; j < n; j++)
            cout << setw(4) << matriz[i][j];
        cout << "\n";
    }
}

// ======================================================
// INICIALIZAR PREORDEN
// ======================================================
void inicializar() {
    preCont = 0;
    while (!S.empty()) S.pop();
    while (!P.empty()) P.pop();

    for (int i = 0; i < n; i++)
        pre[i] = -1;
}

// ======================================================
// GABOW DFS
// ======================================================
void gabowDFS(int u) {
    pre[u] = preCont++;
    S.push(u);
    P.push(u);

    for (int v = 0; v < n; v++) {

        if (matriz[u][v] == 1) {

            if (pre[v] == -1) {
                gabowDFS(v);
            }
            else if (pre[v] < pre[u]) {
                while (!P.empty() && pre[P.top()] > pre[v])
                    P.pop();
            }
        }
    }

    if (!P.empty() && P.top() == u) {

        cout << "\nComponente fuertemente conexa: ";

        int v;
        do {
            v = S.top();
            S.pop();
            cout << elementos[v] << " ";
        } while (v != u);

        cout << "\n";
        P.pop();
    }
}

// ======================================================
// EJECUTAR TODO EL ALGORITMO
// ======================================================
void ejecutarGabow() {
    for (int i = 0; i < n; i++)
        if (pre[i] == -1)
            gabowDFS(i);
}

// ======================================================
// MAIN SUPER LIMPIO
// ======================================================
int main() {

    cout << "=========== GABOW - SCC ===========\n";

    cout << "Numero de vertices (max 26): ";
    cin >> n;

    if (n <= 0 || n > 26) {
        cout << "Numero invalido\n";
        return 1;
    }

    leerMatriz();

    inicializar();

    cout << "\n=== Componentes fuertemente conexas ===\n";
    ejecutarGabow();

    cout << "\n=======================================\n";

    return 0;
}
