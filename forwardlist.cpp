#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class ForwardList {
private:
    Node<T>* head;
    Node<T>* tail;
    int list_size;

public:
    ForwardList() : head(nullptr), tail(nullptr), list_size(0) {}
    ~ForwardList() { clear(); }

    T back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    void push_front(T value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = head;
        head = new_node;
        if (!tail) tail = new_node;
        list_size++;
    }

    void push_back(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (tail) {
            tail->next = new_node;
        } else {
            head = new_node;
        }
        tail = new_node;
        list_size++;
    }

    T pop_front() {
        if (empty()) throw std::out_of_range("List is empty");
        Node<T>* temp = head;
        T value = head->data;
        head = head->next;
        delete temp;
        if (!head) tail = nullptr;
        list_size--;
        return value;
    }

    T pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        if (head == tail) {
            T value = head->data;
            delete head;
            head = tail = nullptr;
            list_size--;
            return value;
        }
        Node<T>* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        T value = tail->data;
        delete tail;
        tail = current;
        tail->next = nullptr;
        list_size--;
        return value;
    }

    T operator[](int index) {
        if (index < 0 || index >= list_size) throw std::out_of_range("Index out of range");
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        return list_size;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void sort() {
        if (list_size < 2) return;
        head = merge_sort(head);
        // Reset tail after sorting
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        tail = current;
    }

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        tail = head;
        while (current) {
            Node<T>* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

private:
    Node<T>* merge_sort(Node<T>* node) {
        if (!node || !node->next) return node;
        Node<T>* middle = get_middle(node);
        Node<T>* next_to_middle = middle->next;
        middle->next = nullptr;

        Node<T>* left = merge_sort(node);
        Node<T>* right = merge_sort(next_to_middle);

        return merge(left, right);
    }

    Node<T>* get_middle(Node<T>* node) {
        if (!node) return node;
        Node<T>* slow = node;
        Node<T>* fast = node->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node<T>* merge(Node<T>* left, Node<T>* right) {
        if (!left) return right;
        if (!right) return left;
        if (left->data < right->data) {
            left->next = merge(left->next, right);
            left->next->next = nullptr;
            return left;
        } else {
            right->next = merge(left, right->next);
            right->next->next = nullptr;
            return right;
        }
    }
};
