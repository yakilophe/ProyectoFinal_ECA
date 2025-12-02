#include <iostream>   // La herramienta que nos permite "hablar" con el usuario (mostrar mensajes y pedir datos).
#include <vector>     // La herramienta para crear "listas flexibles" que guardan los puntos y las conexiones.
#include <iomanip>    // La herramienta para darle formato a la salida (por ejemplo, alinear numeros o poner ceros).
#include <cstdlib>    // La herramienta que usamos para generar numeros al azar (la base del sorteo).
#include <ctime>      // La herramienta que usa la hora actual para que los numeros al azar sean diferentes cada vez.

using namespace std; // Una simplificacion para no tener que escribir "std::" antes de cada comando.

// ====================== GRAFOS PREDEFINIDOS ==========================

// No dirigido – No ponderado
int ND_NP_u[] = {0,0,0,1,1,2,3,3,3,4};
int ND_NP_v[] = {1,4,3,0,3,1,2,1,0,0};
int ND_NP_m = 10;
int ND_NP_n = 5;

// No dirigido – Ponderado
int ND_P_u[] = {0,0,0,1,1,1,2,2,3,3,3,4};
int ND_P_v[] = {1,4,3,0,3,2,1,3,2,1,0,0};
int ND_P_w[] = {4,6,9,4,8,7,7,5,5,8,9,6};
int ND_P_m = 12;
int ND_P_n = 5;

// ====================================================================

// Estructura: Es como una "ficha de conexion" o tarjeta de identificacion para cada posible arista.
struct Arista {
    int u, v;     // 'u' y 'v' son los dos "puntos" (nodos) que conecta la arista.
    int peso;     // El valor o costo de esta conexion. (Si no se usa, vale 1).
    bool activa;  // Un indicador de si esta arista todavia esta en el "sorteo" ('true') o ya fue descartada ('false').
};

// Funcion para mostrar el titulo y las reglas del algoritmo.
void mostrarTitulo() {
    cout << "\n=======================================================\n";
    cout << "         ALGORITMO ISRAELI-ITAI - MATCHING MAXIMAL\n";
    cout << "=======================================================\n";
    cout << "[IMPORTANTE]: Este algoritmo SOLO es valido para\n";
    cout << "             GRAFOS NO DIRIGIDOS.\n\n";
    cout << "[OBJETIVO]: Encontrar un conjunto MAXIMAL de aristas.\n";
    cout << "[NOTA]: Algoritmo paralelo adaptado a secuencial.\n";
    cout << "        Ignora pesos; si escoges ponderado, solo se muestran.\n";
    cout << "-------------------------------------------------------\n";
}

// ================= MATRIZ DE ADYACENCIA ======================
void imprimirMatriz(int n, vector<Arista> &A) {
    vector< vector<int> > M(n, vector<int>(n, 0));

    for (size_t i = 0; i < A.size(); i++) {
        int u = A[i].u;
        int v = A[i].v;
        int w = A[i].peso;
        M[u][v] = w;
        M[v][u] = w;
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
// ===============================================================


// La funcion 'main' es la "Receta Principal" donde sucede toda la accion del programa.
int main() {

    srand((unsigned)time(NULL));
    mostrarTitulo();

    // ========================== MENÚ A/B ===============================
    char origen;
    cout << "Seleccione origen del grafo:\n";
    cout << " A) Ingresar manualmente\n";
    cout << " B) Usar grafo predefinido\n";
    cout << "Opcion: ";
    cin >> origen;

    int tipo; // 1 no ponderado, 2 ponderado
    int n, m;
    vector<Arista> aristas;

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
                aristas[i].activa = true;
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
                aristas[i].activa = true;
            }
            cout << "\n[ADVERTENCIA]: Israeli-Itai NO usa pesos.\n";
        }
    }
    else {
        // ================= INGRESO MANUAL ==========================
        cout << "1. Seleccione el tipo de grafo:\n";
        cout << " [1] No ponderado\n";
        cout << " [2] Ponderado\n";
        cout << "Opcion: ";
        cin >> tipo;

        if (tipo == 2) {
            cout << "\n[ADVERTENCIA]: El algoritmo Israeli-Itai NO considera pesos.\n";
            cout << "-------------------------------------------------------\n";
        }

        cout << "\nIngrese el numero de vertices (nodos): ";
        cin >> n;
        cout << "Ingrese el numero de aristas (conexiones): ";
        cin >> m;

        aristas.resize(m);

        cout << "\n=======================================================\n";
        cout << "                 INGRESO DE ARISTAS\n";
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
            aristas[i].activa = true;

            if (aristas[i].u < 0 || aristas[i].u >= n || aristas[i].v < 0 || aristas[i].v >= n) {
                cout << "[ERROR]: Nodos fuera de rango. Reingrese.\n";
                i--;
            }
        }
    }

    // ========= IMPRIMIR MATRIZ DE ADYACENCIA ==========
    imprimirMatriz(n, aristas);

    // 3. PREPARACION DEL ALGORITMO ISRAELI-ITAI
    vector< vector<int> > incidentes(n);
    for (int i = 0; i < m; i++) {
        incidentes[ aristas[i].u ].push_back(i);
        incidentes[ aristas[i].v ].push_back(i);
    }

    vector<bool> usado(n, false);
    vector<Arista> matching;

    cout << "\n=======================================================\n";
    cout << "                 PROCESO ISRAELI-ITAI\n";
    cout << "=======================================================\n";

    int ronda = 1;

    while (true) {

        bool anyActive = false;
        for (int i = 0; i < m; i++) {
            if (aristas[i].activa && !usado[ aristas[i].u ] && !usado[ aristas[i].v ]) {
                anyActive = true;
                break;
            }
        }
        if (!anyActive) break;

        cout << "\n--- RONDA " << ronda++ << " ---\n";

        vector<int> elegidaPorNodo(n, -1);

        for (int u = 0; u < n; u++) {
            if (usado[u]) continue;

            vector<int> opciones;

            for (size_t k = 0; k < incidentes[u].size(); k++) {
                int idx = incidentes[u][k];
                if (!aristas[idx].activa) continue;

                int v = (aristas[idx].u == u) ? aristas[idx].v : aristas[idx].u;
                if (usado[v]) continue;

                opciones.push_back(idx);
            }

            if (opciones.size() > 0) {
                int elegido = opciones[ rand() % opciones.size() ];
                elegidaPorNodo[u] = elegido;
            }
        }

        for (int e = 0; e < m; e++) {
            if (!aristas[e].activa) continue;

            int u = aristas[e].u;
            int v = aristas[e].v;
            if (usado[u] || usado[v]) continue;

            if (elegidaPorNodo[u] == e && elegidaPorNodo[v] == e) {

                matching.push_back(aristas[e]);
                usado[u] = true;
                usado[v] = true;

                cout << " -> [ACEPTADA] Arista (" << u << " , " << v << ")";
                if (tipo == 2) cout << " [Peso: " << aristas[e].peso << "]";
                cout << "\n";

                for (size_t k = 0; k < incidentes[u].size(); k++)
                    aristas[ incidentes[u][k] ].activa = false;

                for (size_t k = 0; k < incidentes[v].size(); k++)
                    aristas[ incidentes[v][k] ].activa = false;
            }
        }

        for (int i = 0; i < m; i++) {
            if (!aristas[i].activa) continue;
            if (usado[ aristas[i].u ] || usado[ aristas[i].v ])
                aristas[i].activa = false;
        }
    }

    cout << "\n=======================================================\n";
    cout << "                 RESULTADO FINAL\n";
    cout << "=======================================================\n";
    cout << "[TAMANO]: " << matching.size() << " aristas seleccionadas.\n";
    cout << "-------------------------------------------------------\n";

    int sumaPesos = 0;

    for (size_t i = 0; i < matching.size(); i++) {
        cout << "PAREJA " << setw(2) << setfill('0') << i + 1 << ": (";
        cout << matching[i].u << " <-> " << matching[i].v << ")";
        cout << setfill(' '); // ? NECESARIO EN GCC 4.9.2

        if (tipo == 2) {
            cout << " [Peso: " << matching[i].peso << "]";
            sumaPesos += matching[i].peso;
        }
        cout << endl;
    }

    if (tipo == 2) {
        cout << "-------------------------------------------------------\n";
        cout << "PESO TOTAL DEL PAREO: " << sumaPesos << endl;
    }

    cout << "=======================================================\n";
    cout << "\nProceso finalizado correctamente.\n";

    return 0;
}
