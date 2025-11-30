#include <iostream>
using namespace std;

int MIncidencia[100][100];   // Matriz de incidencia (vértices x aristas)
int numVertices = 0;
int numAristas = 0;
bool esPonderado = false;
bool esDirigido = false;

// ============================================================
//          FUNCION PARA INICIALIZAR LA MATRIZ EN CERO
// ============================================================
void limpiarMatriz()
{
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
            MIncidencia[i][j] = 0;  // Todas las celdas a 0
}

// ============================================================
//     FUNCION PARA CREAR EL GRAFO (DIRIGIDO / NO DIRIGIDO)
// ============================================================
void crearGrafo()
{
    limpiarMatriz(); // Limpia la matriz antes de llenar

    cout << "\nIngrese el numero de vertices: ";
    cin >> numVertices;

    cout << "Ingrese el numero de aristas: ";
    cin >> numAristas;

    cout << "\n¿El grafo es ponderado? (1 = Si, 0 = No): ";
    cin >> esPonderado;

    cout << "¿El grafo es dirigido? (1 = Si, 0 = No): ";
    cin >> esDirigido;

    cout << "\nIngrese las aristas:\n";

    for(int e = 0; e < numAristas; e++)
    {
        int u, v, peso = 1;

        if(esPonderado)
        {
            // Si es ponderado se pide el peso también
            cout << "Arista " << e << " (origen destino peso): ";
            cin >> u >> v >> peso;
        }
        else
        {
            // Si no es ponderado, solo origen y destino
            cout << "Arista " << e << " (origen destino): ";
            cin >> u >> v;
        }

        // --------------------------------------------------------
        // GRAFO DIRIGIDO
        // --------------------------------------------------------
        if(esDirigido)
        {
            // En el origen va el negativo
            MIncidencia[u][e] = -(peso);

            // En el destino va el positivo
            MIncidencia[v][e] = +(peso);
        }
        // --------------------------------------------------------
        // GRAFO NO DIRIGIDO
        // --------------------------------------------------------
        else
        {
            // En grafos NO dirigidos:
            // Se marca con el peso en ambos vértices

            MIncidencia[u][e] = peso;
            MIncidencia[v][e] = peso;
        }
    }
}

// ============================================================
//            FUNCION PARA IMPRIMIR MATRIZ DE INCIDENCIA
// ============================================================
void imprimirMatriz()
{
    cout << "\n====== MATRIZ DE INCIDENCIA ======\n\n";

    // Imprimir encabezado (aristas)
    cout << "      ";
    for(int e = 0; e < numAristas; e++)
        cout << "A" << e << " ";
    cout << endl;

    // Imprimir filas (vértices)
    for(int i = 0; i < numVertices; i++)
    {
        cout << "V" << i << " |  ";

        for(int j = 0; j < numAristas; j++)
        {
            cout << MIncidencia[i][j] << "  ";
        }
        cout << endl;
    }

    cout << endl;
}

// ============================================================
//                          MENU
// ============================================================
int main()
{
    int opcion;

    do {
        cout << "\n===== MENU DE GRAFOS =====\n";
        cout << "1. Crear grafo (dirigido / no dirigido)\n";
        cout << "2. Mostrar matriz de incidencia\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1: crearGrafo(); break;
            case 2: imprimirMatriz(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n"; break;
        }

    } while(opcion != 0);

    return 0;
}
