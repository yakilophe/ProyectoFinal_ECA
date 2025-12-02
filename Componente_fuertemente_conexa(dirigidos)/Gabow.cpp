#include <iostream>     // Biblioteca para imprimir texto y leer datos
#include <stack>        // Biblioteca para usar pilas (Stack)
#include <iomanip>      // Biblioteca para imprimir tablas alineadas
using namespace std;

const int MAXN = 50;    // Maximo numero de nodos permitidos

// ---------------------------------------------------------------
// VARIABLES GLOBALES
// ---------------------------------------------------------------

int n;                      // Cantidad de nodos del grafo
int matriz[MAXN][MAXN];     // Matriz de adyacencia (guarda si hay conexion entre nodos)
int pre[MAXN];              // Arreglo para guardar el tiempo en que un nodo es descubierto
int preCont = 0;            // Contador para asignar valores crecientes a pre[]

stack<int> S;               // Pila principal usada en el algoritmo
stack<int> P;               // Pila auxiliar para encontrar SCC

// Letras que representan cada nodo (A,B,C,...)
char elementos[] = {
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

// ======================================================
// LIMPIAR MATRIZ COMPLETA
// ======================================================
void limpiarMatriz() {

    // Recorre todas las posiciones de la matriz y las llena con 0
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            matriz[i][j] = 0;
}

// ======================================================
// LEER MATRIZ DE ADYACENCIA DE FORMA MANUAL
// ======================================================
void leerMatrizManual() {
    cout << "\nIngrese la matriz de adyacencia (0 = no, 1 = si)\n";

    // Se pide fila por fila al usuario
    for (int i = 0; i < n; i++) {

        // Se imprime la letra del nodo de la fila actual
        cout << "Fila para nodo " << elementos[i] << ": ";

        // Se lee cada columna de esa fila
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];   // 0 si no hay arista, 1 si si hay
        }
    }
}

// ======================================================
// CARGAR GRAFO PREDEFINIDO (DIRIGIDO Y NO PONDERADO)
// ======================================================
void cargarDirigidoNoPonderado() {

    n = 5;             // El grafo tendra 5 nodos
    limpiarMatriz();   // Se limpia antes de rellenar

    // Se colocan las aristas segun el grafo dado
    matriz[1][0] = 1;   // B -> A
    matriz[0][3] = 1;   // A -> D
    matriz[1][2] = 1;   // B -> C
    matriz[3][2] = 1;   // D -> C
    matriz[3][1] = 1;   // D -> B
    matriz[4][0] = 1;   // E -> A
}

// ======================================================
// IMPRIMIR MATRIZ EN FORMATO DE TABLA
// ======================================================
void imprimirMatriz() {

    cout << "\n=== Matriz usada ===\n\n";

    // Encabezados de columnas
    cout << setw(4) << " ";
    for (int j = 0; j < n; j++)
        cout << setw(4) << elementos[j];
    cout << "\n";

    // Imprimir cada fila
    for (int i = 0; i < n; i++) {

        // Imprime letra del nodo de la fila
        cout << setw(4) << elementos[i];

        // Imprime cada valor de la fila
        for (int j = 0; j < n; j++)
            cout << setw(4) << matriz[i][j];

        cout << "\n";  // Salto de linea
    }
}

// ======================================================
// INICIALIZAR TODAS LAS VARIABLES ANTES DEL ALGORITMO
// ======================================================
void inicializar() {

    preCont = 0;    // Reinicia el contador de tiempos

    // Vaciar la pila S completa
    while (!S.empty()) S.pop();

    // Vaciar la pila P completa
    while (!P.empty()) P.pop();

    // Establecer pre[] en -1 para indicar que ningun nodo ha sido visitado aun
    for (int i = 0; i < n; i++)
        pre[i] = -1;
}

// ======================================================
// DFS DE GABOW (PARTE PRINCIPAL DEL ALGORITMO)
// ======================================================
void gabowDFS(int u) {

    // Asignar tiempo de descubrimiento al nodo
    pre[u] = preCont++;

    // Meter nodo en la pila principal
    S.push(u);

    // Tambien meter el nodo en la pila auxiliar
    P.push(u);

    // Recorrer todos los posibles destinos desde u
    for (int v = 0; v < n; v++) {

        // Si hay arista de u hacia v
        if (matriz[u][v] == 1) {

            // Si v aun no ha sido visitado
            if (pre[v] == -1) {

                // Se sigue explorando recursivamente
                gabowDFS(v);
            }
            // Si v ya fue descubierto y su tiempo es menor al de u
            else if (pre[v] < pre[u]) {

                // Se hace "rebobinado" de pila P para mantener limites correctos
                while (!P.empty() && pre[P.top()] > pre[v])
                    P.pop();
            }
        }
    }

    // Si el tope de la pila P coincide con u, encontramos una SCC
    if (!P.empty() && P.top() == u) {

        cout << "\nComponente fuertemente conexa: ";

        int v;

        // Extraemos nodos de la pila S hasta volver a u
        do {
            v = S.top();  // Obtener nodo del tope
            S.pop();      // Quitarlo de la pila
            cout << elementos[v] << " "; // Imprimir su letra

        } while (v != u);   // Se detiene cuando regresamos al nodo inicial u

        cout << "\n";

        P.pop();   // Quitar tambien el nodo de la pila auxiliar
    }
}

// ======================================================
// EJECUTAR TODO EL ALGORITMO DE GABOW
// ======================================================
void ejecutarGabow() {

    // Iniciar DFS desde todos los nodos no visitados
    for (int i = 0; i < n; i++)
        if (pre[i] == -1)
            gabowDFS(i);
}

// ======================================================
// PROGRAMA PRINCIPAL
// ======================================================
int main() {

    cout << "========================================\n";
    cout << "           GABOW - SCC                  \n";
    cout << "========================================\n";

    cout << "\nGRAFOS PREDEFINIDOS:\n";
    cout << "1. Dirigido y no ponderado\n";
    cout << "2. Ingresar grafo manualmente \n";

    int opcion;
    cout << "\nElija una opcion: ";
    cin >> opcion;

    if (opcion == 1) {

        // Cargar ejemplo fijo
        cargarDirigidoNoPonderado();
    }
    else if (opcion == 2) {

        // Leer tamaño del grafo
        cout << "\nNumero de vertices (max 26): ";
        cin >> n;

        if (n <= 0 || n > 26) {  // Validacion
            cout << "Numero invalido\n";
            return 1;
        }

        limpiarMatriz();     // Limpiar matriz
        leerMatrizManual();  // Leer datos ingresados por usuario
    }
    else {
        cout << "Opcion invalida\n";
        return 1;
    }

    imprimirMatriz();  // Mostrar matriz en pantalla

    inicializar();     // Preparar variables

    cout << "\n=== Componentes fuertemente conexas ===\n";
    ejecutarGabow();

    cout << "\n========================================\n";
    return 0;
}
