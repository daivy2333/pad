#include "some.h"
// 其实就是桶排序

void RadixSort(int arr[], int size)
{
    int MaxData = arr[0];
    for(int i=1; i<size; i++)
    {
        if(MaxData < arr[i])
        {
            MaxData = arr[i];
        }
    }

    int len = to_string(MaxData).size();

    vector<vector<int>> vecs;
    int mod = 10;
    int dev = 1;
    for(int i=0; i<len; mod *= 10, dev *= 10, i++)
    {
        vecs.resize(10);
        for(int j=0; j<size; j++)
        {
            int index = arr[j]%mod/dev;
            vecs[index].push_back(arr[j]);
        }
        int idx = 0;
        for(auto vec : vecs)
        {
            for(int v : vec)
            {
                arr[idx++] = v;
            }
        }
        vecs.clear();
    }
}