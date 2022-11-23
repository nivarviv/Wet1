//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>
using namespace std;

struct node {
    struct node *left;
    int data;
    int height;
    struct node *right;
};

template<class T>
class AvlTree {

public:
    struct node * root;
    AvlTree(){
        this->root = NULL;
    }
    virtual ~AvlTree();
    virtual T* addToTree(T type);
    virtual void removeFromTree(T type);

    int calHeight(struct node *p);
    int bf(struct node *n);
    struct node * llRotation(struct node *n);
    struct node * rrRotation(struct node *n);
    struct node * rlRotation(struct node *n);
    struct node * lrRotation(struct node *n);

    struct node* insert(struct node *r,int data);

    void levelorder_newline();
    void levelorder_newline(struct node *v);

    struct node * deleteNode(struct node *p,int data);
    struct node* inpre(struct node* p);
    struct node* insuc(struct node* p);


#endif //WET1_AVLTREE_H
