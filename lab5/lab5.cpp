//laba5
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <random>
#include<iomanip>

using namespace std;

const int min_size = 64;
ofstream deb("debug.txt");
class matrix{
    vector <vector <int> > mtrx;
    int column;
    int row;
    void set_size(int, int);
    matrix strassen_mtrx(matrix a, int privacy);
public:
    matrix(vector<vector<int> > mtrx);
    matrix(int column=0, int row=0);
    ~matrix();
    void output();
    void read();
    matrix sum(matrix  a);
    matrix subtruct(matrix a);
 
    void random_matrix(int n,int m){
        resize(n, m);
        srand((int)time(0));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                mtrx[i][j]=rand()%10;
            }
        }
    }
    matrix strassen_mtrx(matrix & a);
    matrix multiplication(matrix & a);
    
    void resize(int n, int m);
    
    // делим матрицу на 4 маленьких ([a11 a12]
    //                                                                 [a21 a22]);
    void division_matrix(matrix & a11, matrix & a12, matrix & a21, matrix & a22);
    
    // ([P11 P12]
   //  собираем 4 в одну матрицу                                         [P21 P22]);
    
    void collect_matrix(matrix & a11, matrix & a12, matrix & a21, matrix & a22);
    bool check(matrix & b);
    
};
matrix::matrix(int n, int m){//конструктор для матрицы
    column = n;
    row = m;
    mtrx.resize(n);
    for (int i = 0; i < n; ++ i){
        mtrx[i].resize(m);
    }
}




void matrix::resize(int n, int m){
    
    column = n;
    row = m;
    mtrx.resize(n);
    for (int i = 0; i < n; ++ i){
        mtrx[i].resize(m);
    }
}

matrix::~matrix(){
    
}

matrix::matrix(vector<vector<int> > mtrx): mtrx(mtrx) {//конструктор
    column = (int)mtrx.size();
    row = (int)mtrx[0].size();
}

void matrix::output(){//вывод
    for (int i = 0; i < column; ++ i){
        for (int j = 0; j < row; ++ j){
            cout << mtrx[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

int  k = 0;
matrix matrix::strassen_mtrx(matrix a, int privacy){//алгоритм штрасена
    
    if(a.column < min_size){
        return multiplication(a);
    }
    
    if(a.column < min_size){
        return multiplication(a);
    }
    
    matrix a11, a12, a21, a22;
    matrix b11, b12, b21, b22;
    
    division_matrix(a11, a12, a21, a22);
    a.division_matrix(b11, b12, b21, b22);
    
    
    matrix p1 = (a11 .sum(a22)).strassen_mtrx(b11 .sum(b22), 1) ;
    matrix p2 = (a21 .sum(a22)).strassen_mtrx(b11, 1) ;
    matrix p3 = a11.strassen_mtrx(b12 .subtruct(b22), 1) ;
    matrix p4 = a22.strassen_mtrx(b21  .subtruct(b11), 1) ;
    matrix p5 = (a11 .sum(a12)).strassen_mtrx(b22, 1) ;
    matrix p6 = (a21 .subtruct(a11)).strassen_mtrx(b11 .sum(b12), 1) ;
    matrix p7 = (a12 .subtruct(a22)).strassen_mtrx(b21 .sum(b22), 1) ;
    
    matrix c11 = p1 .sum(p4).sum(p7).subtruct(p5) ;
    matrix c12 = p3.sum(p5) ;
    matrix c21 = p2.sum(p4);
    matrix c22 = p1 .subtruct( p2) .sum(p3).sum(p6);
    
    matrix c; c.collect_matrix(c11, c12, c21, c22);
    
    return c;
}

void matrix::read(){//чтение с файла
    cin >> column >>  row;
    resize(column, row);
    for (int i = 0; i < column; ++ i){
        for (int j = 0; j < row; ++ j){
            cin >> mtrx[i][j];
            
        }
    }
}

matrix matrix::sum(matrix a){//сумирование матриц
    if(column != a.column && row != a.row){
        cout << "matrixes must have equal sizes!" << endl;
        
    }
    matrix result(a.column, a.row);
    
    for(int i = 0; i < column; i ++){
        for (int j = 0; j < row; j ++){
            result.mtrx[i][j] = mtrx[i][j] + a.mtrx[i][j];
        }
    }
    return result;
}

matrix matrix::subtruct(matrix a){//вычетание матриц
    if(column != a.column || row != a.row){
        cout << "matrixes must have equal sizes!" << endl;
        
    }
    matrix result(a.column, a.row);
    for(int i = 0; i < column; i ++){
        for (int j = 0; j < row; j ++){
            result.mtrx[i][j] = mtrx[i][j] - a.mtrx[i][j];
        }
    }
    return result;
}

matrix matrix::multiplication(matrix & a){//умножение матриц
    
    if(row != a.column){
        cout << "size error !";
        return matrix();
    }
    
    matrix result(column, a.row);
    
    
    for (int i = 0; i < column; ++ i){
        for (int j = 0; j < a.row; ++ j){
            for (int k = 0; k < row; ++ k){
                result.mtrx[i][j] +=
                mtrx[i][k] * a.mtrx[k][j];
                
            }
        }
    }
    return result;
}

void matrix::division_matrix(matrix & a11, matrix & a12, matrix & a21, matrix & a22){//деление матриц
    int n = column / 2;
    a11.mtrx.clear();a11.resize(n, n);
    a12.mtrx.clear();a12.resize(n, n);
    a21.mtrx.clear();a21.resize(n, n);
    a22.mtrx.clear();a22.resize(n, n);
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j){
            a11.mtrx[i][j] = mtrx[i][j];
            a12.mtrx[i][j] = mtrx[i][j + n];
            a21.mtrx[i][j] = mtrx[i + n][j];
            a22.mtrx[i][j] = mtrx[i + n][j + n];
        }
    }
}

void matrix::collect_matrix(matrix & a11, matrix & a12, matrix & a21, matrix & a22){//4 в 1
    
    int n = a11.row;
    
    resize(2*n, 2*n);
    
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j){
            mtrx[i][j] = a11.mtrx[i][j];
            mtrx[i][j + n] = a12.mtrx[i][j];
            mtrx[i + n][j] = a21.mtrx[i][j];
            mtrx[i + n][j + n] = a22.mtrx[i][j];
        }
    }
}

matrix matrix::strassen_mtrx(matrix & a){//задает новый размер
    
    int need_sz = max(max(column, row), max(a.column, a.row));
    int n = column, m = a.row;
    need_sz = pow(2, (int)log2(need_sz-1) + 1);
    cout << need_sz << endl;
    resize(need_sz, need_sz);
    a.resize(need_sz, need_sz);
    
    
    
    matrix ans = strassen_mtrx(a, 1);
    ans.resize(n,m);
    return ans;
    
}
bool matrix:: check(matrix & b){
    for(int i=0;i<column;i++){
        for(int j=0;j<row;j++){
            if(mtrx[i][j]!=b.mtrx[i][j]){
                return false;
            }
            
        }
    }
    return true;
}

using namespace std;


int main()
{
    
    
   
    matrix a, b;
 
    int n,m;
    cin>>n>>m;
    a.random_matrix(n, m);
    //a.output();cout << endl;
    
    cin >> n >> m;
    b.random_matrix(n, m);
    //b.output();cout << endl;
    double time1=clock();
    matrix c = a.multiplication(b);
    double time2=clock();
    matrix d = a.strassen_mtrx(b);
    double time3=clock();
    c.check(d);
    if(c.check(d)){
        cout<<"correct";
    }
    else cout<<"no";
    cout << endl;

    
    cout << fixed << setprecision(7) << (time2 - time1) / CLOCKS_PER_SEC << endl;
    cout << endl;
    cout << fixed << setprecision(7) << (time3 - time2) / CLOCKS_PER_SEC << endl;
    
    return 0;
}

