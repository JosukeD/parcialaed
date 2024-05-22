#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int list_size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), list_size(0) {}
    ~DoublyLinkedList() { clear(); }

    T front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    void push_front(T value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = head;
        if (head) {
            head->prev = new_node;
        }
        head = new_node;
        if (!tail) {
            tail = new_node;
        }
        list_size++;
    }

    void push_back(T value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->prev = tail;
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
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        list_size--;
        return value;
    }

    T pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        Node<T>* temp = tail;
        T value = tail->data;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        list_size--;
        return value;
    }

    void insert(T value, int index) {
        if (index < 0 || index > list_size) throw std::out_of_range("Index out of range");
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == list_size) {
            push_back(value);
            return;
        }
        Node<T>* new_node = new Node<T>(value);
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
        list_size++;
    }

    void remove(int index) {
        if (index < 0 || index >= list_size) throw std::out_of_range("Index out of range");
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == list_size - 1) {
            pop_back();
            return;
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        list_size--;
    }

    T operator[](int index) {
        if (index < 0 || index >= list_size) throw std::out_of_range("Index out of range");
        Node<T>* current = head;
        for (int i = 0; i <= index; i++) {
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

    void reverse() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp) {
            head = temp->prev;
        }
    }
};

int main() {
    DoublyLinkedList<int> dll;
    dll.push_back(1);
    dll.push_back(2);
    dll.push_back(3);
    std::cout << "Front: " << dll.front() << std::endl;
    std::cout << "Back: " << dll.back() << std::endl;
    dll.push_front(0);
    std::cout << "Front after push_front: " << dll.front() << std::endl;
    dll.pop_back();
    std::cout << "Back after pop_back: " << dll.back() << std::endl;
    dll.insert(5, 1);
    std::cout << "Element at index 1 after insert: " << dll[1] << std::endl;
    dll.remove(1);
    std::cout << "Element at index 1 after remove: " << dll[1] << std::endl;
    std::cout << "Size: " << dll.size() << std::endl;
    dll.clear();
    std::cout << "Size after clear: " << dll.size() << std::endl;
    return 0;
}
