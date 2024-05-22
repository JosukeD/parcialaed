#include <iostream>

class Stack {
private:
    int* arr;
    int capacity;
    int topIndex;

public:
    // Constructor to initialize stack
    Stack(int size) {
        arr = new int[size];
        capacity = size;
        topIndex = -1;
    }

    // Destructor to clean up memory
    ~Stack() {
        delete[] arr;
    }

    // Function to add an element to the stack
    void push(int x) {
        if (isfull()) {
            std::cout << "Stack overflow\n";
            return;
        }
        arr[++topIndex] = x;
    }

    // Function to pop the top element from the stack
    void pop() {
        if (isempty()) {
            std::cout << "Stack underflow\n";
            return;
        }
        --topIndex;
    }

    // Function to return the top element of the stack
    int top() {
        if (!isempty()) {
            return arr[topIndex];
        } else {
            std::cout << "Stack is empty\n";
            return -1; // Returning -1 as an error value
        }
    }

    // Function to check if the stack is empty
    bool isempty() {
        return topIndex == -1;
    }

    // Function to check if the stack is full
    bool isfull() {
        return topIndex == capacity - 1;
    }
};

int main() {
    Stack stack(5); // Stack of capacity 5

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    std::cout << "Top element is: " << stack.top() << "\n";

    stack.pop();
    stack.pop();

    std::cout << "Top element after pop operations is: " << stack.top() << "\n";

    stack.push(6);

    std::cout << "Top element after pushing 6 is: " << stack.top() << "\n";

    return 0;
}
