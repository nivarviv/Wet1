//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>

template<class T, class K>
class AvlTree {

private:

    struct node {
        T data;
        K key;
        struct node *right;
        struct node *left;
    };

    node* root;
    void deleteTree(node* r);


public:
    AvlTree(){
        this->root = NULL;
    }
    ~AvlTree();
    node* insert(node* r, T value, K key);
    int height(node* r);
    int bf(node* r);
    node* balance(node* r);
    node* findMin(node* t);
    node* llRotation( node *parent);
    node* rrRotation( node *parent);
    node* rlRotation( node *parent);
    node* lrRotation( node *parent);
    node* remove(node* node, K key);


    T& find( node *p,T data); //or node*

#endif //WET1_AVLTREE_H
