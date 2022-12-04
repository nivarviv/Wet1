//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>
#include "team.h"
#include "player.h"
#include "playerStats.h"
#include "playerStatsDifferentOrder.h"

template<class T, class K>
struct node {
    T data;
    K key;
    node *right;
    node *left;
    node(T value, K key):data(value), key(key), right(NULL), left(NULL) {}
    ~node(){
        delete left;
        delete right;
    }
};

template<class T, class K>
class AvlTree {
private:
    node *m_root;

public:
    AvlTree();
    ~AvlTree();
    void insert(node<T,K>* node,T value, K key);
    int height(node *r);
    int bf(node *r);
    node *balance(node *r);
    node *findMin(node *t);
    node *llRotation(node *parent);
    node *rrRotation(node *parent);
    node *rlRotation(node *parent);
    node *lrRotation(node *parent);
    void remove(node<T,K>* node, K key);
    T *find_by_key(node<T,K>* node,K key);
    void deleteTree(node *r);
    void makeNearlyEmpty(node<T,K>* node, int *toDelete);
    node<T,K>* createEmptyTree(node<T,K> *node,int height);
    void setRoot(node<T,K>* root);
    node<T,K>* getRoot();
    //change to player and playerStats only?
    T* findSuc(node<T,K>* node,K stats);
    T* findPre(node<T,K>* node,K stats);
  //  player* findSuc(node<T,K>* node, playerStats key);
    void storeInOrderRecursive(node<T, K> *pNode, node<T, K> **pNode1);
    void arrayToBST(node<T, K> *pNode, node<T, K> *pNode1[]);
}
/////////////////////////////////////////////////////implementation//////////////////////////////////////////////////

template<class T, class K>
AvlTree<T,K>::AvlTree() : m_root(NULL) {}

template<class T, class K>
AvlTree<T,K>::~AvlTree() {
        deleteTree(this->m_root);
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
void AvlTree<T,K>::insert(node<T,K>* node,T value, K key) {
        if (node==NULL)
        {
            node=new node(value, key);
        }
        else if (key < node->key) {
            insert(node->left,value, key);
            node = balance(node);
        }
        else if (key < node->key) {
            insert(node->right,value, key);
            node = balance(node);
        }
        else if (<K>key==node->key) {
            return;
        }
    return;
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
void AvlTree<T,K>::remove(node<T,K>* node,K key) {
    node * temp;
        // Element not found
        if (node == NULL)
            return;
            // Searching for element
        else if (key < node->key)
            remove(node->left, key);
        else if (key > node->key)
            remove(node->right, key);
        // Element found
        // With 2 children
        if (node->left && node->right) {
            temp = findMin(node->right);
            node->data = temp->data;
            node->key = temp->key;
            remove(node->right, node->key);
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
        if (node == NULL)
            return;
        balance(node);
        return;
    }

template<class T, class K>
T *AvlTree<T,K>::find_by_key(node<T,K>* node,K key) {
        if (key < node->key)
            find_by_key(node->left,key);
        else if (key > node->key)
            find_by_key(node->right,key);
        else
            return NULL;

        if (key == node->key) {
            T* tPtr= &(node->data);
            return tPtr;
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
void AvlTree<T, K>::arrayToBST(node<T,K>* pNode, node<T,K> *pNode1[]) {
    if(pNode=NULL)
        return;
    arrayToBST(pNode->left,pNode1);
    pNode->data=**pNode1->data;
    pNode->key=**pNode1->key;
    *pNode1++;
    arrayToBST(pNode->right,pNode1);
}

template<class T, class K>
void AvlTree<T, K>::makeNearlyEmpty(node<T,K> *node, int *toDelete) {
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

/*template<class T, class K>
AvlTree<T, K> AvlTree<T, K>::createEmptyTree(int height) {
    AvlTree<T,K> tree = AvlTree<T,K>;
    node* node=m_root;
    if(height<=0)
        return tree;
    node=NULL;
    node->left = createEmptyTree(height_needed-1);
    node->right = createEmptyTree(height_needed-1);
    return tree;;
}*/


template<class T, class K>
node<T,K>* AvlTree<T, K>::createEmptyTree(node<T,K> *node,int height) {
    if(height<=0)
        return node;
    node=new node(T(), K());
    createEmptyTree(node->left,height-1);
    createEmptyTree(node->right,height-1);
    return node;
}

template<class T, class K>
void AvlTree<T, K>::setRoot(node<T,K> *root) {
m_root=node;
}

template<class T, class K>
node<T,K>* *AvlTree<T, K>::getRoot() {
    return m_root;
}

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursive(node *pNode, node **pNode1) {
    if(pNode == NULL)
        return;
    storeInOrderRecursive(pNode->left,pNode1);
    (*arr1)++ = node;
    storeInOrderRecursive(pNode->right,pNode1);
    return;
}

template<class T, class K>
T *AvlTree<T, K>::findPre(node<T, K> *node, K stats) {
    // Base case
    if (node == NULL) return NULL;
    // If key is present at root
    if (node->key == <K>stats) {
        // the maximum value in left subtree is predecessor
        if (node->left != NULL) {
            node * tmp = node->left;
            while (tmp->right)
                tmp = tmp->right;
            return tmp->data;
        } else
            return NULL;
    }
    // If key is smaller than root's key, go to left subtree
    if (root->key > stats)
    {
        findPre(node->left,stats);
    }
    else // go to right subtree
    {
        findPre(node->right,stats);
    }
}


    template<class T, class K>
    T * AvlTree<T, K>::findSuc(node < T, K > *node, K stats){
        // Base case
        if (node == NULL) return NULL;
        // If key is present at root
        if (node->key == <K>stats) {
            // the minimum value in right subtree is successor
            if (node->right != NULL) {
                node * tmp = node->right;
                while (tmp->left)
                    tmp = tmp->left;
                return tmp->data;
            } else
                return NULL;
        }
            // If key is smaller than root's key, go to left subtree
            if (root->key > stats)
            {
                findSuc(node->left,stats);
            }
            else // go to right subtree
            {
                findSuc(node->right,stats);
            }
    }

template<class T, class K>
bool AvlTree<T, K>::compareStats(node<T, K> *node, playerStats key) {
    if(key==node->key){
        return true;
    }
    return false;
}

template<class T, class K>
bool AvlTree<T, K>::compareId(node<T, K> *node, int key) {
    if(key==node->key){
        return true;
    }
    return false;
}


/*

template<class T, class K>
player *AvlTree<T, K>::findSuc(node *node, playerStats key) {
// Base case
    if (node == NULL)  return NULL;
    // If key is present at root
    if (node->key == key) {
        // the minimum value in right subtree is successor
        if (node->right != NULL) {
            node * tmp = node->right;
            while (tmp->left)
                tmp = tmp->left;
            return tmp->data;
        } else
            return NULL;
    }
    // If key is smaller than root's key, go to left subtree
    if (root->key > key)
    {
        findSuc(node->left,key);
    }
    else // go to right subtree
    {
        findSuc(node->right,key);
    }
}

*/





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
