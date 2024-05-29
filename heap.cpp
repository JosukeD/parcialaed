#include <iostream>
#include <vector>
#include <stdexcept>

class Heap {
protected:
    std::vector<int> data;

    virtual void heapifyUp(int index) = 0;
    virtual void heapifyDown(int index) = 0;

public:
    Heap() {}

    void insert(int value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    int extractTop() {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        int topValue = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            heapifyDown(0);
        }
        return topValue;
    }

    bool isEmpty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }

    void printHeap() const {
        for (int value : data) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

class MaxHeap : public Heap {
protected:
    void heapifyUp(int index) override {
        if (index == 0) return;
        int parentIndex = (index - 1) / 2;
        if (data[parentIndex] < data[index]) {
            std::swap(data[parentIndex], data[index]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) override {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int largest = index;

        if (leftChildIndex < data.size() && data[leftChildIndex] > data[largest]) {
            largest = leftChildIndex;
        }
        if (rightChildIndex < data.size() && data[rightChildIndex] > data[largest]) {
            largest = rightChildIndex;
        }
        if (largest != index) {
            std::swap(data[index], data[largest]);
            heapifyDown(largest);
        }
    }

public:
    int extractMax() {
        return extractTop();
    }
};

class MinHeap : public Heap {
protected:
    void heapifyUp(int index) override {
        if (index == 0) return;
        int parentIndex = (index - 1) / 2;
        if (data[parentIndex] > data[index]) {
            std::swap(data[parentIndex], data[index]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) override {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallest = index;

        if (leftChildIndex < data.size() && data[leftChildIndex] < data[smallest]) {
            smallest = leftChildIndex;
        }
        if (rightChildIndex < data.size() && data[rightChildIndex] < data[smallest]) {
            smallest = rightChildIndex;
        }
        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    int extractMin() {
        return extractTop();
    }
};

int main() {
    MaxHeap maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(7);
    maxHeap.insert(8);
    maxHeap.insert(15);

    std::cout << "MaxHeap elements: ";
    maxHeap.printHeap();
    std::cout << "Extracted max: " << maxHeap.extractMax() << std::endl;
    std::cout << "MaxHeap elements after extraction: ";
    maxHeap.printHeap();

    MinHeap minHeap;
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(5);
    minHeap.insert(7);
    minHeap.insert(8);
    minHeap.insert(15);

    std::cout << "MinHeap elements: ";
    minHeap.printHeap();
    std::cout << "Extracted min: " << minHeap.extractMin() << std::endl;
    std::cout << "MinHeap elements after extraction: ";
    minHeap.printHeap();

    return 0;
}
