#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killSelf(Node<T>* node) {
        if(next!=node)
            next->killSelf(node);
        delete this;
    }

    void reverseF(Node<T>* node){
        if(next->next!=node)
            next->reverseF(node);
        next->next=this;
    }

    void reverseL(Node<T>* node){
        if(next!=node){
            next->reverseL(node);
        }
        swap(prev,next);
    }


};

#endif
