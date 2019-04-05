/*
============================================================================
 Name        - matrix_arithm.h
 Author      - Sahaj Jain (ssaahhaajj@gmail.com)
 Description - File includes simple matrix algebra (+,-,+=,-=,*)(both scalar and matrix)
============================================================================
*/
#ifndef _2nd_attempt_h

#include<iostream>
#include<cassert>

/* ..............................................................................................*/
template<typename T, size_t n, size_t m,typename LeftOp, typename RightOp>
class EtMatrixAdd            // for matrix addition 
{
public:
  EtMatrixAdd(const LeftOp& lhs, const RightOp& rhs) : 
    m_lhs(lhs), m_rhs(rhs) {}
 
  T ElementAt(size_t nn, size_t mm) const
  { return m_lhs.ElementAt(nn, mm) + m_rhs.ElementAt(nn, mm); }

  int row() const {return n;}      // return the row count of matrix
  int col() const {return m;}      // return column count of matrix   
 
private:
  const LeftOp& m_lhs;
  const RightOp& m_rhs;
};
/* ..............................................................................................*/

template<typename T, size_t n, size_t m,typename LeftOp, typename RightOp>
class EtMatrixSub           // for matrix subtraction
{
public:
  EtMatrixSub(const LeftOp& lhs, const RightOp& rhs) : 
    m_lhs(lhs), m_rhs(rhs) {}
 
  T ElementAt(size_t nn, size_t mm) const
  { return m_lhs.ElementAt(nn, mm) - m_rhs.ElementAt(nn, mm); }

  int row() const {return n;}      // return the row count of matrix
  int col() const {return m;}      // return column count of matrix 
 
private:
  const LeftOp& m_lhs;
  const RightOp& m_rhs;
};
/* ..............................................................................................*/

template<typename T, size_t n, size_t m,typename LeftOp, typename RightOp>
class EtMatrixMul         // for matrix multilication 
{
public:
  EtMatrixMul(const LeftOp& lhs, const RightOp& rhs) : 
    m_lhs(lhs), m_rhs(rhs) {}
 
  T ElementAt(size_t nn, size_t mm) const
  { 
    T tmp=0;
    for(int i=0 ;i<m_rhs.row() ;i++)
    {
      tmp+=m_lhs.ElementAt(nn,i)*m_rhs.ElementAt(i,nn);
    }
    return tmp;
  }

  int row() const {return n;}      // return the row count of matrix
  int col() const {return m;}      // return column count of matrix 
 
private:
  const LeftOp& m_lhs;
  const RightOp& m_rhs;
};
/* ..............................................................................................*/
template<typename T, size_t n, size_t m,typename LeftOp>
class EtMatrixMulScal            // for matrix sclar multiplication 
{
public:
  EtMatrixMulScal(const LeftOp& lhs, const T& num) : 
    m_lhs(lhs), dig(num) {}
 
  T ElementAt(size_t nn, size_t mm) const
  { return m_lhs.ElementAt(nn, mm)*dig; }

private:
  const LeftOp& m_lhs;
  const T& dig;
};
/* ..............................................................................................*/
template<typename T, size_t n, size_t m,typename LeftOp>
class EtMatrixAddScal           // for matrix sclar addition 
{
public:
  EtMatrixAddScal(const LeftOp& lhs, const T& num) : 
    m_lhs(lhs), dig(num) {}
 
  T ElementAt(size_t nn, size_t mm) const
  { return m_lhs.ElementAt(nn, mm)+dig; }

private:
  const LeftOp& m_lhs;
  const T& dig;
};
/* ..............................................................................................*/
template<typename T, size_t n, size_t m,typename LeftOp>
class EtMatrixSubScal            // for matrix sclar subtraction 
{
public:
  EtMatrixSubScal(const LeftOp& lhs, const T& num) : 
    m_lhs(lhs), dig(num) {}
 
  T ElementAt(size_t nn, size_t mm) const
  { return m_lhs.ElementAt(nn, mm)-dig; }
 
private:
  const LeftOp& m_lhs;
  const T& dig;
};
/* ..............................................................................................*/

template<typename T, size_t n, size_t m>
class Matrix      // general matix class 
{
public:
  /* ..............................................................................................*/

  Matrix(){}      // default constructor
 /* ..............................................................................................*/

 Matrix(const Matrix& rhs) {      // copy constructor
    for(int i=0; i<n; ++i)
      for(int j=0; j<m; ++j)
        ElementAt(i,j) = rhs.ElementAt(i,j);
  }
   
 Matrix& operator=(const Matrix& rhs) {     // overloading = operator
    if( this != &rhs )
      for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
          ElementAt(i,j) = rhs.ElementAt(i,j);
    return *this;
  }
  /* ..............................................................................................*/

  void operator+=(const Matrix& rhs) {      // overloading +=operator
    if( this != &rhs )
    {
      *this=*this+rhs;
    }
  }

   void operator-=(const Matrix& rhs) {      // overloading -= operator
    if( this != &rhs )
    {
      *this=*this-rhs;
    }
  }
  /* ..............................................................................................*/

  int row() const       // return the row count of matrix
  {
    return n;
  }
  int col() const       // return column count of matrix 
  {
    return m;
  }
  /* ..............................................................................................*/ 
  virtual ~Matrix() {}  // destructor
  /* ..............................................................................................*/
 
  const T& ElementAt(size_t nn, size_t mm) const   
   { return arrData[nn][mm]; }

  T& ElementAt(size_t nn, size_t mm)       
   { return arrData[nn][mm]; }

   /* ..............................................................................................*/

  friend std::ostream &operator<<(std::ostream &os, const Matrix<T,n,m> &mo) {  // overloading << operator
    for (int i=0; i < n; ++i) {
        for (int j=0; j < m; ++j) {
            os << mo.ElementAt(i,j) << "  " ;
        }
        os << '\n';
    }
    return os;
    }
  friend std::istream &operator>>(std::istream &is,  Matrix<T,n,m> &mo) {   // overloading >> operator
    for (int i=0; i < n; ++i) {
        for (int j=0; j < m; ++j) {
            is >> mo.ElementAt(i,j);
        }
    }
    return is;
    }
  /* ..............................................................................................*/

   template< typename TT, size_t nn, size_t mm, typename LeftOp, typename RightOp >
   Matrix<T, nn, mm>& operator=( const EtMatrixAdd<TT, nn, mm, LeftOp, RightOp>& rhs) // overloading = operator for EtMatrixAdd
    {
        for(int i=0; i<nn; ++i)
            for(int j=0; j<mm; ++j)
                ElementAt(i,j) = rhs.ElementAt(i,j);

        return *this; 
    }  
  /* ..............................................................................................*/

   template< typename TT, size_t nn, size_t mm, typename LeftOp, typename RightOp >  // overloading = operator for EtMatrixSub
   Matrix<TT, nn, mm>& operator=( const EtMatrixSub<TT, nn, mm, LeftOp, RightOp>& rhs)
    {
        for(int i=0; i<nn; ++i)
            for(int j=0; j<mm; ++j)
                ElementAt(i,j) = rhs.ElementAt(i,j);

        return *this; 
    } 
  /* ..............................................................................................*/

  template< typename TT, size_t nn, size_t mm, typename LeftOp, typename RightOp > // overloading = operator for EtMatrixMul
  Matrix<TT, nn, mm>& operator=( const EtMatrixMul<TT, nn, mm, LeftOp, RightOp>& rhs)
    {
        for(int i=0; i<nn; ++i)
            for(int j=0; j<mm; ++j)
                ElementAt(i,j) = rhs.ElementAt(i,j);

        return *this; 
    } 
  /* ..............................................................................................*/

   template< typename TT, size_t nn, size_t mm, typename LeftOp >  // overloading = operator for EtMatrixMulScal
   Matrix<TT, nn, mm>& operator=( const EtMatrixMulScal<TT, nn, mm, LeftOp>& rhs)
    {
        for(int i=0; i<nn; ++i)
            for(int j=0; j<mm; ++j)
                ElementAt(i,j) = rhs.ElementAt(i,j);

        return *this; 
    } 
  /* ..............................................................................................*/


   template< typename TT, size_t nn, size_t mm, typename LeftOp >  // overloading = operator for EtMatrixSubScal
   Matrix<TT, nn, mm>& operator=( const EtMatrixSubScal<TT, nn, mm, LeftOp>& rhs)
    {
        for(int i=0; i<nn; ++i)
            for(int j=0; j<mm; ++j)
                ElementAt(i,j) = rhs.ElementAt(i,j);

        return *this; 
    } 
  /* ..............................................................................................*/

   template< typename TT, size_t nn, size_t mm, typename LeftOp >  // overloading = operator for EtMatrixAddScal
   Matrix<TT, nn, mm>& operator=( const EtMatrixAddScal<TT, nn, mm, LeftOp>& rhs)
    {
        for(int i=0; i<nn; ++i)
            for(int j=0; j<mm; ++j)
                ElementAt(i,j) = rhs.ElementAt(i,j);

        return *this; 
    } 
  /* ..............................................................................................*/

 
private:
  T arrData[n][m];
};
/* ..............................................................................................*/

// overloading + operator #1
template<typename T, size_t n, size_t m>
inline EtMatrixAdd<T, n, m, Matrix<T, n, m>, Matrix<T, n, m> >
operator+(const Matrix<T, n, m>& lhs,const Matrix<T, n, m>& rhs) 
{
  assert(lhs.row()==rhs.row()&&lhs.col()==rhs.col());

  return EtMatrixAdd<T, n, m, Matrix<T, n, m>, Matrix<T, n, m> >(lhs, rhs);
}
 
// overloading + operator #2
template< typename T, size_t n, size_t m,typename LeftOp, typename RightOp>
inline EtMatrixAdd<T, n, m,EtMatrixAdd<T, n, m, LeftOp, RightOp>,Matrix<T, n, m> > 
operator+(const EtMatrixAdd<T, n, m, LeftOp, RightOp>& lhs,const Matrix<T, n, m>& rhs)
{
  assert(lhs.row()==rhs.row()&&lhs.col()==rhs.col());

  return EtMatrixAdd<T, n, m, EtMatrixAdd<T, n, m, LeftOp, RightOp>, Matrix<T, n, m> >(lhs, rhs);
}
/* ..............................................................................................*/

// overloading - operator #1
template<typename T, size_t n, size_t m>
inline EtMatrixSub<T, n, m, Matrix<T, n, m>, Matrix<T, n, m> >
operator-(const Matrix<T, n, m>& lhs,const Matrix<T, n, m>& rhs) 
{
  assert(lhs.row()==rhs.row()&&lhs.col()==rhs.col());

  return EtMatrixSub<T, n, m, Matrix<T, n, m>, Matrix<T, n, m> >(lhs, rhs);
}

 // overloading - operator #2
template< typename T, size_t n, size_t m,typename LeftOp, typename RightOp>
inline EtMatrixSub<T, n, m,EtMatrixSub<T, n, m, LeftOp, RightOp>,Matrix<T, n, m> > 
operator-(const EtMatrixSub<T, n, m, LeftOp, RightOp>& lhs,const Matrix<T, n, m>& rhs) 
{
  assert(lhs.row()==rhs.row()&&lhs.col()==rhs.col());

  return EtMatrixSub<T, n, m, EtMatrixSub<T, n, m, LeftOp, RightOp>, Matrix<T, n, m> >(lhs, rhs);
}
/* ..............................................................................................*/

// overloading * operator #1
template<typename T, size_t n, size_t m>
inline EtMatrixMul<T, n, m, Matrix<T, n, m>, Matrix<T, n, m> >
operator*(const Matrix<T, n, m>& lhs,const Matrix<T, n, m>& rhs) 
{
  assert(lhs.row()==rhs.row()&&lhs.col()==rhs.col());

  return EtMatrixMul<T, n, m, Matrix<T, n, m>, Matrix<T, n, m> >(lhs, rhs);
}
 
// overloading * operator #2
template< typename T, size_t n, size_t m,typename LeftOp, typename RightOp>
inline EtMatrixMul<T, n, m,EtMatrixMul<T, n, m, LeftOp, RightOp>,Matrix<T, n, m> > 
operator*(const EtMatrixMul<T, n, m, LeftOp, RightOp>& lhs,const Matrix<T, n, m>& rhs) 
{
   assert(lhs.row()==rhs.row()&&lhs.col()==rhs.col());

  return EtMatrixMul<T, n, m, EtMatrixMul<T, n, m, LeftOp, RightOp>, Matrix<T, n, m> >(lhs, rhs);
}
/* ..............................................................................................*/

// overloading *(scalar) operator #1
template<typename T, size_t n, size_t m>
inline EtMatrixMulScal<T, n, m, Matrix<T, n, m> >
operator*(const Matrix<T, n, m>& lhs,const T& num) 
{
  return EtMatrixMulScal<T, n, m, Matrix<T, n, m> >(lhs, num);
}
 
// overloading *(scalar) operator #2
template< typename T, size_t n, size_t m,typename LeftOp>
inline EtMatrixMulScal<T, n, m,EtMatrixMulScal<T, n, m, LeftOp> > 
operator*(const EtMatrixMulScal<T, n, m, LeftOp>& lhs,const T& num) 
{

  return EtMatrixMulScal<T, n, m, EtMatrixMulScal<T, n, m, LeftOp> >(lhs, num);
}
/* ..............................................................................................*/

// overloading -(scalar) operator #1
template<typename T, size_t n, size_t m>
inline EtMatrixSubScal<T, n, m, Matrix<T, n, m> >
operator-(const Matrix<T, n, m>& lhs,const T& num) 
{
  return EtMatrixSubScal<T, n, m, Matrix<T, n, m> >(lhs, num);
}
 
// overloading -(scalar) operator #2
template< typename T, size_t n, size_t m,typename LeftOp>
inline EtMatrixSubScal<T, n, m,EtMatrixSubScal<T, n, m, LeftOp> > 
operator-(const EtMatrixSubScal<T, n, m, LeftOp>& lhs,const T& num) 
{

  return EtMatrixSubScal<T, n, m, EtMatrixSubScal<T, n, m, LeftOp> >(lhs, num);
}
/* ..............................................................................................*/

// overloading +(scalar) operator #1
template<typename T, size_t n, size_t m>
inline EtMatrixAddScal<T, n, m, Matrix<T, n, m> >
operator+(const Matrix<T, n, m>& lhs,const T& num) 
{
  return EtMatrixAddScal<T, n, m, Matrix<T, n, m> >(lhs, num);
}
 
// overloading +(scalar) operator #2
template< typename T, size_t n, size_t m,typename LeftOp>
inline EtMatrixAddScal<T, n, m,EtMatrixAddScal<T, n, m, LeftOp> > 
operator+(const EtMatrixAddScal<T, n, m, LeftOp>& lhs,const T& num) 
{

  return EtMatrixAddScal<T, n, m, EtMatrixAddScal<T, n, m, LeftOp> >(lhs, num);
}
/* ..............................................................................................*/
#endif // MATRIX_ARITHM_H_
