#include <iostream>
using namespace std;

void shiftdown(int arr[], int i, int size)
{
    int val = arr[i];
    while(i < (size/2))
    {
        int child = 2*i+1;
        if(child+1<size && arr[child+1]>arr[child])
        {
            child = child+1;
        }
        if(arr[child] > val)
        {
            arr[i] = arr[child];
            i = child;
        }
        else
        {
            break;
        }
    }
    arr[i] = val;
}
void HeapSort(int arr[], int size)
{
    int end = size-1;
    for(int i=(end-1)/2; i>=0; i--)
    {
        shiftdown(arr,i,size);
    }
    for(int i=end; i>0; i--)
    {
        int t = arr[0];
        arr[0] = arr[i];
        arr[i] = t;

        shiftdown(arr, 0, i);
    }
    for(int i=0; i<size; i++)
    {
        cout<< arr[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    // 测试用例1：普通数组
    int arr1[] = {12, 11, 13, 5, 6, 7};
    int size1 = sizeof(arr1)/sizeof(arr1[0]);

    cout << "测试用例1：" << endl;
    cout << "原始数组：";
    for(int i=0; i<size1; i++)
        cout << arr1[i] << " ";
    cout << endl;

    HeapSort(arr1, size1);

    cout << "排序结果：";
    for(int i=0; i<size1; i++)
        cout << arr1[i] << " ";
    cout << endl << endl;

    // 测试用例2：已排序数组
    int arr2[] = {1, 2, 3, 4, 5, 6};
    int size2 = sizeof(arr2)/sizeof(arr2[0]);

    cout << "测试用例2：" << endl;
    cout << "原始数组：";
    for(int i=0; i<size2; i++)
        cout << arr2[i] << " ";
    cout << endl;

    HeapSort(arr2, size2);

    cout << "排序结果：";
    for(int i=0; i<size2; i++)
        cout << arr2[i] << " ";
    cout << endl << endl;

    // 测试用例3：逆序数组
    int arr3[] = {6, 5, 4, 3, 2, 1};
    int size3 = sizeof(arr3)/sizeof(arr3[0]);

    cout << "测试用例3：" << endl;
    cout << "原始数组：";
    for(int i=0; i<size3; i++)
        cout << arr3[i] << " ";
    cout << endl;

    HeapSort(arr3, size3);

    cout << "排序结果：";
    for(int i=0; i<size3; i++)
        cout << arr3[i] << " ";
    cout << endl << endl;

    // 测试用例4：包含重复元素的数组
    int arr4[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int size4 = sizeof(arr4)/sizeof(arr4[0]);

    cout << "测试用例4：" << endl;
    cout << "原始数组：";
    for(int i=0; i<size4; i++)
        cout << arr4[i] << " ";
    cout << endl;

    HeapSort(arr4, size4);

    cout << "排序结果：";
    for(int i=0; i<size4; i++)
        cout << arr4[i] << " ";
    cout << endl;

    return 0;
}