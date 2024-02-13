#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <queue>

using namespace std;

// Necesitamos un comparador personalizado para que la cola prioritaria trabaje con el segundo valor
// del par, que será la frecuencia de aparición.
struct ComparePairs {
    bool operator()(const pair<char, int>& lhs, const pair<char, int>& rhs) {
        // Ordenar por el segundo elemento de cada par (int)
        // Si son iguales, se compara el primer elemento (char)
        return lhs.second > rhs.second || (lhs.second == rhs.second && lhs.first > rhs.first);
    }
};

void comprimir(ifstream &fichero);

unordered_map<char, int> contar_caracteres(ifstream &fichero);

priority_queue<pair<char, int>, vector<pair<char, int> >, ComparePairs> crear_cola_prio(unordered_map<char, int> map_freq);

void descomprimir(ifstream &fichero);
