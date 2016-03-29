#ifndef GTKMM_APP_MATRIX
#define GTKMM_APP_MATRIX

template <typename T>

class Matrix
{

public:

  Matrix(int rows, int columns)
      : rows(rows),
        columns(columns)
  {
    matrix = new T*[rows];
    for(int i = 0; i < rows; i++)
    {
      matrix[i] = new int[columns];
    }
    for(int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++)
    {
      matrix[i][j] = 0;
    }
  }

  int get(int row, int column)
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
  ~Matrix() {}

  void set(int row, int column, T value)
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

  Matrix operator+(Matrix another)
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

  Matrix operator*(Matrix<T> another)
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

// protected:
  int rows, columns;
  T** matrix;

};

#endif
