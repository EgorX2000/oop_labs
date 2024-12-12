#pragma once

#include <iterator>
#include <memory_resource>

#include "Allocator.hpp"

template <typename T>
class UnidirectionalList {
   private:
    struct Node {
        T value;
        Node* next;

        Node(const T& val, Node* nxt) : value(val), next(nxt) {}
    };

    Node* head_ = nullptr;
    std::pmr::polymorphic_allocator<Node> allocator_;

   public:
    explicit UnidirectionalList(std::pmr::memory_resource* resource)
        : allocator_(resource) {}

    ~UnidirectionalList() { clear(); }

    void push_front(const T& value) {
        Node* newNode = allocator_.allocate(1);
        allocator_.construct(newNode, value, head_);
        head_ = newNode;
    }

    void clear() {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next;
            allocator_.destroy(temp);
            allocator_.deallocate(temp, 1);
        }
    }

    class Iterator {
       public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* node) : current_(node) {}

        reference operator*() const { return current_->value; }

        pointer operator->() const { return &(current_->value); }

        Iterator& operator++() {
            current_ = current_->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

       private:
        Node* current_;
    };

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }
};