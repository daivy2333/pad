#include <iostream>
#include <cstring>
using namespace std;
#include <queue>

class QStack
{
private:
    queue<int> q1;
    queue<int> q2;
public:
    QStack()
    {

    }
    ~QStack()
    {

    }

    void push(int val)
    {
        q1.push(val);
        while(!q2.empty())
        {
            q1.push(q2.front());
            q2.pop();
        }
        swap(q1, q2);
    }
    void pop()
    {
        q2.pop();
    }

    int top()
    {
        return q2.front();
    }

    bool empty()
    {
        return q2.empty();
    }
};