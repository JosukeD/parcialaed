#include <iostream>
#include <vector>

using namespace std;

class Trie {
public:
    struct Node {
        Node* links[26];
        bool flag = false;
        
        bool isContains(char ch) {
            return links[ch - 'a'] != nullptr;
        }
        
        void put(char ch, Node* node) {
            links[ch - 'a'] = node;
        }
        
        Node* get(char ch) {
            return links[ch - 'a'];
        }
        
        void setEnd() {
            flag = true;
        }
        
        bool isEnd() {
            return flag;
        }
    };

    Node* root;
    
    Trie() {
        root = new Node();
    }
    
    void insert(const char* str) {
        Node* node = root;
        int len = length(str);
        for (int i = len - 1; i >= 0; i--) {
            if (!node->isContains(str[i])) {
                node->put(str[i], new Node());
            }
            node = node->get(str[i]);
        }
        node->setEnd();
    }
    
    bool check(const char* str) {
        Node* node = root;
        int len = length(str);
        for (int i = len - 1; i >= 0; i--) {
            if (node->isContains(str[i])) {
                node = node->get(str[i]);
                if (node->isEnd()) return true;
            } else {
                return false;
            }
        }
        return false;
    }

private:
    int length(const char* str) {
        int len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }
};

class StreamChecker {
public:
    Trie *trie;
    char str[2000];
    int index;
    
    StreamChecker(vector<const char*>& words) {
        trie = new Trie();
        for (int i = 0; i < words.size(); i++) {
            trie->insert(words[i]);
        }
        str[0] = '\0';
        index = 0;
    }
    
    bool query(char letter) {
        str[index++] = letter;
        str[index] = '\0';
        return trie->check(str);
    }
};

int main() {
    vector<const char*> words = {"cd", "f", "kl"};
    StreamChecker streamChecker(words);
    
    cout << boolalpha;
    cout << streamChecker.query('a') << endl; // false
    cout << streamChecker.query('b') << endl; // false
    cout << streamChecker.query('c') << endl; // false
    cout << streamChecker.query('d') << endl; // true
    cout << streamChecker.query('e') << endl; // false
    cout << streamChecker.query('f') << endl; // true
    cout << streamChecker.query('g') << endl; // false
    cout << streamChecker.query('h') << endl; // false
    cout << streamChecker.query('i') << endl; // false
    cout << streamChecker.query('j') << endl; // false
    cout << streamChecker.query('k') << endl; // false
    cout << streamChecker.query('l') << endl; // true
    
    return 0;
}
