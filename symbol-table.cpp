#include <iostream>
#include <unordered_set>

template <typename T>
class SymbolTable
{
private:
    //TODO make own dataset
    std::unordered_set<T> symbols;
public:
    T get(int pozition);
    void insert(T symbol);
};

template<typename T>
T SymbolTable<T>::get(int pozition)
{
    return this.symbols.find(pozition);
}

template<typename T>
void SymbolTable<T>::insert(T symbol)
{
    this.symbols.insert(symbol);
}



int main()
{
    //TEST
}


