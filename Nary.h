#pragma once
// change soemthnge
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Node {
    Node* children[6];
    double keys[5];
    map<double, Node*> keynodes;
    int size;
    bool ifLeaf;
    string URL;
    string name;
    string cat;
    string image;
    string dev;
    double price;
};

class NaryTree {
private:
    Node* root = nullptr;
public:
    void insert(double key);
};

void NaryTree::insert(double key) {
    if (root == nullptr) {
        root = new Node;
        root->keys[0] = key;
        root->size = 1;
        root->keynodes.insert({key, root});
        root->ifLeaf = true;
        return;
    }

    Node* currentNode = root;
    while (!currentNode->ifLeaf) {
        int index = 0;
        // Finds the child index to traverse
        while (index < currentNode->size && currentNode->keys[index] < key) {
            index++;
        }
        currentNode = currentNode->children[index];
    }

    int index = 0;
    // Finds the index to insert the key
    while (index < currentNode->size && currentNode->keys[index] < key) {
        index++;
    }

    for (int i = currentNode->size; i > index; i--) {
        currentNode->keys[i] = currentNode->keys[i - 1];
    }
    currentNode->keys[index] = key;
    currentNode->size++;

    Node* newChild = new Node;
    currentNode->keynodes.insert({key, newChild});

}
