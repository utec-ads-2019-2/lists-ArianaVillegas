#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {}

        T front() {
            return this->head->data;
        }

        T back() {
            return this->tail->data;
        }

        void push_front(T value) {
            Node<T>* node=new Node<T>;
            node->data=value;
            if(this->nodes)
                node->next=this->head;
            else
                this->tail=node;
            this->head=node;
            ++this->nodes;
        }

        void push_back(T value) {
            Node<T>* node=new Node<T>;
            node->data=value;
            if(this->nodes)
                this->tail->next=node;
            else
                this->head=node;
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
                    this->head=node;
                }
                --this->nodes;
            }
        }

        void pop_back() {
            if(this->nodes){
                Node<T>* node=this->head;
                int size=this->nodes-1;
                for(int i=1; i<size; ++i){
                    node=node->next;
                }
                delete this->tail;
                if(this->nodes==1){
                    this->head=nullptr;
                }else{
                    this->tail=node;
                }
                --this->nodes;
            }
        }

        T operator[](int index) {
            int size=this->nodes;
            if(size>index){
                Node<T>* node=this->head;
                for(int i=0; i<index; ++i){
                    node=node->next;
                }
                return node->data;
            } else {
                cout << "Index fuera de rango\n";
            }
        }

        bool empty() {
            return !(this->nodes);
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
                this->head->reverseF(nullptr);
                swap(this->head,this->tail);
            }
            this->tail->next=nullptr;
        }

        string name() {
            return "Forward List";
        }

        ForwardIterator<T> begin() {
            ForwardIterator<T> itr(this->head);
            return itr;
        }

	    ForwardIterator<T> end() {
            ForwardIterator<T> itr(this->tail->next);
            return itr;
        }

        void merge(ForwardList<T> list) {
            if(this->nodes){
                this->tail->next=list.head;
            }else{
                this->head=list.head;
            }
            this->tail=list.tail;
            this->nodes+=list.nodes;

            //Si queremos que cada lista se mantenga independiente
            /*
            Node<T>* node=list.head;
            while(node!=nullptr){
                push_back(node->data);
                node=node->next;
            }*/
        }
};

#endif