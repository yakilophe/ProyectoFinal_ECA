// incluir la libreria iostream para entrada y salida
#include <iostream>
// incluir la libreria algorithm para usar sort
#include <algorithm>
// usar el espacio de nombres std para no escribir std:: cada vez
using namespace std;

// definir la estructura Arista que representa una arista del grafo
struct Arista {
    // nodo origen de la arista
    int u;
    // nodo destino de la arista
    int v;
    // peso de la arista
    int w;   // Peso
};

// declarar un arreglo global para almacenar hasta 300 aristas del grafo
Arista aristas[300];
// declarar un arreglo global para almacenar hasta 300 aristas del MST
Arista mst[300];
// arreglo para la estructura union find que guarda el padre de cada nodo
int padre[300];
// arreglo para union find que guarda el rango (altura aproximada) de cada raiz
int rangoUF[300];

// numero de vertices actual del grafo
int N = 0;
// numero de aristas actual del grafo
int E = 0;
// bandera que indica que el grafo tiene pesos (siempre true en esta version)
bool grafoTienePesos = true;

/********** UNION-FIND **********/
// funcion que inicializa union find para n elementos
void hacerSet(int n) {
    // bucle para cada nodo desde 0 hasta n-1
    for(int i = 0; i < n; i++) {
        // asignar que el padre inicial de i es i mismo
        padre[i] = i;
        // inicializar el rango de i en 0
        rangoUF[i] = 0;
    }
}

// funcion que encuentra el representante (raiz) del conjunto que contiene x
int encontrarPadre(int x) {
    // si x es su propio padre entonces es la raiz
    if(padre[x] == x)
        // devolver la raiz
        return x;
    // aplicar compresion de caminos: asignar directamente la raiz
    padre[x] = encontrarPadre(padre[x]);
    // devolver la raiz encontrada
    return padre[x];
}

// funcion que une los conjuntos que contienen a y b usando union por rango
void unir(int a, int b) {
    // encontrar la raiz de a
    a = encontrarPadre(a);
    // encontrar la raiz de b
    b = encontrarPadre(b);

    // si las raices son distintas unir los conjuntos
    if(a != b) {
        // si el rango de a es menor que el de b, hacer b padre de a
        if(rangoUF[a] < rangoUF[b])
            padre[a] = b;
        // si el rango de b es menor que el de a, hacer a padre de b
        else if(rangoUF[b] < rangoUF[a])
            padre[b] = a;
        // si los rangos son iguales, escoger una raiz y aumentar su rango
        else {
            padre[b] = a;
            rangoUF[a]++;
        }
    }
}

// comparador usado por sort para ordenar aristas por peso ascendente
bool compararAristas(const Arista &A, const Arista &B) {
    // devolver true si el peso de A es menor que el peso de B
    return A.w < B.w;
}

/********** KRUSKAL **********/
// funcion que ejecuta el algoritmo de Kruskal sobre el grafo actual
void ejecutarKruskal() {
    // ordenar las aristas desde la de menor peso a la de mayor
    sort(aristas, aristas + E, compararAristas);
    // inicializar union find para N vertices
    hacerSet(N);

    // contador para cuantas aristas se han agregado al MST
    int contador = 0;
    // variable para sumar el peso total del MST
    int pesoTotal = 0;

    // recorrer todas las aristas ordenadas
    for(int i = 0; i < E; i++) {
        // obtener el extremo u de la arista i
        int u = aristas[i].u;
        // obtener el extremo v de la arista i
        int v = aristas[i].v;

        // si u y v pertenecen a conjuntos distintos no forman ciclo
        if(encontrarPadre(u) != encontrarPadre(v)) {
            // agregar la arista i al arreglo mst en la posicion contador
            mst[contador] = aristas[i];
            // incrementar el contador de aristas del MST
            contador++;
            // sumar el peso de esta arista al peso total
            pesoTotal += aristas[i].w;
            // unir los conjuntos de u y v en union find
            unir(u, v);
        }
    }

    // imprimir encabezado del resultado MST
    cout << "\n======= ARBOL DE EXPANSION MINIMA (MST) =======\n";
    // imprimir cada arista que quedo en el MST
    for(int i = 0; i < contador; i++)
        // mostrar los nodos de la arista y su peso
        cout << mst[i].u << " -- " << mst[i].v << "  (peso = " << mst[i].w << ")\n";

    // mostrar el peso total del MST
    cout << "\nPeso total del MST = " << pesoTotal << "\n";
}

/********** CAPTURA MANUAL **********/
// funcion que permite al usuario ingresar un grafo manualmente
void capturarGrafo() {
    // pedir y leer el numero de vertices
    cout << "\nNumero de vertices: ";
    cin >> N;

    // pedir y leer el numero de aristas
    cout << "Numero de aristas: ";
    cin >> E;

    // asumir que el grafo tiene pesos inicialmente
    grafoTienePesos = true;

    // instruccion para el usuario sobre el formato de ingreso
    cout << "\nIngrese cada arista (u v peso):\n";

    // leer las E aristas
    for(int i = 0; i < E; i++) {
        // mostrar el indice de la arista que se va a ingresar
        cout << "Arista " << i << ": ";
        // leer origen, destino y peso de la arista i
        cin >> aristas[i].u >> aristas[i].v >> aristas[i].w;

        // validar que el peso sea positivo, si no marcar error
        if(aristas[i].w <= 0) {
            // informar que todas las aristas deben tener peso positivo
            cout << "\nERROR: Todas las aristas deben tener peso POSITIVO.\n";
            // marcar que el grafo no es valido para Kruskal
            grafoTienePesos = false;
        }
    }

    // si alguna arista tenia peso no valido informar al usuario
    if(!grafoTienePesos) {
        cout << "\nEl grafo no es valido para Kruskal.\n";
    }
}

/********** GRAFOS PREDEFINIDOS (SOLO PONDERADOS) **********/
// funcion que carga un grafo predefinido segun el parametro tipo
void cargarGrafoPredefinido(int tipo) {
    // si tipo es 1 cargar el grafo no dirigido y ponderado
    if(tipo == 1) {
        // fijar numero de vertices en 5
        N = 5;
        // fijar numero de aristas en 12
        E = 12;
        // indicar que el grafo tiene pesos
        grafoTienePesos = true;

        // definir los datos de las aristas: origen, destino, peso
        int datos[12][3] = {
            {0,1,4},{0,4,6},{0,3,9},
            {1,0,4},{1,3,8},{1,2,7},
            {2,1,7},{2,3,5},
            {3,2,5},{3,1,8},{3,0,9},
            {4,0,6}
        };
        // copiar los datos a la estructura global aristas
        for(int i = 0; i < E; i++){
            aristas[i].u = datos[i][0];
            aristas[i].v = datos[i][1];
            aristas[i].w = datos[i][2];
        }
        // indicar en pantalla que se cargo el grafo
        cout << "\nGrafo NO dirigido y ponderado cargado.\n";
    }

    // si tipo es 2 cargar el grafo dirigido y ponderado
    else if(tipo == 2) {
        // fijar numero de vertices en 5
        N = 5;
        // fijar numero de aristas en 6
        E = 6;
        // indicar que el grafo tiene pesos
        grafoTienePesos = true;

        // definir los datos de las aristas dirigidas con peso
        int datos[6][3] = {
            {1,0,3},{0,3,12},
            {1,2,18},{3,2,15},
            {3,1,9},{4,0,6}
        };
        // copiar los datos al arreglo global aristas
        for(int i = 0; i < E; i++){
            aristas[i].u = datos[i][0];
            aristas[i].v = datos[i][1];
            aristas[i].w = datos[i][2];
        }
        // indicar en pantalla que se cargo el grafo dirigido ponderado
        cout << "\nGrafo dirigido y ponderado cargado.\n";
    }
}

/********** MENÚ DE GRAFOS **********/
// funcion que muestra las opciones de grafos y carga segun la eleccion
void menuGrafos() {
    // variable para la opcion elegida por el usuario
    int opcion;

    // imprimir las opciones disponibles
    cout << "\n====== SELECCION DE GRAFOS ======\n";
    cout << "1. Grafo NO dirigido y ponderado\n";
    cout << "2. Grafo dirigido y ponderado\n";
    cout << "3. Ingresar grafo manualmente\n";
    cout << "Opcion: ";
    // leer la opcion del usuario
    cin >> opcion;

    // si la opcion es 1 o 2 cargar el grafo predefinido correspondiente
    if(opcion == 1 || opcion == 2)
        cargarGrafoPredefinido(opcion);
    // si la opcion es 3 permitir capturar el grafo manualmente
    else if(opcion == 3)
        capturarGrafo();
    // si la opcion no es valida informar al usuario
    else
        cout << "\nOpcion invalida.\n";
}

/********** MENÚ PRINCIPAL **********/
// funcion main que muestra el menu principal y controla el programa
int main() {
    // variable para la opcion principal
    int op;

    // bucle que repite el menu hasta que el usuario elija salir (op == 0)
    do {
        // imprimir el menu principal con opciones
        cout << "\n=========== MENU PRINCIPAL ===========\n";
        cout << "1. Seleccionar grafo\n";
        cout << "2. Ejecutar Kruskal\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        // leer la opcion elegida por el usuario
        cin >> op;

        // si el usuario elige 1 abrir el menu de grafos
        if(op == 1)
            menuGrafos();
        // si el usuario elige 2 ejecutar Kruskal sobre el grafo cargado
        else if(op == 2)
            ejecutarKruskal();

    // repetir mientras la opcion sea diferente de 0
    } while(op != 0);

    // retornar 0 para indicar que el programa finalizo correctamente
    return 0;
}
