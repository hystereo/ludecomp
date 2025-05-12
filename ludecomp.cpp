#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

void LU(const vector<vector<float>>& A, vector<vector<float>>& L, vector<vector<float>>& U, int n){ //funkcja robiąca rozklad LU
   for(int i = 0; i<n;i++){ //ustawiamy dla tablicy L 1-ki po przekątnej
         L[i][i] = 1;
   }
   for(int i = 0; i< n;i++){ //ustawiamy dla tablicy U wartości z pierwszego wiersza tablicy A
      U[0][i] = A[0][i];
   }

   for (int i = 0; i < n; i++) {
      //rozkład U
      #pragma acc parallel loop
        for (int k = i; k < n; k++) {
            float sum = 0;
            for (int j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]);
            }
            U[i][k] = A[i][k] - sum;
        }


      //rozkład L
      #pragma acc parallel loop
         for (int k = i; k < n; k++) {

                float sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += (L[k][j] * U[j][i]);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
   }
}

vector<vector<float>> generateRandomMatrix(int n){
   vector<vector<float>> matrix(n, vector<float>(n));
   for(int i = 0; i < n; i ++){
      int sum = 0;
      for(int j = 0; j < n; j ++) {
         matrix[i][j] = 1 + rand() % 10;
         sum += matrix[i][j];
      }
      matrix[i][i] = sum;
   }
   return matrix;
}

void testLU(int n) {
   vector<vector<float>> A = generateRandomMatrix(n);
   vector<vector<float>> L (n, vector<float>(n, 0.0));
   vector<vector<float>> U (n, vector<float>(n, 0.0));

#pragma acc parallel loop
   for(int i = 0; i < n; i ++){
      for(int j = 0; j < n; j ++){
         cout<<A[i][j]<<" ";
      }
      cout<<endl;
   }

   LU (A, L, U, n);

   // for(int i = 0; i < n; i ++){
   //    for(int j = 0; j < n; j ++){
   //       cout<<L[i][j]<<" ";
   //    }
   //    cout<<endl;
   // }

   // for(int i = 0; i < n; i ++){
   //    for(int j = 0; j < n; j ++){
   //       cout<<U[i][j]<<" ";
   //    }
   //    cout<<endl;
   // }
   
}

void printMatrix(vector<vector<float>>& M){
   unsigned int n = M.size();
   for(int i = 0; i < n; i ++){
      for(int j = 0; j < n; j++){
         cout<<M[i][j]<<" ";
      }
      cout<<endl;
   }
}


int main(){
   int n;
   cout<<"Podaj rozmiar macierzy:"<<endl;
   cin>>n;

   vector<vector<float>> A = generateRandomMatrix(n);
   vector<vector<float>> L (n, vector<float>(n, 0.0));
   vector<vector<float>> U (n, vector<float>(n, 0.0));

   //vector<vector<float>> A(n, vector<float>(n, 0.0));
   // vector<vector<float>> L(n, vector<float>(n, 0.0));
   // vector<vector<float>> U(n, vector<float>(n, 0.0));

   // cout<<"Podaj wartości w macierzy: "<<endl;
   // for (int i = 0; i < n; i++)
   //    for (int j = 0; j < n; j++)
   //       cin >> A[i][j];

   //testLU(n);

   LU(A,L,U,n);
   
   cout<<"Macierz A:"<<endl;
   printMatrix(A);
   cout<<"Macierz L:"<<endl;
   printMatrix(L);
   cout<<"Macierz U:"<<endl;
   printMatrix(U);

   return 0;
}