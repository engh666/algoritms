#include <iostream>
#include <vector>

using namespace std;

void buble_sort(vector<int>& a){
    for (int i = 0; i < a.size(); ++ i){
        for (int j = 0; j < a.size()-i-1; ++ j){
            if(a[j] > a[j+1]){
                swap(a[j], a[j+1]);
            }
        }
    }
}

void selection_sort(vector<int>& a){
    int mn_i;
    for(int i = 0; i < a.size(); ++ i){
        mn_i = i;
        for (int j = i; j < a.size(); ++ j){
            if(a[mn_i] > a[j]){
                mn_i = j;
            }
        }
        swap(a[i], a[mn_i]);
    }
}

void insertion_sort(vector<int>& a){
    for (int i = 1; i < a.size(); ++ i){
        if(a[i-1] > a[i]){
            int it = i;
            while(a[it-1]>a[it]){
                swap(a[it-1], a[it]), it --;
            }
        }
    }
}

void merge_sort(){
    
}



#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++ i){
        cin >> a[i];
    }
    insertion_sort(a);
    
    for (int i = 0; i < n; ++ i){
        cout << a[i] << " ";
    }
    return 0;
}
