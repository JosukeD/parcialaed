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
class CircularDoublyLinkedList {
private:
    Node<T>* head;
    int list_size;

public:
    CircularDoublyLinkedList() : head(nullptr), list_size(0) {}
    ~CircularDoublyLinkedList() { clear(); }

    T front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T back() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->prev->data;
    }

    void push_front(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (empty()) {
            head = new_node;
            head->next = head;
            head->prev = head;
        } else {
            new_node->next = head;
            new_node->prev = head->prev;
            head->prev->next = new_node;
            head->prev = new_node;
            head = new_node;
        }
        list_size++;
    }

    void push_back(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (empty()) {
            head = new_node;
            head->next = head;
            head->prev = head;
        } else {
            new_node->next = head;
            new_node->prev = head->prev;
            head->prev->next = new_node;
            head->prev = new_node;
        }
        list_size++;
    }

    T pop_front() {
        if (empty()) throw std::out_of_range("List is empty");
        Node<T>* temp = head;
        T value = head->data;
        if (head->next == head) {
            head = nullptr;
        } else {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
        }
        delete temp;
        list_size--;
        return value;
    }

    T pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        Node<T>* temp = head->prev;
        T value = temp->data;
        if (head->next == head) {
            head = nullptr;
        } else {
            temp->prev->next = head;
            head->prev = temp->prev;
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

    void reverse() {
        if (empty()) return;
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        do {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        } while (current != head);
        head = head->next;
    }
};

int main() {
    CircularDoublyLinkedList<int> cdll;
    cdll.push_back(1);
    cdll.push_back(2);
    cdll.push_back(3);
    std::cout << "Front: " << cdll.front() << std::endl;
    std::cout << "Back: " << cdll.back() << std::endl;
    cdll.push_front(0);
    std::cout << "Front after push_front: " << cdll.front() << std::endl;
    cdll.pop_back();
    std::cout << "Back after pop_back: " << cdll.back() << std::endl;
    cdll.insert(5, 1);
    std::cout << "Element at index 1 after insert: " << cdll[1] << std::endl;
    cdll.remove(1);
    std::cout << "Element at index 1 after remove: " << cdll[1] << std::endl;
    std::cout << "Size: " << cdll.size() << std::endl;
    cdll.clear();
    std::cout << "Size after clear: " << cdll.size() << std::endl;
    return 0;
}
