#include <iostream>
#include <vector>
#include <string>
using namespace std;
void compute_prefix(string & P,vector<int> &prefix){
    int m= (int) P.size();
    prefix[0]=0;
    int k=0;
    for(int q=1;q<m;q++){
        k = prefix[q-1];
        while(k>0 && P[k]!=P[q]){
            k=prefix[k-1];
        }
        if(P[k]==P[q]){
            k=k+1;
        }
        prefix[q]=k;
    }
    
}
bool kmp(string & T,string & P){
    int n = (int) T.size();
    int m = (int) P.size();
    vector <int > prefix(m);
    compute_prefix(P, prefix);
    
    int q=0;
    for(int i=0;i<n;i++){
        if(q == m-1)return true;
        while(q>0 && P[q]!=T[i]) q=prefix[q-1];
        if(P[q]==T[i]) q++;

    }
    return false;
}
int main(int argc, const char * argv[]) {
    string T;
    string P;
    cin>>T;
    cin>>P;
    T=T+T;
    if(kmp(T,P)){
        cout<<"yes";
    }
    else{
        cout<<"false";
    }
}
