#include "huf.hh"
#include <stdlib.h>
#include <cstdio>     // Para printf
#include <iostream>
#include <string>
#include "arbol.hh"

using namespace std;

unordered_map<string, int> contar_caracteres(string fich) {

    ifstream fichero;
    fichero.open(fich);

    unordered_map<string, int> map_freq;
    char char_leido;
    string string_leido;

    if(fichero.is_open()){
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
        for (auto& it : map_freq) {
            cout << it.first << ' '
                << it.second << '\n';
        }
        */
        

        fichero.close();
    }
    else{
        printf("ERROR: No se ha podido abrir el fichero con nombre: \"%s\" para su lectura", fich);
    }
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


void construir_arbol(unordered_map<string, int> map_freq, Node* nodos[]){

    // Construimos la cola de prioridad de parejas de los caracteres y su frecuencia de aparición
    priority_queue<pair<string, int>, vector<pair<string, int>>, ComparePairs> pq_freq = crear_cola_prio(map_freq);
    int nodo_actual = 0, indice = 0;

    for (auto& pareja : map_freq) {
        nodos[nodo_actual] = new Node(pareja);
        cout << "Se ha anadido: " << nodos[nodo_actual]->data.first << "," << nodos[nodo_actual]->data.second << " con indice: " << nodo_actual << endl; // para depurar
        nodo_actual++;
    }

    pair<string,int> par_1, par_2, new_par;

    for(int i = 0; i < map_freq.size() - 1; i++){

        if (!pq_freq.empty()){
            par_1 = pq_freq.top();
            pq_freq.pop();
            cout << "Se ha sacado: " << par_1.first << "," << par_1.second << " de la cola prio" << endl; // para depurar


            par_2 = pq_freq.top();
            pq_freq.pop();
            cout << "Se ha sacado: " << par_2.first << "," << par_2.second << " de la cola prio" << endl; // para depurar
            
            new_par.first = par_1.first + "+" + par_2.first;
        }

        new_par.second = par_1.second + par_2.second;

        nodos[nodo_actual] = new Node(new_par);
        cout << "Se ha anadido: " << nodos[nodo_actual]->data.first << "," << nodos[nodo_actual]->data.second << " con indice: " << nodo_actual << endl; // para depurar
        construir_nuevo_nodo(par_1, par_2, nodos, nodo_actual);
        
        cout << "---- Nodo actual: " << nodo_actual << " ----\n";
        print_arbol(nodos[nodo_actual], i+1);
        cout << "\n";
    
        nodo_actual++;

        pq_freq.push(new_par);
    }
}
/*
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
*/

/*
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
*/

void asignar_codigos_subarbol(Node* arbol, string codigo, unordered_map<string, string>& codigos){
    if(arbol->data.first.size() == 1){ // es un nodo hoja = nodo con caracter que introducir en el diccionario
        codigos[arbol->data.first] = codigo;

    } else {
        if(arbol->left != NULL) {
            asignar_codigos_subarbol(arbol->left, codigo + "0", codigos);
        }

        if(arbol->right != NULL) {
            asignar_codigos_subarbol(arbol->right, codigo + "1", codigos);
        }
    }
}


void asignar_codigos(Node* arbol, int num_caracteres, unordered_map<string, string>& codigos){
    if(arbol->left != NULL) {
        asignar_codigos_subarbol(arbol->left, "0", codigos);
    }

    if(arbol->right != NULL) {
        asignar_codigos_subarbol(arbol->right, "1", codigos);
    }
}


void escribirFicheroHuffman(string fichero, unordered_map<string, string>& codigos){
    ifstream f_in;
    ofstream f_out;
    f_in.open(fichero);
    if(!f_in.is_open()){
        printf("ERROR: No se ha podido abrir el fichero con nombre: \"%s\" para su lectura", fichero);
    }
    else{

        // Para cambiar la extensión de fichero si es que tiene alguna.
        cout << fichero << endl;
        string delimiter = ".";
        string token = fichero.substr(0, fichero.find_last_of(delimiter));
        string fichero_out = token + ".huf";
        // FALTA EL CASO DE QUE NO TENGA EXTENSIÓN ... ------------------------------------------------------------------------------

        f_out.open(fichero_out);
        if(!f_out.is_open()){
            printf("ERROR: No se ha podido abrir el fichero con nombre: \"%s\" para su escritura", fichero_out);
        }
        else{
            char char_leido;
            string string_leido;

            while (f_in.get(char_leido)) {
            string_leido = char_leido;
            f_out << codigos[string_leido]; // Escribimos en el fichero a crear el caracter en su codificación correspondiente
        }
            f_out.close();
        }
        f_in.close();
    }
}



void comprimir(string fichero){

    // Obtenemos la cola de prioridad de caracteres y su frecuencia de aparición
    unordered_map<string, int> frecuencia = contar_caracteres(fichero);
    int num_caracteres = frecuencia.size();
    int num_arboles = (num_caracteres * 2)-1;

    // Creamos el árbol
    Node* nodos[num_arboles];
    construir_arbol(frecuencia, nodos);

    Node* arbol = nodos[num_arboles-1]; // le pasamos el ultimo nodo raiz, que corresponde al arbol 'final' (ultima iteracion)
    //asignar_ceros_y_unos(arbol);

    
    unordered_map<string, string> codigos; // Contiene codificado los prefijos binarios para cada caracter
    asignar_codigos(arbol, num_caracteres, codigos);

    // PARA IMPRIMIR EL DICCIONARIO
    for (auto& it : codigos) {
        cout << it.first << ' '
             << it.second << '\n';
    }
    

    // escribir fichero (diccionario de codigos + el texto codificado)
    //escribirFicheroHuffman(fichero, codigos);
}


void descomprimir(string fichero){
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

        if (flag == "-c") {
            comprimir(nombreFichero);

        } else if (flag == "-d") {
            descomprimir(nombreFichero);

        } else {
            cout << "FLAG INVALIDA";

        }
    }
}