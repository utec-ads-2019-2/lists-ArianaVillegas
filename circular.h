#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

template <typename T>
class CircularLinkedList : public List<T> {
    public:
        CircularLinkedList() : List<T>() {}

        T front() {
            // Falta controlar el caso vacío
            return this->head->data;
        }

        T back() {
            // Falta controlar el caso vacío
            return this->tail->data;
        }

        void push_front(T value) {
            Node<T>* node=new Node<T>;
            node->data=value;
            // Sería mejor trabajar con head en vez de nodes
            if(this->nodes) {
                node->next = this->head;
                node->prev = this->tail;
                this->head->prev = node;
                this->head = node;
            }else {
                this->tail = node;
                this->head = node;
                this->head->prev = node;
            }
            this->tail->next = node;
            ++this->nodes;
        }

        void push_back(T value) {
            Node<T>* node=new Node<T>;
            node->data=value;
            if(this->nodes) {
                node->next = this->head;
                node->prev = this->tail;
                this->tail->next = node;
                this->tail = node;
            }else {
                this->tail = node;
                this->tail->next = node;
                this->head = node;
            }
            this->head->prev = node;
            ++this->nodes;
        }

        void pop_front() {
            if(this->nodes){
                Node<T>* node=this->head->next;
                delete this->head;
                this->head=nullptr;
                if(this->nodes==1){
                    this->tail=nullptr;
                }else{
                    node->prev=this->tail;
                    this->tail->next=node;
                    this->head=node;
                }
                --this->nodes;
            }
        }

        void pop_back() {
            if(this->nodes){
                Node<T>* node=this->tail->prev;
                delete this->tail;
                this->tail=nullptr;
                if(this->nodes==1){
                    this->head=nullptr;
                }else{
                    node->next=this->head;
                    this->head->prev=node;
                    this->tail=node;
                }
                --this->nodes;
            }
        }

        T operator[](int index) {
            // Algunos pasos de más
            int size=this->nodes;
            index=index%size;
            if(size>index){
                Node<T>* node;
                if(size/2>=index){
                    node=this->head;
                    for(int i=0; i<index; ++i){
                        node=node->next;
                    }
                } else {
                    node=this->tail;
                    for(int i=size-1; i>index; --i){
                        node=node->prev;
                    }
                }
                return node->data;
            }
        }

        bool empty() {
            return !this->nodes;
        }

        int size() {
            return this->nodes;
        }

        void clear() {
            this->head->killSelf(this->head);
            this->head=nullptr;
            this->tail=nullptr;
            this->nodes=0;
        }

        void sort() {
            int size=this->nodes;
            T arr[size];
            Node<T>* node=this->head;
            for(int i=0; i<size; ++i){
                arr[i]=node->data;
                node=node->next;
            }
            sortArray(arr,0,size);
            node=this->head;
            for(int i=0; i<size; ++i){
                node->data=arr[i];
                node=node->next;
            }
        }
    
        void reverse() {
            if(this->nodes){
                this->head->reverseL(this->head);
                swap(this->head,this->tail);
            }
        }

        string name() {
            return "Circular Linked List";
        }

        BidirectionalIterator<T> begin() {
            Node<T>* node;
            node->next=this->head->next;
            node->prev=this->head->prev;
            node->data=this->head->data;
            BidirectionalIterator<T> itr(node);
            return itr;
        }

	    BidirectionalIterator<T> end() {
            BidirectionalIterator<T> itr(this->head);
            return itr;
        }

        void merge(CircularLinkedList<T> list) {
            if(this->nodes){
                this->tail->next=list.head;
                list.head->prev=this->tail;
            }else{
                this->head=list.head;
            }
            this->tail=list.tail;
            this->tail->next=this->head;
            this->head->prev=this->tail;
            this->nodes+=list.nodes;

            //Si queremos que cada lista se mantenga independiente
            /*
            Node<T>* node=list.head;
            while(node){
                push_back(node->data);
                node=node->next;
            }*/
        }
};

#endif
