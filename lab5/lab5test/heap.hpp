#ifndef heap_hpp
#define heap_hpp

#include "list.hpp"

template <class T>
class heap{
private:
    list<T> l;
    void heapify_down(int);
    void heapify_up(int);
    int size;
public:
    void extract_max();
    T get_max();
    void print() { l.show(); }
    void insert(T k);
    heap(): size(0), l() {}
};

template<class T>
void heap<T>::extract_max(){//delete
    swap(l[0], l[size-1]);
    l.pop_back();
    size--;
    heapify_down(0);
}

template <class T>
T heap<T>::get_max(){
    return l[0];
}

template <class T>
void heap<T>:: heapify_down(int i){//просеивание с верхнего элемента
    int largest;
    if(l[2*i] <size() && l[2*i] > l[i] ){
        largest= 2*i;
    }
    else largest=l[i];
    
    if(l[(2*i+1)]<size() && l[(2*i+1)] > l[largest]){
        largest =(2*i+1);
    }
    if(l[largest]!=l[i]){
        swap(l[i],l[largest]);
        heapify_down(largest);
    }
    
}

template <class T>
void swap(T a, T b){
    T c = a;
    a = b;
    b = c;
    
}

template <class T>
void heap<T>:: heapify_up(int i){//просеивание с нижнего элемента
    if(l[i] > l[i/2]){
        swap(l[i],l[i/2]);
        heapify_up(i/2);
    }
}
template <class T>
void heap<T>::insert(T data){//добавление+просеивание с нижнего элемента
    l.push_back(data);
    size ++;
    heapify_up(size-1);
}


#endif /* heap_hpp */
