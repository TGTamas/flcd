#include <iostream>
#include <functional> 
#include <algorithm> 
#include <fstream>
#include <unordered_map>
#include <unordered_set>

template <typename T>
class HashTable {
private:
    static const int default_capacity = 50;
    std::unordered_map<int, std::unordered_set<T>> table;
    int size;
    int capacity;

    int hash(const T& key) const {
        return std::hash<T>()(key) % capacity;
    }

public:
    HashTable(int cap = default_capacity) : capacity(cap), size(0) {
    }

    std::pair<int,int> find(const T& key) const {
        int index = hash(key);
        auto it = table.find(index);
        if (it != table.end()) {
            const std::unordered_set<T>& set = it->second;
            auto set_it = set.find(key);
            if (set_it != set.end()) {
                int i = std::distance(set.begin(), set_it);
                return std::make_pair(index, i);
            }
        }
        return std::make_pair(-1, -1);
    }

    std::string getById(int bucketIndex, int listIndex) {
        if (bucketIndex < 0 || bucketIndex >= capacity) {
            throw std::invalid_argument("Invalid bucket index.");
        }

        auto bucketIt = table.find(bucketIndex);
        if (bucketIt != table.end()) {
            const std::unordered_set<T>& keySet = bucketIt->second;
            if (listIndex < 0 || listIndex >= keySet.size()) {
                throw std::invalid_argument("Invalid list index.");
            }

            auto setIt = keySet.begin();
            std::advance(setIt, listIndex);
            return *setIt;
        }
        else {
            throw std::invalid_argument("Invalid bucket index.");
        }
    }

    std::pair<int,int> insert(const T& key) {
        int index = hash(key);
        if (find(key).first == -1) {
            table[index].insert(key);
            size++;
        }
        return find(key);
    }

    void remove(const T& key) {
        int index = hash(key);
        auto it = table.find(index);
        if (it != table.end()) {
            std::unordered_set<T>& keySet = it->second;
            auto set_it = keySet.find(key);
            if (set_it != keySet.end()) {
                keySet.erase(set_it);
                size--;
            }
        }
    }

    int getSize() const {
        return size;
    }

    void printHashTable(std::ofstream& out) {
        for (const auto& entry : table) {
            int index = entry.first;
            const std::unordered_set<T>& keySet = entry.second;

            out << index << " -> [";
            for (const T& key : keySet) {
                out << key << ", ";
            }
            out << "]" << std::endl;
        }
    }
};

template <typename T>
class SymbolTable
{
private:
    HashTable<T> symbols;
public:
    std::pair<int,int> find(const T& key) {
        return symbols.find(key);
    }

    std::string get(int bucketIndex, int listIndex) {
        return symbols.getById(bucketIndex, listIndex);
    }

    std::pair<int, int> addIdentifier(std::string value) {
        return symbols.insert(value);
    }
    std::pair<int, int> addConstant(std::string value) {
        return symbols.insert(value);
    }
    std::pair<int, int> addStringConstant(std::string value) {
        return symbols.insert("\"" + value + "\"");
    }
    std::pair<int, int> addCharConstant(std::string value) {
        return symbols.insert("\'" + value + "\'");
    }

    std::pair<int, int> findIdentifier(std::string value) {
        return symbols.find(value);
    }
    std::pair<int, int> findConstant(std::string value) {
        return symbols.find(value);
    }
    std::pair<int, int> findStringConstant(std::string value) {
        return symbols.find("\"" + value + "\"");
    }
    std::pair<int, int> findCharConstant(std::string value) {
        return symbols.find("\'" + value + "\'");
    }

    std::string getIdentifier(int bucketIndex, int listIndex) {
        return symbols.getById(bucketIndex, listIndex);
    }
    std::string getConstant(int bucketIndex, int listIndex) {
        return symbols.getById(bucketIndex, listIndex);
    }
    std::string getStringConstant(int bucketIndex, int listIndex) {
        std::string value = symbols.getById(bucketIndex, listIndex);
        value.erase(0, 1);
        return value.substr(0, value.find("\""));
    }
    std::string getCharConstant(int bucketIndex, int listIndex) {
        std::string value = symbols.getById(bucketIndex, listIndex);
        value.erase(0, 1);
        return value.substr(0, value.find("\'"));
    }

    void remove(const T& symbol) {
        symbols.remove(symbol);
    }

    int size() const {
        return symbols.getSize();
    }

    void printSymbolTable(std::ofstream& out) {
        symbols.printHashTable(out);
    }
};

