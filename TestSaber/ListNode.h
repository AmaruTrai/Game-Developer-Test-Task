#pragma once
#include <string>

class ListNode
{
public:
    ListNode* Prev;
    ListNode* Next;
    ListNode* Rand; // произвольный элемент внутри списка
    std::string Data;

    ListNode(std::string data = std::string());

private:
    ListNode(const ListNode& rhs) = delete;
    ListNode(ListNode&& rhs) = delete;
    ListNode& operator=(const ListNode& rhs) = delete;
    ListNode& operator=(ListNode&& rhs) = delete;
};