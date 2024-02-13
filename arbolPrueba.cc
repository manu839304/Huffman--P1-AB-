//A c++ Program to implement a binary tree in data structures

#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

//A structure to create node

struct Node {

    pair<int,char> data;
    struct Node* left;
    struct Node* right;

    // A constructor to the struct node
    // that inserts value in the data variable.

    Node(pair<int,char> value)
    {
        data = value;
        left = NULL;//Left child is initialized to NULL
        right = NULL;//Right child is initialized to NULL
    }
};

//A function to print the tree

void Printtree(struct Node *root)
{

    //Check if tree is empty
    if(root == NULL)
    return;

    //We will use inorder traversal to print the tree

    Printtree(root -> left);
    cout << root -> data.first << ": " << root -> data.second << " ";
    Printtree(root -> right);
}

/*
int main()
{

// creating root

struct Node* root = new Node(1);

/* 

(1)

/ \

      NULL NULL



root->left = new Node(2);//inserting 2 to the left of root

root->right = new Node(3);//Inserting 3 to the right of root



                  (1)

    /     \

(2) (3)

/ \ / \

NULL NULL NULL NULL



root->left->left = new Node(4);//inserting 4 as left child of 2



      (1)

                  / \

(2) (3)

/ \ / \

(4) NULL NULL NULL

          

//function call to print the tree

Printtree(root);

return 0;

}
*/
