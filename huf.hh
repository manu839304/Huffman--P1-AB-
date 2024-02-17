#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <queue>
#include "arbol.hh"

using namespace std;

// Necesitamos un comparador personalizado para que la cola prioritaria trabaje con el segundo valor
// del par, que será la frecuencia de aparición.
struct ComparePairs {
    bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) {
        // Ordenar por el segundo elemento de cada par (int)
        return lhs.second > rhs.second or ((lhs.second == rhs.second) and (lhs.first > lhs.first));
    }
};

unordered_map<string, int> contar_caracteres(string fich);

priority_queue<pair<string, int>, vector<pair<string, int> >, ComparePairs> crear_cola_prio(unordered_map<string, int> map_freq);

int encontrar_indice_nodo(pair<string, int> pareja, Node* nodos[], int ultimo_nodo);

void construir_nuevo_nodo(pair<string, int> par_izq, pair<string, int> par_dch, Node* nodos[], int indice_raiz);

void print_arbol(Node* nodo, int num_it);

void asignar_codigos_subarbol(Node* arbol, string codigo, unordered_map<string, string>& codigos);

void asignar_codigos(Node* arbol, int num_caracteres, unordered_map<string, string>& codigos);

void escribirFicheroHuffman(string fichero, unordered_map<string, string>& codigos);

void comprimir(string fichero);

void obtenerDiccionario(ifstream& fich_compr, unordered_map<string, string>& decod);

string obtenerNombreFichDecod(ifstream& fich_compr);

void escribirFicheroOriginal(ifstream& f_in, unordered_map<string, string>& decod, string nombreFichDecod);

void descomprimir(string fichero);



