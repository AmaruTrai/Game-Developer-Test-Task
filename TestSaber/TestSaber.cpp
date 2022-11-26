#include <iostream>
#include "ListRand.h"

int main()
{
    // Генерация тестового списка.
    std::cout.flush();
    std::srand(std::time(nullptr));
    int count = 5;
    auto vector = std::vector<ListNode*>(count);

    for (int i = 0; i < count; i++)
    {
        vector[i] = new ListNode("тестовые данные " + std::to_string(i + 1));    
    }

    auto list = new ListRand();
    list->Head = vector[0];
    auto current = list->Head;
    std::cout << "Before serialization:\n";
    for (int i = 1; i < count; i++) {
        current->Next = vector[i];
        current->Next->Prev = current;
        int random = rand() % count;
        current->Rand = vector[random];
        current = current->Next;
        std::cout << "Node index: " << i - 1 << " Random Node Index: " << random << '\n';
    }
    int random = rand() % count;
    std::cout << "Node index: " << count - 1 << " Random Node Index: " << random << '\n';
    current->Rand = vector[random];
    list->Tail = current;
    list->Count = count;

    // Сериализация
    auto stream = std::ofstream("Test.txt");
    list->Serialize(stream);
    stream.close();

    // Десериализация
    auto fstream = std::ifstream("Test.txt");
    auto newRand = new ListRand();
    newRand->Deserialize(fstream);
    fstream.close();

    delete list;
    delete newRand;
}
