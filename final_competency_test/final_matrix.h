
//Library for matrix arithmetics
/*
 ============================================================================
 Name        - final_matrix.h
 Author      - Sahaj Jain (ssaahhaajj@gmail.com)
 Description - File includes simple matrix algebra (+,-,+=,-=,*)(both scalar and matrix)
 ============================================================================
 */
#ifndef FINAL_MATRIX_H

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

 struct nxm
 {
  int row_no,col_no;
 };

//  plus_op for elementwise addition

struct plus_op {
  template <typename T, typename TT>
  auto operator()(const T &mat1, const TT &mat2, const size_t &i, const size_t &j) const 
  {
    assert(mat1.dimensn().row_no==mat2.dimensn().row_no && mat1.dimensn().col_no==mat2.dimensn().col_no);
    return mat1(i, j) + mat2(i, j);
  }
};

//  sub_op for elementwise subtraction

struct sub_op {
  template <typename T, typename TT>
  auto operator()(const T &mat1, const TT &mat2, const size_t &i, const size_t &j) const 
  {
    assert(mat1.dimensn().row_no==mat2.dimensn().row_no && mat1.dimensn().col_no==mat2.dimensn().col_no);
    return mat1(i, j) - mat2(i, j);
  }
};
//   scal_mul_op for scalar multiplication

struct scal_mul_op {
  template <typename T, typename TT>
  auto operator()(const T &mat1, const TT &ele, const size_t &i, const size_t &j) const 
  {
    return mat1(i, j) * ele;
  }
};

//  scal_mul_op for scalar multiplication

struct matrix_mul_op {
  template <typename T, typename TT>
  auto operator()(const T &mat1, const TT &mat2, const size_t &i,const size_t &j) const {
      assert(mat1.dimensn().col_no==mat2.dimensn().row_no);
    auto temp1=mat1.dimensn().col_no;  // no of columns
    auto temp2=0;
    while(temp1!=0)
    {
      temp2+=mat1(i,temp1-1)*mat2(temp1-1,j);
      temp1--;
    }
    return temp2;
  }
};

//    Expression class for the building expression for further lazy evaluation

template<typename T, typename TT, typename op> class expression {

public:
  //    parameterised constructor
  expression(const T &m1, const TT &m2, op o)
      : mat1(m1), mat2(m2), n(m1.dimensn().row_no), m(m2.dimensn().col_no),
        oper(o) {}

  //     Gives the dimensions nXm of matrix expression built
  nxm dimensn() const 
  { 
    nxm dim;
    dim.row_no=n;
    dim.col_no=m;
    return dim; 
  }

  //  operator overloading of <<
  friend std::ostream &operator<<(std::ostream &os, expression<T, TT, op> &mat) {
    size_t n = mat.dimensn().row_no;
    size_t m = mat.dimensn().col_no;

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) 
      {
        os << mat(i, j) <<" ";
      }
      os <<"\n";
    }
    return os;
  }

 //   operator overloading of +
  template <typename T2> 
  auto operator+(const T2 &mat) {
    return expression<expression<T, TT, op>, T2, plus_op>(*this,mat,plus_op());
  }

  //   operator overloading of -
  template <typename T2> 
  auto operator-(const T2 &mat) {
    return expression<expression<T, TT, op>, T2, sub_op>(*this,mat,sub_op());
  }

  //   operator overloading of *
  template <typename T2> 
  auto operator*(const T2 &mat) {
    return expression<expression<T, TT, op>, T2, scal_mul_op>(*this,mat,scal_mul_op());
  }

  // operator overloading of ~ as a symbol for matrix multiplication
  template <typename T2> 
  auto operator^(const T2 &mat) {
    return expression<expression<T, TT, op>, T2,matrix_mul_op>(*this,mat,matrix_mul_op());
  }
  // operator overloading () to get the i,j element of the expression evaluation obtainied 
  auto operator()(const size_t &i, const size_t &j) const {
    return oper(mat1,mat2,i,j);
  }

  private:
      const T &mat1;
      const TT &mat2;     
      op oper;
      const size_t n;
      const size_t m;
};

// following row major

template <typename T>
class row_major {

   auto operator()(const size_t &i, const size_t &j, const T &ta) const {
    return ta.lazy[i * ta.m + j];
  }
  
   auto& operator()(const size_t &i, const size_t &j, T &ta) {
    return ta.lazy[i * ta.m + j];
  }
};

//  Class for lazy matrix assuming vector to be the container

template <typename T> 
class lazy_genre{
private:
  std::vector<T> lazy;
  const size_t n;
  const size_t m;

public:
  //  default constructor
  lazy_genre() {}

  //   parameterised constructor with size provided
  lazy_genre(const std::size_t &rowno, const std::size_t &colno){
    std::vector<T> vec[rowno * colno];
    lazy=vec;
    n=rowno;
    m=colno;
    } 

  //   parameterised constructor with size and initial value provided
  lazy_genre(const std::size_t &rowno, const std::size_t &colno,const T &initi){
    std::vector<T> vec[rowno * colno](initi);
    lazy=vec;
    n=rowno;
    m=colno;
    }

  //  Initialization with an expression
  template <typename R1, typename R2, typename R3>
  lazy_genre(const expression<R1, R2, R3> &exp) {
    n=exp.dimensn().row_no;
    m=exp.dimensn().col_no;

      for (size_t i = 0; i < n; i++) 
        for (size_t j = 0; j < m; j++) {
          lazy.push_back(exp(i, j));
        }    
  }

  // Gives the dimensions of the matrix
  nxm dimensn() const 
  { 
    nxm dim;
    dim.row_no=n;
    dim.col_no=m;
    return dim; 
  }
  //   Overloading = operator
  template <typename R1> 
  lazy_genre operator=(const R1 &sec) {
  assert(dimensn().row_no==sec.dimensn().row_no && dimensn().col_no==sec.dimensn().col_no);
  for (size_t i = 0; i < n; i++) 
      for (size_t j = 0; j < m; j++) {
        (*this)(i, j) = sec(i, j);
      }
    return *this;
  }

  //  Overloading == operator
  template <typename R1> 
  bool operator==(const R1 &sec) {
    if (dimensn().row_no!=sec.dimensn().row_no && dimensn().col_no!=sec.dimensn().col_no) {
      return false;
    }
    for (size_t i = 0; i < n; i++) 
      for (size_t j = 0; j < m; j++) 
        if ((*this)(i, j) != sec(i, j)) {
          return false;
        }
      
    return true;
  }

  //  Overloading + operator
  template <typename R1> 
  auto operator+(const R1 &sec) {
  assert(dimensn().row_no==sec.dimensn().row_no && dimensn().col_no==sec.dimensn().col_no);
    return expression<lazy_genre<T>, R1, plus_op>(*this, sec, plus_op());
  }
  //   overloading +=operator
  template <typename R1> 
  void operator+=(const R1 &sec) {
    *this = *this + sec;
  }
  //  Overloading - operator
  template <typename R1> 
  auto operator-(const R1 &sec) {
  assert(dimensn().row_no==sec.dimensn().row_no && dimensn().col_no==sec.dimensn().col_no);
    return expression<lazy_genre<T>, R1, sub_op>(*this, sec, sub_op());
  }
  //   overloading -=operator
  template <typename R1> 
  void operator-=(const R1 &sec) {
    *this = *this - sec;
  }

  //  Overloading * operator 
  template <typename R1> 
  auto operator*(const R1 &sec) {
  assert(dimensn().row_no==sec.dimensn().row_no && dimensn().col_no==sec.dimensn().col_no);
    return expression<lazy_genre<T>, R1, scal_mul_op>(*this, sec, scal_mul_op());
  }

  //  Overloading *= operator 
  template <typename R1> void operator*=(const R1 &other) {
    *this = (*this) * other;
  }

  //  Overloading ^ operator for matrix multiplication
  template <typename R1> 
  auto operator^(const R1 &sec) {
      assert(dimensn().col_no==sec.dimensn().row_no);
    return expression<lazy_genre<T>, R1, matrix_mul_op>(*this, sec, matrix_mul_op());
  }

  //  Overloading ^= operator
  template <typename R1>
  void operator^=(const R1 &sec) {
    *this = (*this) ^ sec;
  }
  
  //  Operator () Overloading for getting the (i,j)th element
  
  inline const T operator()(const std::size_t i, const std::size_t j) const {
    return row_major<T>(i, j, *this);
  }
  inline T &operator()(const std::size_t i, const std::size_t j) {
    return row_major<T>(i, j, *this);
  }
 
  //   Oveloading operator << to use std:: cout
  friend std::ostream &operator<<(std::ostream &os,lazy_genre<T> &lazy2) {
    size_t n = lazy2.dimensn().row_no;
    size_t m = lazy2.dimensn().col_no;
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) {
        os << lazy2(i, j) << ' ';
      }
      os <<"\n";
    }
    return os;
  }
};
#endif
