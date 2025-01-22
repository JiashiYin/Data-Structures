#include <iostream>
#include <cassert>
#include <string>
#include "Doubly.hpp"

template <typename T>
void printList(const DoublyLinkedList<T>& list, const std::string& label) {
    std::cout << label << " (size=" << list.size() << "): ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testBigFive() {
    std::cout << "\n=== Testing Big Five ===" << std::endl;
    
    // Test Constructor
    std::cout << "\nTesting Default Constructor" << std::endl;
    DoublyLinkedList<int> list1;
    assert(list1.size() == 0);
    std::cout << "Default constructor passed" << std::endl;

    // Populate list1
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    printList(list1, "Original list");

    // Test Copy Constructor
    std::cout << "\nTesting Copy Constructor" << std::endl;
    DoublyLinkedList<int> list2(list1);
    printList(list2, "Copied list");
    assert(list2.size() == list1.size());
    for (int i = 0; i < list1.size(); ++i) {
        assert(list1[i] == list2[i]);
    }
    std::cout << "Copy constructor passed" << std::endl;

    // Test Copy Assignment
    std::cout << "\nTesting Copy Assignment" << std::endl;
    DoublyLinkedList<int> list3;
    list3 = list1;
    printList(list3, "Copy assigned list");
    assert(list3.size() == list1.size());
    for (int i = 0; i < list1.size(); ++i) {
        assert(list1[i] == list3[i]);
    }
    std::cout << "Copy assignment passed" << std::endl;

    // Test Move Constructor
    std::cout << "\nTesting Move Constructor" << std::endl;
    DoublyLinkedList<int> list4(std::move(list2));
    printList(list4, "Move constructed list");
    printList(list2, "Original list after move");
    assert(list2.size() == 0); // Original should be empty after move
    std::cout << "Move constructor passed" << std::endl;

    // Test Move Assignment
    std::cout << "\nTesting Move Assignment" << std::endl;
    DoublyLinkedList<int> list5;
    list5 = std::move(list3);
    printList(list5, "Move assigned list");
    printList(list3, "Original list after move assignment");
    assert(list3.size() == 0); // Original should be empty after move
    std::cout << "Move assignment passed" << std::endl;
}

void testBasicOperations() {
    std::cout << "\n=== Testing Basic Operations ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    // Test push_back
    std::cout << "\nTesting push_back" << std::endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    printList(list, "After push_back");
    assert(list.size() == 3);
    assert(list[0] == 10);
    assert(list[2] == 30);
    
    // Test insert
    std::cout << "\nTesting insert" << std::endl;
    list.insert(1, 15);
    printList(list, "After insert");
    assert(list.size() == 4);
    assert(list[1] == 15);
    
    // Test pop_front
    std::cout << "\nTesting pop_front" << std::endl;
    int popped = list.pop_front();
    printList(list, "After pop_front");
    assert(popped == 10);
    assert(list.size() == 3);
    
    // Test erase
    std::cout << "\nTesting erase" << std::endl;
    list.erase(1);
    printList(list, "After erase");
    assert(list.size() == 2);
    
    // Test clear
    std::cout << "\nTesting clear" << std::endl;
    list.clear();
    printList(list, "After clear");
    assert(list.size() == 0);
}

void testIterator() {
    std::cout << "\n=== Testing Iterator ===" << std::endl;
    
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i * 10);
    }
    
    std::cout << "Forward iteration: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test iterator arithmetic
    std::cout << "Testing iterator + operator" << std::endl;
    auto it = list.begin();
    auto it2 = it + 2;
    assert(*it2 == 20);
    std::cout << "Iterator arithmetic passed" << std::endl;
}

void testEdgeCases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    // Test operations on empty list
    std::cout << "Testing operations on empty list" << std::endl;
    try {
        list.pop_front();
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "Expected exception caught: " << e.what() << std::endl;
    }
    
    // Test invalid index access
    try {
        list.insert(-1, 10);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "Expected exception caught: " << e.what() << std::endl;
    }
}

// Helper function to print list backwards using Walk_To
template <typename T>
void printListBackward(const DoublyLinkedList<T>& list, const std::string& label) {
    std::cout << label << " (size=" << list.size() << ") backwards: ";
    if (list.size() == 0) {
        std::cout << "[empty list]";
    } else {
        for (int i = list.size() - 1; i >= 0; --i) {
            std::cout << list[i] << " ";
        }
    }
    std::cout << std::endl;
}

void testBackwardTraversal() {
    std::cout << "\n=== Testing Backward Traversal ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    // Test with empty list
    std::cout << "\nTesting empty list:" << std::endl;
    printListBackward(list, "Empty list");
    
    // Test with single element
    std::cout << "\nTesting single element:" << std::endl;
    list.push_back(42);
    printList(list, "Forward");
    printListBackward(list, "Backward");
    
    // Test with multiple elements
    std::cout << "\nTesting multiple elements:" << std::endl;
    list.push_back(43);
    list.push_back(44);
    list.push_back(45);
    printList(list, "Forward");
    printListBackward(list, "Backward");
    
    // Test Walk_To with negative indices
    std::cout << "\nTesting Walk_To with negative indices:" << std::endl;
    try {
        // Testing walking backwards from middle
        int mid_idx = list.size() / 2;
        std::cout << "Walking backwards from index " << mid_idx << ": ";
        for (int i = 0; i <= mid_idx; ++i) {
            std::cout << list[mid_idx - i] << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test after modifications
    std::cout << "\nTesting after modifications:" << std::endl;
    list.insert(2, 100);  // insert in middle
    printList(list, "After insert in middle - Forward");
    printListBackward(list, "After insert in middle - Backward");
    
    list.erase(2);  // Remove from middle
    printList(list, "After remove from middle - Forward");
    printListBackward(list, "After remove from middle - Backward");
    
    // Test edge cases
    std::cout << "\nTesting edge cases:" << std::endl;
    
    // Remove all but one element
    while (list.size() > 1) {
        list.pop_front();
    }
    printList(list, "Single element - Forward");
    printListBackward(list, "Single element - Backward");
    
    // Remove last element
    list.pop_front();
    printList(list, "Empty again - Forward");
    printListBackward(list, "Empty again - Backward");
    
    // Test prev pointers after multiple operations
    std::cout << "\nTesting complex operations:" << std::endl;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.insert(1, 4);
    list.pop_front();
    list.erase(1);
    printList(list, "After complex operations - Forward");
    printListBackward(list, "After complex operations - Backward");
}

int main() {
    try {
        testBigFive();
        testBasicOperations();
        testIterator();
        testEdgeCases();
        testBackwardTraversal();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}