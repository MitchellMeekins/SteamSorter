#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct Node{
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
    
    Node(){
        /* add other constuctor information later */
        ifLeaf = true;
    }
    

};

class BTree{
private:
    Node* root;
public:
    void Insert(double key);
    void Split(Node* root);
};

void BTree::Insert(double key){
    //automatically split root if its full
    if(root->size == 5){
        Node* newroot = new Node;
        //makes new root key middle of child
        newroot->keys[0] = root->keys[2];
        newroot->keynodes.insert({root->keys[2], newroot});
        //did all this manually sorry (:/ I was too lazy to code actual logic, if u can think of smth better pls fix this lol
        //keys on left of middle key get added to first new child, and keys on right of middle key get add to second middle child. These new children get added to the new root nodes children array. the children of the root node get readded to the respective new children node children arrays. Also dont forget to fix the ifLeaf variables and to set root as new root
        Node* child1 = root->children[0];
        Node* child2 = root->children[1];
        Node* child3 = root->children[2];
        Node* child4 = root->children[3];
        Node* child5 = root->children[4];
        Node* child6 = root->children[5];
        Node* newchild1 = new Node;
        Node* newchild2 = new Node;
        newchild1->keys[0] = root->keys[0];
        newchild1->keys[1] = root->keys[1];
        newchild2->keys[0] = root->keys[3];
        newchild2->keys[1] = root->keys[4];
        newchild1->children[0] = child1;
        newchild1->children[1] = child2;
        newchild1->children[2] = child3;
        newchild2->children[0] = child4;
        newchild2->children[1] = child5;
        newchild2->children[2] = child6;
        
        newchild1->ifLeaf = false;
        newchild2->ifLeaf = false;
        newroot->children[0] = newchild1;
        newroot->children[1] = newchild2;
        newroot->ifLeaf = false;
        
        root = newroot;
        
        
    }
    //checks if root is leaf node and add keys
    if(root->ifLeaf){
        int ind = 0;
        //finds index where key needs to be inserted
        for(int i = 0; i < root->size; i++){
            if(root->keys[i] < key){
                ind = i;
            }
        }
        //if key needs to be inserted at end
        if(ind == root->size-1)
        {
            root->keys[ind+1] = key;
            Node* newnode = new Node;
            root->keynodes.insert({key, newnode});
            root->size = root->size+1;
        }
        //if key needs to be inserted in middle or beginning
        else{
            for(int i = root->size-1; i >= ind; i--){
                root->keys[i+1] = root->keys[i];
        }
            root->keys[ind] = key;
            Node* newnode = new Node;
            root->keynodes.insert({key, newnode});
            root->size = root->size+1;
        
        }
    }
    //if root has children
    else{
        //find where key belongs in key array, find corresponding child array [i+1]. ex. if key is lower than first element, it stays at 0 and if its higher than first element its 0+1, so it belongs at index 1 in child array.
        //split
    }
}
