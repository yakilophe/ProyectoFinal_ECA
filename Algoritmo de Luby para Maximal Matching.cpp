#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Estructura para representar una arista
struct Arista {
    int u, v;
    int peso;
};

// Funcion para mostrar el titulo
void mostrarTitulo() {
    cout << "\n=======================================================\n";
    cout << "         ALGORITMO GREEDY MAXIMAL MATCHING\n";
    cout << "=======================================================\n";
    cout << "[IMPORTANTE]: Este algoritmo SOLO es valido para\n";
    cout << "             GRAFOS NO DIRIGIDOS.\n\n";
    cout << "[OBJETIVO]: Encontrar un conjunto MAXIMAL de aristas.\n";
    cout << "[NOTA]: La seleccion de aristas se basa en el ORDEN\n";
    cout << "        de entrada, NO en el peso ni la optimalidad.\n";
    cout << "-------------------------------------------------------\n";
}

// ===============================================================
// GRAFOS PREESTABLECIDOS
// ===============================================================
void cargarGrafoNoPonderado(vector<Arista>& aristas, int& n, int& m) {
    n = 6;
    m = 7;

    aristas.clear();
    aristas.push_back({1, 2, 1});
    aristas.push_back({1, 3, 1});
    aristas.push_back({2, 4, 1});
    aristas.push_back({3, 4, 1});
    aristas.push_back({4, 5, 1});
    aristas.push_back({5, 6, 1});
    aristas.push_back({3, 6, 1});
}

void cargarGrafoPonderado(vector<Arista>& aristas, int& n, int& m) {
    n = 6;
    m = 7;

    aristas.clear();
    aristas.push_back({1, 2, 3});
    aristas.push_back({1, 3, 5});
    aristas.push_back({2, 4, 2});
    aristas.push_back({3, 4, 8});
    aristas.push_back({4, 5, 6});
    aristas.push_back({5, 6, 4});
    aristas.push_back({3, 6, 7});
}

// ===============================================================
// IMPRIMIR MATRIZ DE ADYACENCIA
// ===============================================================
void imprimirMatriz(int n, const vector<Arista>& aristas) {
    vector< vector<int> > A(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < aristas.size(); i++) {
        int u = aristas[i].u;
        int v = aristas[i].v;
        A[u][v] = aristas[i].peso;
        A[v][u] = aristas[i].peso; // No dirigido
    }

    cout << "\n=======================================================\n";
    cout << "                MATRIZ DE ADYACENCIA\n";
    cout << "=======================================================\n";

    cout << "      ";
    for (int j = 1; j <= n; j++)
        cout << setw(4) << j;
    cout << "\n";

    for (int i = 1; i <= n; i++) {
        cout << setw(4) << i << " ";
        for (int j = 1; j <= n; j++) {
            cout << setw(4) << A[i][j];
        }
        cout << "\n";
    }
}

int main() {

    mostrarTitulo();

    int tipo;
    cout << "1. Seleccione el tipo de grafo:\n";
    cout << " [1] No ponderado\n";
    cout << " [2] Ponderado\n";
    cout << "Opcion: ";
    cin >> tipo;

    if (tipo == 2) {
        cout << "\n[ADVERTENCIA]: Este algoritmo NO garantiza el pareo de mayor peso.\n";
    }

    int opcionPre;
    vector<Arista> aristas;
    int n = 0, m = 0;

    cout << "\n2. Seleccione modo:\n";
    cout << " [1] Ingresar aristas manualmente\n";
    cout << " [2] Usar grafo preestablecido\n";
    cout << "Opcion: ";
    cin >> opcionPre;

    if (opcionPre == 2) {
        if (tipo == 1) {
            cargarGrafoNoPonderado(aristas, n, m);
        } else {
            cargarGrafoPonderado(aristas, n, m);
        }
    } else {
        cout << "\nIngrese el numero de vertices: ";
        cin >> n;
        cout << "Ingrese el numero de aristas: ";
        cin >> m;

        aristas.resize(m);

        cout << "\n=======================================================\n";
        cout << "                INGRESO DE ARISTAS\n";
        cout << "=======================================================\n";

        for (int i = 0; i < m; i++) {
            if (tipo == 1) {
                cout << "Arista " << i + 1 << " (u v): ";
                cin >> aristas[i].u >> aristas[i].v;
                aristas[i].peso = 1;
            } else {
                cout << "Arista " << i + 1 << " (u v peso): ";
                cin >> aristas[i].u >> aristas[i].v >> aristas[i].peso;
            }

            if (aristas[i].u < 1 || aristas[i].u > n || aristas[i].v < 1 || aristas[i].v > n) {
                cout << "[ERROR]: nodos invalidos.\n";
                i--;
            }
        }
    }

    // Imprimir matriz de adyacencia
    imprimirMatriz(n, aristas);

    // ===============================================================
    // ALGORITMO GREEDY
    // ===============================================================
    vector<bool> usado(n + 1, false);
    vector<Arista> matching;

    cout << "\n=======================================================\n";
    cout << "                PROCESO GREEDY\n";
    cout << "=======================================================\n";

    for (int i = 0; i < aristas.size(); i++) {
        int u = aristas[i].u;
        int v = aristas[i].v;

        if (!usado[u] && !usado[v]) {
            matching.push_back(aristas[i]);
            usado[u] = true;
            usado[v] = true;
            cout << " -> [ACEPTADA] (" << u << " , " << v << ") Peso: " << aristas[i].peso << "\n";
        } else {
            cout << " -> [RECHAZADA] (" << u << " , " << v << ")\n";
        }
    }

    cout << "\n=======================================================\n";
    cout << "                RESULTADO FINAL\n";
    cout << "=======================================================\n";

    cout << "Tamaño del pareo: " << matching.size() << "\n";

    int sumaPesos = 0;
    for (int i = 0; i < matching.size(); i++) {
        cout << "PAREJA " << i + 1 << ": ("
             << matching[i].u << " <-> " << matching[i].v << ")";
        if (tipo == 2) {
            cout << " [Peso: " << matching[i].peso << "]";
            sumaPesos += matching[i].peso;
        }
        cout << "\n";
    }

    if (tipo == 2) {
        cout << "Peso total: " << sumaPesos << "\n";
    }

    cout << "=======================================================\n";

    return 0;
}
