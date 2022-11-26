#include "Tools.h"

void Heapify(std::vector<std::tuple<ListNode*, int>>& arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && std::get<0>(arr[left]) > std::get<0>(arr[largest]))
    {
        largest = left;
    }

    if (right < n && std::get<0>(arr[right]) > std::get<0>(arr[largest]))
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

void HeapSort(std::vector<std::tuple<ListNode*, int>>& arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}


int BinarySearchFindIndex(const std::vector<std::tuple<ListNode*, int>>& v, const ListNode* data) {
    int left = 0;
    int right = v.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (std::get<0>(v[mid]) == data)
        {
            return mid;
        }
        else if (std::get<0>(v[mid]) < data)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}