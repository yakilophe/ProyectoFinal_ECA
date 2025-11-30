#include <iostream>   // La herramienta que nos permite "hablar" con el usuario (mostrar mensajes y pedir datos).
#include <vector>     // La herramienta para crear "listas flexibles" que guardan los puntos y las conexiones.
#include <iomanip>    // La herramienta para darle formato a la salida (por ejemplo, alinear numeros o poner ceros).
#include <cstdlib>    // La herramienta que usamos para generar numeros al azar (la base del sorteo).
#include <ctime>      // La herramienta que usa la hora actual para que los numeros al azar sean diferentes cada vez.

using namespace std; // Una simplificacion para no tener que escribir "std::" antes de cada comando.

// Estructura: Es como una "ficha de conexion" o tarjeta de identificacion para cada posible arista.
struct Arista {
    int u, v;     // 'u' y 'v' son los dos "puntos" (nodos) que conecta la arista.
    int peso;     // El valor o costo de esta conexion. (Si no se usa, vale 1).
    bool activa;  // Un indicador de si esta arista todavia esta en el "sorteo" ('true') o ya fue descartada ('false').
};

// Funcion para mostrar el titulo y las reglas del algoritmo.
void mostrarTitulo() {
    // setlocale(LC_ALL, ""); // Eliminado

    // A partir de aqui, todo es texto que se muestra al usuario sin modificar.
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

// La funcion 'main' es la "Receta Principal" donde sucede toda la accion del programa.
int main() {
    // Inicializa el generador de numeros al azar usando la hora actual del sistema.
    srand((unsigned)time(NULL));
    mostrarTitulo();

    int tipo;
    // 1. Configuracion del tipo de red (grafo).
    cout << "1. Seleccione el tipo de grafo:\n";
    cout << " [1] No ponderado\n";
    cout << " [2] Ponderado\n";
    cout << "Opcion: ";
    cin >> tipo;

    // Muestra una advertencia si se elige un grafo con peso (ponderado).
    if (tipo == 2) {
        cout << "\n[ADVERTENCIA]: El algoritmo Israeli-Itai NO considera pesos.\n";
        cout << "El resultado NO garantiza mayor peso total; los pesos solo se muestran.\n";
        cout << "-------------------------------------------------------\n";
    }

    // 2. Configuracion de los puntos y las conexiones.
    int n, m;
    cout << "\nIngrese el numero de vertices (nodos): ";
    cin >> n; // 'n' guarda la cantidad total de puntos.
    cout << "Ingrese el numero de aristas (conexiones): ";
    cin >> m; // 'm' guarda la cantidad total de conexiones.

    // Creamos la lista 'aristas' para guardar las 'm' fichas de conexion.
    vector<Arista> aristas(m);
    cout << "\n=======================================================\n";
    cout << "                 INGRESO DE ARISTAS\n";
    cout << "=======================================================\n";
    cout << "Usa numeros del 1 al " << n << " para los vertices.\n";

    // Bucle: Repite 'm' veces para pedir la informacion de cada conexion.
    for (int i = 0; i < m; ++i) {
        if (tipo == 1) {
            // Si es sin peso: se piden solo los dos puntos (u, v).
            cout << "Arista " << i + 1 << " (u v): ";
            cin >> aristas[i].u >> aristas[i].v;
            aristas[i].peso = 1; // El peso se fija en 1.
        } else {
            // Si es con peso: se piden los dos puntos (u, v) y el valor (peso).
            cout << "Arista " << i + 1 << " (u v peso): ";
            cin >> aristas[i].u >> aristas[i].v >> aristas[i].peso;
        }
        aristas[i].activa = true; // Al inicio, todas las conexiones estan activas.

        // Validacion: Verifica que los numeros de los puntos esten dentro del rango permitido [1, n].
        if (aristas[i].u <= 0 || aristas[i].u > n || aristas[i].v <= 0 || aristas[i].v > n) {
            cout << "[ERROR]: Nodos fuera de rango. Reingrese.\n";
            --i; // Regresa el contador para pedir de nuevo esta conexion.
        }
    }

    // 3. PREPARACION DEL ALGORITMO ISRAELI-ITAI

    // 'incidentes': Una lista de listas. Para cada punto (nodo), guarda una lista de las conexiones (indices de aristas) que lo tocan.
    vector< vector<int> > incidentes(n + 1);
    for (int i = 0; i < m; ++i) {
        // Agrega el indice de la arista 'i' a la lista del punto 'u' y a la lista del punto 'v'.
        incidentes[ aristas[i].u ].push_back(i);
        incidentes[ aristas[i].v ].push_back(i);
    }

    vector<bool> usado(n + 1, false); // 'usado': Marca que puntos ya tienen pareja ('true' = ocupado).
    vector<Arista> matching; // 'matching': Lista final donde se guardan las conexiones elegidas.

    cout << "\n=======================================================\n";
    cout << "                 PROCESO ISRAELI-ITAI\n";
    cout << "=======================================================\n";

    bool quedanAristas = true; // Indicador de si el proceso debe seguir.
    int ronda = 1; // Contador de rondas.

    // El bucle principal: Continua hasta que no se pueda formar ninguna pareja nueva.
    while (true) {
        // Verificar si queda alguna arista activa y con ambos nodos libres:
        // Buscamos si hay alguna conexion disponible que tenga dos puntos sin pareja.
        bool anyActive = false;
        for (int i = 0; i < m; ++i) {
            if (aristas[i].activa && !usado[ aristas[i].u ] && !usado[ aristas[i].v ]) {
                anyActive = true;
                break; // Si encontramos una, el proceso sigue.
            }
        }
        if (!anyActive) break; // Si no encontramos ninguna, terminamos el bucle.

        cout << "\n--- RONDA " << ronda++ << " ---\n";

        // Paso 1: Cada nodo no usado elige UNA arista activa al azar (si tiene)
        // 'elegidaPorNodo[u]': Guarda el indice de la arista que el punto 'u' eligio. (-1 significa que no eligio nada).
        vector<int> elegidaPorNodo(n + 1, -1);

        for (int u = 1; u <= n; ++u) { // Recorremos todos los puntos.
            if (usado[u]) continue; // Si el punto ya esta en una pareja, lo ignoramos.

            // Recolectar aristas activas incidentes al punto 'u'.
            vector<int> opciones;
            for (int k = 0; k < incidentes[u].size(); ++k) {
                int idx = incidentes[u][k]; // 'idx' es la posicion de la arista que toca a 'u'.
                if (!aristas[idx].activa) continue; // Si la arista ya fue descartada, la ignoramos.

                // Averiguamos cual es el otro punto de la arista.
                int v = (aristas[idx].u == u) ? aristas[idx].v : aristas[idx].u;
                if (usado[v]) continue; // Si el otro punto ('v') ya tiene pareja, ignoramos esta opcion.

                opciones.push_back(idx); // Si es una buena opcion, la anadimos a la lista de opciones de 'u'.
            }
            if (opciones.size() > 0) {
                // Sorteo: 'u' elige una opcion al azar de su lista.
                int elegido = opciones[ rand() % opciones.size() ];
                elegidaPorNodo[u] = elegido;
            }
        }

        // Paso 2: Aceptar aquellas aristas que fueron elegidas mutuamente por ambos extremos
        // Solo si el punto 'u' eligio la arista 'e' Y el punto 'v' tambien eligio la misma arista 'e'.
        for (int e = 0; e < m; ++e) { // Recorremos todas las aristas.
            if (!aristas[e].activa) continue; // Si esta inactiva, la ignoramos.
            int u = aristas[e].u;
            int v = aristas[e].v;
            if (usado[u] || usado[v]) continue; // Si alguno de sus puntos ya tiene pareja, la ignoramos.

            // La condicion clave: Ambos puntos deben haber elegido esta misma arista 'e' en el Paso 1.
            if (elegidaPorNodo[u] == e && elegidaPorNodo[v] == e) {
                // Aceptar la arista:
                matching.push_back(aristas[e]); // La anadimos al pareo final.
                usado[u] = true; // Marcamos 'u' como ocupado.
                usado[v] = true; // Marcamos 'v' como ocupado.
                
                // Muestra el resultado de la aceptacion (sin modificar el texto del cout).
                cout << " -> [ACEPTADA] Arista (" << u << " , " << v << ")";
                if (tipo == 2) cout << " [Peso: " << aristas[e].peso << "]";
                cout << "\n";

                // Desactivar todas las aristas incidentes a u y v (la regla del pareo).
                // Descartamos todas las conexiones que tocan a los puntos recien emparejados.
                for (int k = 0; k < incidentes[u].size(); ++k) {
                    int idx = incidentes[u][k];
                    aristas[idx].activa = false;
                }
                for (int k = 0; k < incidentes[v].size(); ++k) {
                    int idx = incidentes[v][k];
                    aristas[idx].activa = false;
                }
            }
        }

        // Despues de aceptar las aristas mutuamente elegidas, puede quedar aristas activas
        // que quedaron "huerfanas" (sus puntos ahora estan ocupados por otras parejas).
        // Las desactivamos para limpiar la lista.
        for (int i = 0; i < m; ++i) {
            if (!aristas[i].activa) continue;
            if (usado[ aristas[i].u ] || usado[ aristas[i].v ]) {
                aristas[i].activa = false;
            }
        }
    }

    // Mostrar resultados
    cout << "\n=======================================================\n";
    cout << "                 RESULTADO FINAL\n";
    cout << "=======================================================\n";
    cout << "[TAMANO]: " << matching.size() << " aristas seleccionadas.\n";
    cout << "-------------------------------------------------------\n";

    int sumaPesos = 0;
    // Bucle para mostrar las conexiones seleccionadas en el pareo final.
    for (int i = 0; i < matching.size(); ++i) {
        // Usa comandos para asegurar que el numero de pareja tenga dos digitos (ej. 01, 02).
        cout << "PAREJA " << setw(2) << setfill('0') << i + 1 << ": ("
             << matching[i].u << " <-> " << matching[i].v << ")";
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
    cout << "\nProceso finalizado correctamente.\n";
    return 0; // El programa termina.
}
