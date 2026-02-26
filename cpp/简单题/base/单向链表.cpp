#include<iostream>
using namespace std;

struct node
{
    node(int data=0) : data_(data), next_(nullptr){}
    int data_;
    node* next_;
};


class clink
{
public:
    node* head_;
    clink()
    {
        head_ = new node();
    }

    ~clink()
    {
        while(head_)
        {
            node* next = head_->next_;
            delete head_;
            head_ = next;
        }
        head_ = nullptr;
    }

    void insert_tail(int val) // 尾插法，找到尾巴节点然后new一个插到后面
    {
        node* p = head_;
        while(p->next_)
        {
            p = p->next_;
        }
        node* Node = new node(val);
        p->next_ = Node;
    }
    void insert_begin(int val)
    {
        node* Node = new node(val);
        Node->next_ = head_;
        head_ = Node;
    }
    void show()
    {
        node* dummy = head_;
        while(dummy)
        {
            cout<<dummy->data_<<" ";
            dummy = dummy->next_;
        }
        cout<<endl;
    }
    void delete_last()
    {
        if(!head_) return;
        if(!head_->next_)
        {
            delete head_;
            head_ = nullptr;
            return;
        }

        node* dummy = head_;
        while(dummy->next_ && dummy->next_->next_)
        {
            dummy = dummy->next_;
        }
        delete dummy->next_;
        dummy->next_ = nullptr;
    }
    void delete_begin()
    {
        if(!head_) return;
        node* dummy = head_;
        head_ = head_->next_;
        delete dummy;
        dummy = nullptr;
    }
    void delete_val(int val) //如果要删掉某个节点，就要停在它的前面
    {
        if(!head_) return;
        if(!head_->next_)
        {
            if(head_->data_ ==val) 
            {
                delete head_;
                head_ = nullptr;
            }
            else return;
        }
        node* dummy = head_;
        while(dummy->next_)
        {
            if(dummy->next_->data_ == val) break;
            dummy = dummy->next_;
        }
        if(!dummy->next_) return;
        node* be = dummy->next_;
        dummy->next_ = be->next_;
        delete be;
        be = nullptr;
    }
    void delete_val_all(int val)
    {
        if(!head_) return;
        if(!head_->next_)
        {
            if(head_->data_ ==val) 
            {
                delete head_;
                head_ = nullptr;
            }
            else return;
        }
        node* dummy = head_;
        while(dummy->next_)
        {
            if(dummy->next_->data_ == val)
            {
                node* be = dummy->next_;
                dummy->next_ = be->next_;
                delete be;
            }
            dummy = dummy->next_;
        }
    }
    void reverse()
    {
        if(!head_) return;
        if(!head_->next_)return;

        node* dummy = nullptr;
        node* fast = head_->next_;
        while(head_->next_)
        {
            head_->next_ = dummy;
            dummy = head_;
            head_ = fast;
            fast = fast->next_;
        }
        head_->next_ = dummy;
        dummy = nullptr;
    }

    void merge(node* other)
    {
        if (!other) return;
        if (!head_) {
            head_ = other;
            return;
        }
        
        node dummy_head;  // 使用虚拟头节点简化操作
        node* current = &dummy_head;
        
        node* l1 = head_;
        node* l2 = other;
        
        while (l1 && l2) {
            if (l1->data_ <= l2->data_) {
                current->next_ = l1;
                l1 = l1->next_;
            } else {
                current->next_ = l2;
                l2 = l2->next_;
            }
            current = current->next_;
        }
        
        // 处理剩余节点
        if (l1) {
            current->next_ = l1;
        } else if (l2) {
            current->next_ = l2;
        }
        
        head_ = dummy_head.next_;
    }
private:
    
};

int main()
{
    clink c,k;
    for(int i=1; i<10; i++)
    {
        if(i%2==0)
        c.insert_tail(i);
        if(i%2==1)
        k.insert_tail(i);
    }
    c.show();
    k.show();
    c.delete_last();
    k.delete_begin();
    k.reverse();
    k.show();
    k.reverse();

    c.show();
    k.show();
    c.merge(k.head_);
    c.show();
    return 0;
}