 /* 
Implementation of the clas My_matrix
*/

#include "My_matrix.h"
#include <stdexcept>
#include <stdlib.h>

My_matrix::My_matrix()
{
  n = 0;
  m = 0;
  ptr = nullptr;
}

void My_matrix::allocate_memory()
{
  ptr = new int*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new int[m];
}

My_matrix::My_matrix(int n1, int m1)
{
  n = n1;
  m = m1;

  ptr = new int*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new int[m];
}

// copy constructor
My_matrix::My_matrix(const My_matrix& mat)
{
  n = mat.number_of_rows();
  m = mat.number_of_columns();

  ptr = new int*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new int[m];

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
    {
      ptr[i][j] = mat.elem(i, j);
    }
  }
}

// move constructor (optional)
My_matrix::My_matrix(My_matrix&& mat)
{
  n = mat.n;
  m = mat.m;
  ptr = mat.ptr;

  mat.ptr = nullptr;
  mat.n = 0;
  mat.m = 0;
}

My_matrix::~My_matrix()
{
  for(int i = 0; i < n; ++i)
    delete[] ptr[i];

  delete[] ptr;
}

// copy assignment
My_matrix& My_matrix::operator=(const My_matrix& mat)
{
  n = mat.number_of_rows();
  m = mat.number_of_columns();

  ptr = new int*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new int[m];

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
    {
      ptr[i][j] = mat.elem(i, j);
    }
  }

  return *this;
}

// move assignment operator (optional)
My_matrix& My_matrix::operator=(My_matrix&& mat)
{
  for(int i = 0; i < n; ++i)
    delete[] ptr[i];

  delete[] ptr;

  n = 0;
  m = 0;

  n = mat.n;
  m = mat.m;
  ptr = mat.ptr;

  mat.n = 0;
  mat.m = 0;
  mat.ptr = nullptr;
  
  return *this;
}

int My_matrix::number_of_rows() const
{
  return n;
}

int My_matrix::number_of_columns() const
{
  return m;
}

int* My_matrix::operator()(int i) const
{
  return ptr[i];
}

int My_matrix::operator()(int i, int j) const
{
  return ptr[i][j];
}

int& My_matrix::operator()(int i, int j)
{
  return ptr[i][j];
}

int My_matrix::elem(int i, int j) const
{
  if (i < 0 || i >= n)
    throw out_of_range("Out of range");

  if (j < 0 || j >= m)
    throw out_of_range("Out of range");
  
  return ptr[i][j];
}

int& My_matrix::elem(int i, int j)
{
  if (i < 0 || i >= n)
    throw out_of_range("Out of range");

  if (j < 0 || j >= m)
    throw out_of_range("Out of range");

  return ptr[i][j];
}

ostream& operator<<(ostream& out, const My_matrix& mat)
{
  out << mat.number_of_rows() << " " << mat.number_of_columns() << endl;

  for(int i = 0; i < mat.number_of_rows(); ++i)
  {
    for(int j = 0; j < mat.number_of_columns() - 1; ++j)
      out << mat.elem(i, j) << " " ;

    out << mat.elem(i, mat.number_of_columns() - 1) << endl;
  }

  return out;
}

istream& operator>>(istream& in, My_matrix& mat)
{
  int nTemp;
  int mTemp;

  in >> nTemp >> mTemp;

  My_matrix maTemp = My_matrix(nTemp, mTemp);

  for(int i = 0; i < nTemp; ++i)
  {
    for(int j = 0; j < mTemp; ++j)
    {
      int temp;
      if(in >> temp)
      {
        maTemp.elem(i, j) = temp;
      }
      else
      {
        cout << "There are few inputs in the file." << endl;
        exit(EXIT_FAILURE);
      }
    }
  }

  int temp1;

  if(in >> temp1)
  {
    cout << "There are more inputs in the file." << endl;
    exit(EXIT_FAILURE);
  }

  mat = maTemp;

  return in;
}

My_matrix operator+(const My_matrix& mat1, const My_matrix& mat2)
{
  
  if(mat1.number_of_rows() != mat2.number_of_rows() || mat1.number_of_columns() != mat2.number_of_columns())
  {
    cout << "Error: Incompitable Matrices" << endl;
    exit(EXIT_FAILURE);
  }
  
  int n = mat1.number_of_rows();
  int m = mat1.number_of_columns();

  My_matrix mTemp = My_matrix(n, m);

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
      mTemp.elem(i, j) = mat1.elem(i, j) + mat2.elem(i, j);
  }

  return mTemp;
  
}

My_matrix operator*(const My_matrix& mat1, const My_matrix& mat2)
{
  if(mat1.number_of_columns() != mat2.number_of_rows())
  {
    cout << "Error: Incompitable Matrices" << endl;
    exit(EXIT_FAILURE);
  }

  int n = mat1.number_of_rows();
  int m = mat2.number_of_columns();

  My_matrix mTemp = My_matrix(n, m);

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
    {
      mTemp.elem(i, j) = 0;

      for(int k = 0; k < mat1.number_of_columns(); ++k)
      {
        mTemp.elem(i, j) += mat1.elem(i, k) * mat2.elem(k, j);
      }
    }
  }

  return mTemp;
}