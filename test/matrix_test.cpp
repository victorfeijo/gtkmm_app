#include "../include/structures/matrix.hpp"
#include <iostream>

using namespace std;

void printMatrix(Matrix<int> matrix)
{
  cout << endl << "Output Matrix: " << endl;
  for(int i=0; i<matrix.getRows(); ++i)
  for(int j=0; j<matrix.getColumns(); ++j)
  {
    cout << " " << matrix.get(i,j);
    if(j == matrix.getColumns() - 1)
    cout << endl;
  }
}

int main()
{
  Matrix<int> a(2,2);
  Matrix<int> b(2,3);
  Matrix<int> c(2,2);
  Matrix<double> d(20,20);

  a.set(0,0,3);a.set(0,1,2);  // a = [ 3  2
  a.set(1,0,8);a.set(1,1,-1); //       8 -1 ]

  b.set(0,0,6);b.set(0,1,3);b.set(0,2,-5);  // b = [ 6  3 -5
  b.set(1,0,-1);b.set(1,1,15);b.set(1,2,0); //      -1 15  0 ]

  c.set(0,0,1);c.set(0,1,2);  // a = [ 1  2
  c.set(1,0,2);c.set(1,1,-1); //       2 -1 ]


  printMatrix(Matrix<int>(2,3));
  printMatrix(a);
  printMatrix(b);
  printMatrix(a * b);
  printMatrix(c);
  printMatrix(a + c);

}
