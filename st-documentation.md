## Link to Github

https://github.com/TGTamas/flcd

# Symbol Table with HashTable Implementation

## Overview
This documentation provides a brief overview of the `SymbolTable` class, which utilizes a hash table to store and manage symbols.

## Classes and their Description

### 1. HashTable<T>
A generic template class that implements a simple hash table.

#### Attributes:
- **default_capacity**: An integer constant representing the default capacity of the hash table.
- **table**: A vector of lists representing the buckets of the hash table. Each bucket contains elements of type `T`.
- **size**: The current number of elements in the hash table.
- **capacity**: The maximum capacity of the hash table.

#### Methods:
- **HashTable(int cap = default_capacity)**: Constructor that initializes the hash table with a given capacity or the default capacity.
- **int hash(const T& key) const**: Private method to hash the given key and determine its position in the table.
- **int find(const T& key) const**: Returns the index of the bucket where the key is located, or `-1` if the key is not present in the table.
- **void insert(const T& key)**: Inserts the key into the hash table, if it's not already present.
- **void remove(const T& key)**: Removes the key from the hash table.
- **int getSize() const**: Returns the current size of the hash table.

### 2. SymbolTable<T>
A generic template class representing a symbol table.

#### Attributes:
- **symbols**: An instance of the HashTable class.

#### Methods:
- **int get(const T& key)**: Retrieves the position of the symbol. If found, it returns the index of the bucket, otherwise returns `-1`.
- **void insert(const T& symbol)**: Inserts a symbol into the table.
- **void remove(const T& symbol)**: Removes a symbol from the table.
- **int size() const**: Returns the current number of symbols in the table.

## Example Usage
```cpp
SymbolTable<std::string> st;
st.insert("a");
st.insert("b");
std::cout << st.size() << std::endl;  // Outputs: 2
st.insert("c");
st.remove("b");
std::cout << st.size() << std::endl;  // Outputs: 2
```

## Important Notes
- The capacity of the HashTable will remain static after its creation. There's no dynamic resizing implemented.
- The hash function used is the default std::hash function provided by the C++ Standard Library.
- Each bucket of the hash table can store multiple elements, which means that there can be collisions. The class uses chaining to handle these collisions.