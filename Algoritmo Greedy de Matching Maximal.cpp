#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Estructura para representar una arista con sus nodos (u, v) y su peso
struct Arista {
    int u, v;
    int peso;
};

// Funcion para mostrar el titulo de manera limpia y profesional
void mostrarTitulo() {
    // setlocale(LC_ALL, ""); // Eliminado

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

int main() {

    mostrarTitulo();

    int tipo;
    // 1. Configuracion del tipo de grafo
    cout << "1. Seleccione el tipo de grafo:\n";
    cout << " [1] No ponderado\n";
    cout << " [2] Ponderado\n";
    cout << "Opcion: ";
    cin >> tipo;

    if (tipo == 2) {
        cout << "\n[ADVERTENCIA IMPORTANTE]:\n";
        cout << "Este algoritmo Greedy NO garantiza el pareo de\n";
        cout << "mayor peso total.\n";
        cout << "Solo selecciona aristas por orden de ingreso.\n";
        cout << "-------------------------------------------------------\n";
    }

    // 2. Configuracion del grafo
    int n, m;
    cout << "\nIngrese el numero de vertices (nodos): ";
    cin >> n;

    cout << "Ingrese el numero de aristas (conexiones): ";
    cin >> m;

    vector<Arista> aristas(m);

    // 3. Lectura de aristas
    cout << "\n=======================================================\n";
    cout << "                INGRESO DE ARISTAS\n";
    cout << "=======================================================\n";
    cout << "Usa numeros del 1 al " << n << " para los vertices.\n";

    for (int i = 0; i < m; i++) {
        if (tipo == 1) {
            cout << "Arista " << i + 1 << " (u v): ";
            cin >> aristas[i].u >> aristas[i].v;
            aristas[i].peso = 1; // Peso uniforme
        } else {
            cout << "Arista " << i + 1 << " (u v peso): ";
            cin >> aristas[i].u >> aristas[i].v >> aristas[i].peso;
        }

        // Validacion de nodos
        if (aristas[i].u <= 0 || aristas[i].u > n || aristas[i].v <= 0 || aristas[i].v > n) {
            cout << "[ERROR]: Los nodos deben estar entre 1 y " << n << ". Reingrese la arista.\n";
            i--;
        }
    }

    // 4. PREPARACION DEL ALGORITMO
    vector<bool> usado(n + 1, false);  // Control de nodos usados
    vector<Arista> matching;           // Almacena el pareo

    // 5. ALGORITMO GREEDY MAXIMAL MATCHING
    cout << "\n=======================================================\n";
    cout << "                PROCESO GREEDY\n";
    cout << "=======================================================\n";
    cout << "Decisiones:\n";

    for (int i = 0; i < m; i++) {
        int u = aristas[i].u;
        int v = aristas[i].v;

        if (!usado[u] && !usado[v]) {
            // Aceptar arista
            matching.push_back(aristas[i]);
            usado[u] = true;
            usado[v] = true;
            cout << " -> [ACEPTADA] Arista (" << u << " , " << v << ") Peso: "
                 << aristas[i].peso << ". Nodos bloqueados.\n";
        } else {
            // Rechazar arista
            cout << " -> [RECHAZADA] Arista (" << u << " , " << v
                 << ") -> Conflicto con nodo(s) ya emparejado(s).\n";
        }
    }

    // 6. RESULTADOS FINALES
    cout << "\n=======================================================\n";
    cout << "                RESULTADO FINAL\n";
    cout << "=======================================================\n";
    cout << "[TIPO DE PAREO]: Maximal (NO garantizado Maximo)\n";
    cout << "[TAMANO]: " << matching.size() << " aristas seleccionadas.\n";
    cout << "-------------------------------------------------------\n";

    int sumaPesos = 0;
    for (int i = 0; i < matching.size(); i++) {
        cout << "PAREJA " << setfill('0') << setw(2) << i + 1
             << ": (Nodo " << matching[i].u
             << " <-> Nodo " << matching[i].v << ")";

        if (tipo == 2) {
            cout << " [Peso: " << matching[i].peso << "]";
            sumaPesos += matching[i].peso;
        }
        cout << endl;
    }

    if (tipo == 2) {
        cout << "-------------------------------------------------------\n";
        cout << "PESO TOTAL DEL PAREO MAXIMAL: " << sumaPesos << endl;
    }

    cout << "=======================================================\n";

    return 0;
}
