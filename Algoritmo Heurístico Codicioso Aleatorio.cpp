#include <iostream>  // Necesaria para la entrada y salida de datos (cin para leer, cout para mostrar).
#include <vector>    // Proporciona la estructura 'vector', una lista dinamica para el grafo y las aristas.
#include <algorithm> // Contiene funciones utiles para manipular colecciones, como ordenar o 'random_shuffle' (barajar).
#include <utility>   // Proporciona la estructura 'pair' (par), usada para representar las aristas (u, v).
#include <limits>    // Contiene informacion sobre limites, esencial para manejar errores de entrada (limpiar el buffer).
#include <cstdlib>   // Proporciona funciones de utilidad general, incluyendo las de generacion de numeros aleatorios (rand y srand).
#include <ctime>     // Proporciona la funcion 'time', usada para inicializar la semilla de aleatoriedad (srand(time(0))).

using namespace std;

// --- ESTRUCTURAS DE DATOS GLOBALES ---
const int MAXN = 100; // Define el limite maximo de nodos (nodos del 1 al 100).
int nNodos = 0;       // Almacena la cantidad de nodos que el usuario ingresa.
// Vector (lista) que guarda todas las conexiones (aristas) del grafo.
vector<pair<int, int> > todasAristas;

// =========================================================================
// FUNCION PRINCIPAL DEL ALGORITMO HEURISTICO ALEATORIO
// =========================================================================

// Algoritmo Codicioso Aleatorio.
// El enfoque es: "toma la primera arista que puedas, sin importar su importancia,
// ¡pero revisa las aristas en un orden totalmente al azar!".
int randomGreedyMatching() {
    // Lista para guardar las aristas que finalmente formaran el emparejamiento (M).
    vector<pair<int, int> > matchingResultante;
    // Lista de control: 'cubierto[i]' es verdadero si el nodo 'i' ya esta emparejado.
    vector<bool> cubierto(nNodos + 1, false); 

    // 1. Barajar las aristas aleatoriamente.
    cout << "\n[PROCESO] Barajando el orden de las aristas aleatoriamente...\n";
    // 'random_shuffle' mezcla todos los elementos de la lista 'todasAristas' al azar.
    random_shuffle(todasAristas.begin(), todasAristas.end()); 

    // 2. Iterar sobre las aristas en el nuevo orden aleatorio.
    cout << "[PROCESO] Analizando aristas en orden aleatorio Codicioso...\n";
    // Recorre la lista de aristas que ahora estan desordenadas.
    for (size_t i = 0; i < todasAristas.size(); ++i) {
        int u = todasAristas[i].first;  // Nodo de inicio de la arista actual.
        int v = todasAristas[i].second; // Nodo de fin de la arista actual.

        // Condicion Codiciosa: Si el nodo 'u' NO esta cubierto Y el nodo 'v' NO esta cubierto...
        // ...es decir, si la arista (u, v) no choca con ninguna ya elegida.
        if (!cubierto[u] && !cubierto[v]) {
            // ...LO TOMAMOS.
            matchingResultante.push_back(todasAristas[i]); // Anade la arista al resultado.
            cubierto[u] = true;                          // Marca el nodo 'u' como cubierto.
            cubierto[v] = true;                          // Marca el nodo 'v' como cubierto.
            cout << " -> Emparejado: (" << u << " -- " << v << ")\n";
        } else {
            // Esta arista es ignorada porque choca con una anterior.
            // No se muestra en pantalla para no saturar.
        }
    }
    
    // Almacenar el resultado en la lista global para que el menu pueda mostrarlo despues.
    todasAristas = matchingResultante; 
    
    // Devuelve el numero total de aristas encontradas.
    return matchingResultante.size();
}

// =========================================================================
// MOSTRAR RESULTADOS Y VERIFICAR
// =========================================================================

void mostrarResultado(int res, const vector<pair<int, int> >& aristasOriginales) {
    // La lista de aristas seleccionadas esta en 'todasAristas' (se actualizo en la funcion anterior).
    vector<pair<int, int> > matchingResultante = todasAristas; 
    vector<bool> cubierto(nNodos + 1, false);
    
    // Vuelve a calcular que nodos quedaron cubiertos por el emparejamiento resultante.
    for (size_t i = 0; i < matchingResultante.size(); ++i) {
        cubierto[matchingResultante[i].first] = true;
        cubierto[matchingResultante[i].second] = true;
    }

    // Muestra el resumen del resultado
    cout << "\n===============================================\n";
    cout << "          RESULTADO DE LA HEURISTICA ALEATORIA\n";
    cout << "===============================================\n";
    cout << "  Tamano del Pareo: " << res << endl;
    cout << "  Aristas totales en el grafo: " << aristasOriginales.size() << endl;
    cout << "-----------------------------------------------\n";

    // 1. Mostrar las aristas
    cout << "  Aristas en el Emparejamiento:\n";
    // ... (Imprime las aristas que fueron elegidas) ...

    // 2. Comprobar Maximalidad 
    cout << "\nVERIFICACION DE MAXIMALIDAD:\n";
    // Todo algoritmo Codicioso es siempre Maximal, porque no deja pasar la oportunidad
    // de tomar una arista si es valida. Por lo tanto, el resultado final no puede ser mejorado localmente.
    cout << "[SI ES MAXIMAL!] La logica Codiciosa siempre garantiza que el resultado es **MAXIMAL**.\n";
    cout << "Esto significa que no se puede anadir ninguna arista mas al conjunto M sin conflicto.\n";

    // 3. Comprobar Perfeccion y Maximo 
    int nodosCubiertos = 0;
    for (int i = 1; i <= nNodos; ++i) {
        if (cubierto[i]) {
            nodosCubiertos++;
        }
    }

    cout << "\nVERIFICACION DE PERFECCION Y MAXIMO (No Garantizado):\n";
    cout << "  - Nodos totales en el grafo: " << nNodos << ".\n";
    cout << "  - Nodos cubiertos por el pareo: " << nodosCubiertos << ".\n";
    
    // Si el numero de nodos cubiertos es igual al numero total de nodos, es "Perfecto".
    if (nodosCubiertos == nNodos) {
        cout << "[POSIBLEMENTE PERFECTO!] El pareo cubre todos los nodos, lo cual es el mejor escenario.\n";
    } else {
        cout << "[NO PERFECTO] Quedaron " << (nNodos - nodosCubiertos) << " nodos libres.\n";
    }
    // Es una heuristica, por lo que NO esta garantizado que sea el *Maximo* (el mejor resultado global).
    cout << "[ADVERTENCIA] El resultado es Maximal, pero **NO** esta garantizado que sea el **MAXIMO**.\n";
    cout << "  -> ¡Ejecutar esta heuristica multiples veces sobre el mismo grafo puede dar resultados diferentes!\n";

    cout << "===============================================\n";
}

// =========================================================================
// MENU PRINCIPAL
// =========================================================================

void menu() {
    int op;
    int resultado = 0;
    // Guarda la lista de aristas original (antes de barajar) para poder reiniciar el proceso.
    vector<pair<int, int> > aristasOriginales;

    // Inicializa la semilla de aleatoriedad. Esto asegura que la funcion 'random_shuffle'
    // genere un orden de aristas diferente cada vez que se ejecuta el programa.
    srand(time(0)); 

    do {
        // Muestra el menu de opciones al usuario
        cout << "\n===============================================\n";
        cout << "  ALGORITMO HEURISTICO: CODICIOSO ALEATORIO\n";
        // ... (Descripcion de las propiedades del algoritmo) ...
        
        cout << "1. Ingresar Grafo (Nodos y Aristas)\n";
        cout << "2. Ejecutar Algoritmo Heuristico (Orden Aleatorio)\n";
        cout << "3. Mostrar Resultados y Verificaciones\n";
        cout << "4. Salir del Programa\n";
        // ... (Pide la opcion y maneja errores) ...
        
        if (!(cin >> op)) { 
            cout << "\n[ERROR] Entrada invalida. Ingresa un numero (1-4).\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = 0; continue;
        }

        switch (op) {
        case 1:
            // Opcion 1: Ingreso de Grafo
            // ... (Logica para limpiar y solicitar la entrada de nodos y aristas) ...
            // Las aristas se guardan en dos lugares: 'todasAristas' (para usar) y 'aristasOriginales' (para restaurar).
            break;

        case 2:
            // Opcion 2: Ejecutar el Algoritmo
            if (nNodos == 0) { /* ... */ break; }
            // Restaurar las aristas originales antes de cada ejecucion aleatoria
            // Esto es crucial, ya que el algoritmo Codicioso Aleatorio modifica 'todasAristas' al final.
            todasAristas = aristasOriginales;
            
            // Ejecutar el calculo.
            resultado = randomGreedyMatching();
            cout << "\n[FINALIZADO] Algoritmo ejecutado. Se encontro un Pareo Maximal de tamano: " << resultado << endl;
            break;

        case 3:
            // Opcion 3: Mostrar Resultados
            // ... (Llama a la funcion de analisis) ...
            break;

        case 4:
            // Opcion 4: Salir
            cout << "\nSaliendo del programa... Hasta pronto!\n";
            break;

        default:
            cout << "\n[ERROR] Opcion invalida.\n";
        }
    } while (op != 4);
}

// Funcion principal de C++: el punto de inicio del programa.
int main() {
    menu(); // Llama al menu principal para comenzar.
    return 0;
}

