#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>

using namespace std;


int main()
{
    ifstream fin("input.txt");
    int n, m;
    cin >> n >> m;
    
    vector< vector <int> > hash(n, vector<int>(n,0));
    vector< vector <int> > arr(n, vector<int>(n,0));
    srand(time(0));
    for (int i = 0; i <n ; ++ i){
        for (int j = 0; j < n; ++ j){
            //fin >> arr[i][j];
            arr[i][j] = rand()%2;
        }
    }
    
    int my_hash = 0;
    fin >> m;
    vector< vector <int> > sample(m, vector<int>(m,0));
    const int q = 2, p = 3;
    const int mod = 1e3+7;
    int pow_q[n+1], pow_p[n+1];
    pow_p[0] = pow_q[0] = 1;
    for (int i = 1; i <= n; ++ i){
        pow_p[i] = pow_p[i-1] * p;
        pow_q[i] = pow_q[i-1] * q;
        pow_p[i] %= mod;
        pow_q[i] %= mod;
    }
    for (int i = 0; i < m; ++ i){
        for (int j = 0; j < m; ++ j){
            sample[i][j] = rand() % 2;
            my_hash += sample[i][j]*pow_p[i]*pow_q[j];
            
        }
    }
    my_hash %= mod;
    
    //calculating hash for each submatrix
    for(int i = 0; i < n; ++ i){
        for(int j = 0; j < n; ++ j){
            hash[i][j] = arr[i][j]*pow_p[i]*pow_q[j];
            
            if(i)
                hash[i][j] += hash[i-1][j];
            if(j)
                hash[i][j] += hash[i][j-1];
            if(i&&j)
                hash[i][j] -= hash[i-1][j-1];
            
            hash[i][j] %= mod;
            
        }
        
    }
    
    cout << my_hash << endl;
    for(int i = m-1; i < n; ++ i){
        for(int j = m-1; j < n; ++ j){
            
            int upx = i-m+1, upy = j-m+1, downx = i, downy = j;
            int cur_hash = hash[downx][downy];
            if(upx) cur_hash -= hash[upx - 1][downy];
            if(upy) cur_hash -= hash[downx][upy - 1];
            if(upx&&upy) cur_hash += hash[upx - 1][upy - 1];
            cur_hash %= mod;
            cur_hash = abs(cur_hash);
            int tmp = pow_p[upx] * pow_q[upy] * my_hash;
            tmp %= mod;
            
            if(cur_hash == tmp    ){
                
                bool candidate = true;
                
                for (int k = i-m+1, iter_i = 0; k <= i; k ++, iter_i ++){
                    for (int g = j-m+1, iter_j = 0; g <= j; g ++,iter_j ++){
                        
                        if(arr[k][g] != sample[iter_i][iter_j]){
                            candidate = false;
                            break;
                        }
                        
                    }
                    
                }
                
                if(candidate){
                    cout  << "answer: " << i-m+1 << " " << j-m+1 << endl;
                }
                
            }
        }
        
    }
    return 0;
}
