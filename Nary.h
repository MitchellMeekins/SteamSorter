#pragma once
#include <iostream>
#include <map>
#include <vector>
using namespace std;


struct Node {
    Node* children[6];
    double key;
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
    Node* search(Node* root, double key);
    Node* searchDev(Node* root, string dev);
    Node* searchPrice(Node* root, double price);
    vector<Node*> devs;
    vector<Node*> price;
};

void NaryTree::insert(double key) {
    if (root == nullptr) {
        root = new Node;
        root->key = key;
        root->size = 1;
        root->keynodes.insert({key, root});
        root->ifLeaf = true;
        return;
    }

    Node* currentNode = root;
    while (!currentNode->ifLeaf) {
        int index = 0;
        // Finds the child index to traverse
        while (index < currentNode->size && currentNode->key < key) {
            index++;
        }
        currentNode = currentNode->children[index];
    }

    int index = 0;
    // Finds the index to insert the key
    while (index < currentNode->size && currentNode->key < key) {
        index++;
    }

    for (int i = currentNode->size; i > index; i--) {
        currentNode->key = currentNode->key;
    }
    currentNode->key = key;
    currentNode->size++;

    Node* newChild = new Node;
    currentNode->keynodes.insert({key, newChild});

}

Node* NaryTree::search(Node* root, double key)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    int total = sizeof(root->children)/sizeof(int);

    // All the children except the last 
    for (int i = 0; i < total - 1; i++)
    {
        search(root->children[i], key);
    }

    // Print the current node's data 
    if (root->key == key)
    {
        return root;
    }
    search(root->children[total - 1], key);

    return nullptr;//
}

Node* NaryTree::searchDev(Node* root, string dev)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    int total = sizeof(root->children)/sizeof(int);

    // All the children except the last 
    for (int i = 0; i < total - 1; i++)
    {
        searchDev(root->children[i], dev);
    }

    // Print the current node's data 
    if (root->dev == dev)
    {
       devs.push_back(root);
    }
    searchDev(root->children[total - 1], dev);

    return nullptr;//
}

Node* NaryTree::searchPrice(Node* root, double price)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    int total = sizeof(root->children)/sizeof(int);

    // All the children except the last 
    for (int i = 0; i < total - 1; i++)
    {
        searchPrice(root->children[i], price);
    }

    // Print the current node's data 
    if (root->price == price)
    {
       devs.push_back(root);
    }
    searchPrice(root->children[total - 1], price);

    return nullptr;//
}


