#include <iostream>
using namespace std;

class greet
{
    private:

    void hi()
    {
        cout<<"hi"<<endl;
    }
    public:
    void say()
    {
        hi();
    }
};

int main()

{
    greet g;

    g.say();
    return 0;
}