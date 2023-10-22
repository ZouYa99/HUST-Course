
#include <iostream>
#include <vector>
#define N 128
using namespace::std;
void add(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, vector<vector<int>>& matrix_result){
    int size = matrix1.size();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            matrix_result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}
void sub(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, vector<vector<int>>& matrix_result){
    int size = matrix1.size();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            matrix_result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

void stressen(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2,vector<vector<int>>& matrix_result){
    int m=matrix1.size(),n=matrix1[0].size(),k=matrix2[0].size();
    if(m==1){
        matrix_result[0][0] = matrix1[0][0]*matrix2[0][0];
        return;
    }
    int m_half=m/2,n_half=n/2,k_half=k/2;
    vector<vector<int>> a11(m_half,vector<int>(n_half)),a12(m_half,vector<int>(n_half)),a21(m_half,vector<int>(n_half)),a22(m_half,vector<int>(n_half)),temp1(m_half,vector<int>(n_half));
    vector<vector<int>> b11(n_half,vector<int>(k_half)),b12(n_half,vector<int>(k_half)),b21(n_half,vector<int>(k_half)),b22(n_half,vector<int>(k_half)),temp2(n_half,vector<int>(k_half));
    vector<vector<int>> c11(m_half,vector<int>(k_half)),c12(m_half,vector<int>(k_half)),c21(m_half,vector<int>(k_half)),c22(m_half,vector<int>(k_half));
    vector<vector<int>> p1(m_half,vector<int>(k_half)),p2(m_half,vector<int>(k_half)),p3(m_half,vector<int>(k_half)),p4(m_half,vector<int>(k_half)),p5(m_half,vector<int>(k_half)),p6(m_half,vector<int>(k_half)),p7(m_half,vector<int>(k_half));
    
    for (int i=0; i<m_half; i++) {
        for (int j=0; j<n_half; j++) {
            a11[i][j] = matrix1[i][j];
            a12[i][j] = matrix1[i][j+n_half];
            a21[i][j] = matrix1[i+m_half][j];
            a22[i][j] = matrix1[i+m_half][j+n_half];
            
            b11[i][j] = matrix2[i][j];
            b12[i][j] = matrix2[i][j+k_half];
            b21[i][j] = matrix2[i+n_half][j];
            b22[i][j] = matrix2[i+n_half][j+k_half];
        }
    }
    
//    for (int i=0; i<n_half; i++) {
//        for (int j=0; j<k_half; j++) {
//            b11[i][j] = matrix2[i][j];
//            b12[i][j] = matrix2[i][j+k_half];
//            b21[i][j] = matrix2[i+n_half][j];
//            b22[i][j] = matrix2[i+n_half][j+k_half];
//        }
//    }
    
    sub(b12, b22, temp2);
    stressen(a11, temp2, p1);
    
    add(a11, a12, temp1);
    stressen(temp1, b22, p2);
    
    add(a21, a22, temp1);
    stressen(temp1, b11, p3);
    
    sub(b21, b11, temp2);
    stressen(a22, temp2, p4);
    
    add(a11, a22, temp1);
    add(b11, b22, temp2);
    stressen(temp1, temp2, p5);
    
    sub(a12, a22, temp1);
    add(b21, b22, temp2);
    stressen(temp1, temp2, p6);
    
    sub(a11, a21, temp1);
    add(b11, b12, temp2);
    stressen(temp1, temp2, p7);
    
    add(p5, p4, c11);
    sub(c11, p2, c11);
    add(c11, p6, c11);
    
    add(p1, p2, c12);
    
    add(p3, p4, c21);
    
    add(p1, p5, c22);
    sub(c22, p3, c22);
    sub(c22, p7, c22);
    
    for (int i=0; i<m_half; i++) {
        for (int j=0; j<k_half; j++) {
            matrix_result[i][j]=c11[i][j];
            matrix_result[i][j+k_half]=c12[i][j];
            matrix_result[i+m_half][j]=c21[i][j];
            matrix_result[i+m_half][j+k_half]=c22[i][j];
        }
    }
}

int main(int argc, const char * argv[]) {
    int m,n,k;
    cin>>m;
    cin>>n;
    cin>>k;
    vector<vector<int>> v1(N,vector<int>(N));
    vector<vector<int>> v2(N,vector<int>(N));
    vector<vector<int>> v3(N,vector<int>(N));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            v1[i][j]=0;
            v2[i][j]=0;
            v3[i][j]=0;
        }
    }
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin>>v1[i][j];
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<k; j++) {
            cin>>v2[i][j];
        }
    }
    stressen(v1, v2, v3);
    for (int i=0; i<m; i++) {
        for (int j=0; j<k; j++) {
            cout << v3[i][j] ;
            if (j != (k - 1)) cout << " ";
        }
        cout<<endl;
    }
    return 0;
}
