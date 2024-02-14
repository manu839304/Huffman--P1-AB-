#include "huf.hh"
#include <stdlib.h>
#include <cstdio>     // Para printf
#include <iostream>
#include <string>
#include "arbol.hh"

using namespace std;

unordered_map<string, int> contar_caracteres(ifstream &fichero) {
    unordered_map<string, int> map_freq;
    char char_leido;
    string string_leido;

    while (fichero.get(char_leido)) {
        string_leido = char_leido;
        // Si el mapa no contiene el caracter, asigna su valor de aparición en 1
        if (map_freq.find(string_leido) == map_freq.end()) {
            map_freq[string_leido] = 1;
        }
 
        // Sino, aumenta su frecuencia
        else {
            map_freq[string_leido]++;
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


priority_queue<pair<string, int>, vector<pair<string, int> >, ComparePairs> crear_cola_prio(unordered_map<string, int> map_freq){
    // Declaramos cola de prioridades
    priority_queue<pair<string, int>, vector<pair<string, int>>, ComparePairs> pq_freq;

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

int encontrar_indice_nodo(pair<string, int> pareja, Node* nodos[], int ultimo_nodo){
    for(int i = 0; i < ultimo_nodo; i++){
        if(nodos[i]->data.first == pareja.first && nodos[i]->data.second == pareja.second){
            return i;
        }
    }
    return -1;
}

void construir_nuevo_nodo(pair<string, int> par_izq, pair<string, int> par_dch, Node* nodos[], int indice_raiz){
    // Buscamos e insertamos hijo izquierdo
    int indice_hijo = encontrar_indice_nodo(par_izq, nodos, indice_raiz);
    if(indice_hijo < 0){
        cout << "ERROR: Nodo <" << par_izq.first << "," << par_izq.second << "> no encontrado.\n";
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


Node* construir_arbol(unordered_map<string, int> map_freq, Node* nodos[]){

    // Construimos la cola de prioridad de parejas de los caracteres y su frecuencia de aparición
    priority_queue<pair<string, int>, vector<pair<string, int>>, ComparePairs> pq_freq = crear_cola_prio(map_freq);
    int nodo_actual = 0, indice = 0;

    for (auto& pareja : map_freq) {
        // Incluimos el valor del mapa a la cola de prioridades
        nodos[nodo_actual] = new Node(pareja);
        nodo_actual++;
    }

    pair<string,int> par_1, par_2, new_par;

    new_par.first = "NULL";

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

void asignar_ceros_y_unos(Node* arbol){
    if(arbol->left != NULL){
        arbol->left->data.second = 0;
        asignar_ceros_y_unos(arbol->left);
    }

    if(arbol->right != NULL){
        arbol->right->data.second = 1;
        asignar_ceros_y_unos(arbol->right);
    }

}

string recoger_codigo(Node* arbol, string* caracter){
    string codigo;
    int bit;
    cout << "Nodo: " << arbol->data.first << "," << arbol->data.second << "\n";
    

    if(arbol->data.first != "NULL"){
        *caracter = arbol->data.first;
        cout << "ANULADO " << *caracter << "\n";
        arbol = NULL;
        return codigo;

    } else if(arbol->left != NULL){
        codigo += arbol->left->data.second + '0';
        codigo += recoger_codigo(arbol->left, caracter);
        cout << "Codigo: " << codigo << "\n";
    } else if (arbol->right != NULL) {
        codigo += arbol->right->data.second + '0';
        codigo += recoger_codigo(arbol->right, caracter);
        cout << "Codigo: " << codigo << "\n";
    } else {
        arbol = NULL;
    }
}


void asignar_codigos(Node* arbol, int num_caracteres, unordered_map<string, string> codigos){
    string caracter, codigo;
    cout << "Num caracteres: " << num_caracteres << "\n";
    for(int i = 0; i < num_caracteres; i++){
        codigo = recoger_codigo(arbol, &caracter);
        cout << caracter << ":" << codigo << "\n";
    }
}



void comprimir(ifstream &fichero){
    
    // Obtenemos la cola de prioridad de caracteres y su frecuencia de aparición
    unordered_map<string, int> frecuencia = contar_caracteres(fichero);
    int num_caracteres = frecuencia.size();
    int num_arboles = (num_caracteres * 2)-1;

    Node* nodos[num_arboles];
    construir_arbol(frecuencia, nodos);

    Node* arbol = nodos[num_arboles-1]; // le pasamos el ultimo nodo raiz, que corresponde al arbol 'final' (ultima iteracion)
    asignar_ceros_y_unos(arbol);

    unordered_map<string, string> codigos;
    asignar_codigos(arbol, num_caracteres, codigos);
    // Printtree(arbol, 0);
    
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