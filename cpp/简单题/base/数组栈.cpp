#include<iostream>
#include <cstring>
using namespace std;

class Stack
{
public:
    Stack(int val=10):
        mtop(0),mcap(val)
        {
            my_stack = new int[mcap];
        };
    ~Stack()
    {
        delete[]my_stack;
        my_stack = nullptr;
    }
    void push(int val);
    void pop();
    int top();
    bool isempty();
    int size();
private:
    int* my_stack;
    int mtop;
    int mcap;
    void expand(int size)
    {
        int* p =new int[size];
        memcpy(p, my_stack, mtop*sizeof(int));
        delete[]my_stack;
        my_stack = p;
        mcap = size;
    }
};

void Stack::push(int val)
{
    if(mtop == mcap)
    {
        expand(2*mcap);
    }
    my_stack[++mtop] = val;
}

void Stack::pop()
{
    if(mtop == 0) return;
    mtop--;
}
int Stack::top()
{
    if(mtop == 0) throw "empty";
    return my_stack[mtop];
}
bool Stack::isempty()
{
    return mtop == 0;
}
int Stack::size()
{
    return mtop;
}

// 测试代码
void testStack() {
    cout << "===== 开始测试 Stack =====" << endl;
    
    // 测试1: 创建栈
    Stack s(5);
    cout << "测试1: 创建栈(容量5) - " << (s.isempty() ? "成功" : "失败") << endl;
    
    // 测试2: push操作
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "测试2: push(10,20,30) - " << (s.size() == 3 ? "成功" : "失败") << endl;
    
    // 测试3: top操作
    cout << "测试3: top() = " << s.top() << " (期望30) - " << (s.top() == 30 ? "成功" : "失败") << endl;
    
    // 测试4: pop操作
    s.pop();
    cout << "测试4: pop()后top() = " << s.top() << " (期望20) - " << (s.top() == 20 ? "成功" : "失败") << endl;
    cout << "测试4: pop()后size() = " << s.size() << " (期望2) - " << (s.size() == 2 ? "成功" : "失败") << endl;
    
    // 测试5: 扩容测试
    Stack s2(2);
    for(int i = 0; i < 5; i++) {
        s2.push(i * 10);
    }
    cout << "测试5: 扩容测试(初始容量2,压入5个元素) - " << (s2.size() == 5 ? "成功" : "失败") << endl;
    
    // 测试6: isempty操作
    Stack s3;
    cout << "测试6: 新建栈isempty() = " << (s3.isempty() ? "true" : "false") << endl;
    s3.push(100);
    cout << "测试6: push后isempty() = " << (s3.isempty() ? "true" : "false") << endl;
    
    // 测试7: 异常测试
    Stack s4;
    try {
        s4.top();
        cout << "测试7: 空栈top()异常 - 失败" << endl;
    } catch(const char* e) {
        cout << "测试7: 空栈top()异常 - 成功 (捕获到异常: " << e << ")" << endl;
    }
    
    cout << "===== 测试完成 =====" << endl;
}

int main() {
    testStack();
    return 0;
}