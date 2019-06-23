// main.cpp
// Tests all functionality of the class My_matrix class.

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "TemplatedMy_matrix.h"

int main(){
  
  // Some test cases are expected to throw an exception.
  // Add more try and catch blocks as necessary for your code
  // to finish execution.
    
  try{
    
    // Test 1
    // * Create an object of type My_matrix, called m1, using constructor
    // * Initialize m1 in main (by assigning numbers to matrix elements)
    // * Display m1 on the screen using the operator <<
    TemplatedMy_matrix<int> m1 = TemplatedMy_matrix<int>(3, 3);

    for(int i = 0; i < m1.number_of_rows(); ++i)
    {
        for(int j = 0; j < m1.number_of_columns(); ++j)
            m1.elem(i, j) = i + j;
    }

    cout << "A 3x3 matrix named m1:" << endl;
    cout << m1 << endl;
    
    // Test 2
    // * Create an object of type My_matrix, called m2, using (default)
    //   constructor
    // * Open an input file containing a matrix (row by row)
    // * Initialize m2 by reading from the input file using
    //   the operator >>
    // * Open an output file (can be empty)
    // * Write m2 to the output file using the operator <<
      ifstream inFile;
      inFile.open("input.txt");

    TemplatedMy_matrix<int> m2;
    inFile >> m2;

      ofstream outFile;
      outFile.open("output.txt");
    outFile << m2;
    
    // Test 3
    // * Use the copy constructor to make a copy of m1 called m3
    // * Apply the copy assignment to m1 called m4
    // * Display m3 and m4 on the screen using the operator <<
    TemplatedMy_matrix<int> m3 = m1;

    TemplatedMy_matrix<int> m4;

    m4 = m1;

    cout << "Set matrix m3 to m1 using a copy constructor:" << endl;
    cout << m3 << endl << "Set matrix m4 to m1 using the copy assignment operator: " << m4 << endl;

    // Test 4
    // * Test the matrix multiplication operator (operator*)
    // * Apply the multiplication operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
    TemplatedMy_matrix<int> m5;

    m5 = m1 + m4;

    cout << "Sum of matrices m1 and m4:" << endl;
    cout << m5 << endl;
   
    // Test 5   
    // * Test the matrix addition operator (operator+)
    // * Apply the addition operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
    TemplatedMy_matrix<int> m7;

    m7 = m1 * m4;

    cout << "Multiplication of matrices m1 and m4:" << endl;
    cout << m7 << endl;

  } catch(exception &error){
    cerr << "Error: " << error.what() << endl;
  }
}
