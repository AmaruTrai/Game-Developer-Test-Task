#include "ListRand.h"

ListRand::ListRand()
{
    Head = nullptr;
    Tail = nullptr;
    Count = 0;
}

ListRand::~ListRand() {
    for(auto pointer = Head; pointer != nullptr; pointer = pointer->Next)
    {
        if (pointer->Prev != nullptr)
        {
            delete pointer->Prev;
        }

        if (pointer->Next == nullptr)
        {
            delete pointer;
            break;
        }
    }
}

//  Сериализация связанного списка со сложностью O(nlog(n)).
void ListRand::Serialize(std::ofstream& s)
{
    if (!s.is_open())
    {
        throw std::invalid_argument("Stream is closed.");
    }

    auto tempArray = std::vector<std::tuple<ListNode*, int>>(Count);
    ListNode* node = Head;
    //  Сложность - O(n), так как место в векторе выделено заранее.
    for (int i = 0; i < Count; i++)
    {
        tempArray[i] = std::make_tuple(node, i);
        node = node->Next;
    }

    //  Сложность - O(nLog(n)).
    //  Так как неизвестно каким образом расположены элементы списка в памяти, выбрал пирамидальную сортировку.
    HeapSort(tempArray, tempArray.size());

    //  O(nLog(n))
    //  Так как сложность бинарного поиска O(Log(n)).
    s << typeid(ListRand).name() << '\n';
    s << Count << '\n';
    for (auto node = Head; node != nullptr; node = node->Next)
    {
        s << typeid(ListNode).name() << '\n';
        int randomId = BinarySearchFindIndex(tempArray, node->Rand);
        if (randomId != -1)
        {
            s << std::get<1>(tempArray[randomId]) << '\n';
        }
        else {
            s << randomId << '\n';
        }

        s << node->Data << '\n';
    }
}

//  Сериализация связанного списка со сложностью O(n).
//  Как решение алгоритмической задачи подойдет.
//  Использовать на практике возможно только если гарантировано,
//  что работа со списком на время сериализации будет заблокирована.
void ListRand::AlternativeSerialize(std::ofstream& s)
{
    if (!s.is_open())
    {
        throw std::invalid_argument("Stream is closed.");
    }

    //  O(n) - Добавляем промежуточные элементы в список. 
    //  В элементах хранится информация о порядке расположения в списке.
    int i = 0;
    ListNode* node = Head;
    while (node != nullptr)
    {
        auto temp = node->Next;
        node->Next = new ListNode(std::to_string(i));
        node->Next->Next = temp;
        node = temp;
        i++;
    }

    //  O(n) - Сериализация
    s << typeid(ListRand).name() << '\n';
    s << Count << '\n';
    node = Head;
    while (node != nullptr)
    {
        s << typeid(ListNode).name() << '\n';
        if (node->Rand != nullptr)
        {
            s << node->Rand->Next->Data << '\n';
        }
        else {
            s << -1 << '\n';
        }
        s << node->Data << '\n';
        node = node->Next->Next;
    }

    //  O(n) - Восстановление данных.
    node = Head;
    while (node != nullptr)
    {
        auto temp = node->Next;
        node->Next = temp->Next;
        node = node->Next;
        delete temp;
    }
}

void ListRand::Deserialize(std::ifstream& s)
{
    if (!s.is_open())
    {
        throw std::invalid_argument("Stream is closed.");
    }

    std::string line;
    if (!std::getline(s, line) || line != typeid(ListRand).name())
    {
        throw std::invalid_argument("Incorrect file format.");
    }

    if (!std::getline(s, line))
    {
        throw std::invalid_argument("Count field not found.");
    }

    int count = atoi(line.c_str());
    if (count < 0)
    {
        throw std::invalid_argument("Negative ListRand size.");
    }

    auto tempArray = std::vector<std::tuple<ListNode*, int>>(count);
    try
    {
        ListNode* node = nullptr;
        int nodeId = 0;
        while (std::getline(s, line))
        {
            if (line == typeid(ListNode).name())
            {
                std::getline(s, line);
                int randomId = atoi(line.c_str());
                node = new ListNode();
                tempArray[nodeId] = std::tuple<ListNode*, int>(node, randomId);
                nodeId++;
            }
            else if (node == nullptr)
            {
                throw std::invalid_argument("Incorrect file format.");
            }
            else
            {
                if (!node->Data.empty()) {
                    node->Data += "\n";
                }
                node->Data += line;
            }
        }
    }
    catch (std::exception& e)
    {
        for (int i = 0; i < count; i++)
        {
            auto temp = std::get<0>(tempArray[i]);
            if (temp != nullptr)
            {
                delete temp;
            }
        }
        throw e;
    }

    Head = std::get<0>(tempArray[0]);
    Count = count;
    auto current = Head;
    for (int i = 0; i < count; i++)
    {
        auto randomId = std::get<1>(tempArray[i]);
        if (i != 0)
        {
            current->Prev = std::get<0>(tempArray[i - 1]);
        }

        if (i < tempArray.size() - 1)
        {
            current->Next = std::get<0>(tempArray[i + 1]);
        }

        if (randomId != -1)
        {
            current->Rand = std::get<0>(tempArray[randomId]);
        }

        current = current->Next;
    }
    Tail = std::get<0>(tempArray[count - 1]);
}