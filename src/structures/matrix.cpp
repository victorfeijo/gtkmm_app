#include "matrix.hpp"

template class Matrix<int>;
template class Matrix<double>;

template <typename T>
Matrix<T>::Matrix(int rows, int columns)
    : rows(rows),
      columns(columns)
{
  matrix = new T*[rows];
  for(int i = 0; i < rows; i++)
  {
    matrix[i] = new T[columns];
  }
  for(int i = 0; i < rows; i++)
  for (int j = 0; j < columns; j++)
  {
    matrix[i][j] = 0;
  }
}

template <typename T>
Matrix<T>::~Matrix()
{
}

template <typename T>
void Matrix<T>::set(int row, int column, T value)
{
  if (column >= this->columns || row >= this->rows)
  {
    return;
  }
  else
  {
    this->matrix[row][column] = value;
  }
}

template <typename T>
T Matrix<T>::get(int row, int column)
{
  if (column >= this->columns || row >= this->rows)
  {
    throw 11;
  }
  else
  {
    return this->matrix[row][column];
  }
}

template <typename T>
Matrix<T> Matrix<T>::getRow(int row)
{
  if (row >= this->rows)
  {
    throw 12;
  }
  else
  {
    Matrix<T> aux(1,columns);
    for (int i = 0; i < columns; i++)
    {
      aux.set(0, i, this->matrix[row][i]);
    }
    return aux;
  }
}

template <typename T>
int Matrix<T>::getRows()
{
  return this->rows;
}

template <typename T>
int Matrix<T>::getColumns()
{
  return this->columns;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix another)
{
  if (this->columns != another.columns || this->rows != another.rows)
  {
    throw 20;
  }
  else
  {
    Matrix sum = Matrix<T>(rows, columns);
    for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++)
    {
      sum.set(i, j, this->get(i,j) + another.get(i,j));
    }
    return sum;
  }
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix another)
{
  return *this + (another * -1);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> another)
{
  if (this->columns != another.rows)
  {
    throw 21;
  }
  else
  {
    Matrix mult = Matrix(this->rows, another.columns);
    for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < another.columns; j++)
    for (int k = 0; k < another.rows; k++)
    {
      mult.matrix[i][j] += this->matrix[i][k] * another.matrix[k][j];
    }
    return mult;
  }
}

template <typename T>
Matrix<T> Matrix<T>::operator*(double n)
{
  Matrix mult = Matrix<T>(rows, columns);
  for (int i = 0; i < rows; i++)
  for (int j = 0; j < columns; j++)
  {
    mult.set(i, j, this->get(i,j) * n);
  }
  return mult;
}

// function to force compile and avoid link error (undefined reference).
void f1()
{
  // INSERT TEMPLATE VARIATIONS THAT WILL BE USED AND CALL EVERY FUNCTION
  // int
  Matrix<int> m1(1,1);
  m1.getRows(); m1.getColumns(); m1.get(0,0); m1.getRow(0); m1.set(0,0,0); m1+m1; m1-m1; m1*m1; m1*1;
  // double
  Matrix<double> m2(1,1);
  m2.getRows(); m2.getColumns(); m2.get(0,0); m2.getRow(0); m2.set(0,0,0); m2+m2; m2-m2; m2*m2; m2*1;
}
