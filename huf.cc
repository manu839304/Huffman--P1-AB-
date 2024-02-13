#include "huf.hh"
#include <stdlib.h>
#include <cstdio>     // Para printf
#include <iostream>
#include "arbol.hh"

using namespace std;

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

int encontrar_indice_nodo(pair<char, int> pareja, Node* nodos[], int ultimo_nodo){
    for(int i = 0; i < ultimo_nodo; i++){
        if( nodos[i]->data.first == pareja.first && nodos[i]->data.second == pareja.second){
            return i;
        }
    }
    return -1;
}

void construir_nuevo_nodo(pair<char, int> par_izq, pair<char, int> par_dch, Node* nodos[], int indice_raiz){
    // Buscamos e insertamos hijo izquierdo
    int indice_hijo = encontrar_indice_nodo(par_izq, nodos, indice_raiz);
    if(indice_hijo < 0){
        cout << "ERROR: Nodo <" << par_izq.first << "," << par_izq.second << "> no encontrado.";
    } else {
        nodos[indice_raiz]->left = nodos[indice_hijo];
        //cout << "Hijo izquierdo de " << nodos[indice_raiz]->data.first << "," << par_izq.second << "> no encontrado."
    }

    // Buscamos e insertamos hijo derecho
    indice_hijo = encontrar_indice_nodo(par_dch, nodos, indice_raiz);
    if(indice_hijo < 0){
        cout << "ERROR: Nodo <" << par_dch.first << "," << par_dch.second << "> no encontrado.";
    } else {
        nodos[indice_raiz]->right = nodos[indice_hijo];
    }
}

void print_arbol(Node* nodo, int num_it){
    cout << "--- ITERACION " << num_it << " ---\n";
    Printtree(nodo, 0);
}


Node* construir_arbol(unordered_map<char, int> map_freq, Node* nodos[]){

    // Construimos la cola de prioridad de parejas de los caracteres y su frecuencia de aparición
    priority_queue<pair<char, int>, vector<pair<char, int>>, ComparePairs> pq_freq = crear_cola_prio(map_freq);
    int nodo_actual = 0, indice = 0;

    for (auto& pareja : map_freq) {
        // Incluimos el valor del mapa a la cola de prioridades
        nodos[nodo_actual] = new Node(pareja);
        nodo_actual++;
    }

    pair<char,int> par_1, par_2, new_par;

    new_par.first = '-';

    for(int i = 0; i < map_freq.size() - 1; i++){

        par_1 = pq_freq.top();
        pq_freq.pop();

        par_2 = pq_freq.top();
        pq_freq.pop();

        new_par.second = par_1.second + par_2.second;

        nodos[nodo_actual] = new Node(new_par);
        construir_nuevo_nodo(par_1, par_2, nodos, nodo_actual);
        /*
        cout << "---- Nodo actual: " << nodo_actual << " ----\n";
        print_arbol(nodos[nodo_actual], i+1);
        cout << "\n";
        */

        nodo_actual++;

        pq_freq.push(new_par);
    }
}

void asignar_codigos(Node* arbol){
    if(arbol->left != NULL){
        arbol->left->data.second = 0;
        asignar_codigos(arbol->left);
    }

    if(arbol->right != NULL){
        arbol->right->data.second = 1;
        asignar_codigos(arbol->right);
    }

}


void comprimir(ifstream &fichero){
    
    // Obtenemos la cola de prioridad de caracteres y su frecuencia de aparición
    unordered_map<char, int> frecuencia = contar_caracteres(fichero);
    int num_arboles = (frecuencia.size() * 2)-1;
    Node* nodos[num_arboles];
    construir_arbol(frecuencia, nodos);
    Node* arbol = nodos[num_arboles-1];
    asignar_codigos(arbol);
    Printtree(arbol, 0);
    // asignar codigos a caracteres
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