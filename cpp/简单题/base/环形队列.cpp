#include <iostream>
#include <cstring>
using namespace std;

class Queue
{
public:
    Queue(int size = 10): cap_(size),front_(0),rear_(0),size_(0)
    {
        pque_ = new int[cap_];
    }
    ~Queue()
    {
        delete[] pque_;
        pque_ = nullptr;
    }
    void push(int val)
    {
        if((rear_+1)%cap_ == front_)
        {
            extend(2 * cap_);
        }
        pque_[rear_] = val;
        rear_ = (rear_+1)%cap_;
        size_++;

    }
    void pop()
    {
        if(front_ == rear_) throw "empty";
        front_ = (front_+1)%cap_;
        size_--;
    }
    int front()
    {
        if(front_ == rear_) throw "empty";    
        return pque_[front_];     
    }
    int back()
    {

        if(front_ == rear_) throw "empty";
        return pque_[(rear_-1+cap_)%cap_];        
    }
    bool isempty()
    {
        return front_==rear_;
    }
    int size()
    {
        return size_;
    }
private:
    int* pque_;
    int cap_;
    int front_;
    int rear_;
    void extend(int data)
    {
        int* p = new int[data];
        int index = 0;
        for(int i = front_; i != rear_; i = (i+1)%cap_)
        {
            p[index++] = pque_[i];
        }
        delete[] pque_;
        pque_ = p;
        front_ = 0;
        rear_ = index;
        cap_ = data;
    }
    int size_;
};