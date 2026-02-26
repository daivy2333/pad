#include<iostream>
using namespace std;

class DClink
{
private:
    /* data */
    struct Node
    {
        /* data */
        Node(int val=0): val_(val), pre_(nullptr), next_(nullptr){}
        int val_;
        Node* pre_;
        Node* next_;
    };
    Node* head_;
public:
    DClink(/* args */);
    ~DClink();
    void insert_head(int val);
    void insert_tail(int val);
    void show()const;
};

DClink::DClink(/* args */)
{
    head_ = new Node();
    head_->next_ = head_;
    head_->pre_ = head_;
}

DClink::~DClink()
{
    Node* p = head_->next_;
    while(p != head_)
    {
        Node* temp = p;
        p = p->next_;
        delete temp;
    }
    delete head_;
}
void DClink::insert_head(int data)
{
    Node* node = new Node(data);
    node->next_ = head_->next_;
    node->pre_ = head_;
    head_->next_->pre_ = node;
    head_->next_ = node;
}
void DClink::insert_tail(int data)
{
    Node* node = new Node(data);
    node->next_ = head_;
    node->pre_ = head_->pre_;
    head_->pre_->next_ = node;
    head_->pre_ = node;
}

void DClink::show() const
{
    Node* node = head_->next_;
    while(node != head_)
    {
        cout << node->val_ << " ";
        node = node->next_;
    }
    cout<<endl;
    node = nullptr;
}

using namespace std;

void test_insert_head() {
    cout << "===== 测试 insert_head =====" << endl;
    DClink list;

    cout << "在头部插入 5, 3, 1" << endl;
    list.insert_head(5);
    list.insert_head(3);
    list.insert_head(1);

    cout << "期望输出: 1 3 5" << endl;
    cout << "实际输出: ";
    list.show();
    cout << endl;
}

void test_insert_tail() {
    cout << "===== 测试 insert_tail =====" << endl;
    DClink list;

    cout << "在尾部插入 2, 4, 6" << endl;
    list.insert_tail(2);
    list.insert_tail(4);
    list.insert_tail(6);

    cout << "期望输出: 2 4 6" << endl;
    cout << "实际输出: ";
    list.show();
    cout << endl;
}

void test_mixed_operations() {
    cout << "===== 测试混合操作 =====" << endl;
    DClink list;

    cout << "在头部插入 10, 8" << endl;
    list.insert_head(10);
    list.insert_head(8);

    cout << "在尾部插入 12, 14" << endl;
    list.insert_tail(12);
    list.insert_tail(14);

    cout << "在头部插入 6" << endl;
    list.insert_head(6);

    cout << "期望输出: 6 8 10 12 14" << endl;
    cout << "实际输出: ";
    list.show();
    cout << endl;
}

void test_empty_list() {
    cout << "===== 测试空列表 =====" << endl;
    DClink list;

    cout << "空列表输出:" << endl;
    cout << "实际输出: ";
    list.show();
    cout << endl;
}

void test_single_element() {
    cout << "===== 测试单个元素 =====" << endl;
    DClink list;

    cout << "在头部插入 100" << endl;
    list.insert_head(100);

    cout << "期望输出: 100" << endl;
    cout << "实际输出: ";
    list.show();
    cout << endl;
}

int main() {
    test_insert_head();
    test_insert_tail();
    test_mixed_operations();
    test_empty_list();
    test_single_element();

    cout << "===== 所有测试完成 =====" << endl;
    return 0;
}
