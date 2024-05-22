#include <iostream>

class Queue {
private:
    int* arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    // Constructor to initialize the queue
    Queue(int size) {
        arr = new int[size];
        capacity = size;
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    // Destructor to clean up memory
    ~Queue() {
        delete[] arr;
    }

    // Function to add an element to the queue
    void enqueue(int x) {
        if (isfull()) {
            std::cout << "Queue overflow\n";
            return;
        }
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = x;
        count++;
    }

    // Function to remove the front element from the queue
    void dequeue() {
        if (isempty()) {
            std::cout << "Queue underflow\n";
            return;
        }
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    // Function to return the front element of the queue
    int front() {
        if (!isempty()) {
            return arr[frontIndex];
        } else {
            std::cout << "Queue is empty\n";
            return -1; // Returning -1 as an error value
        }
    }

    // Function to check if the queue is empty
    bool isempty() {
        return count == 0;
    }

    // Function to check if the queue is full
    bool isfull() {
        return count == capacity;
    }
};

int main() {
    Queue queue(5); // Queue of capacity 5

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);

    std::cout << "Front element is: " << queue.front() << "\n";

    queue.dequeue();
    queue.dequeue();

    std::cout << "Front element after dequeue operations is: " << queue.front() << "\n";

    queue.enqueue(6);

    std::cout << "Front element after enqueueing 6 is: " << queue.front() << "\n";

    return 0;
}
