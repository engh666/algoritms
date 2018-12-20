#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
void quickSortScrew(vector<int> & screw_nut, vector<int> & screw, int left, int right, int kernel) {//сортировка болтов
    if (right <= left) {
        return;
    }
    int pointer = left - 1;
    for (int i = left; i < right; i++) {
        if (screw[i] < kernel) {
            pointer++;
            swap(screw[pointer], screw[i]);
        }
    }
    
    pointer++;
    
    swap(screw[pointer], screw[right]);
}


void quickSortScrew_nut(vector<int> & screw_nut, vector<int> & screw, int left, int right) {//сорттировка гаек
    
    
    if (right <= left) {
        return;
    }
    
    int kernel = screw[  right];
    int pointer = left - 1;
    
    for (int i = left; i < right; i++) {
        if (screw_nut[i] < kernel) {
            pointer++;
            swap(screw_nut[pointer], screw_nut[i]);
        }
        else if(screw_nut[i] == kernel) {
            swap(screw_nut[i], screw_nut[right]);
            
            i--;
        }
    }
    
    pointer++;
    swap(screw_nut[pointer], screw_nut[right]);
    
    quickSortScrew(screw_nut, screw, left, right, screw_nut[pointer]);
    quickSortScrew_nut(screw_nut, screw, left, pointer - 1);
    quickSortScrew_nut(screw_nut, screw, pointer + 1, right);
}



int main() {
    
    int n;
    cin >> n;
    vector<int> screw_nut(n);
    vector<int> screw(n);
    
    for (int i = 0; i < n; i++) {
        screw_nut[i] = i + 1;
        screw[i] = i + 1;
    }
    
    random_shuffle(screw.begin(), screw.end());
    random_shuffle(screw_nut.begin(), screw_nut.end());
    
    
    cout << "Sorting haven't been done yet" << endl;
    for(auto nt: screw_nut){
        cout << nt << " ";
    }
    cout <<  endl;
    for(auto bt: screw){
        cout << bt << " ";
    }
    cout << endl << endl;
    
    quickSortScrew_nut(screw_nut, screw, 0, n - 1);
    
    cout << "Sorting done" << endl;
    for(auto nt: screw_nut ){
        cout << nt << " ";
    }
    cout << endl;
    for(auto bt: screw){
        cout << bt << " ";
    }
    cout << endl << endl;
    
    
    return 0;
}

