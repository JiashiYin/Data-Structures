#include "Circular.hpp"
#include <iostream>
#include <cassert>
#include <chrono> // For high-resolution clock
using namespace std;

template <typename T>
void PrintList(const CircularLinkedList<T>& list) {
    if (list.size() == 0) {
        cout << "List is empty.\n";
        return;
    }
    auto iter = list.begin();
    do {
        cout << *iter << " ";
        ++iter;
    } while (iter != list.begin());
    cout << endl;
}

int main() {
    // Start measuring time
    auto start_time = std::chrono::high_resolution_clock::now();

    CircularLinkedList<int> list;

    // Test push_back and PrintList
    cout << "Testing push_back:\n";
    for (int i = 1; i <= 5; ++i) {
        list.push_back(i);
    }
    PrintList(list);

    // Test insert
    cout << "\nTesting insert:\n";
    list.insert(0, 0);  // insert at head
    PrintList(list);
    list.insert(3, 99); // insert at middle
    PrintList(list);
    list.insert(7, 42); // insert at tail
    PrintList(list);

    // Test erase
    cout << "\nTesting erase:\n";
    list.erase(0);  // erase head
    list.erase(2);  // erase middle
    std::cout << list.size() << endl;
    list.erase(5);  // erase tail
    PrintList(list);

    // Test pop_front
    cout << "\nTesting pop_front:\n";
    while (list.size() > 0) {
        cout << "Popped: " << list.pop_front() << endl;
        PrintList(list);
    }

    // Test the big five
    cout << "\nTesting Big Five:\n";
    CircularLinkedList<int> list1;
    for (int i = 1; i <= 3; ++i) {
        list1.push_back(i);
    }
    PrintList(list1);
    // Copy constructor
    CircularLinkedList<int> list2 = list1;
    cout << "List2 (copy constructor):\n";
    PrintList(list2);

    // Copy assignment
    CircularLinkedList<int> list3;
    list3 = list1;
    cout << "List3 (copy assignment):\n";
    PrintList(list3);

    // Move constructor
    CircularLinkedList<int> list4 = move(list1);
    cout << "List4 (move constructor):\n";
    PrintList(list4);

    // Move assignment
    CircularLinkedList<int> list5;
    list5 = move(list2);
    cout << "List5 (move assignment):\n";
    PrintList(list5);

    // End measuring time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " ns" << std::endl;

    return 0;
}
