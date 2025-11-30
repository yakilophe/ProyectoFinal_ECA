#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Estructura para representar una arista (edge)
struct Arista {
    int origen;
    int destino;
    int peso;
};

int main() {
    int V, E, origen;
    cout << "Introduce el número de vértices: ";
    cin >> V;
    cout << "Introduce el número de aristas: ";
    cin >> E;

    vector<Arista> aristas(E);

    cout << "Introduce las aristas (u v peso):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> aristas[i].origen >> aristas[i].destino >> aristas[i].peso;
    }

    cout << "Introduce el vértice origen: ";
    cin >> origen;

    // Paso 1: Inicializar distancias
    const int INF = numeric_limits<int>::max();
    vector<int> dist(V, INF);
    dist[origen] = 0;

    // Paso 2: Relajar todas las aristas V-1 veces
    for (int i = 1; i <= V - 1; i++) {
        for (const auto &a : aristas) {
            if (dist[a.origen] != INF && dist[a.origen] + a.peso < dist[a.destino]) {
                dist[a.destino] = dist[a.origen] + a.peso;
            }
        }
    }

    // Paso 3: Comprobar si hay ciclos de peso negativo
    bool hayCicloNegativo = false;
    for (const auto &a : aristas) {
        if (dist[a.origen] != INF && dist[a.origen] + a.peso < dist[a.destino]) {
            hayCicloNegativo = true;
            break;
        }
    }

    if (hayCicloNegativo) {
        cout << "El grafo contiene un ciclo de peso negativo." << endl;
    } else {
        cout << "Distancias mínimas desde el vértice " << origen << ":" << endl;
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF)
                cout << "Distancia a " << i << " = INF" << endl;
            else
                cout << "Distancia a " << i << " = " << dist[i] << endl;
        }
    }

    return 0;
}