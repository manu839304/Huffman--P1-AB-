#include "huf.hh"
#include <stdlib.h>
#include <cstdio>     // Para printf
#include <iostream>
#include "arbol.hh"
#include "trees/include/st_tree.h"

using namespace st_tree;

unordered_map<char, int> contar_caracteres(ifstream &fichero) {
    unordered_map<char, int> map_freq;
    char char_leido;

    while (fichero.get(char_leido)) {
        
        // Si el mapa no contiene el caracter, asigna su valor de aparición en 1
        if (map_freq.find(char_leido) == map_freq.end()) {
            map_freq[char_leido] = 1;
        }
 
        // Sino, aumenta su frecuencia
        else {
            map_freq[char_leido]++;
        }
    }

    // MOSTRAR FRECUENCIAS NO ORDENADAS
    /*
    for (auto& it : frecuencia) {
        cout << it.first << ' '
             << it.second << '\n';
    }
    */

    return map_freq;
}


priority_queue<pair<char, int>, vector<pair<char, int> >, ComparePairs> crear_cola_prio(unordered_map<char, int> map_freq){
    // Declaramos cola de prioridades
    priority_queue<pair<char, int>, vector<pair<char, int>>, ComparePairs> pq_freq;

    for (auto& pareja : map_freq) {
        // Inlcuimos el valor del mapa a la cola de prioridades
        pq_freq.push(pareja);
    }
    
    //MOSTRAR COLA PRIORIDADES
    /*
    pair<char,int> p;

    for (int i = 0; i < map_freq.size(); i++){
        p = pq_freq.top();
        pq_freq.pop();

        printf("%c", p.first);
    }
    
    printf("\n");
    */
   return pq_freq;
}


void construir_arbol(unordered_map<char, int> map_freq){

    // Construimos la cola de prioridad de parejas de los caracteres y su frecuencia de aparición
    priority_queue<pair<char, int>, vector<pair<char, int>>, ComparePairs> pq_freq = crear_cola_prio(map_freq);
    
    // Declaramos las variables 
    tree<pair<char, int>> arboles[map_freq.size() - 1];
    typedef tree<pair<char, int>>::iterator iterator;
    typedef tree<pair<char, int>>::node_type node_type;
    //struct Node* nodo_x;
    //struct Node* nodo_y;
    //struct Node* nodo_z;
    pair<char,int> par_1, par_2, new_par;

    

    new_par.first = '-';

    for(int i = 0; i < map_freq.size() - 1; i++){

        par_1 = pq_freq.top();
        pq_freq.pop();

        par_2 = pq_freq.top();
        pq_freq.pop();

        new_par.second = par_1.second + par_2.second;
        
        arboles[i].insert(new_par);
        arboles[i].root().insert(par_1);
        arboles[i].root().insert(par_2);

        pq_freq.push(new_par);
        
        iterator F = arboles[i].begin();
        iterator L = arboles[i].end();
        cout << "ITERACION " << i+1 << " || Arbol z: ";
        for (iterator j(F);  j != L;  ++j) {
            cout << j->data().first << ":" << j->data().second << " ";
        }
        cout << " || Nodos: x-" << arboles[i].size() << ", y-" << arboles[i].size() << ", z-" << arboles[i].size();
        cout << "\n";
       
        //FALTA HACER QUE LOS NODOS NO DESAPAREZCAN
    }
}



void comprimir(ifstream &fichero){
    
    // Obtenemos la cola de prioridad de caracteres y su frecuencia de aparición
    unordered_map<char, int> frecuencia = contar_caracteres(fichero);
    construir_arbol(frecuencia);
    // construir arbol (y asignar codigos a caracteres)
    // escribir fichero (diccionario de codigos + el texto codificado)

    // input = archivo original
    // output = archivo .huf


}


void descomprimir(ifstream &fichero){
    // leer diccionario de codigos
    // escribir fichero descodificado

    // input = archivo .huf
    // output = archivo original


}

// extension archivo original
// string con el diccionario
// texto

int main(int argc, char *argv[]){


    if (argc != 3){
        cout << "NUMERO DE PARAMETROS INVALIDO";
    
    } else {
        string nombreFichero = argv[2];
        string flag = argv[1];
        ifstream fichero(nombreFichero); // Abre el fichero.

        if (!fichero) { 
            // Si ha habido un error al abrirlo, se informa al usuario y se cierra el programa.
            cerr << "No se ha podido abrir el fichero \"" << nombreFichero << "\"." << endl;
            exit(1);
        }

        if (flag == "-c") {
            comprimir(fichero);

        } else if (flag == "-d") {
            descomprimir(fichero);

        } else {
            cout << "FLAG INVALIDA";

        }
        fichero.close();
    }
}