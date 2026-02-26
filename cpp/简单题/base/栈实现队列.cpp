#include <iostream>
#include <cstring>
#include<stack>
using namespace std;

class SQueue
{
private:
    stack<int> s1;
    stack<int> s2;
public:
    SQueue()
    {

    }
    ~SQueue()
    {

    }
    void push(int val)
    {
        s1.push(val);
    }

    int pop()
    {
        if(s2.empty())
        {
            while(!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }

        int val = s2.top();
        s2.pop();
        return val;
    }
    int peek()
    {
        if(s2.empty())
        {
            while(!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    bool isempty()
    {
        return s1.empty() && s2.empty();
    }
};