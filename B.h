#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    Node* children[6];
    double keys[5];
    int size;
    bool ifLeaf;
    string URL;
    string name;
    string cat;
    string image;
    string dev;
    double price;

    Node() {
        ifLeaf = true;
    }


};

class BTree {
private:
    Node* root;
public:
    void Insert(double key);
    void Split(Node* root);

};

void BTree::Insert(double key) {
    //automatically split root if its full
    if (root->size == 5) {
        Node* newroot = new Node;
        //makes new root key middle of child
        newroot->keys[0] = root->keys[2];
    }
    //checks if root is leaf node and add keys
    if (root->ifLeaf) {
        int ind = 0;
        for (int i = 0; i < root->size; i++) {
            if (root->keys[i] < key) {
                ind = i;
            }
        }
        //if key needs to be inserted at end
        if (ind == root->size - 1)
        {
            root->keys[ind + 1] = key;
            root->size = root->size + 1;
        }
        //if key needs to be inserted in middle or beginning
        else {
            for (int i = root->size - 1; i >= ind; i--) {
                root->keys[i + 1] = root->keys[i];
            }
            root->keys[ind] = key;


        }
    }
    //if root has children
    else {

    }

}