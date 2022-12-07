//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>
#include "node.h"
/*#include "team.h"
#include "player.h"
#include "playerStats.h"*/

template<class T, class K>
class AvlTree {
private:
    node<T,K> *m_root;

public:
    AvlTree();
    ~AvlTree();
    int height(node<T,K> *N);
    node<T,K> * minValueNode(node<T,K>* root);
    node<T,K> * removeHelper(node<T,K>* root, K key);
    T *find_by_key(node<T,K>* root,K key);
    void makeNearlyEmpty(node<T,K>* root, int *toDelete);
    node<T,K>* createEmptyTree(node<T,K> *root,int height);
    void setRoot(node<T,K>* root);
    node<T,K>* getRoot();
    void storeInOrderRecursive(node<T, K> *root, node<T, K> **pNode1);
    void storeInOrderRecursiveKey(node<T, K> *pNode, int *pNode1);
    void storeInOrderRecursiveByTerms(int min, int max,node<T, K> *pNode, T **pNode1);
    void storeInOrderRecursiveByTermsHelper(int min, int max,node<T, K> *pNode, T **pNode1);
    void arrayToBST(node<T, K> *pNode, node<T, K> *pNode1[]);
    void successorPredecessor(node < T, K > * root, K val, T* pre, T* suc);
    node<T,K>* newNode(T data, K key);
    node<T,K> *rightRotate(node<T,K> *y);
    node<T,K> *leftRotate(node<T,K> *x);
    int getBalance(node<T,K> *N);
    node<T,K>* insert(node<T,K>* root, T data, K key);
    void deleteTree(node<T,K> *r);
    void remove(node<T, K> *root, K key);
    T* getBiggest(node<T, K> *root);
    bool compareStats(node<T, K> *root, K key);
    bool compareId(node<T, K> *root, int key);
    node<T, K> *findBiggerThan(node<T, K> *root, node<T, K> *closest, int min);
};
/////////////////////////////////////////////////////implementation//////////////////////////////////////////////////
template<class T, class K>
AvlTree<T,K>::AvlTree() : m_root(NULL) {}

template<class T, class K>
AvlTree<T,K>::~AvlTree() {
        deleteTree(this->m_root);
    }

int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Given a non-empty binary search tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
template<class T, class K>
node<T, K> *AvlTree<T, K>::minValueNode(node<T,K> *root) {
    node<T,K>* current = root;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node
// with given key from subtree with
// given root. It returns root of the
// modified subtree.
template<class T, class K>
node<T,K> * AvlTree<T,K>::removeHelper(node<T,K>* root,K key) {

    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( key < root->key )
        root->left = removeHelper(root->left, key);

        // If the key to be deleted is greater
        // than the root's key, then it lies
        // in right subtree
    else if( key > root->key )
        root->right = removeHelper(root->right, key);

        // if key is same as root's key, then
        // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            node<T,K> *temp = root->left ?
                         root->left :
                         root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            node<T,K>* temp = minValueNode(root->right);

            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = removeHelper(root->right,
                                     temp->key);
        }
    }

    // If the tree had only one node
    // then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
    }

template<class T, class K>
T *AvlTree<T,K>::find_by_key(node<T,K>* root,K key) {
    if(root==NULL){
        return NULL;
    }
    if (key == root->key) {
        return &root->data;
    }
    else{
        if (key < root->key){
            return find_by_key(root->left,key);
        }
        else if (key > root->key){
            return find_by_key(root->right,key);
        }
        else {
            return NULL;
        }
    }
}

template<class T, class K>
void AvlTree<T, K>::deleteTree(node<T,K> *r) {
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
    pNode->data=*pNode1->data;
    pNode->key=*pNode1->key;
    *pNode1++;
    arrayToBST(pNode->right,pNode1);
}

template<class T, class K>
void AvlTree<T, K>::makeNearlyEmpty(node<T,K> *root, int *toDelete) {
    if(root==NULL)
        return;
    if(*toDelete==0){
        return;
    }
    makeNearlyEmpty(root->right,toDelete);
    if(root->right==NULL && root->left==NULL){
        delete root;
    }
    *toDelete--;
    makeNearlyEmpty(root->left,toDelete);
}

template<class T, class K>
node<T,K>* AvlTree<T, K>::createEmptyTree(node<T,K> *root,int height) {
    if(height<=0)
        return root;
    root=newNode(T(),K());
    createEmptyTree(root->left,height-1);
    createEmptyTree(root->right,height-1);
    return root;
}

template<class T, class K>
void AvlTree<T, K>::setRoot(node<T,K> *root) {
    m_root=root;
}

template<class T, class K>
node<T,K>* AvlTree<T, K>::getRoot() {
    return m_root;
}

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursive(node<T,K> *root, node<T,K> **pNode1) {
    if(root == NULL)
        return;
    storeInOrderRecursive(root->left,pNode1);
    (*pNode1)++ = root;
    storeInOrderRecursive(root->right,pNode1);
}

template<class T, class K>
void AvlTree<T, K>::successorPredecessor(node<T, K> *root, K val, T *pre, T *suc) {
    // Base case
    if (root == NULL)  return ;
    K rootKey=root->key;
    if (rootKey==val) {
        // go to the right most element in the left subtree, it will the
        // predecessor.
        if (root->left != NULL) {
            node<T,K> *t = root->left;
            while (t->right != NULL) {
                t = t->right;
            }
            pre = &t->data;
        }
        if (root->right != NULL) {
            // go to the left most element in the right subtree, it will
            // the successor.
            node<T,K> *t = root->right;
            while (t->left != NULL) {
                t = t->left;
            }
            suc = &t->data;
        }
        return;
    }
    if (root->key > val) {
        // we make the root as successor because we might have a
        // situation when value matches with the root, it wont have
        // right subtree to find the successor, in that case we need
        // parent to be the successor
            suc = &root->data;
            successorPredecessor(root->left,val,pre,suc);
        } else if (root->key < val) {
            // we make the root as predecessor because we might have a
            // situation when value matches with the root, it wont have
            // left subtree to find the predecessor, in that case we need
            // parent to be the predecessor.
            pre = &root->data;
            successorPredecessor(root->right,val,pre,suc);
        }
    }

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursiveByTerms(int min, int max, node<T, K> *pNode, T **pNode1) {
    node<T,K>* closest=NULL;
    node<T,K>* minNode=findBiggerThan(pNode,closest,min);
    storeInOrderRecursiveByTermsHelper(min,max,minNode,pNode1);
}

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursiveByTermsHelper(int min, int max, node<T, K> *pNode, T **pNode1) {
    if(pNode == NULL || pNode->key>max || pNode->key<min)
        return;
    storeInOrderRecursiveByTermsHelper(min,max,pNode->left,pNode1);
    (*pNode1)++ = pNode->data;
    storeInOrderRecursiveByTermsHelper(min,max,pNode->right,pNode1);
}

template<class T, class K>
node<T, K> *AvlTree<T, K>::findBiggerThan(node<T, K> *root, node<T, K> *closest, int min) {
    if(root==NULL){
        return closest;
    }
    if(root->key==min){
        return root;
    }
    else if(root->key<min){
        return(root->right,closest,min);
    }
    else if(root->key>min){
        closest=root;
        return(root->left,closest,min);
    }
}


/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
template<class T, class K>
node<T, K> *AvlTree<T, K>::newNode(T data, K key) {
    node<T,K>* newNode = new node<T, K>();
    newNode->key = key;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // new node is initially
    // added at leaf
    return(newNode);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
template<class T, class K>
node<T, K> *AvlTree<T, K>::rightRotate(node<T, K> *y) {
    node<T,K> *x = y->left;
    node<T,K> *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
template<class T, class K>
node<T, K> *AvlTree<T, K>::leftRotate(node<T, K> *x) {
    node<T,K> *y = x->right;
    node<T,K> *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
template<class T, class K>
int AvlTree<T, K>::getBalance(node<T, K> *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

template<class T, class K>
void AvlTree<T, K>::remove(node<T, K> *root, K key) {
    this->m_root=removeHelper(root,key);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
template<class T, class K>
node<T, K> *AvlTree<T, K>::insert(node<T,K> *root, T data, K key) {
/* 1. Perform the normal BST insertion */
    if (root == NULL)
        return(newNode(data,key));

    if (key < root->key)
        root->left = insert(root->left, data,key);
    else if (key > root->key)
        root->right = insert(root->right,data, key);
    else // Equal keys are not allowed in BST
        return root;

    /* 2. Update height of this ancestor node */
    root->height = 1 + max(height(root->left),
                           height(root->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(root);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    /* return the (unchanged) node pointer */
    return root;
}

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursiveKey(node<T, K> *pNode, int *pNode1) {
    if(pNode == NULL)
        return;
    storeInOrderRecursiveKey(pNode->left,pNode1);
    (*pNode1)++ = pNode->data.getId();
    storeInOrderRecursiveKey(pNode->right,pNode1);
}

template<class T, class K>
T *AvlTree<T, K>::getBiggest(node<T, K> *root) {
    if(root==NULL){
        return NULL;
    }
    return getBiggest(root->right);
}

template<class T, class K>
bool AvlTree<T, K>::compareStats(node<T, K> *root, K key) {
    if(key==root->key){
        return true;
    }
    return false;
}

template<class T, class K>
bool AvlTree<T, K>::compareId(node<T, K> *root, int key) {
    if(key==root->key){
        return true;
    }
    return false;
}

// A utility function to get height of the tree
template<class T, class K>
int AvlTree<T, K>::height(node<T, K> *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

#endif //WET1_AVLTREE_H
