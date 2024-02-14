#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <queue>

using namespace std;

// Necesitamos un comparador personalizado para que la cola prioritaria trabaje con el segundo valor
// del par, que será la frecuencia de aparición.
struct ComparePairs {
    bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) {
        // Ordenar por el segundo elemento de cada par (int)
        return lhs.second > rhs.second or ((lhs.second == rhs.second) and (lhs.first > lhs.first));
    }
};

void comprimir(ifstream &fichero);

unordered_map<string, int> contar_caracteres(ifstream &fichero);

priority_queue<pair<string, int>, vector<pair<string, int> >, ComparePairs> crear_cola_prio(unordered_map<string, int> map_freq);

void descomprimir(ifstream &fichero);
