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




    node * llRotation(struct node *n);
    node * rrRotation(struct node *n);
    node * rlRotation(struct node *n);
    node * lrRotation(struct node *n);

    void delete(struct node *p,T data);
    T& find(struct node *p,T data); //or node*

#endif //WET1_AVLTREE_H
