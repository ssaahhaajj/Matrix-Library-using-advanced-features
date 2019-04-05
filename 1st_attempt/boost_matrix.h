#include <iostream>
#include <cassert>
#include<time.h>

template <class t>class Matrix
{
  int rows;    // private data members
  int cols;
  t **Mat;

  public:
    Matrix (const int &rows,const int &cols);
    Matrix(const Matrix &other);
    ~Matrix ();
    t* & operator[](const int &index) const ;
    void operator=(const Matrix<t> &other );
    Matrix<t>  operator -(const Matrix<t> &other)const;
    Matrix<t>  operator +(const Matrix<t> &other)const ;
    Matrix<t>  operator *(const Matrix<t> &other)const;
    Matrix<t>  operator *=(const int &num)const;
    Matrix<t>  operator *(const int &num)const;
    t getMatrixRows(const Matrix<t> &other){return other.rows;}
    t getMatrixCols(const Matrix<t> &other){return other.cols;}

    friend  Matrix<t> operator *(const t & num,const Matrix<t> &m)
    {
     return (m*num);
    }

    friend Matrix<t> operator +(const t &num,const Matrix<t> &k)
    {
     return (num+k);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<t> &m) {
    for (int i=0; i < m.rows; ++i) {
        for (int j=0; j < m.cols; ++j) {
            os << (t)m.Mat[i][j] << "  " ;
        }
        os << '\n';
    }
    return os;
    }
    friend std::istream &operator>>(std::istream &is, const Matrix<t> &m) {
    for (int i=0; i < m.rows; ++i) {
        for (int j=0; j < m.cols; ++j) {
            is >> m.Mat[i][j];
        }
    }
    return is;
    }

};

template <class t>
 Matrix<t>::Matrix(const int &n_rows,const int &n_cols )//constructor of class Matrix
{
    rows=n_rows; 
    cols=n_cols;
    Mat=new t* [cols];
    assert(Mat);             // checker1
    for(int i =0;i<rows;i++)
    {
       Mat[i]=new t[cols];
       assert(Mat[i]);      // checker2
    }
    for(int i=0;i<rows;i++)
      for(int j=0;j<cols;j++)
        Mat[i][j]=(t)0;       
}
template <class t>
 Matrix<t>::Matrix(const Matrix<t> &other)  //copy constructor
{
    cols=other.cols;
    rows=other.rows;
    Mat=new t* [other.rows];
    assert(Mat);
    for(int i =0;i<other.rows;i++)
    {
       Mat[i]=new t[other.cols];
       assert(Mat[i]);
    }
    for(int i=0;i<other.rows;i++)
      for(int j=0;j<other.cols;j++)
            Mat[i][j]=(t)other[i][j];
}

template <class t>
t* & Matrix<t>::operator [](const int &index) const  // overloading operator []
{
  return  Mat [index];
}
template <class t>
void Matrix<t>::operator=(const Matrix<t> &other )   // overloading operator =
{
    if(cols==other.cols && rows==other.rows)
     {
       for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            Mat[i][j]=other.Mat[i][j];
     }
}

template <class t>
 Matrix<t>  Matrix<t>::operator +(const Matrix<t> &other)const  //matrix addition
{
    Matrix<t> temp(rows,cols);  
    if (rows!=other.rows ||cols!=other.cols)
    {
       for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            temp.Mat[i][j]=Mat[i][j];
       return temp;
    }
    else
     {      
         for(int i=0;i<rows;i++)
             for(int j=0;j<cols;j++)
                 temp.Mat[i][j]=(t)other.Mat[i][j]+Mat[i][j];
     }
    return temp; 
}

template <class t>
Matrix<t>  Matrix<t>::operator -(const Matrix<t> &other)const //matrix subtraction 
{
    Matrix<t> temp(rows,cols);  
    if (rows!=other.rows ||cols!=other.cols)
    {
       for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            temp.Mat[i][j]=Mat[i][j];
       return temp;
    }
    else
     {

         for(int i=0;i<rows;i++)
             for(int j=0;j<cols;j++)
                 temp.Mat[i][j]=(t)Mat[i][j]-other.Mat[i][j];
     }
    return temp;
}

template <class t>
Matrix<t>  Matrix<t>::operator *(const int &num)const   //multiply with number
{
    Matrix<t> temp(rows,cols);
    for(int i=0;i<rows;i++)
       for(int j=0;j<cols;j++)
            temp.Mat[i][j]=(t)Mat[i][j]*num;
    return temp; 
}

template <class t>
Matrix<t>  Matrix<t>::operator *=(const int &num)const   //multiply with number
{
    Matrix<t> temp(rows,cols);
    for(int i=0;i<rows;i++)
       for(int j=0;j<cols;j++)
            temp.Mat[i][j]=(t)Mat[i][j]*num;
    return temp; 
}
template <class t>
Matrix<t>  Matrix<t>::operator *(const Matrix<t> &other)const   //multiply matrix on the right
{
    if (cols!=other.rows)
    {
      Matrix temp(cols,rows);
      for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            temp.Mat[i][j]=Mat[i][j];
      return temp;
    }
    else
    {
      Matrix<t> temp(cols,other.rows);  
      for(int i=0;i<rows;i++)
          for(int j=0;j<other.cols;j++)
            for(int k =0;k<cols;k++)
                temp[i][j]=(t)temp[i][j]+(t)(Mat[i][k]*other.Mat[k][j]);
      return temp;          
    }
}

template <class t>
Matrix<t>::~Matrix ()      //destructor 
{
 for(int i =0;i<rows;i++)
   delete [] Mat[i]; 
 delete [] Mat;

}

