//
// Created by 97254 on 21/11/2022.
//

#include "AvlTree.h"


void AvlTree::deleteTree(node* r){
    if(r != NULL){
        deleteTree(r->left);
        deleteTree(r->right);
        delete node;
    }
}

AvlTree::~AvlTree(){
    deleteTree(this->root);
}

node* AvlTree::insert(node *r, T value, K key){
        if (r == NULL)
        {
            r = new node;
            r->data = value;
            r->key=key;
            r->left = NULL;
            r->right = NULL;
        }
        else if (key<r->key)
        {
            r->left = insert(r->left, value, key);
            r = balance(r);
        }
        else if (key<r->key)
        {
            r->right = insert(r->right, value, key);
            r = balance(r);
        }
        return r;
    }

node* AvlTree::balance(node* r)
{
    if(bf(r)>1)
    {
        if(bf(r->left)>=0)
        {
            r= llRotation(r);
        }
        else
        {
            r= lrRotation(r);
        }
    }
    else if(bf(r)<-1)
    {
        if(bf(r->right)=1)
        {
            r = rlRotation(r);
        }
        else
        {
            r=rrRotation(r);
        }
    }
    return  r;
}

int AvlTree::height(node *r)
{
    int height=0;
    if(r!=NULL)
    {
        int l_height=height(r->left);
        int r_height=height(r->right);
        int max_height = (l_height>r_height) ? l_height : r_height;
        height = max_height + 1;
    }
    return height;
}

int AvlTree::bf(node *r)
{
    int l_height = height(r->left);
    int r_height = height(r->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

node* AvlTree::llRotation(node *parent)
{
    node* leftSon;
    leftSon = parent->left;
    parent->left = leftSon->right;
    leftSon->right = parent;
    return leftSon;
}

node* AvlTree::rrRotation(node *parent)
{
    node *rightSon;
    rightSon = parent->right;
    parent->right = rightSon->left;
    rightSon->left = parent;
    return rightSon;
}

node* AvlTree::rlRotation( node *parent)
{
    node *rightSon;
    rightSon = parent->right;
    parent->right = ll_rotat(rightSon);
    return rr_rotat(parent);
}

node* AvlTree::lrRotation( node *parent)
{
    node *leftSon;
    leftSon = parent->left;
    parent->left = rr_rotat(leftSon);
    return ll_rotat(parent);
}