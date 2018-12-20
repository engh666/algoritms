#ifndef list_hpp
#define list_hpp

#include <iostream>
using namespace std;


template <class T>
class node_list{
public:
    node_list *next;
    node_list *prev;
    T data;

    node_list(): next(nullptr), prev(nullptr) {}
    node_list(T data1, node_list *next_p = nullptr, node_list *prev_p = nullptr):
    next(next_p), prev(prev_p), data(data1) {}
};

template <class T>
class list{
private:
    node_list<T> *head;
    node_list<T> *tail;
public:
    list(): head(nullptr), tail(nullptr){}
    void push_front(T data);
    void push_back(T);
    void pop_front();
    void pop_back();
    bool search(T data);
    bool empty();
    void clear();
    void show();
    T operator [] (int i);
    void pop(node_list<T> * to_delete);
};

template <class T>
void list<T> :: push_back(T data){
    if(!head){
        head = tail = new node_list<T>(data);
        return;
    }
    tail->next=new node_list<T>(data, nullptr, tail);
    tail=tail->next;
    return;
}


template <class T>
void list<T>::push_front(T data){
    if (!head){
        head = tail = new node_list<T>(data);
        return;
    }
    node_list<T> *pointer = new node_list<T>(data, head, nullptr);
    pointer->next = head;
    head = pointer;
    
}


template <class T>
void list<T>::pop_front(){
    if(!head){
        return;
    }
    if(head==tail){
        delete(head);
        head = tail = nullptr;
        return;
    }
    
    node_list<T> *tmp = head;
    head = tmp->next;
    head->prev = nullptr;
    
    delete(tmp);
}

template <class T>
void list<T>::pop_back(){
    if(!head){
        return;
    }
    if(head==tail){
        delete(tail);
        head = tail =nullptr;
        return;
    }
    node_list<T> *pointer=tail->prev;
    delete(tail);
    tail=pointer;
    pointer->next=nullptr;
}


template <class T>
void list<T>::pop(node_list<T> * to_delete){
    if(to_delete->prev) to_delete->prev->next=to_delete->next;
    if(to_delete->next) to_delete->next->prev=to_delete->prev;
    delete(to_delete);
}


template <class T>
bool list<T>::empty(){
    if(!head){
        return true;
    }
    else{
        return false;
    }
}

template <class T>
bool list<T>::search(T data){
    node_list<T> *pointer=head;
    while(pointer){
        if(pointer->data==data){
            return true;
        }
        pointer=pointer->next;
    }
    return false;
}

template <class T>
void list<T>::clear(){
    node_list<T> *pointer=head;
    while(pointer){
        pointer=pointer->next;
        delete (pointer->prev);
    }
    delete tail;
    head = tail =nullptr;
}

template <class T>
T list<T>::operator[] (int i){
    node_list<T> *pointer=head;
    int index=0;
    while(index!=i){
        pointer=pointer->next;
        index++;
    }
    return pointer->data;
}
template <class T>
void list<T> ::show(){
    node_list<T> *pointer=head;
    while(pointer){
        cout<<pointer->data<< ' ';
        pointer=pointer->next;
        
    }
    
}


#endif /* list_hpp */
