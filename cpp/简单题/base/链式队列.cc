#include <iostream>
#include <cstring>
using namespace std;
class CQueue
{
private:
    struct Node
    {
        /* data */
        Node(int data=0): data_(data), next_(nullptr), pre_(nullptr)
        {

        }
        int data_;
        Node* next_;
        Node* pre_;
    };
    Node* head_;
public:
    CQueue()
    {
        head_ = new Node(0);
        head_->next_ = head_;
        head_->pre_ = head_;
    }
    ~CQueue()
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

    void push(int val)
    {
        Node* p = head_->pre_;
        Node* node = new Node(val);
        node->next_ = head_;
        node->pre_ = p;
        p->next_ = node;
        head_->pre_ = node;
    }
    void pop()
    {
        if(isempty()) throw "empty";
        Node* p = head_->next_;
        head_ = p->next_;
        p->next_->pre_ = head_;
        delete p;
    }
    bool isempty()
    {
        return head_->next_ == head_;
    }
    int front()
    {
        if(isempty()) throw "empty";
        return head_->next_->data_;
    }
    int back()
    {
        if(isempty()) throw "empty";
        return head_->pre_->data_;
    }
};