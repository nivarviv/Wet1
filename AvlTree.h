//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>
#include "team.h"
#include "player.h"
#include "playerStats.h"

template<class T, class K>
class AvlTree {

private:

    struct node {
        T data;
        K key;
        node *right; //struct
        node *left; //struct
    };

    node *m_root;


public:
    AvlTree() {
        this->m_root = NULL;
    }

/*
    ~AvlTree();

    node *insert(node *r, T value, K key);

    int height(node *r);

    int bf(node *r);

    node *balance(node *r);

    node *findMin(node *t);

    node *llRotation(node *parent);

    node *rrRotation(node *parent);

    node *rlRotation(node *parent);

    node *lrRotation(node *parent);

    node *remove(node *node, K key);

    T *find_by_key(K key);

    //see if needed or remove node* from excisting implementation
todo:
    void remove_by_key(K key);

todo:
    void add(T value, K key);

    T &find(node *p, T data); //or node*

*/

/////////////////////////////////////////////////////implementation//////////////////////////////////////////////////

    void deleteTree(node *r) {
        if (r != NULL) {
            deleteTree(r->left);
            deleteTree(r->right);
            delete node;
        }
    }

    ~AvlTree() {
        deleteTree(this->root);
    }

// PERHAPS REMOVE NODE *R
    node *insert(node *r, T value, K key) {
        if (r == NULL) {
            r = new node;
            r->data = value;
            r->key = key;
            r->left = NULL;
            r->right = NULL;
        } else if (key < r->key) {
            r->left = insert(r->left, value, key);
            r = balance(r);
        } else if (key < r->key) {
            r->right = insert(r->right, value, key);
            r = balance(r);
        }
        return r;
    }

    node *balance(node *r) {
        if (bf(r) > 1) {
            if (bf(r->left) >= 0) {
                r = llRotation(r);
            } else {
                r = lrRotation(r);
            }
        } else if (bf(r) < -1) {
            if (bf(r->right) = 1) {
                r = rlRotation(r);
            } else {
                r = rrRotation(r);
            }
        }
        return r;
    }

    int height(node *r) {
        int height = 0;
        if (r != NULL) {
            int l_height = height(r->left);
            int r_height = height(r->right);
            int max_height = (l_height > r_height) ? l_height : r_height;
            height = max_height + 1;
        }
        return height;
    }

    int bf(node *r) {
        int l_height = height(r->left);
        int r_height = height(r->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    node *llRotation(node *parent) {
        node *leftSon;
        leftSon = parent->left;
        parent->left = leftSon->right;
        leftSon->right = parent;
        return leftSon;
    }

    node *rrRotation(node *parent) {
        node *rightSon;
        rightSon = parent->right;
        parent->right = rightSon->left;
        rightSon->left = parent;
        return rightSon;
    }

    node *rlRotation(node *parent) {
        node *rightSon;
        rightSon = parent->right;
        parent->right = ll_rotat(rightSon);
        return rr_rotat(parent);
    }

    node *lrRotation(node *parent) {
        node *leftSon;
        leftSon = parent->left;
        parent->left = rr_rotat(leftSon);
        return ll_rotat(parent);
    }

    node *findMin(node *t) {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node *remove(node *node, K key) {
        node * temp;
        // Element not found
        if (node == NULL)
            return NULL;

            // Searching for element
        else if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);

        // Element found
        // With 2 children
        if (node->left && node->right) {
            temp = findMin(node->right);
            node->data = temp->data;
            node->key = temp->key;
            node->right = remove(node->right, node->key);
        }

            // With one or zero child
        else {
            temp = node;
            if (node->left == NULL)
                node = node->right;
            else if (node->right == NULL)
                node = node->left;
            delete temp;
        }
        if (t == NULL)
            return t;
        balance(node);
        return node;
    }

    T *find_by_key(K key) {
        node *node;
        node = m_root;

        if (key < node->key)
            node->left = find_by_key(key);
        else if (key > node->key)
            node->right = find_by_key(key);
        else
            return NULL;

        if (key == node->key) {
            return node;
        }
    }
}
#endif //WET1_AVLTREE_H

