#include <iostream>
using namespace std;

const int INF = 1000000000; // Valor grande para representar "infinito"

int main() {
    int n;
    cout << "Numero de vertices: ";
    cin >> n;

    int dist[100][100]; // matriz (ajusta el tamaño si necesitas más)

    cout << "Ingresa la matriz de adyacencia (usa " << INF << " para infinito):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    // Algoritmo Floyd–Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "\nMatriz de distancias mas cortas:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

