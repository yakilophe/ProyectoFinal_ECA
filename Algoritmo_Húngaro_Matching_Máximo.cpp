#include <iostream>   // Es la herramienta principal que permite que el programa hable con el usuario (mostrar textos y pedir datos).
#include <vector>     // Permite crear "listas" o "tablas" flexibles que se ajustan al tamaño de los datos que pones (como la matriz de costos).
#include <iomanip>    // Ayuda a darle formato bonito a los numeros que se muestran.
#include <climits>    // Nos da el numero mas grande posible (INT_MAX), util para buscar el "minimo" inicialmente.
#include <locale.h>   // Se usa para configurar el idioma y que las tildes, enes y otros caracteres especiales se vean bien en la consola.

using namespace std; // Una forma de escribir menos. Permite usar comandos como 'cout' y 'cin' directamente, sin escribir 'std::' antes.

// ============================
// MOSTRAR TITULO
// ============================
// Esta es una "funcion" (una pequena receta) que solo sirve para mostrar la presentacion del programa.
void mostrarTitulo() {
    setlocale(LC_ALL, ""); // Configura la consola para el idioma local.
    // Todo este bloque es texto de bienvenida que se muestra al usuario sin modificar.
    cout << "\n============================================================\n";
    cout << "     ALGORITMO HUNGARO - MATCHING MAXIMO \n";
    cout << "============================================================\n";
    cout << "[NOTA]: Este algoritmo SOLO funciona con grafos bipartitos\n";
    cout << "       no dirigidos y PONDERADOS.\n";
    cout << "       Para convertir a MAXIMIZACION se transforma la matriz.\n";
    cout << "------------------------------------------------------------\n";
}

// ============================
// IMPLEMENTACION DEL HUNGARO (MINIMO)
// ============================
// Esta es la "receta magica" que resuelve el problema de ASIGNACION de MINIMO COSTO.
// Recibe la matriz 'costo' y el tamaño del problema 'n'.
int hungaroMin(vector< vector<int> >& costo, int n) {
    // Listas internas que el algoritmo usa para hacer sus calculos:
    // u y v: Son "etiquetas" que se ajustan a cada nodo. Ayudan a encontrar la mejor solucion.
    // p: Guarda las parejas encontradas (p[j] es el nodo que esta emparejado con el nodo j).
    // way: Ayuda a encontrar un "camino de mejora" para optimizar las parejas.
    vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);

    // Bucle principal: Intenta encontrar una pareja optima para cada elemento (i) del primer grupo.
    for (int i = 1; i <= n; i++) {
        p[0] = i; // Establece el nodo 'i' como el que actualmente busca una pareja.
        int j0 = 0;
        vector<int> minv(n + 1, INT_MAX); // minv: Minimo "precio de conexion" para los nodos libres.
        vector<bool> usado(n + 1, false); // usado: Marca los nodos que ya se estan considerando en el intento de emparejamiento actual.

        // Bucle que busca un "camino aumentante" (una forma de mejorar la asignacion ya hecha).
        do {
            usado[j0] = true;
            int i0 = p[j0], delta = INT_MAX, j1 = 0;

            // Busca la arista con el menor "costo ajustado" para seguir el camino.
            for (int j = 1; j <= n; j++) {
                if (!usado[j]) { // Si el nodo de destino aun no esta en el camino...
                    // 'cur' calcula el "costo reducido": costo original - etiquetas.
                    int cur = costo[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0; // Recuerda por donde llegaste a 'j'.
                    }
                    if (minv[j] < delta) { // Encuentra el valor mas pequeno para el ajuste.
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            // Esta parte clave ajusta las etiquetas (u y v) para que el algoritmo pueda continuar buscando la solucion.
            for (int j = 0; j <= n; j++) {
                if (usado[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0); // Repite hasta que 'i' encuentra una pareja.

        // Reconstruye el emparejamiento con la nueva y mejor pareja encontrada.
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    // El resultado final de esta funcion es el costo MINIMO de la asignacion.
    int resultadoMin = -v[0];
    return resultadoMin;
}

// ============================
// PROGRAMA PRINCIPAL
// ============================
// El programa comienza a ejecutarse aqui.
int main() {
    mostrarTitulo();

    int tipo;
    cout << "Seleccione el tipo de grafo:\n";
    cout << " [1] No ponderado\n";
    cout << " [2] Ponderado\n";
    cout << "Opcion: ";
    cin >> tipo;

    if (tipo == 1) {
        cout << "\n[AVISO]: Se asignara peso = 1 a todas las aristas.\n";
    }

    int n;
    cout << "\nIngrese el numero de nodos por cada lado del bipartito: ";
    cin >> n; // 'n' es el numero de elementos en cada grupo (tamaño del problema).

    // Crea la tabla de 'costo' (la matriz nxn) y una variable para guardar el peso mas alto que ingrese el usuario.
    vector< vector<int> > costo(n + 1, vector<int>(n + 1));
    int maxValor = 0;

    cout << "\n============================================================\n";
    cout << "             INGRESO DE MATRIZ DE PESOS\n";
    cout << "============================================================\n";

    // Bucle para pedir al usuario todos los costos/pesos de la matriz.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (tipo == 2) {
                cout << "Peso [" << i << "][" << j << "]: ";
                cin >> costo[i][j];
            } else {
                costo[i][j] = 1;
            }

            // Al mismo tiempo que se ingresan los valores, se busca cual es el peso mas grande (maxValor).
            // Esto es necesario para el "truco" de maximizacion.
            if (costo[i][j] > maxValor) {
                maxValor = costo[i][j];
            }
        }
    }

    // ============================
    // TRANSFORMACION PARA MAXIMIZACION
    // ============================
    // Este es el paso clave para convertir el problema de MAXIMIZAR (ganancia/peso) a MINIMIZAR (costo).
    cout << "\n[TRANSFORMACION]: Convirtiendo a problema de MINIMIZACION...\n";

    // Se resta cada peso de la matriz del peso mas grande encontrado (maxValor).
    // Ejemplo: Si el maxValor es 10. Un peso de 8 se convierte en 2 (10-8).
    // Ahora, el camino mas "barato" (2) en la matriz transformada es el camino mas "caro" (8) en la matriz original.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            costo[i][j] = maxValor - costo[i][j];
        }
    }

    cout << "\n============================================================\n";
    cout << "                 PROCESANDO ALGORITMO\n";
    cout << "============================================================\n";

    // Llama a la funcion del Algoritmo Hungaro (que ahora resuelve el MINIMO COSTO de la matriz transformada).
    int resultadoMin = hungaroMin(costo, n);

    // Se revierte la transformacion para obtener el resultado Maximo original:
    // El Costo Minimo de la matriz transformada se resta del "costo total posible" (n * maxValor).
    int resultadoMax = n * maxValor - resultadoMin;
    // La variable 'resultadoMax' es el peso total del matching MAXIMO.

    cout << "\n============================================================\n";
    cout << "                 RESULTADO FINAL\n";
    cout << "============================================================\n";
    // Muestra el resultado final (el peso maximo de la asignacion).
    cout << "[MATCHING MAXIMO REAL]: " << resultadoMax << endl;
    cout << "============================================================\n";

    return 0; // El programa termina.
}
