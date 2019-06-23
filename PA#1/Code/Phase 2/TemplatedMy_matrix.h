#include <iostream>
#include <exception>
#include <stdexcept>
#include <stdlib.h>

using namespace std;
// Definitions of user defined type exceptions 
struct invalid_input : public exception {
  virtual const char* what() const throw()
  { return "Invalid matrix input"; }
};

struct incompatible_matrices : public exception {
  virtual const char* what() const throw()
  { return "Incompatible matrices"; }
};

template<typename T> 
class TemplatedMy_matrix {
	
  //member variables
  int n, m;
  T **ptr;
  void allocate_memory();  // optional	
  
public:	
  //member functions
  TemplatedMy_matrix();  // default constructor
  TemplatedMy_matrix(int n1, int m1); // parameter constructor
  ~TemplatedMy_matrix(); // destructor
  TemplatedMy_matrix(const TemplatedMy_matrix<T>& mat); // copy constructor
  TemplatedMy_matrix(TemplatedMy_matrix<T>&& mat);  // move constructor (optional)
  TemplatedMy_matrix<T>& operator=(const TemplatedMy_matrix<T>& mat); //copy assignment operator
  TemplatedMy_matrix<T>& operator=(TemplatedMy_matrix<T>&& mat); // move assignment operator (optional)
  int number_of_rows() const; 
  int number_of_columns() const;
  T* operator()(int i) const; // overloaded to access to ith row
  T& operator()(int i, int j); // overloaded to access (i,j) element
  T operator()(int i, int j) const; // overloaded to access (i,j) element
  T elem(int i, int j) const; // overloaded to access (i,j) element
  T& elem(int i, int j); // overloaded to access (i,j) element
};

// see the handout for the description of these operators
template<typename T> 
ostream& operator<<(ostream& out, const TemplatedMy_matrix<T>& mat);
template<typename T> 
istream& operator>>(istream& in, TemplatedMy_matrix<T>& mat);
template<typename T> 
TemplatedMy_matrix<T> operator+(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2);
template<typename T> 
TemplatedMy_matrix<T> operator*(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2);


/* 
Implementation of the clas My_matrix
*/

template<typename T> 
TemplatedMy_matrix<T>::TemplatedMy_matrix()
{
  n = 0;
  m = 0;
  ptr = nullptr;
}

template<typename T> 
void TemplatedMy_matrix<T>::allocate_memory()
{
  ptr = new T*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new T[m];
}

template<typename T> 
TemplatedMy_matrix<T>::TemplatedMy_matrix(int n1, int m1)
{
  n = n1;
  m = m1;

  ptr = new T*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new T[m];
}

template<typename T> 
// copy constructor
TemplatedMy_matrix<T>::TemplatedMy_matrix(const TemplatedMy_matrix<T>& mat)
{
  n = mat.number_of_rows();
  m = mat.number_of_columns();

  ptr = new T*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new T[m];

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
    {
      ptr[i][j] = mat.elem(i, j);
    }
  }
}

template<typename T> 
// move constructor (optional)
TemplatedMy_matrix<T>::TemplatedMy_matrix(TemplatedMy_matrix&& mat)
{
  n = mat.n;
  m = mat.m;
  ptr = mat.ptr;

  mat.ptr = nullptr;
  mat.n = 0;
  mat.m = 0;
}

template<typename T> 
TemplatedMy_matrix<T>::~TemplatedMy_matrix()
{
  for(int i = 0; i < n; ++i)
    delete[] ptr[i];

  delete[] ptr;
}

template<typename T> 
// copy assignment
TemplatedMy_matrix<T>& TemplatedMy_matrix<T>::operator=(const TemplatedMy_matrix<T>& mat)
{
  n = mat.number_of_rows();
  m = mat.number_of_columns();

  ptr = new T*[n];

  for(int i = 0; i < n; ++i)
    ptr[i] = new T[m];

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
    {
      ptr[i][j] = mat.elem(i, j);
    }
  }

  return *this;
}

template<typename T> 
// move assignment operator (optional)
TemplatedMy_matrix<T>& TemplatedMy_matrix<T>::operator=(TemplatedMy_matrix<T>&& mat)
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

template<typename T> 
int TemplatedMy_matrix<T>::number_of_rows() const
{
  return n;
}

template<typename T> 
int TemplatedMy_matrix<T>::number_of_columns() const
{
  return m;
}

template<typename T> 
T* TemplatedMy_matrix<T>::operator()(int i) const
{
  return ptr[i];
}

template<typename T> 
T TemplatedMy_matrix<T>::operator()(int i, int j) const
{
  return ptr[i][j];
}

template<typename T> 
T& TemplatedMy_matrix<T>::operator()(int i, int j)
{
  return ptr[i][j];
}

template<typename T> 
T TemplatedMy_matrix<T>::elem(int i, int j) const
{
  if (i < 0 || i >= n)
    throw out_of_range("Out of range");

  if (j < 0 || j >= m)
    throw out_of_range("Out of range");
  
  return ptr[i][j];
}

template<typename T> 
T& TemplatedMy_matrix<T>::elem(int i, int j)
{
  if (i < 0 || i >= n)
    throw out_of_range("Out of range");

  if (j < 0 || j >= m)
    throw out_of_range("Out of range");

  return ptr[i][j];
}

template<typename T> 
ostream& operator<<(ostream& out, const TemplatedMy_matrix<T>& mat)
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

template<typename T> 
istream& operator>>(istream& in, TemplatedMy_matrix<T>& mat)
{
  int nTemp;
  int mTemp;

  in >> nTemp >> mTemp;

  TemplatedMy_matrix<T> maTemp = TemplatedMy_matrix<T>(nTemp, mTemp);

  for(int i = 0; i < nTemp; ++i)
  {
    for(int j = 0; j < mTemp; ++j)
    {
      T temp;
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

  T temp1;

  if(in >> temp1)
  {
    cout << "There are more inputs in the file." << endl;
    exit(EXIT_FAILURE);
  }

  mat = maTemp;

  return in;
}

template<typename T> 
TemplatedMy_matrix<T> operator+(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2)
{
  
  if(mat1.number_of_rows() != mat2.number_of_rows() || mat1.number_of_columns() != mat2.number_of_columns())
  {
    cout << "Error: Incompitable Matrices" << endl;
    exit(EXIT_FAILURE);
  }
  
  int n = mat1.number_of_rows();
  int m = mat1.number_of_columns();

  TemplatedMy_matrix<T> mTemp = TemplatedMy_matrix<T>(n, m);

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
      mTemp.elem(i, j) = mat1.elem(i, j) + mat2.elem(i, j);
  }

  return mTemp;
  
}

template<typename T> 
TemplatedMy_matrix<T> operator*(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2)
{
  if(mat1.number_of_columns() != mat2.number_of_rows())
  {
    cout << "Error: Incompitable Matrices" << endl;
    exit(EXIT_FAILURE);
  }

  int n = mat1.number_of_rows();
  int m = mat2.number_of_columns();

  TemplatedMy_matrix<T> mTemp = TemplatedMy_matrix<T>(n, m);

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
