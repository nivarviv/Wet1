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
    int height;
    node *right;
    node *left;
    node(T value, K key):data(value), key(key), height(1), right(NULL), left(NULL) {}
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
    node<T,K> * minValueNode(node<T,K>* node)
    node<T,K> * removeHelper(node<T,K>* node, K key);

    T *find_by_key(node<T,K>* node,K key);
    void deleteTree(node *r);
    void makeNearlyEmpty(node<T,K>* node, int *toDelete);
    node<T,K>* createEmptyTree(node<T,K> *node,int height);
    void setRoot(node<T,K>* root);
    node<T,K>* getRoot();
    void storeInOrderRecursive(node<T, K> *pNode, node<T, K> **pNode1);
    void storeInOrderRecursiveKey(node<T, K> *pNode, int const *pNode1);
    void storeInOrderRecursiveByTerms(int min, int max,node<T, K> *pNode, node<T, K> **pNode1);
    void storeInOrderRecursiveByTermsHelper(int min, int max,node<T, K> *pNode, node<T, K> **pNode1);
    void arrayToBST(node<T, K> *pNode, node<T, K> *pNode1[]);
    void successorPredecessor(node < T, K > * root, K val, T* pre, T* suc);
    node<T,K>* findBiggerThan(node<T, K> *node, node<T, K> *closest, int min);
    node<T,K>* newNode(T data, K key);
    node<T,K> *rightRotate(node<T,K> *y);
    node<T,K> *leftRotate(node<T,K> *x);
    int getBalance(node<T,K> *N);
    node<T,K>* insert(node<T,K>* node, T data, K key);

    /*  int height(node *r);
int bf(node *r);
node *balance(node *r);*/
    /*  node *llRotation(node *parent);
      node *rrRotation(node *parent);
      node *rlRotation(node *parent);
      node *lrRotation(node *parent);*/
    /*   T* findSuc(node<T,K>* node,K stats);
       T* findPre(node<T,K>* node,K stats);*/
    //  player* findSuc(node<T,K>* node, playerStats key);

    void remove(node<T, K> *node, K key);
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
        if (r == NULL)
            return 0;
        return r->height;
    }
*/

int max(int a, int b)
{
    return (a > b)? a : b;
}
/*

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
*/

/* Given a non-empty binary search tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
template<class T, class K>
node<T, K> *AvlTree<T, K>::minValueNode(node<T,K> *node) {
    node* current = node;

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
node<T,K> * AvlTree<T,K>::removeHelper(node<T,K>* node,K key) {

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
            Node *temp = root->left ?
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
            node* temp = minValueNode(root->right);

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
T *AvlTree<T,K>::find_by_key(node<T,K>* node,K key) {
    if(node==NULL){
        return NULL;
    }
    if (key == node->key) {
        return &node->data;
    }
    else{
        if (key < node->key)
            return find_by_key(node->left,key);
        else if (key > node->key)
            return find_by_key(node->right,key);
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
void AvlTree<T, K>::successorPredecessor(node<T, K> *root, K val, T *pre, T *suc) {
    // Base case
    if (root == NULL)  return ;
    if (root->key == <K>val) {
        // go to the right most element in the left subtree, it will the
        // predecessor.
        if (root->left != NULL) {
            node *t = root->left;
            while (t->right != NULL) {
                t = t->right;
            }
            pre = t->data;
        }
        if (root->right != NULL) {
            // go to the left most element in the right subtree, it will
            // the successor.
            node *t = root->right;
            while (t->left != NULL) {
                t = t->left;
            }
            suc = t->data;
        }
        return;
    }
    if (root->key > val) {
        // we make the root as successor because we might have a
        // situation when value matches with the root, it wont have
        // right subtree to find the successor, in that case we need
        // parent to be the successor
            suc = root->data;
            successorPredecessor(root->left,val,pre,suc);
        } else if (root->key < val) {
            // we make the root as predecessor because we might have a
            // situation when value matches with the root, it wont have
            // left subtree to find the predecessor, in that case we need
            // parent to be the predecessor.
            pre = root->data;
            successorPredecessor(root.right,val,pre,suc);
        }
    }

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursiveByTerms(int min, int max, node<T, K> *pNode, node<T, K> **pNode1) {
    node<T,K>* closest=NULL;
    node<T,K>* minNode=findBiggerThan(node,closest,min);
    storeInOrderRecursiveByTermsHelper(min,max,minNode,pNode1);
}

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursiveByTermsHelper(int min, int max, node<T, K> *pNode, node<T, K> **pNode1) {
    if(pNode == NULL || pNode->key>max || pNode->key<min)
        return;
    storeInOrderRecursiveByTermsHelper(pNode->left,pNode1);
    (*arr1)++ = node;
    storeInOrderRecursiveByTermsHelper(pNode->right,pNode1);
    return;
}

template<class T, class K>
node<T, K> *AvlTree<T, K>::findBiggerThan(node<T, K> *node, node<T, K> *closest, int min) {
    if(node==NULL){
        return closest;
    }
    if(node->key==min){
        return node;
    }
    else if(node->key<min){
        return(node->right,closest,min);
    }
    else if(node->key>min){
        closest=node;
        return(node->left,closest,min);
    }
}


/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
template<class T, class K>
node<T, K> *AvlTree<T, K>::newNode(T data, K key) {
    node* node = new node();
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
    // added at leaf
    return(node);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
template<class T, class K>
node<T, K> *AvlTree<T, K>::rightRotate(node<T, K> *y) {
    node *x = y->left;
    node *T2 = x->right;

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
    node *y = x->right;
    node *T2 = y->left;

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
void AvlTree<T, K>::remove(node<T, K> *node, K key) {
    this->m_root=removeHelper(node,key);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
template<class T, class K>
node<T, K> *AvlTree<T, K>::insert(node<T,K> *node, T data, K key) {
/* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(data,key));

    if (key < node->key)
        node->left = insert(node->left, data,key);
    else if (key > node->key)
        node->right = insert(node->right,data, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

template<class T, class K>
void AvlTree<T, K>::storeInOrderRecursiveKey(node<T, K> *pNode, int const *pNode1) {
    if(pNode == NULL)
        return;
    storeInOrderRecursiveKey(pNode->left,pNode1);
    (*arr1)++ = node->key;
    storeInOrderRecursiveKey(pNode->right,pNode1);
    return;
}


/*
template<class T, class K>
T *AvlTree<T, K>::findPre(node<T, K> *node, K stats,node<T, K> *pre) {
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
*/


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








//todo: copy constructor in case we dont have already










#endif //WET1_AVLTREE_H
