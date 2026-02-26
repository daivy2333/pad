#include <iostream>
#include <vector>
using namespace std;

// 合并两个有序子数组
void merge(vector<int>& arr, int left, int mid, int right) {
    // 创建临时数组存储合并结果
    vector<int> temp(right - left + 1);

    int i = left;      // 左子数组起始索引
    int j = mid + 1;   // 右子数组起始索引
    int k = 0;         // 临时数组索引

    // 比较左右子数组的元素，将较小的放入临时数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // 将左子数组剩余元素放入临时数组
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // 将右子数组剩余元素放入临时数组
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 将临时数组复制回原数组
    for (int p = 0; p < temp.size(); p++) {
        arr[left + p] = temp[p];
    }
}

// 归并排序主函数
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // 找到中间点
        int mid = left + (right - left) / 2;

        // 递归排序左半部分
        mergeSort(arr, left, mid);

        // 递归排序右半部分
        mergeSort(arr, mid + 1, right);

        // 合并两个有序子数组
        merge(arr, left, mid, right);
    }
}

// 打印数组
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // 测试用例
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90, 5};

    cout << "原始数组: ";
    printArray(arr);

    // 执行归并排序
    mergeSort(arr, 0, arr.size() - 1);

    cout << "排序后数组: ";
    printArray(arr);

    return 0;
}
