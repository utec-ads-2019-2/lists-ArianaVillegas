#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killSelf(Node<T>* node) {
        if(this->next!=node)
            this->next->killSelf(node);
        delete this;
    }

    void reverseF(Node<T>* node){
        if(this->next->next!=node)
            this->next->reverseF(node);
        this->next->next=this;
    }

    void reverseL(Node<T>* node){
        if(this->next!=node){
            this->next->reverseL(node);
        }
        swap(this->prev,this->next);
    }


};

#endif