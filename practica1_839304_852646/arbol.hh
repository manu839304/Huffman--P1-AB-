#include <iostream>
#include <functional>

using namespace std;

//A structure to create node
struct Node {

    pair<string,int> data;
    struct Node* left;
    struct Node* right;

    // A constructor to the struct node
    // that inserts value in the data variable.

    Node(pair<string,int> value)
    {
        data = value;
        left = NULL;//Left child is initialized to NULL
        right = NULL;//Right child is initialized to NULL
    }
};
