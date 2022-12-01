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
struct node {
    T data;
    K key;
    node *right;
    node *left;
    node(T value, K key):data(value), key(key), right(NULL), left(NULL) {} //maybe add helper function for newNode
};

template<class T, class K>
class AvlTree {
private:

    node *m_root;


public:

    AvlTree();

    ~AvlTree();

    node *insert(T value, K key);

    int height(node *r);

    int bf(node *r);

    node *balance(node *r);

    node *findMin(node *t);

    node *llRotation(node *parent);

    node *rrRotation(node *parent);

    node *rlRotation(node *parent);

    node *lrRotation(node *parent);

    node *remove( K key);

    T *find_by_key(K key);

    void deleteTree(node *r);

    //AvlTree* sortedArrayToBST(node* A[], int start, int end);

    void storeInOrderRecursive(node<T,K> **arr1);
    void arrayToBST(node** arr);
    void makeNearlyEmpty(node* node, int *toDelete);
    AvlTree<T,K> createEmptyTree(int height);

}
/////////////////////////////////////////////////////implementation//////////////////////////////////////////////////

template<class T, class K>
AvlTree<T,K>::AvlTree() : m_root(NULL) {}

template<class T, class K>
AvlTree<T,K>::~AvlTree() {
        deleteTree(this->m_root);
    }

template<class T, class K>
void AvlTree<T,K>::storeInOrderRecursive(node<T,K> **arr1) {
    node* node= m_root;

    if(node == NULL)
        return;

    node=node->left
    storeInOrderRecursive(arr1);

    (*arr1)++ = node;

    node=node->right
    storeInOrderRecursive(arr1);

    return;
}
/*

template<class T, class K>
void AvlTree<T,K>::storeInOrderRecursive(T **arr1) {
    node* root= m_root;

    if(root == NULL)
        return;

    root=root->left
    storeInOrderRecursive(arr1);

    (*arr1)++ = root1.data;

    root=root->right
    storeInOrderRecursive(arr1);

    return;
}
*/


template<class T, class K>
node *AvlTree<T,K>::insert(T value, K key) {
        node* node = m_root;
        if (node==NULL)
        {
            node=new node(value, key);
        }
        else if (key < node->key) {
            node->left = insert(value, key);
            node = balance(node);
        } else if (key < node->key) {
            node->right = insert(value, key);
            node = balance(node);
        }
        else if(key==node->key)
        {
            return NULL
        }
        return node;
    }

template<class T, class K>
node *AvlTree<T,K>::balance(node *r) {
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

template<class T, class K>
int AvlTree<T,K>::height(node *r) {
        int height = 0;
        if (r != NULL) {
            int l_height = height(r->left);
            int r_height = height(r->right);
            int max_height = (l_height > r_height) ? l_height : r_height;
            height = max_height + 1;
        }
        return height;
    }

template<class T, class K>
int AvlTree<T,K>::bf(node *r) {
        int l_height = height(r->left);
        int r_height = height(r->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

template<class T, class K>
node *AvlTree<T,K>::llRotation(node *parent) {
        node *leftSon;
        leftSon = parent->left;
        parent->left = leftSon->right;
        leftSon->right = parent;
        return leftSon;
    }

template<class T, class K>
node *AvlTree<T,K>::rrRotation(node *parent) {
        node *rightSon;
        rightSon = parent->right;
        parent->right = rightSon->left;
        rightSon->left = parent;
        return rightSon;
    }

template<class T, class K>
node *AvlTree<T,K>::rlRotation(node *parent) {
        node *rightSon;
        rightSon = parent->right;
        parent->right = ll_rotat(rightSon);
        return rr_rotat(parent);
    }

template<class T, class K>
node *AvlTree<T,K>::lrRotation(node *parent) {
        node *leftSon;
        leftSon = parent->left;
        parent->left = rr_rotat(leftSon);
        return ll_rotat(parent);
    }

template<class T, class K>
node *AvlTree<T,K>::findMin(node *t) {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

template<class T, class K>
node *AvlTree<T,K>::remove(K key) {
    node * node;
    node * temp;
    node=this->m_root;
        // Element not found
        if (node == NULL)
            return NULL;

            // Searching for element
        else if (key < node->key)
            temp->left = remove(node->left, key);
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

template<class T, class K>
T *AvlTree<T,K>::find_by_key(K key) {
        node *node;
        node = m_root;

        if (key < node->key)
            node->left = find_by_key(key);
        else if (key > node->key)
            node->right = find_by_key(key);
        else
            return NULL;

        if (key == node->key) {
            return node->data;
        }
    }

template<class T, class K>
void AvlTree<T, K>::deleteTree(node *r) {
    if (r != NULL) {
        deleteTree(r->left);
        deleteTree(r->right);
        delete r;
    }
}

template<class T, class K>
void AvlTree<T, K>::arrayToBST(node **arr) {
    node= m_root;
    if(node=NULL)
        return;
    arrayToBST(node->left);
    node->data=*arr->data;
    node->key=*arr->key;
    arrayToBST(node->right);
}

template<class T, class K>
void AvlTree<T, K>::makeNearlyEmpty(node *node, int *toDelete) {

    node= m_root;
    if(node=NULL)
        return;
    if(*toDelete==0){
        return;
    }
    makeNearlyEmpty(node->right,toDelete);
    if(node->right==NULL && node->left==NULL){
        delete node;
    }
    *toDelete--;
    makeNearlyEmpty(node->left,toDelete);
}

template<class T, class K>
AvlTree<T, K> AvlTree<T, K>::createEmptyTree(int height) {
    AvlTree<T,K> tree = AvlTree<T,K>;
    node* node=m_root;
    if(height<=0)
        return tree;
    node=NULL;
    node->left = createEmptyTree(height_needed-1);
    node->right = createEmptyTree(height_needed-1);
    return tree;;
}

/*template<class T, class K>
AvlTree *AvlTree<T, K>::sortedArrayToBST(node* root, node **A, int start, int end) {
    // continue while this branch has values to process
    if(start > end)
        return NULL;
    AvlTree<T,K>* newTree = AvlTree<T,K>();
    // Get the middle element and make it root
    int mid = start + (end - start)/2;
    root = newTree.insert(*A[mid]->data, *A[mid]->key);
    // Recursively construct the left subtree
    // and make it left child of root
    sortedArrayToBST_helper(A, start, mid - 1);
    // Recursively construct the right subtree
    // and make it right child of root
    sortedArrayToBST_helper(A, mid + 1, end);
    return newTree;
}*/


#endif //WET1_AVLTREE_H
