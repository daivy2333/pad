#include<iostream>
using namespace std;

class CLink
{
public:
    CLink()
    {
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CLink()
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }
        delete head_;
    }
    void insert_tail(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_;
        tail_->next_ = node;
        tail_ = tail_->next_;
    }
    void insert_head(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        if(node->next_ == head_)
        {
            tail_ = node;
        }
    }
    void remove(int val)
    {
        Node* q = head_;
        Node* p = head_->next_;

        while(p != head_)
        {
            if(p->data_ == val)
            {
                q->next_ = p->next_;
                delete p;
                if(q->next_ == head_)
                {
                    tail_ = head_;
                }
                return;
            }
            else
            {
                q = p;
                p = p->next_;
            }
        }
    }
    bool find(int val)
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            if(p->data_ == val) return true;
            p = p->next_;
        }
        return false;
    }
    void show() const
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            cout<< p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }
private:
    struct Node
    {
        /* data */
        Node(int data=0): data_(data), next_(nullptr){}
        int data_;
        Node* next_;
    };
    Node* head_;
    Node* tail_;
};

int main()
{
    CLink clink;
    
    cout << "========== 单向循环链表测试 ==========" << endl << endl;
    
    // 测试1: 空链表测试
    cout << "【测试1】空链表测试" << endl;
    cout << "空链表中查找100: " << (clink.find(100) ? "找到" : "未找到") << endl;
    cout << "空链表内容: "; clink.show();
    cout << endl;
    
    // 测试2: 尾部插入测试
    cout << "【测试2】尾部插入测试" << endl;
    cout << "依次插入10, 20, 30, 40" << endl;
    clink.insert_tail(10);
    clink.insert_tail(20);
    clink.insert_tail(30);
    clink.insert_tail(40);
    cout << "链表内容: "; clink.show();
    cout << endl;
    
    // 测试3: 头部插入测试
    cout << "【测试3】头部插入测试" << endl;
    cout << "依次插入5, 3, 1" << endl;
    clink.insert_head(5);
    clink.insert_head(3);
    clink.insert_head(1);
    cout << "链表内容: "; clink.show();
    cout << endl;
    
    // 测试4: 查找测试
    cout << "【测试4】查找测试" << endl;
    cout << "查找10: " << (clink.find(10) ? "找到" : "未找到") << endl;
    cout << "查找20: " << (clink.find(20) ? "找到" : "未找到") << endl;
    cout << "查找100: " << (clink.find(100) ? "找到" : "未找到") << endl;
    cout << endl;
    
    // 测试5: 删除中间元素
    cout << "【测试5】删除中间元素测试" << endl;
    cout << "删除20后, 链表内容: ";
    clink.remove(20);
    clink.show();
    cout << endl;
    
    // 测试6: 删除头部元素
    cout << "【测试6】删除头部元素测试" << endl;
    cout << "删除1后, 链表内容: ";
    clink.remove(1);
    clink.show();
    cout << endl;
    
    
    // 测试7: 删除尾部元素
    cout << "【测试7】删除尾部元素测试" << endl;
    cout << "删除40后, 链表内容: ";
    clink.remove(40);
    clink.show();
    cout << endl;
    
    // 测试8: 删除不存在的元素
    cout << "【测试8】删除不存在的元素测试" << endl;
    cout << "尝试删除100(不存在)..." << endl;
    clink.remove(100);
    cout << "删除后链表内容: "; clink.show();
    cout << endl;
    
    // 测试9: 删除所有元素
    cout << "【测试9】删除所有元素测试" << endl;
    cout << "删除剩余所有元素..." << endl;
    clink.remove(10);
    clink.remove(30);
    clink.remove(5);
    clink.remove(3);
    cout << "删除后链表内容: "; clink.show();
    cout << endl;
    
    // 测试10: 清空后再次插入
    cout << "【测试10】清空后再次插入测试" << endl;
    cout << "清空后插入100, 200, 300" << endl;
    clink.insert_tail(100);
    clink.insert_tail(200);
    clink.insert_tail(300);
    cout << "链表内容: "; clink.show();
    cout << endl;
    
    // 测试11: 删除唯一元素
    cout << "【测试11】删除唯一元素测试" << endl;
    cout << "创建新链表并插入50" << endl;
    CLink clink2;
    clink2.insert_tail(50);
    cout << "链表内容: "; clink2.show();
    cout << "删除50后, 链表内容: ";
    clink2.remove(50);
    clink2.show();
    cout << endl;
    
    // 测试12: 连续头部插入
    cout << "【测试12】连续头部插入测试" << endl;
    cout << "创建新链表并连续头部插入1, 2, 3, 4, 5" << endl;
    CLink clink3;
    clink3.insert_head(1);
    clink3.insert_head(2);
    clink3.insert_head(3);
    clink3.insert_head(4);
    clink3.insert_head(5);
    cout << "链表内容: "; clink3.show();
    cout << endl;
    
    cout << "========== 所有测试完成 ==========" << endl;
    return 0;
}