#include<iostream>
using namespace std;

int main()
{
    int arr[10];
    for(int i=0; i<10; i++)
    {
        arr[i] = i;
    }
    int* p = arr+1;
    int& q = arr[2];
    cout<< *p<< endl;
    cout<< p+1<< endl;
    cout<< q << endl;
    cout<< &q<< endl;

}