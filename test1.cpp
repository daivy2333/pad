#include <iostream>
#include <random>
using namespace std;

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);
    int randomNumber = distrib(gen);
    cout << randomNumber << endl;
    
    int you_in;
    do
    {
        cin >> you_in;
        if (you_in > randomNumber)
            cout << "有点大了" << endl;
        if (you_in < randomNumber)
            cout << "有点小了" << endl;
        if (you_in == randomNumber)
            cout << "对了" << endl;
    } while (you_in != randomNumber);
    
    return 0;
}
