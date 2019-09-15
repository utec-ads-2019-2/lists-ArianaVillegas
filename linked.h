#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template <typename T>
class LinkedList : public List<T> {
    public:
        LinkedList() : List<T>() {}

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
            if(this->nodes) {
                node->next = this->head;
                this->head->prev = node;
            }else {
                this->tail = node;
            }
            this->head=node;
            ++this->nodes;
        }

        void push_back(T value) {
            Node<T>* node=new Node<T>;
            node->data=value;
            if(this->nodes) {
                node->prev=this->tail;
                this->tail->next = node;
            }else {
                this->head = node;
            }
            this->tail=node;
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
                    node->prev=nullptr;
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
                    node->next=nullptr;
                    this->tail=node;
                }
                --this->nodes;
            }
        }

        T operator[](int index) {
            int size=this->nodes;
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
            } else {
                cout << "Index fuera de rango\n";
            }
        }

        bool empty() {
            return !this->nodes;
        }

        int size() {
            return this->nodes;
        }

        void clear() {
            this->head->killSelf(nullptr);
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
                this->head->reverseL(nullptr);
                swap(this->head,this->tail);
            }
        }

        string name() {
            return "Linked List";
        }

        BidirectionalIterator<T> begin() {
            BidirectionalIterator<T> itr(this->head);
            return itr;
        }

	    BidirectionalIterator<T> end() {
            BidirectionalIterator<T> itr(this->tail->next);
            return itr;
        }

        void merge(LinkedList<T> list) {
            if(this->nodes){
                this->tail->next=list.head;
                list.head->prev=this->tail;
            }else{
                this->head=list.head;
            }
            this->tail=list.tail;
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
