#include <iostream>
#include <unordered_set>
#include <list>
#include <functional> 
#include <algorithm> 

template <typename T>
class HashTable {
private:
    static const int default_capacity = 10;
    std::vector<std::list<T>> table;
    int size;
    int capacity;

    int hash(const T& key) const {
        return std::hash<T>()(key) % capacity;
    }

public:
    HashTable(int cap = default_capacity) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    bool find(const T& key) const {
        int index = hash(key);
        return std::find(table[index].begin(), table[index].end(), key) != table[index].end();
    }

    void insert(const T& key) {
        int index = hash(key);
        if (!find(key)) {
            table[index].push_back(key);
            size++;
        }
    }

    void remove(const T& key) {
        int index = hash(key);
        table[index].remove(key);
        size--;
    }

    int getSize() const {
        return size;
    }
};

template <typename T>
class SymbolTable
{
private:
    HashTable<T> symbols;
public:
    bool get(const T& key) {
        return symbols.find(key);
    }

    void insert(const T& symbol) {
        symbols.insert(symbol);
    }

    void remove(const T& symbol) {
        symbols.remove(symbol);
    }

    int size() const {
        return symbols.getSize();
    }
};



int main()
{
    SymbolTable<std::string> st;
    st.insert("a");
    st.insert("b");
    std::cout << st.size() << std::endl;
    st.insert("c");
    st.remove("b");
    std::cout << st.size() << std::endl;
    if (st.get("c") && st.get("b"))
        std::cout << "Not working" << std::endl;
    else if (st.get("c") && !st.get("b"))
        std::cout << "Working" << std::endl;
    std::cout << st.get("a") << std::endl;
    std::cout << st.get("c") << std::endl;
    std::cout << st.get("b") << std::endl;

    return 0;
}


