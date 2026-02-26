#pragma only
#include<iostream>
#include <cstring>
#include <memory>
using namespace std;
class Array
{
    public:
        Array(int size = 10): mCur(0), mCap_(size)
        {
            mpArr = new int[mCap_]();
        }
        ~Array()
        {
            delete []mpArr;
            mpArr = nullptr;
        }

    public:
        void show()
        {
            for(int i=0; i<mCur; i++)
            {
                cout<< mpArr[i]<<" ";
            }
            cout<<endl;
        }
        void push_back(int val)
        {
            if(mCur == mCap_)
            {
                cout<<"full, and double"<< endl;
                expend(2*mCap_);
            }
            mpArr[mCur++] = val;
        }

        void pop_back()
        {
            if(mCur == 0)
            {
                std::cout<<"reach 0"<< std::endl;
                return;
            }
            mCur--;
        }
        void insert(int pos, int val)
        {
            if(pos<0 || pos>mCur)
            {
                cout<< "pos invalid" << endl;
                return;
            }
            if(mCur == mCap_)
            {
                cout<<"full, and double"<< endl;
                expend(2*mCap_);
            }

            for(int i = mCur-1; i>=pos; i--)
            {
                mpArr[i+1] = mpArr[i];
            }
            mpArr[pos] = val;
            mCur++;
        }

        void erase(int pos)
        {
            if(pos<0 || pos>=mCur) return;
            for(int i=pos+1; i<mCur; i++)
            {
                mpArr[i-1] = mpArr[i];
            }
            mCur--;
        }
        int search(int val)
        {
            for(int i=0; i<mCur; i++)
            {
                if(mpArr[i] == val) return i;
            }
            return -1;
        }
    private:
        int *mpArr; //指向可扩容内存
        int mCap_; //容量
        int mCur; //有效个数

        void expend(int size) //换瓶子装
        {
            int *p = new int[size];

            memcpy(p, mpArr, sizeof(int) * mCap_);
            delete[] mpArr;
            mpArr = p;
            mCap_ = size;
        }
};

int main()
{
    Array arr;
    for(int i=0; i<=20; i++)
    {
        arr.push_back(i);
    }
    arr.show();
    arr.pop_back();
    arr.show();
    return 0;
}