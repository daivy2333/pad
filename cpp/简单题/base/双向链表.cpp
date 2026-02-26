#include<iostream>
using namespace std;

struct  Node
{
    Node(int val=0):
    data(val),next(nullptr), pre(nullptr)
    {};
    int data;
    Node* next;
    Node* pre;
};


class aslink
{
public:
    Node* head;
    aslink()
    {
        head = new Node();
    }
    ~aslink()
    {
        Node* p = head;
        while(p)
        {
            head = head->next;
            delete p;
            p = head;
        }
    }

    void insert_begin(int val)
    {
        if(!head) return;

        Node* dummy = new Node(val);
        dummy->next = head;
        head->pre = dummy;
        head = dummy;
        dummy = nullptr;
    }
    void insert_end(int val)
    {
        if(!head) return;
        Node* T = head;
        while(T->next)
        {
            T = T->next;
        }
        Node* dummy = new Node(val);
        T->next = dummy;
        dummy->pre = T;
        T = nullptr;
        dummy = nullptr;
    }
    void reverse()
    {
        if(!head) return;
        if(!head->next) 
        {
            cout<< head->data<<endl;
            return;
        }
        Node* T = nullptr;
        Node* F = head->next;
        while(head->next)
        {
            head->pre = F;
            head->next = T;
            T = head;
            head = F;
            F = F->next;
        }
        head->pre = F;
        head->next = T;
        F = nullptr;
        T = nullptr;
    }
    void delete_val(int val)
    {
        if(!head || !head->next) return;  // 空链表或只有哑节点
        
        Node* current = head->next;  // 从第一个实际数据节点开始（跳过哑节点）
        
        while(current)
        {
            if(current->data == val)
            {
                // 调整前后节点的指针
                if(current->pre)
                {
                    current->pre->next = current->next;
                }
                if(current->next)
                {
                    current->next->pre = current->pre;
                }
                
                // 如果要删除的是第一个实际数据节点，需要更新哑节点的next
                if(current->pre == head)
                {
                    head->next = current->next;
                }
                
                delete current;
                return;  // 只删除第一个匹配的节点
            }
            current = current->next;
        }
    }
    void delete_val_all(int val)
    {
        if(!head || !head->next) return;  // 空链表或只有哑节点
        
        Node* current = head->next;  // 从第一个实际数据节点开始
        Node* toDelete = nullptr;
        
        while(current)
        {
            if(current->data == val)
            {
                toDelete = current;
                current = current->next;  // 先移动到下一个节点
                
                // 调整前后节点的指针
                if(toDelete->pre)
                {
                    toDelete->pre->next = toDelete->next;
                }
                if(toDelete->next)
                {
                    toDelete->next->pre = toDelete->pre;
                }
                
                // 如果要删除的是第一个实际数据节点，更新哑节点的next
                if(toDelete->pre == head)
                {
                    head->next = toDelete->next;
                }
                
                delete toDelete;
            }
            else
            {
                current = current->next;
            }
        }
    }
    void show_forward()
    {
        Node* dummy = head;
        while(dummy)
        {
            cout<< dummy->data <<" ";
            dummy = dummy->next;
        }
        cout<<endl;
    }
    void show_back()
    {
        Node* dummy = head;
        while(dummy->next)
        {
            dummy = dummy->next;
        }
        while(dummy)
        {
            cout<< dummy->data <<" ";
            dummy = dummy->pre;
        }
        cout<<endl;
    }
private:
};

int main()
{
    aslink A;
    for(int i=1; i<10; i++)
    {
        if(i%2==0) A.insert_end(i);
        else A.insert_begin(i);
    }
    A.show_forward();
    A.show_back();
    A.reverse();
    A.show_forward();
    A.delete_val(4);
    A.show_forward();
    return 0;
}