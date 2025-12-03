#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ====================== GRAFOS PREDEFINIDOS ==========================

// NO DIRIGIDO – NO PONDERADO (sin duplicados)
int ND_NP_u[] = {0,0,0,1,1,2};
int ND_NP_v[] = {1,4,3,3,2,3};
int ND_NP_m = 6;
int ND_NP_n = 5;

// NO DIRIGIDO – PONDERADO (sin duplicados)
int ND_P_u[] = {0,0,0,1,1,2};
int ND_P_v[] = {1,4,3,3,2,3};
int ND_P_w[] = {4,6,9,8,7,5};
int ND_P_m = 6;
int ND_P_n = 5;

// ====================================================================

// Estructura para representar una arista
struct Arista {
    int u, v;
    int peso;
};

// ---------------------------------------------------------
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

// ================= MATRIZ DE ADYACENCIA ======================
void imprimirMatriz(int n, vector<Arista> &A) {
    vector< vector<int> > M(n, vector<int>(n, 0));

    for (int i = 0; i < A.size(); i++) {
        int u = A[i].u;
        int v = A[i].v;
        int w = A[i].peso;
        M[u][v] = w;
        M[v][u] = w; // no dirigido
    }

    cout << "\nMATRIZ DE ADYACENCIA:\n\n   ";
    for (int i = 0; i < n; i++)
        cout << setw(3) << i;
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << setw(3) << i;
        for (int j = 0; j < n; j++)
            cout << setw(3) << M[i][j];
        cout << "\n";
    }
}
// =============================================================


int main() {

    mostrarTitulo();

    // ========================== MENÚ A/B ===============================
    char origen;
    cout << "Seleccione origen del grafo:\n";
    cout << " A) Ingresar manualmente\n";
    cout << " B) Usar grafo predefinido\n";
    cout << "Opcion: ";
    cin >> origen;

    int tipo;
    int n, m;
    vector<Arista> aristas;

    // ===================== PREDEFINIDOS ======================
    if (origen == 'B' || origen == 'b') {

        cout << "\nSeleccione grafo predefinido:\n";
        cout << " 1) No dirigido y no ponderado\n";
        cout << " 2) No dirigido y ponderado\n";
        cout << "Opcion: ";
        int op; cin >> op;

        if (op == 1) {
            tipo = 1;
            n = ND_NP_n;
            m = ND_NP_m;
            aristas.resize(m);
            for (int i = 0; i < m; i++) {
                aristas[i].u = ND_NP_u[i];
                aristas[i].v = ND_NP_v[i];
                aristas[i].peso = 1;
            }
        }
        else {
            tipo = 2;
            n = ND_P_n;
            m = ND_P_m;
            aristas.resize(m);
            for (int i = 0; i < m; i++) {
                aristas[i].u = ND_P_u[i];
                aristas[i].v = ND_P_v[i];
                aristas[i].peso = ND_P_w[i];
            }
        }

    } else {
    // ===================== INGRESO MANUAL =====================

        cout << "1. Seleccione el tipo de grafo:\n";
        cout << " [1] No ponderado\n";
        cout << " [2] Ponderado\n";
        cout << "Opcion: ";
        cin >> tipo;

        if (tipo == 2) {
            cout << "\n[ADVERTENCIA IMPORTANTE]:\n";
            cout << "Este algoritmo Greedy NO garantiza el pareo de\n";
            cout << "mayor peso total.\n";
            cout << "-------------------------------------------------------\n";
        }

        cout << "\nIngrese el numero de vertices (nodos): ";
        cin >> n;

        cout << "Ingrese el numero de aristas (conexiones): ";
        cin >> m;

        aristas.resize(m);

        cout << "\n=======================================================\n";
        cout << "                INGRESO DE ARISTAS\n";
        cout << "=======================================================\n";
        cout << "Usa numeros del 0 al " << n - 1 << " para los vertices.\n";

        for (int i = 0; i < m; i++) {

            if (tipo == 1) {
                cout << "Arista " << i + 1 << " (u v): ";
                cin >> aristas[i].u >> aristas[i].v;
                aristas[i].peso = 1;
            }
            else {
                cout << "Arista " << i + 1 << " (u v peso): ";
                cin >> aristas[i].u >> aristas[i].v >> aristas[i].peso;
            }

            if (aristas[i].u < 0 || aristas[i].u >= n ||
                aristas[i].v < 0 || aristas[i].v >= n) {
                cout << "[ERROR]: Nodos fuera de rango. Reingrese.\n";
                i--;
            }
        }
    }

    // ========= IMPRIMIR MATRIZ DE ADYACENCIA ===========
    imprimirMatriz(n, aristas);

    // ================================================
    //         ALGORITMO GREEDY MAXIMAL MATCHING
    // ================================================
    vector<bool> usado(n, false);
    vector<Arista> matching;

    cout << "\n=======================================================\n";
    cout << "                PROCESO GREEDY\n";
    cout << "=======================================================\n";
    cout << "Decisiones:\n";

    for (int i = 0; i < m; i++) {
        int u = aristas[i].u;
        int v = aristas[i].v;

        if (!usado[u] && !usado[v]) {

            matching.push_back(aristas[i]);
            usado[u] = true;
            usado[v] = true;

            cout << " -> [ACEPTADA] Arista (" << u << " , " << v
                 << ") Peso: " << aristas[i].peso << ". Nodos bloqueados.\n";
        }
        else {
            cout << " -> [RECHAZADA] Arista (" << u << " , " << v
                 << ") -> Conflicto con nodo(s) ya emparejado(s).\n";
        }
    }

    // ============== RESULTADOS ====================
    cout << "\n=======================================================\n";
    cout << "                RESULTADO FINAL\n";
    cout << "=======================================================\n";
    cout << "[TIPO DE PAREO]: Maximal (NO garantizado Maximo)\n";
    cout << "[TAMANO]: " << matching.size() << " aristas seleccionadas.\n";
    cout << "-------------------------------------------------------\n";

    int sumaPesos = 0;
    for (int i = 0; i < matching.size(); i++) {
        cout << "PAREJA " << setfill('0') << setw(2) << i + 1
             << ": (" << matching[i].u
             << " <-> " << matching[i].v << ")";

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
