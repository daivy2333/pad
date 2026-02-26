#include <iostream>
using namespace std;

class LStack
{
private:
    struct Node
    {
        int data_;
        Node* next_;
        Node(int val = 0) : data_(val), next_(nullptr) {}
    };

    Node* head_;
    int size_;

public:
    LStack() : head_(new Node), size_(0) {
        size_ = 0;
    } // 使用初始化列表
    ~LStack()
    {
        Node* p = head_;
        while (p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

    void push(int data)
    {
        Node* node = new Node(data);
        node->next_ = head_->next_;
        head_->next_ = node;
        size_++;
    }

    void pop()
    {
        if (isempty()) throw "Stack is empty"; // 更清晰的错误信息
        Node* node = head_->next_;
        head_->next_ = head_->next_->next_;
        delete node;
        size_--;
    }

    int top()
    {
        if (isempty()) throw "Stack is empty"; // 添加空栈检查
        return head_->next_->data_;
    }

    bool isempty()
    {
        return head_->next_ == nullptr;
    }

    int size()
    {
        return size_;
    }
}; // 注意这里的分号

int main()
{
    LStack stack;
    stack.push(10);
    stack.push(20);
    cout << "Top: " << stack.top() << endl; // 输出 20
    stack.pop();
    cout << "Top: " << stack.top() << endl; // 输出 10
    cout << "Size: " << stack.size() << endl; // 输出 1
    stack.pop();
    cout << "Is empty: " << (stack.isempty() ? "Yes" : "No") << endl; // 输出 Yes

    try
    {
        stack.pop(); // 会抛出异常
    }
    catch (const char* msg)
    {
        cerr << "Error: " << msg << endl;
    }

    return 0;
}
