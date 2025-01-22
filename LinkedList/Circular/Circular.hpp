#ifndef __LINKEDLIST_CIRCULAR_CIRCULAR_HPP
#define __LINKEDLIST_CIRCULAR_CIRCULAR_HPP
#include <stdexcept>

namespace CircularNode  {
    template <typename T>
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
        
        Node* walk_to(size_t index) const  {
            const Node* current = this;
            size_t count = 0;
            while (index != count)   { // supports any index > 0 walk!
                current = current->next;
                ++count;
            }
            // We are sure that this func but do not modify the object
            return const_cast<CircularNode::Node<int>*>(current);  // Cast away const
        }
    };
}

template <typename T>
class CircularLinkedList {
using Node = typename CircularNode::Node<T>;
public:
    class iterator  {
    public:
        using Node = typename CircularNode::Node<T>;
        iterator(Node* ptr_in);

        /*
        iterator cls should have:
        > ++ increm op
        > + offsetting op
        > * deref op
        > ==, != (in)eq op, for control conditioning
        */

        iterator& operator++(); // return by ref means pre increm
        iterator operator+(size_t incr) const; // Note that we want it+incr to return a new incr-ed iter but not modify the original

        T& operator*() const; // return by ref :  could modify through iter as *iter = a;

        bool operator==(iterator rhs) const;
        bool operator!=(iterator rhs) const;

    private:
        Node* ptr_;
        // NOT T*! Otherwise would abuse T: T is the data type in this context.
    };

    CircularLinkedList(); // default constructor: nullptr
    ~CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& other); // copy constructor
    CircularLinkedList& operator=(const CircularLinkedList& other); // copy assignment
    CircularLinkedList(CircularLinkedList&& other) noexcept; // move constructor
    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept; // move assignment

    T& operator[](size_t index) const;

    void push_back(const T& input);
    void insert(size_t index, const T& input);
    T pop_front(); 
    void erase(size_t index);
    void clear();

    size_t size() const;

    iterator begin() const;
    iterator end() const;

private:
    Node* head_;
    Node* tail_;
};

template <typename T>
void CircularLinkedList<T>::clear() {
    if (!head_) return;
    auto current = head_;
    while (1)   {
        auto temp = current;
        current = current->next;
        delete temp;
        if (current == head_) break;
    }

    head_ = nullptr;
    tail_ = nullptr;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList() : head_(nullptr), tail_(nullptr) {}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    clear();
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& other) : head_(nullptr), tail_(nullptr) {
    auto current = other.head_;
    if (!current) return;
    while (1)   {
        push_back(current->data);
        current = current->next;
        if (current == other.head_) break;
    }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& other) {
    if (this != &other) {
        clear();
        auto current = other.head_;
        if (!current) return *this;
        while (1)   {
            push_back(current->data);
            current = current->next;
            if (current == other.head_) break;
        }
    }
    return *this;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(CircularLinkedList<T>&& other) noexcept : head_(other.head_), tail_(other.tail_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(CircularLinkedList<T>&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
    }
    return *this;
}

template <typename T>
T& CircularLinkedList<T>::operator[](size_t index) const {
    if (index >= size()) throw std::out_of_range("Index out of bounds.");
    auto target = head_->walk_to(index);
    return *target;
}

template <typename T>
void CircularLinkedList<T>::push_back(const T& input) {
    if (!head_)    {
        head_ = tail_ = new Node(input); // create head and tail first
        head_->next = tail_->next = head_;
        return;
    }

    auto new_tail = new Node(input);
    new_tail->next = head_;

    tail_->next = new_tail;
    tail_ = new_tail;
}

template <typename T>
void CircularLinkedList<T>::insert(size_t index, const T& input) {
    if (index > size()) throw std::out_of_range("insert: index out of bounds");

    if (!head_ && index == 0)    {
        head_ = tail_ = new Node(input); // create head and tail first
        head_->next = tail_->next = head_;
        return;
    }

    if (index == size())    {
        push_back(input);
        return;
    }

    auto inserted = new Node(input);

    if (index == 0) {
        tail_->next = inserted; // modif of head needs special handling
        inserted->next = head_;
        head_ = inserted;
        return;
    }

    auto current = head_->walk_to(index - 1);
    inserted->next = current->next;
    current->next = inserted;
}

template <typename T>
T CircularLinkedList<T>::pop_front() {
    if (!head_) throw std::runtime_error("pop_front: list is empty");

    if (head_->next == head_) {
        auto to_return = head_->data;
        clear();
        return to_return;
    }

    auto to_return = head_->data;
    auto temp = head_;
    tail_->next = head_->next;
    head_ = head_->next;
    delete temp;
    return to_return;
}

template <typename T>
void CircularLinkedList<T>::erase(size_t index) {
    if (index >= size())    {
        throw std::out_of_range("erase: index out of bounds.");
    }

    if (index == 0) {
        tail_->next = head_->next;
        auto erased = head_;
        head_ = head_->next;
        delete erased;
        return;
    }

    auto predecessor = head_->walk_to(index - 1);
    auto erased = predecessor->next;
    predecessor->next = erased->next;
    if (erased == tail_)    tail_ = predecessor;
    delete erased;


}

template <typename T>
size_t CircularLinkedList<T>::size() const {
    if (!head_) return 0;

    size_t count = 0;
    auto current = head_;
    do
    {
        ++count;
        current = current->next;
    } while (current != head_);
    return count;
}

template <typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::begin() const {
    return iterator(head_);
}

template <typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::end() const {
    return iterator(head_); // One past end, needs do while iteration
}

template <typename T>
CircularLinkedList<T>::iterator::iterator(Node* ptr_in) : ptr_(ptr_in) {}

template <typename T>
typename CircularLinkedList<T>::iterator& CircularLinkedList<T>::iterator::operator++() {
    ptr_ = ptr_->next;
    return *this;
}

template <typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::iterator::operator+(size_t incr) const {
    if (incr < 0) {
        throw std::invalid_argument("Increment must be positive");
    }
    auto ptr_copy = ptr_;
    while (incr > 0) {
        ptr_copy = ptr_copy->next;;
        --incr;
    }
    return CircularLinkedList<T>::iterator(ptr_copy);
}

template <typename T>
T& CircularLinkedList<T>::iterator::operator*() const {
    return ptr_->data;
}

template <typename T>
bool CircularLinkedList<T>::iterator::operator==(iterator rhs) const {
    return this->ptr_ == rhs.ptr_;
}

template <typename T>
bool CircularLinkedList<T>::iterator::operator!=(iterator rhs) const {
    return this->ptr_ != rhs.ptr_;
}

#endif // __LINKEDLIST_CIRCULAR_CIRCULAR_HPP