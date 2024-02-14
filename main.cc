#include "arbol.hh"

int main()
{
    pair<string, int> par, par2, par3;
    par.first = "a";
    par.second = 1;
    par2.first = "b";
    par2.second = 2;    
    par3.first = "c";
    par3.second = 3;
    
    struct Node* root = new Node(par);
    root->left = new Node(par2);//inserting 2 to the left of root
    root->right = new Node(par3);//Inserting 3 to the right of root
    Printtree(root, 0);
}