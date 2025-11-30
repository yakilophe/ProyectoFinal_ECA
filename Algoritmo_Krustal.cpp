#include <iostream>
#include <algorithm>   // Necesario para sort()
using namespace std;

/***********************************************************
   Estructura para almacenar cada arista del grafo.
   Contiene: nodo u, nodo v y peso w.
***********************************************************/
struct Arista {
    int u;   // extremo 1
    int v;   // extremo 2
    int w;   // peso de la arista
};

/***********************************************************
   Arreglos globales:
   - aristas[] almacena TODAS las aristas ingresadas.
   - mst[] guardar unicamente las aristas elegidas por Kruskal.
   - padre[] y rangoUF[] son usados por Union-Find.
***********************************************************/
Arista aristas[300];
Arista mst[300];
int padre[300];
int rangoUF[300];

int N, E;   // N vertices, E aristas ingresadas por el usuario

/***********************************************************
   Inicializa la estructura Union-Find:
   Cada nodo empieza siendo su propio representante.
***********************************************************/
void hacerSet(int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        padre[i] = i;      // Un nodo es padre de si mismo
        rangoUF[i] = 0;    // Rango inicial = 0
    }
}

/***********************************************************
   Busca el representante del conjunto de un nodo.
   Si el nodo no es su propio padre, "sube" recursivamente.
   Tambien aplica compresion de caminos para acelerar.
***********************************************************/
int encontrarPadre(int x)
{
    if(padre[x] == x)      // Si es su propio representante
        return x;

    // Compresi�n de caminos: apuntamos directo al representante final
    padre[x] = encontrarPadre(padre[x]);

    return padre[x];
}

/***********************************************************
   Une dos conjuntos usando Union-Find con rangos:
   - El de menor rango se cuelga del mayor.
   - Si ambos tienen mismo rango, uno crece.
***********************************************************/
void unir(int a, int b)
{
    // Se encuentran los representantes reales
    a = encontrarPadre(a);
    b = encontrarPadre(b);

    if(a != b) // Solo une si son conjuntos distintos
    {
        if(rangoUF[a] < rangoUF[b])
            padre[a] = b;
        else if(rangoUF[b] < rangoUF[a])
            padre[b] = a;
        else
        {
            padre[b] = a;     // Se hace padre
            rangoUF[a]++;     // Se incrementa rango
        }
    }
}

/***********************************************************
   Comparador que permite ordenar aristas por peso ascendente.
***********************************************************/
bool compararAristas(const Arista &A, const Arista &B)
{
    return A.w < B.w;   // True si A pesa menos que B
}

/***********************************************************
   Implementacion del algoritmo de Kruskal:
   1. Ordena todas las aristas.
   2. Recorre en ese orden, eligiendo solo las que no formen ciclo.
   3. Para detectar ciclos usa Union-Find.
***********************************************************/
void ejecutarKruskal()
{
    // Ordenar las aristas segun su peso (menor primero)
    sort(aristas, aristas + E, compararAristas);

    // Se prepara Union-Find
    hacerSet(N);

    int contador = 0;   // Contara cuantas aristas lleva el MST
    int i;

    // Se recorren las aristas ordenadas
    for(i = 0; i < E; i++)
    {
        int u = aristas[i].u;
        int v = aristas[i].v;

        // Si los representantes son diferentes = NO hay ciclo
        if(encontrarPadre(u) != encontrarPadre(v))
        {
            // Guardamos esta arista en el MST
            mst[contador] = aristas[i];
            contador++;

            // Unimos los subconjuntos
            unir(u, v);
        }
    }

    // Mostrar el MST obtenido
    cout << "\n======= ARBOL DE EXPANSION MINIMA (MST) =======\n";

    int pesoTotal = 0;

    for(i = 0; i < contador; i++)
    {
        cout << mst[i].u << " -- " << mst[i].v
             << "  (peso = " << mst[i].w << ")\n";

        pesoTotal += mst[i].w;   // Suma de pesos del MST
    }

    cout << "\nPeso total del MST = " << pesoTotal << "\n";
}

/***********************************************************
   Captura el grafo desde teclado:
   - Pide cantidad de vertices y aristas.
   - Solicita cada arista con su peso.
   - El grafo siempre es NO dirigido.
***********************************************************/
void capturarGrafo()
{
    cout << "\nNumero de vertices: ";
    cin >> N;

    cout << "Numero de aristas: ";
    cin >> E;

    cout << "\nIngrese cada arista en el formato (u v peso):\n";

    int i;
    for(i = 0; i < E; i++)
    {
        cout << "Arista " << i << ": ";
        cin >> aristas[i].u >> aristas[i].v >> aristas[i].w;
    }

    cout << "\nSe cargo correctamente.\n";
}

/***********************************************************
   MENU PRINCIPAL:
   Permite capturar el grafo y ejecutar Kruskal.
***********************************************************/
int main()
{
    int opcion;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Capturar grafo\n";
        cout << "2. Ejecutar Kruskal\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1)
            capturarGrafo();
        else if(opcion == 2)
            ejecutarKruskal();

    } while(opcion != 0);

    return 0;
}

