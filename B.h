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
        for(int i = 0; i < 6; i++){
            children[i] = nullptr;
        }
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
        newroot->keynodes.insert({root->keys[2], root->keynodes[root->keys[2]]});
        newroot->size = 1;
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
        //insert key nodes into map
        newchild1->size = 2;
        newchild2->size = 2;
        newchild1->keys[0] = root->keys[0];
        newchild1->keys[1] = root->keys[1];
        newchild1->keynodes.insert({root->keys[0], root->keynodes[root->keys[0]]});
        newchild1->keynodes.insert({root->keys[1], root->keynodes[root->keys[1]]});
        newchild2->keys[0] = root->keys[3];
        newchild2->keys[1] = root->keys[4];
        newchild2->keynodes.insert({root->keys[3], root->keynodes[root->keys[3]]});
        newchild2->keynodes.insert({root->keys[4], root->keynodes[root->keys[4]]});
        newchild1->children[0] = child1;
        newchild1->children[1] = child2;
        newchild1->children[2] = child3;
        newchild2->children[0] = child4;
        newchild2->children[1] = child5;
        newchild2->children[2] = child6;
        
        if(newchild1->children[0]->ifLeaf){
            newchild1->ifLeaf = false;
            newchild2->ifLeaf = false;}
        newroot->children[0] = newchild1;
        newroot->children[1] = newchild2;
        newroot->ifLeaf = false;
        
        root = newroot;
        
        
    }
    //checks if root is leaf node and add keys
    if(root->ifLeaf){
        int ind = -1;
        //finds index where key needs to be inserted
        for(int i = 0; i < root->size; i++){
            if(root->keys[i] < key){
                ind = i+1;
            }
        }
        //if key needs to be inserted at end
        if(ind == root->size-1)
        {
            root->keys[ind] = key;
            Node* newnode = new Node;
            root->keynodes.insert({key, newnode});
            root->size = root->size+1;
        }
        else if(ind == -1){
            for(int i = root->size-1; i >= 0; i--){
                root->keys[i] = root->keys[i-1];
            }
            root->keys[0] = key;
            Node* newnode = new Node;
            root->keynodes.insert({key, newnode});
            root->size = root->size+1;
        }
        //if key needs to be inserted in middle or beginning
        else{
            for(int i = root->size-1; i >= ind+1; i--){
                root->keys[i] = root->keys[i-1];
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
        Node* curr = root;
        while(curr->children[0]->ifLeaf != true){
            //traverses tree to find where key belongs
            int ind = -1;
            for(int i = 0; i < curr->size; i++){
                if(curr->keys[i] < key){
                    ind = i;
                }
            }
            curr = curr->children[ind+1];
        }
        int ind = -1;
        for(int i = 0; i < curr->size; i++){
            if(curr->keys[i] < key){
                ind = i;
            }}
        //checks if a child doesn't exist there yet
        if(curr->children[ind+1] == nullptr){
            curr->children[ind+1] = new Node;
            curr->children[ind+1]->keys[0] = key;
            curr->children[ind+1]->size = 1;
            curr->children[ind+1]->keynodes.insert({key, curr->children[ind+1]});
        }
        else{
            //if child node isn't full
            if(curr->children[ind+1]->size != 5){
                ind = -1;
                for(int i = 0; i < curr->children[ind+1]->size; i++){
                    if(curr->children[ind+1]->keys[i] < key){
                        ind = i+1;
                    }
                }
                if(ind == curr->children[ind+1]->size-1){
                    Node* newnode = new Node;
                    curr->children[ind+1]->keys[ind] = key;
                    curr->children[ind+1]->size += 1;
                    curr->children[ind+1]->keynodes.insert({key, newnode});
                    //split this node since its full
                }
                else if(ind == -1){
                    for(int i = curr->children[ind+1]->size-1; i >= 0; i--){
                        curr->children[ind+1]->keys[i] = curr->children[ind+1]->keys[i-1];
                    }
                    curr->children[ind+1]->keys[0] = key;
                    curr->children[ind+1]->size += 1;
                    Node* newnode = new Node;
                    curr->children[ind+1]->keynodes.insert({key, newnode});
                }
                else{
                    for(int i = curr->children[ind+1]->size-1; i >= ind+1; i--){
                        curr->children[ind+1]->keys[i] = curr->children[ind+1]->keys[i-1];
                    }
                    curr->children[ind+1]->keys[ind] = key;
                    curr->children[ind+1]->size += 1;
                    Node* newnode = new Node;
                    curr->children[ind+1]->keynodes.insert({key, newnode});
                }
            }

            
        }
    }
}
