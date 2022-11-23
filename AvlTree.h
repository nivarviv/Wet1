//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

template<class T>
class AvlTree {
public:
    AvlTree();
    virtual ~AvlTree();
    virtual T* addToTree(T type);
    virtual void removeFromTree(T type);


};


#endif //WET1_AVLTREE_H
