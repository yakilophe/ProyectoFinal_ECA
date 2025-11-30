#include <iostream>  // Herramienta para "hablar" con el usuario (mostrar mensajes y pedir datos).
#include <vector>    // Herramienta para crear "listas" que pueden crecer (para guardar puntos y conexiones).
#include <iomanip>   // Herramienta para formatear la salida (ej: poner ceros delante de los numeros).
#include <cstdlib>   // Herramienta que nos ayuda a generar numeros aleatorios.
#include <ctime>     // Herramienta para usar la hora del sistema como base para la aleatoriedad.

using namespace std; // Usamos el espacio de nombres estandar para simplificar los comandos.

// Estructura: Es como crear una "tarjeta de identificacion" para cada posible conexion (Arista).
struct Arista {
    int u, v;      // 'u' y 'v' son los dos "puntos" (nodos o vertices) que se conectan.
    int peso;      // El valor o costo de esa conexion. Si no es ponderado, vale 1.
    bool activa;   // Un indicador: 'true' si esta conexion todavia puede ser elegida, 'false' si ya fue descartada.
};

// Funcion para mostrar el titulo y las reglas del algoritmo.
void mostrarTitulo() {
    // setlocale(LC_ALL, ""); // Eliminado
    
    cout << "\n=======================================================\n";
    cout << "         ALGORITMO DE LUBY - MATCHING MAXIMAL\n";
    cout << "=======================================================\n";
    cout << "[IMPORTANTE]: Este algoritmo SOLO es valido para\n";
    cout << "             GRAFOS NO DIRIGIDOS.\n\n";
    cout << "[OBJETIVO]: Encontrar un conjunto MAXIMAL de aristas.\n";
    cout << "[NOTA]: Seleccion ALEATORIA por rondas.\n";
    cout << "-------------------------------------------------------\n";
}

// La funcion 'main' es la "Receta Principal" donde se ejecuta el programa.
int main() {
    // Inicializa la semilla aleatoria: Usa la hora actual para asegurar que los sorteos sean diferentes cada vez.
    srand(time(NULL));
    mostrarTitulo();

    int tipo;
    // 1. Configuracion del tipo de grafo: Pregunta si las conexiones tienen un peso extra.
    cout << "1. Seleccione el tipo de grafo:\n";
    cout << " [1] No ponderado\n";
    cout << " [2] Con peso extra (Ponderado)\n";
    cout << "Opcion: ";
    cin >> tipo;

    // Muestra una advertencia si eligen el grafo ponderado.
    if (tipo == 2) {
        cout << "\n[ADVERTENCIA IMPORTANTE]:\n";
        cout << "El algoritmo de Luby NO considera pesos.\n";
        cout << "El resultado NO garantiza mayor peso total.\n";
        cout << "-------------------------------------------------------\n";
    }

    // 2. Configuracion de la red (Grafo): Puntos y Conexiones.
    int n, m;
    cout << "\nIngrese el numero de vertices (nodos): ";
    cin >> n; // Guarda la cantidad de puntos.

    cout << "Ingrese el numero de aristas (conexiones): ";
    cin >> m; // Guarda la cantidad de conexiones.

    // Creamos la lista para guardar las 'm' tarjetas de conexion.
    vector<Arista> aristas(m);

    // 3. Lectura de las conexiones (Aristas).
    cout << "\n=======================================================\n";
    cout << "               INGRESO DE ARISTAS\n";
    cout << "=======================================================\n";
    cout << "Usa numeros del 1 al " << n << " para los vertices.\n";

    // Bucle: Repite 'm' veces para pedir la informacion de cada conexion.
    for (int i = 0; i < m; i++) {
        if (tipo == 1) {
            // Si es sin peso: pide solo los dos puntos.
            cout << "Arista " << i + 1 << " (u v): ";
            cin >> aristas[i].u >> aristas[i].v;
            aristas[i].peso = 1; // El peso se fija en 1.
        } else {
            // Si es con peso: pide los dos puntos y el valor.
            cout << "Arista " << i + 1 << " (u v peso): ";
            cin >> aristas[i].u >> aristas[i].v >> aristas[i].peso;
        }

        // Marca esta conexion como disponible para empezar.
        aristas[i].activa = true;

        // Validacion: Verifica que los numeros de los puntos esten dentro del rango [1, n].
        if (aristas[i].u <= 0 || aristas[i].u > n || aristas[i].v <= 0 || aristas[i].v > n) {
            cout << "[ERROR]: Nodos fuera de rango. Reingrese.\n";
            i--; // Regresa el contador para repetir el ingreso de esta conexion.
        }
    }

    // 4. PREPARACION DEL ALGORITMO
    // 'usado': Lista de marcas para saber que puntos ya estan emparejados ('true' = ocupado).
    vector<bool> usado(n + 1, false);
    // 'matching': Lista donde guardaremos las conexiones que forman el pareo final.
    vector<Arista> matching;

    // 5. ALGORITMO DE LUBY (Proceso de Rondas)
    cout << "\n=======================================================\n";
    cout << "                 PROCESO LUBY\n";
    cout << "=======================================================\n";

    bool quedanAristas = true; // Indicador para saber si hay conexiones activas.
    int ronda = 1; // Contador de rondas.

    // El bucle principal: Continua hasta que no quede ninguna conexion activa en el grafo.
    while (quedanAristas) {
        cout << "\n--- RONDA " << ronda++ << " ---\n";

        // 'seleccionadas': Lista temporal para guardar las posiciones (indices) de las conexiones sorteadas en esta ronda.
        vector<int> seleccionadas;

        // 1. Seleccion aleatoria: Se lanza una moneda por cada conexion activa.
        for (int i = 0; i < m; i++) {
            if (aristas[i].activa) { // Solo si la conexion no ha sido descartada.
                if (rand() % 2 == 0) { // Sorteo con 50% de probabilidad (si el residuo de dividir entre 2 es 0).
                    seleccionadas.push_back(i); // Guarda la posicion de la arista que gano el sorteo.
                }
            }
        }
        cout << "Conexiones sorteadas para esta ronda: " << seleccionadas.size() << ".\n";


        // 2. Resolver conflictos: Revisamos las conexiones sorteadas para ver si chocan con algo.
        for (int k = 0; k < seleccionadas.size(); k++) {
            int idx = seleccionadas[k]; // Obtenemos la posicion de la conexion a revisar.

            int u = aristas[idx].u; // El primer punto.
            int v = aristas[idx].v; // El segundo punto.

            // Condicion para ACEPTAR: Si ambos puntos estan LIBRES (no usados) Y la conexion esta ACTIVA.
            if (!usado[u] && !usado[v] && aristas[idx].activa) {
                // Aceptar conexion:
                matching.push_back(aristas[idx]); // Añade la conexion a la lista de pareo final.
                usado[u] = true; // Marca el punto 'u' como ocupado.
                usado[v] = true; // Marca el punto 'v' como ocupado.

                cout << " -> [ACEPTADA] (" << u << " , " << v << ")\n";

                // REGLA DE LUBY: Desactivar las conexiones que toquen a los puntos 'u' o 'v' para que no choquen despues.
                for (int j = 0; j < m; j++) {
                    if (aristas[j].activa && // Solo si la conexion 'j' sigue activa...
                       (aristas[j].u == u || aristas[j].v == u || // ...y toca al punto 'u'
                         aristas[j].u == v || aristas[j].v == v)) { // ...o toca al punto 'v'
                        aristas[j].activa = false; // ...¡la desactivamos!
                    }
                }
            }
        }


        // 3. Verificar si quedan aristas activas: Revisar si el juego debe continuar.
        quedanAristas = false; // Asumimos que no quedan.
        for (int i = 0; i < m; i++) {
            if (aristas[i].activa) {
                quedanAristas = true; // Si encontramos una, entonces si quedan.
                break; // Salimos del bucle si ya encontramos una.
            }
        }
        if (!quedanAristas) {
            cout << "--- NO QUEDAN CONEXIONES ACTIVAS. FIN DEL PROCESO. ---\n";
        }
    }

    // RESULTADO FINAL
    cout << "\n=======================================================\n";
    cout << "                 RESULTADO FINAL\n";
    cout << "=======================================================\n";
    cout << "[TAMANO]: " << matching.size() << " aristas seleccionadas.\n";
    cout << "-------------------------------------------------------\n";

    int sumaPesos = 0;
    // Bucle para mostrar las conexiones seleccionadas en el pareo final.
    for (int i = 0; i < matching.size(); i++) {
        // Usa setfill y setw para que el numero de pareja se vea con un cero delante (ej. 01, 02).
        cout << "PAREJA " << setfill('0') << setw(2) << i + 1
             << ": (" << matching[i].u
             << " <-> " << matching[i].v << ")";

        if (tipo == 2) {
            // Si el grafo fue ponderado, muestra el peso y lo suma.
            cout << " [Peso: " << matching[i].peso << "]";
            sumaPesos += matching[i].peso;
        }
        cout << endl;
    }

    // Muestra la suma total de pesos si el grafo fue ponderado.
    if (tipo == 2) {
        cout << "-------------------------------------------------------\n";
        cout << "PESO TOTAL DEL PAREO: " << sumaPesos << endl;
    }

    cout << "=======================================================\n";

    return 0; // El programa termina con exito.
}
