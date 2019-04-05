#include<iostream>
#include <time.h>
#include "2nd_attempt.h"

using namespace std;
/* a simple test program testing the matrix_arithm.h library */
int main()
{
    clock_t start, end;   // variables for time calculations

    Matrix<int,2,2> tt1;  // simple checking << and >> operator
      cin>>tt1;
      cout<<tt1;
    
    Matrix<int,2,2> tt2;
      std::cin>>tt2;
      std::cout<<tt2;
 
    Matrix<int,2,2> tt3;

    start = clock();
    tt3=tt1+2;
    end = clock();

    cout<<tt3;

    cout << "Time required for scalar addition(+): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";

    start = clock();
    tt3=tt1-2;
    end = clock();

    cout<<tt3;

    cout << "Time required for scalar subtraction(-): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";

    start = clock();
    tt3=tt1*2;
    end = clock();

    cout<<tt3;

    cout << "Time required for scalar multiplication(*): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";
   
    start = clock();
    tt1+=tt2;
    end = clock();

    cout<<tt1;

    cout << "Time required for scalar addition(+=): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";

    start = clock();
    tt1-=tt2;
    end = clock();

    cout<<tt1;

    cout << "Time required for scalar subtraction(-=): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";

    Matrix<int,2,2> tt4;
    start = clock();
    tt4=tt1+tt2;
    end = clock();

    cout<<tt4;

    cout << "Time required for elementwise addition(+): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";
   
    Matrix<int,2,2> tt5;
    start = clock();
    tt5=tt1-tt2;
    end = clock();

    cout<<tt5;

    cout << "Time required for elementwise subtraction(-): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";

    Matrix<int,2,2> tt6;
    start = clock();
    tt6=tt1*tt2;
    end = clock();

    cout<<tt6;

    cout << "Time required for elementwise multipllication(*): "<< (double)(end-start)/CLOCKS_PER_SEC<< " sec." << "\n\n";
    
    // for output screenshot 
    // https://drive.google.com/file/d/1VSmCMooWhnYXCXODqFFAe2GTMm_cb1N_/view?usp=sharing
      
}
