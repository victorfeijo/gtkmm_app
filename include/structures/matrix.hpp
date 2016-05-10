#ifndef GTKMM_APP_MATRIX
#define GTKMM_APP_MATRIX

template <typename T>
class Matrix
{

public:

  Matrix(int rows, int columns);
  ~Matrix();

  void set(int row, int column, T value);
  T get(int row, int column);
  Matrix<T> getRow(int row);
  int getRows();
  int getColumns();

  Matrix operator+(Matrix another);
  Matrix operator-(Matrix another);
  Matrix operator*(Matrix<T> another);
  Matrix operator*(double n);

protected:
  int rows, columns;
  T** matrix;

};

#endif
