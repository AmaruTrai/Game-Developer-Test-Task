#pragma once
#include <vector>
#include <tuple>
#include "ListNode.h"


//	������� ������������� ���������� (���������� �����).
void HeapSort(std::vector<std::tuple<ListNode*, int>>& arr, int n);
//	������� ���������� ����.
void Heapify(std::vector<std::tuple<ListNode*, int>>& arr, int n, int i);
//	������� ��������� ������ ������� �������� � �������� ���������.
int BinarySearchFindIndex(const std::vector<std::tuple<ListNode*, int>>& v, const ListNode* data);