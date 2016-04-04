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
int Matrix<T>::get(int row, int column)
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
Matrix<T> Matrix<T>::operator*(int n)
{
  Matrix mult = Matrix<T>(rows, columns);
  for (int i = 0; i < rows; i++)
  for (int j = 0; j < columns; j++)
  {
    mult.set(i, j, this->get(i,j) * n);
  }
  return mult;
}
