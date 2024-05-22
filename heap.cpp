#include <iostream>
#include <vector>
#include <stdexcept>

class MaxHeap {
private:
    std::vector<int> heap;

    // Get the parent index of a given node
    int parent(int i) { return (i - 1) / 2; }

    // Get the left child index of a given node
    int left(int i) { return 2 * i + 1; }

    // Get the right child index of a given node
    int right(int i) { return 2 * i + 2; }

    // Heapify up to maintain the max-heap property
    void heapifyUp(int index) {
        while (index != 0 && heap[parent(index)] < heap[index]) {
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    // Heapify down to maintain the max-heap property
    void heapifyDown(int index) {
        int largest = index;
        int leftChild = left(index);
        int rightChild = right(index);

        if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap() {}

    // Insert a new element into the heap
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Extract the maximum element from the heap
    int extractMax() {
        if (heap.size() == 0) {
            throw std::runtime_error("Heap is empty");
        }

        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return root;
    }

    // Get the maximum element from the heap
    int getMax() const {
        if (heap.size() == 0) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // Check if the heap is empty
    bool isEmpty() const {
        return heap.size() == 0;
    }

    // Print the elements of the heap
    void printHeap() const {
        for (int value : heap) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MaxHeap heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    heap.insert(15);

    std::cout << "Heap elements: ";
    heap.printHeap();

    std::cout << "Maximum element: " << heap.getMax() << std::endl;

    std::cout << "Extracted maximum element: " << heap.extractMax() << std::endl;

    std::cout << "Heap elements after extraction: ";
    heap.printHeap();

    return 0;
}
