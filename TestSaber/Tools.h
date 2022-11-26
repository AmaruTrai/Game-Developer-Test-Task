#pragma once
#include <vector>
#include <tuple>
#include "ListNode.h"


//	Функция пирамидальной сортировки (сортировки кучей).
void HeapSort(std::vector<std::tuple<ListNode*, int>>& arr, int n);
//	Функция построения кучи.
void Heapify(std::vector<std::tuple<ListNode*, int>>& arr, int n, int i);
//	Функция бинарного поиска индекса элемента в заданной коллекции.
int BinarySearchFindIndex(const std::vector<std::tuple<ListNode*, int>>& v, const ListNode* data);