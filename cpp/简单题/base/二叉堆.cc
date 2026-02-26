#include <iostream>
#include <cstring>
#include<functional>
using namespace std;

class PQueue
{
public:
    using Comp = function<bool(int,int)>;
    PQueue(int cap=20, Comp comp = greater<int>()):
    size_(0),cap_(cap),comp_(comp)
    {
        que_ = new int[cap_];
    }
    PQueue(Comp comp = greater<int>()):
    size_(0),cap_(20),comp_(comp)
    {
        que_ = new int[cap_];
    }
    ~PQueue()
    {
        delete[]que_;
        que_ = nullptr;
    }
    void push(int val)
    {
        if(size_ == cap_)
        {
            int* p = new int[2*cap_];
            memcpy(p,que_,cap_*sizeof(int));
            delete[] que_;
            que_ = p;
            cap_ *= 2;
        }
        if(size_ == 0) que_[size_] = val;
        else
        {
            shiftup(size_, val);
        }
        size_++;
    }
    void pop()
    {
        if(size_ == 0) throw "empty";
        size_--;
        if(size_ > 0)
        {
            shiftdown(0, que_[size_]);
        }
    }
    bool empty()
    {
        return size_ == 0;
    }
    int top()
    {
        if(size_ == 0) throw "empty";
        return que_[0];
    }

    int size()
    {
        return size_;
    }
private:
    int* que_;
    int size_;
    int cap_;
    Comp comp_;
    void shiftup(int i, int val)
    {
        while(i>0)
        {
            int father = (i-1)/2;
            if(comp_(val, que_[father]))
            {
                que_[i] = que_[father];
                i = father;
            }
            {
                break;
            }
        }
        que_[i] = val;
    }
    void shiftdown(int i, int val)
    {
        while(i < size_ /2)
        {
            int child = 2*i+1;
            if(child+1 < size_ && comp_(que_[child+1], que_[child]))
            {
                child = child+1;
            }  
            
            if(comp_(que_[child], val))
            {
                que_[i] = que_[child];
                i = child;
            }
        }
        que_[i] = val;
    }
};