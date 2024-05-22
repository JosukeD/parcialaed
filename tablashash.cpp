#include <iostream>
#include <string>

// Node class for chaining in hash table
template <typename K, typename V>
class HashNode {
public:
    K key;
    V value;
    HashNode* next;

    HashNode(K key, V value) : key(key), value(value), next(nullptr) {}
};

// Hash map class
template <typename K, typename V>
class HashMap {
private:
    HashNode<K, V>** table;
    int capacity;
    int size;

    // Hash function
    int hash(K key) {
        return std::hash<K>()(key) % capacity;
    }

public:
    // Constructor to initialize the hash table
    HashMap(int capacity) : capacity(capacity), size(0) {
        table = new HashNode<K, V>*[capacity]();
    }

    // Destructor to clean up memory
    ~HashMap() {
        for (int i = 0; i < capacity; ++i) {
            HashNode<K, V>* entry = table[i];
            while (entry != nullptr) {
                HashNode<K, V>* prev = entry;
                entry = entry->next;
                delete prev;
            }
            table[i] = nullptr;
        }
        delete[] table;
    }

    // Insert key-value pair
    void insert(K key, V value) {
        int hashIndex = hash(key);
        HashNode<K, V>* prev = nullptr;
        HashNode<K, V>* entry = table[hashIndex];

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            entry = new HashNode<K, V>(key, value);
            if (prev == nullptr) {
                table[hashIndex] = entry;
            } else {
                prev->next = entry;
            }
            ++size;
        } else {
            entry->value = value;
        }
    }

    // Retrieve value by key
    V get(K key) {
        int hashIndex = hash(key);
        HashNode<K, V>* entry = table[hashIndex];

        while (entry != nullptr) {
            if (entry->key == key) {
                return entry->value;
            }
            entry = entry->next;
        }

        throw std::runtime_error("Key not found");
    }

    // Remove key-value pair
    void remove(K key) {
        int hashIndex = hash(key);
        HashNode<K, V>* prev = nullptr;
        HashNode<K, V>* entry = table[hashIndex];

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            std::cout << "Key not found\n";
            return;
        } else {
            if (prev == nullptr) {
                table[hashIndex] = entry->next;
            } else {
                prev->next = entry->next;
            }
            delete entry;
            --size;
        }
    }

    // Check if hash map is empty
    bool isempty() const {
        return size == 0;
    }

    // Get the size of the hash map
    int getSize() const {
        return size;
    }
};

int main() {
    HashMap<std::string, int> map(10);

    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);

    std::cout << "Value for key 'one': " << map.get("one") << std::endl;
    std::cout << "Value for key 'two': " << map.get("two") << std::endl;
    std::cout << "Value for key 'three': " << map.get("three") << std::endl;

    map.remove("two");

    try {
        std::cout << "Value for key 'two': " << map.get("two") << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
