#include <vector>
#include "symbol-table.cpp"
#include <fstream>
#include <string>

enum tokenType {
    Operator,
    Separator,
    ReservedWord,
    Identifier,
    Int,
    Bool,
    Char,
    String
};

class Scanner {
private:
    SymbolTable<std::string> st;
    std::vector<std::pair<tokenType, std::pair<int, int>>> pif;
    int index = 0;
    int rowNumber = 1;
    int tokenIndex = 0;
    std::string program;
    std::vector<std::string> tokens;
    int operatorIndex = 17;
    int separatorIndex = 28;
    int reservedWordIndex = 42;

    std::string fileToString(std::ifstream& file);
    std::vector<std::string> fileToVector(std::ifstream& file);

    void skipWhiteSpaces();
    bool startsWith(std::string& b);
public:
    Scanner(std::ifstream& programFile, std::ifstream& tokensFile);
    std::vector<std::pair<tokenType, std::pair<int, int>>> getPif();
    SymbolTable<std::string> getST();
    std::vector<std::string> getTokens();

    void scan();

    void nextToken();

    bool treatToken();

    bool treatIdentifier();
    bool treatIntConstant();
    bool treatBoolConstant();
    bool treatCharConstant();
    bool treatStringConstant();
};