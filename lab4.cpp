#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct node{
    int key;
    int data;
};
void sort2(vector<node>&mas){//за линейное время и не требует доп памяти
    int i,j=0;
    for( i=0;i<mas.size();i++){
        if(mas[i].key ==1){
            while((j<i && j<mas.size()) ||mas[j].key!=0){
                j++;
            }
            if(j < mas.size()) swap(mas[i],mas[j]);//меняем элементы
            
        }
    }
    
    
}
void sort1(vector<node> &mas){//counting
    vector<node> first;
    vector<node> second;
    for(int i=0;i<mas.size();i++){
        if(mas[i].key==0){
            first.push_back(mas[i]);
        }
        else{
            second.push_back(mas[i]);
        }
    }
    int j=0;
    for(int i=0;i<first.size();i++){
        mas[j]=first[i];
        j++;
    }
    for(int i=0;i<second.size();i++){
        mas[j]=second[i];
        j++;
    }
}
void sort3(vector<node>&mas){
    int i,j;
    int n=mas.size();
    for(i=0;i<n;i++){
        for(j=n-1;j>i;j--){
            if(mas[j-1].key >mas[j].key){
                swap(mas[j],mas[j-1]);
            }
        }
    }
    
}
int main(int argc, const char * argv[]) {
    int n =0;
    map<int, int> ff;
    ff.insert({1,2});
    if(ff[2] == 2)cout << 1;
    cout << endl << ff.size();
    cout << (1<<2);
    cin>>n;
    vector<node> mas(n);
    for(int i=0;i<n;i++){
        cin>>mas[i].key;
        mas[i].data = i;
    }
    
    sort3(mas);
    
    for(int i=0;i<n;i++){
        cout<<mas[i].key<<' '<<mas[i].data<<endl;
    }
}
