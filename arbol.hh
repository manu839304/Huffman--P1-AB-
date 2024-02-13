#include <iostream>
#include <functional>

using namespace std;

//A structure to create node

struct Node {

    pair<char,int> data;
    struct Node* left;
    struct Node* right;

    // A constructor to the struct node
    // that inserts value in the data variable.

    Node(pair<char,int> value)
    {
        data = value;
        left = NULL;//Left child is initialized to NULL
        right = NULL;//Right child is initialized to NULL
    }
};

//A function to print the tree

void Printtree(struct Node *root, int tab)
{

    //Check if tree is empty
    if(root == NULL)
    return;
    /*
    //We will use inorder traversal to print the tree

    Printtree(root -> left);
    cout << root -> data.first << ": " << root -> data.second << " ";
    Printtree(root -> right);
    */
    for(int i = 0; i < tab; i++){
        cout << "\t";
    }

    cout << "Raiz: " << root -> data.first << "," << root -> data.second << "\n";
    for(int i = 0; i < tab; i++){
        cout << "\t";
    }

    cout << "Izquierda: ";
    if(root->left != NULL){
        cout << "\n";
        Printtree(root -> left, tab+1);
    } else {
        cout << "NULL";
    }
    
    cout << "\n";
    for(int i = 0; i < tab; i++){
        cout << "\t";
    }

    cout << "Derecha: ";
    if(root->right != NULL){
        cout << "\n";
        Printtree(root -> right, tab+1);
    } else {
        cout << "NULL";
    }
}