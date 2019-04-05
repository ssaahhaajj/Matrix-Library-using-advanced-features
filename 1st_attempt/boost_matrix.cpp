#include<iostream>
#include <time.h>
#include "boost_matrix.h"

using namespace std;

int main()
{

    clock_t start, end;
 //////////////////////////// example for integer matrix ////////////////   
    cout<<"Enter two integer 2x2 matrices:\n";
    
    Matrix<int> m1(2,2);
    std::cin>>m1;
    Matrix<int> m2(2,2);
    std::cin>>m2;
    cout<<"\n";

    start=clock();
    std::cout<<m1+m2<<"\n";
    end=clock();
    cout << "int Time for addition per n "<< (double)(end-start)/(CLOCKS_PER_SEC*2)<<"sec \n\n";

    start=clock();
    std::cout<<m1-m2<<"\n";
    end=clock();
    cout << "int Time for subtraction per n "<< (double)(end-start)/(CLOCKS_PER_SEC*2)<<"sec \n\n";

    start=clock();
    std::cout<<m1*m2<<"\n";
    end=clock();
    cout << "int Time for multiplication per n "<< (double)(end-start)/(CLOCKS_PER_SEC*2)<<"sec \n\n";
    
//////////////////// example for float matrix ////////////////////    
    cout<<"Enter two float 2x2 matrices:\n";

    Matrix<float> m3(2,2);
    std::cin>>m3;
    Matrix<float> m4(2,2);
    std::cin>>m4;

    start=clock();
    std::cout<<m3+m4<<"\n";
    end=clock();
    cout << "float Time for addition per n "<< (double)(end-start)/(CLOCKS_PER_SEC*2)<<"sec \n\n";

    start=clock();
    std::cout<<m3-m4<<"\n";
    end=clock();
    cout << "float Time for subtraction per n "<< (double)(end-start)/(CLOCKS_PER_SEC*2)<<"sec \n\n";

    start=clock();
    std::cout<<m3*m4<<"\n";
    end=clock();
    cout << "float Time for multiplication per n "<< (double)(end-start)/(CLOCKS_PER_SEC*2)<<"sec \n\n";

    std::cout<<"done!";
}
