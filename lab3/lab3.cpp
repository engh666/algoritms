#include <iostream>
#include <vector>
using namespace std;
int d=2;
int get_max(vector<int> &mas){//нахождение максимума
    return mas[0];
}
void heapify_down(vector<int> &mas,int i){//просеивание вниз
    int largest =i;
    if(i>(mas.size()+1)/d) return;
    for(int j = d*i+1; j <= d*i+d; j ++){
     
        if(j >= mas.size())break;
        if(mas[largest] < mas[j]){
            largest = j;
        }
    }
    if(largest!=i){
        swap(mas[i],mas[largest]);
        heapify_down(mas,largest);
    }
    
}
void heapify_up(vector<int> &mas,int i){//просеивание вверх
    if(mas[i] > mas[(i-1)/d]){
        swap(mas[i],mas[(i-1)/d]);
        heapify_up(mas,(i-1)/d);
    }
    
}
void extract_max(vector <int> &mas){//удаление
    swap(mas[0],mas[mas.size()-1]);
    mas.pop_back();
    
    heapify_down(mas,0);
}
void add_elem(vector<int> &mas,int k){//добавление в конец
    mas.push_back(k);
    heapify_up(mas,(int)mas.size()-1);
}
int main(int argc, const char * argv[]) {
    vector<int> mas;
    add_elem(mas,3);
    add_elem(mas,8);
    add_elem(mas,5);
    add_elem(mas,7);
    add_elem(mas,2);
    add_elem(mas,4);
    cout<<get_max(mas)<<' ';
    extract_max(mas);
    
    cout<<get_max(mas)<<' ';
    extract_max(mas);
    
    
    cout<<get_max(mas)<<' ';
    extract_max(mas);
//    for(auto a: mas){
 //       cout << a << " ";
 //   }

}
