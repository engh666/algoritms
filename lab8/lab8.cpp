#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <random>
#include <map>

using namespace std;

void naive_string_matcher(string & basic_st, string & sample){
    int n  = basic_st.size();
    int m = sample.size();
    for (int i = 0; i <= n - m; ++ i){
        bool b = true;
        for (int j = 0; j < m; j ++){
            if(basic_st[j + i] != sample[j]){
                b = false;
                break;
            }
        }
        if(b){
            cout << i << " ";
        }
    }
}

void rabin_kapr_method(string & basic_st, string & sample){
    
    const int q = 1e7+7;
    const int d = 256;
    
    int n  = basic_st.size();
    int m = sample.size();
    int h = 1;
    
    for (int i = 1; i < m; i ++){
        h *= d;
        h %= q;
    } /// h = d^(m-1) % q
    
    int p = 0;
    vector <int> t(n-m+1,0);
    
    for (int i = 0; i < m; ++ i){
        p = (d * p + sample[i]) % q;
        t[0] = (d * t[0] + basic_st[i]) % q;
    }
    
    for (int i = 0; i < n - m; ++ i){
        t[i+1] = (d*(t[i] - basic_st[i]*h) + basic_st[i+m]) % q;
    }
    
    for (int i = 0; i <= n - m; ++ i){
        if(t[i] != p) continue;
        bool b = true;
        for (int j = 0; j < m; j ++){
            if(basic_st[j + i] != sample[j]){
                b = false;
                break;
            }
        }
        if(b){
            cout << i << " ";
        }
    }
    
}

void knut_morris_pratt(string & basic_st, string & sample){
    sample += "$";
    int m = sample.size();
    int n = basic_st.size();
    
    /// count prefix function for sample string
    vector <int> pi(m + 1);
    pi[0] = 0;
    for (int i = 1; i < m; ++ i){
        int j = pi[i - 1];
        while(j > 0 && sample[i] != sample[j]) j = pi[j-1];
        if(sample[i] == sample[j]) j ++;
        pi[i] = j;
    }
    
    
    /// update on each symbol function and if on i-th step func = m => substring starts there
    int cur = 0;
    for (int i = 0; i < n; ++ i){
        if(cur == m - 1){
            cout << i - m + 1 << " ";
        }
        int j = cur;
        while(j > 0 && basic_st[i] != sample[j]) j = pi[j-1];
        if(basic_st[i] == sample[j]) j ++;
        cur = j;
        
    }
    
}

void boera_mura_hourspula(string & basic_st, string & sample){
    
    int n  =(int) basic_st.size();
    int m = (int) sample.size();
    
    vector <int> shift_table(256, m);
    
    for (int i = 0; i < m - 1; ++ i){
        shift_table[ sample[i] ] = m - i - 1;
    }
    
    int i = m - 1,
    j = m - 1,
    k = m - 1;
    
    while(i < n){
        j = m - 1;
        k = i;
        while(j >= 0 && basic_st[k] == sample[j]){
            k --; j --;
        }
        if( j < 0 ){
            cout << k + 1 << " ";
        }
        i += shift_table[ basic_st[i] ];
    }
    
    
}

vector<int> prefix_func(const string &s) {
    vector<int> p(s.length());
    
    int k = 0;
    p[0] = 0;
    for (int i = 1; i < s.length(); ++i) {
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            ++k;
        }
        p[i] = k;
    }
    return p;
}

void boera_mura(string &basic_st, string & sample) {
    
    map<char, int> stop_table;
    map<int, int> suffics_table;
    
    for (int i = 0; i < sample.length(); ++i) {
        stop_table[sample[i]] = i;
    }
    
    string rev_sample(sample.rbegin(), sample.rend());
    vector<int> p = prefix_func(sample);
    vector<int> pr = prefix_func(rev_sample); // reversed
    for (int i = 0; i < sample.length() + 1; ++i) {
        suffics_table[i] = sample.length() - p.back();
    }
    
    for (int i = 1; i < sample.length(); ++i) {
        int j = pr[i];
        suffics_table[j] = min(suffics_table[j], i - pr[i] + 1);
    }
    
    for (int shift = 0; shift <= basic_st.length() - sample.length();) {
        int pos = sample.length() - 1;
        
        while (sample[pos] == basic_st[pos + shift]) {
            if (pos == 0){ cout << shift << " "; }
            --pos;
        }
        
        if (pos == sample.length() - 1) {
            map<char, int>::const_iterator stop_symbol = stop_table.find(basic_st[pos + shift]);
            int stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
            shift += stop_symbol_additional;
        } else {
            shift += suffics_table[sample.length() - pos - 1];
        }
    }
    
    
}

int main()
{
    srand(time(0));
    int n, m;
    cin >>n >> m;
    string s1, s2;
    for (int i = 0; i < n; ++ i){
        s1.push_back(rand() % 2);
    }
    for (int i = 0; i < m; ++ i){
        s2.push_back(rand() % 2);
    }
    
    double time1 = clock();
    naive_string_matcher(s1, s2);
    double time2 = clock();
    cout << fixed << setprecision(7) << (time2 - time1) / CLOCKS_PER_SEC << endl;
    cout << endl;
    time1 = clock();
    rabin_kapr_method(s1, s2);
    time2 = clock();
    cout << fixed << setprecision(7) << (time2 - time1) / CLOCKS_PER_SEC << endl;
    cout << endl;
    time1 = clock();
    boera_mura_hourspula(s1, s2);
    time2 = clock();
    cout << fixed << setprecision(7) << (time2 - time1) / CLOCKS_PER_SEC << endl;
    cout << endl;
    time1 = clock();
    boera_mura(s1, s2);
    time2 = clock();
    cout << fixed << setprecision(7) << (time2 - time1) / CLOCKS_PER_SEC << endl;
    cout << endl;
    time1 = clock();
    knut_morris_pratt(s1, s2);
    time2 = clock();
    cout << fixed << setprecision(7) << (time2 - time1) / CLOCKS_PER_SEC << endl;
    
    return 0;
}

