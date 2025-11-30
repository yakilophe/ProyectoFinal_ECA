#include <iostream>
#include <vector>
#include <climits> // Para INT_MAX

using namespace std;

// Estructura para representar una arista
struct Arista {
    int destino;
    int peso;
};

// Grafo como lista de adyacencia
vector< vector<Arista> > grafo;

// Variables globales
int mejorCosto = INT_MAX;         // Guarda el menor costo encontrado
vector<int> mejorCamino;          // Guarda el mejor camino encontrado
int limiteMaximo;                 // Límite de costo que el usuario define

// --------------------------------------------
// Función recursiva del Backtracking con poda
// --------------------------------------------
void buscarCamino(int nodoActual, int destino, vector<bool>& visitado, vector<int>& camino, int costoActual) {
    // Si ya superamos el límite, cortamos ("poda")
    if (costoActual > limiteMaximo) return;

    // Si ya superamos el mejor costo encontrado, también podamos
    if (costoActual >= mejorCosto) return;

    // Si llegamos al destino, actualizamos si es mejor
    if (nodoActual == destino) {
        if (costoActual < mejorCosto) {
            mejorCosto = costoActual;
            mejorCamino = camino;
        }
        return;
    }

    // Marcamos este nodo como visitado
    visitado[nodoActual] = true;

    // Recorremos los vecinos del nodo actual
    for (int i = 0; i < grafo[nodoActual].size(); i++) {
        int vecino = grafo[nodoActual][i].destino;
        int peso = grafo[nodoActual][i].peso;

        if (!visitado[vecino]) {
            camino.push_back(vecino); // agregamos al camino
            buscarCamino(vecino, destino, visitado, camino, costoActual + peso);
            camino.pop_back();        // retrocedemos ("backtrack")
        }
    }

    // Desmarcamos el nodo antes de regresar (para otras rutas)
    visitado[nodoActual] = false;
}

int main() {
    int nodos, aristas;
    cout << "Ingrese la cantidad de nodos del grafo: ";
    cin >> nodos;
    cout << "Ingrese la cantidad de aristas: ";
    cin >> aristas;

    grafo.resize(nodos);

    cout << "\nIngrese las aristas en formato: origen destino peso\n";
    for (int i = 0; i < aristas; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        grafo[u].push_back( (Arista){v, w} );
        // Si es no dirigido, también agrega el inverso:
        // grafo[v].push_back( (Arista){u, w} );
    }

    int origen, destino;
    cout << "\nNodo origen: ";
    cin >> origen;
    cout << "Nodo destino: ";
    cin >> destino;

    cout << "Límite máximo de costo: ";
    cin >> limiteMaximo;

    vector<bool> visitado(nodos, false);
    vector<int> camino;
    camino.push_back(origen);

    buscarCamino(origen, destino, visitado, camino, 0);

    cout << "\n--------------------------------------\n";
    if (mejorCosto == INT_MAX) {
        cout << "No se encontró un camino dentro del límite.\n";
    } else {
        cout << "Mejor camino encontrado: ";
        for (int i = 0; i < mejorCamino.size(); i++) {
            cout << mejorCamino[i];
            if (i != mejorCamino.size() - 1) cout << " -> ";
        }
        cout << "\nCosto total: " << mejorCosto << "\n";
    }
    cout << "--------------------------------------\n";

    return 0;
}