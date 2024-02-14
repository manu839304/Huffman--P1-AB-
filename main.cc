#include "arbol.hh"

int main()
{
    pair<string, int> par, par2, par3;
    par.first = 1;
    par.second = 'a';
    par2.first = 2;
    par2.second = 'b';    
    par3.first = 3;
    par3.second = 'c';
    
    struct Node* root = new Node(par);
    root->left = new Node(par2);//inserting 2 to the left of root
    root->right = new Node(par3);//Inserting 3 to the right of root
    Printtree(root, 0);
}