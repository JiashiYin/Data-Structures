#include <iostream>
#include "Singly.hpp"

void TestSinglyLinkedList() {
    // Create a SinglyLinkedList instance
    SinglyLinkedList<int> list;

    // Test push_back
    std::cout << "Testing push_back...\n";
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::cout << "List after push_back: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test operator[] for random access
    std::cout << "Testing operator[]...\n";
    try {
        std::cout << "Element at index 1: " << list[1] << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Test insert
    std::cout << "Testing insert...\n";
    list.insert(3, 77); // insert 15 at index 
    std::cout << "List after insert: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test pop_front
    std::cout << "Testing pop_front...\n";
    int front = list.pop_front();
    std::cout << "Popped front: " << front << "\n";
    std::cout << "List after pop_front: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test erase
    std::cout << "Testing erase...\n";
    list.erase(2); // Remove element at index 
    std::cout << "List after erase: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test size
    std::cout << "Testing size...\n";
    std::cout << "Current size of the list: " << list.size() << "\n";

    // Test clear
    std::cout << "Testing clear...\n";
    list.clear();
    std::cout << "List after clear: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(should be empty)\n";

    // Test exception handling
    std::cout << "Testing exception handling for operator[]...\n";
    try {
        std::cout << "Accessing element at index 0: " << list[0] << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }
}


void test_default_constructor() {
    SinglyLinkedList<int> list;
    std::cout << "Default Constructor: Size = " << list.size() << "\n";
}

void test_copy_constructor() {
    SinglyLinkedList<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    SinglyLinkedList<int> copy(original);
    std::cout << "Copy Constructor: ";
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << copy.size() << ")\n";
}

void test_copy_assignment() {
    SinglyLinkedList<int> original;
    original.push_back(4);
    original.push_back(5);
    original.push_back(6);

    SinglyLinkedList<int> copy;
    copy = original;
    std::cout << "Copy Assignment: ";
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << copy.size() << ")\n";
}

void test_move_constructor() {
    SinglyLinkedList<int> temporary;
    temporary.push_back(7);
    temporary.push_back(8);
    temporary.push_back(9);

    SinglyLinkedList<int> moved(std::move(temporary));
    std::cout << "Move Constructor: ";
    for (auto it = moved.begin(); it != moved.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << moved.size() << ")\n";
}

void test_move_assignment() {
    SinglyLinkedList<int> temporary;
    temporary.push_back(10);
    temporary.push_back(11);
    temporary.push_back(12);

    SinglyLinkedList<int> moved;
    moved = std::move(temporary);
    std::cout << "Move Assignment: ";
    for (auto it = moved.begin(); it != moved.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Size = " << moved.size() << ")\n";
}

int main() {
    TestSinglyLinkedList();

    std::cout << "\n" << "Testing Big Five:\n\n";
    test_default_constructor();
    test_copy_constructor();
    test_copy_assignment();
    test_move_constructor();
    test_move_assignment();
    return 0;
}

