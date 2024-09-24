#include <iostream>

// function to swap values of two integers
int swapIntegers(int* a, int* b){

    int placeholder_a = *a;
    int placeholder_b = *b;

    *a = placeholder_b;
    *b = placeholder_a;

    return 0;
}


int main() {

    int A[] = {1,2,3,4,5,6,7,8,9,0};
    int B[] = {0,9,8,7,6,5,4,3,2,1};

    std::cout<<"Array A = ";
    for (int i = 0; i < 10; i++) std::cout << A[i];
    std::cout<<std::endl;
    std::cout<<"Array B = ";
    for (int i = 0; i < 10; i++) std::cout << B[i];
    std::cout<<std::endl;

    for(int i = 0; i<10; i++) {
        swapIntegers(A+i, B+i);
    }

    std::cout<<"Array A = ";
    for (int i = 0; i < 10; i++) std::cout << A[i];
    std::cout<<std::endl;
    std::cout<<"Array B = ";
    for (int i = 0; i < 10; i++) std::cout << B[i];
    std::cout<<std::endl;

    return 0;
}
