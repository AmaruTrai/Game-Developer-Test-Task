#pragma once
#include "ListNode.h"
#include "Tools.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>

class ListRand
{
public:
    ListNode* Head;
    ListNode* Tail;
    int Count;

    ListRand();
    ~ListRand();

    void Serialize(std::ofstream& s);
    void Deserialize(std::ifstream& s);

    void AlternativeSerialize(std::ofstream& s);

private:
    ListRand(const ListRand& rhs) = delete;
    ListRand(ListRand&& rhs) = delete;
    ListRand& operator=(const ListRand& rhs) = delete;
    ListRand& operator=(ListRand&& rhs) = delete;
};