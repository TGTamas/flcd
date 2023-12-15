#include "lexical-analyzer.h"
#include <regex>
#include <iostream>
#include "fa.h"

Scanner::Scanner(std::ifstream& programFile, std::ifstream& tokensFile) {
    this->program = fileToString(programFile);
    programFile.close();
    this->tokens = fileToVector(tokensFile);
    tokensFile.close();
}

std::vector<std::pair<tokenType, std::pair<int, int>>> Scanner::getPif() {
    return this->pif;
}

SymbolTable<std::string> Scanner::getST() {
    return this->st;
}

std::vector<std::string> Scanner::getTokens() {
    return this->tokens;
}

std::string Scanner::fileToString(std::ifstream& file) {
    std::string outputString;
    std::string var;
    while (std::getline(file, var)) {
        outputString += var + "\n";
    }
    return outputString;
}

std::vector<std::string> Scanner::fileToVector(std::ifstream& file) {
    std::vector<std::string> returnValue;
    std::string var;
    while (file >> var) {
        returnValue.push_back(var);
    }
    return returnValue;
}

void Scanner::scan() {
    while (this->index < this->program.size()) {
        this->nextToken();
    }
}

void Scanner::skipWhiteSpaces() {
    while (this->index < this->program.size()) {
        if (this->program[this->index] != ' ' && this->program[this->index] != 13 && this->program[this->index] != 10) {
            this->tokenIndex++;
            return;
        }
        
        if (this->program[this->index] == '\n') {
            this->rowNumber++;
            this->tokenIndex = 0;
        }

        this->index++;
    }
}

void Scanner::nextToken() {
    this->skipWhiteSpaces();

    if (this->index >= this->program.size())
        return;

    if (this->treatIntConstant())
        return;
    if (this->treatBoolConstant())
        return;
    if (this->treatCharConstant())
        return;
    if (this->treatStringConstant())
        return;
    if (this->treatToken())
        return;
    if (this->treatIdentifier())
        return;

    throw std::string("Lexical Error: Not identified token at line: " + std::to_string(this->rowNumber) + ", token: " + std::to_string(this->tokenIndex));
}

bool Scanner::startsWith(std::string& b) {
    return this->program.substr(this->index).find(b) == 0;
}

bool Scanner::treatToken() {
    for (int i = 0; i < this->operatorIndex; i++) {
        if (startsWith(this->tokens[i])) {
            this->pif.push_back(std::make_pair(Operator, std::make_pair(i, -1)));
            this->index += this->tokens[i].size();
            return true;
        }
    }
    for (int i = this->operatorIndex; i < this->separatorIndex; i++) {
        if (startsWith(this->tokens[i])) {
            this->pif.push_back(std::make_pair(Separator, std::make_pair(i, -1)));
            this->index += this->tokens[i].size();
            return true;
        }
    }
    for (int i = this->separatorIndex; i < this->reservedWordIndex; i++) {
        std::string wordBoundary = R"()\b)";
        std::string formStart = R"(^()";
        std::string formString = formStart + this->tokens[i] + wordBoundary;
        std::regex form(formString);
 
        auto start = std::sregex_iterator(this->program.begin() + this->index, this->program.end(), form);
        auto end = std::sregex_iterator();

       if (start != end) {
            auto match = *start;
            if (match.prefix() != "")
                continue;
            std::string element = match[1].str();

            this->pif.push_back(std::make_pair(ReservedWord, std::make_pair(i, -1)));
            this->index += this->tokens[i].size();
            return true;
        }

    }
    return false;
}

bool Scanner::treatIntConstant() {
    /*std::regex form("^([+-]?[1-9][0-9]*|0)\\b");
    auto start = std::sregex_iterator(this->program.begin() + this->index, this->program.end(), form);
    auto end = std::sregex_iterator();

    if (start != end) {
        auto match = *start;
        if (match.prefix() != "")
            return false;
        std::string element = match[1].str();

        if ((element[0] == '+' || element[0] == '-') && this->pif.size() != 0 && (this->pif.back().first == Identifier || this->pif.back().first == Int))
            return false;

        this->index += element.size();
        std::pair<int, int> pos = this->st.addConstant(element);
        this->pif.push_back(std::make_pair(Int, pos));
        return true;
    }*/
    FiniteAutomata automata("integer.in");
    std::string word = automata.getAccepted(this->program.substr(this->index, this->program.size() - this->index));

    //Check if we found an integer
    if (word.empty() || word == "--") return false;

    // Check if the current element has a prefix, or is part of an operation
    if ((word[0] == '+' || word[0] == '-') && this->pif.size() != 0 && (this->pif.back().first == Identifier || this->pif.back().first == Int))
        return false;

    //Check if next element not an integer or letter
    char nextChar = this->program[this->index + word.size()];
    if ((nextChar >= 48 && nextChar <= 57) || (nextChar >= 65 && nextChar <= 90) || (nextChar >= 97 && nextChar <= 122))
        return false;

    //Increment the index and store the token
    this->index += word.size();
    std::pair<int, int> pos = this->st.addConstant(word);
    this->pif.push_back(std::make_pair(Int, pos));
    return false;
}

bool Scanner::treatBoolConstant() {
    std::regex form("^(true|false)\\b");
    auto start = std::sregex_iterator(this->program.begin() + this->index, this->program.end(), form);
    auto end = std::sregex_iterator();

    if (start != end) {
        auto match = *start;
        if (match.prefix() != "")
            return false;
        std::string element = match[1].str();

        this->index += element.size();
        std::pair<int, int> pos = this->st.addConstant(element);
        this->pif.push_back(std::make_pair(Bool, pos));
        return true;
    }
    return false;
}

bool Scanner::treatCharConstant() {
    std::regex form("^'([a-zA-Z0-9])'\\B");
    auto start = std::sregex_iterator(this->program.begin() + this->index, this->program.end(), form);
    auto end = std::sregex_iterator();

    if (start != end) {
        auto match = *start;
        if (match.prefix() != "")
            return false;
        std::string element = match[1].str();

        this->index += element.size();
        std::pair<int, int> pos = this->st.addConstant(element.substr(1, element.size() - 2));
        this->pif.push_back(std::make_pair(Char, pos));
        return true;
    }
    return false;
}

bool Scanner::treatStringConstant() {
    std::regex form("^\"([a-zA-Z0-9 ]*)\"\\B");
    auto start = std::sregex_iterator(this->program.begin() + this->index, this->program.end(), form);
    auto end = std::sregex_iterator();

    if (start != end) {
        auto match = *start;
        if (match.prefix() != "")
            return false;
        std::string element = match[1].str();

        this->index += element.size();
        std::pair<int, int> pos = this->st.addStringConstant(element.substr(1, element.size() - 2));
        this->pif.push_back(std::make_pair(String, pos));
        return true;
    }
    return false;
}

bool Scanner::treatIdentifier() {
    /*std::regex form("^([a-zA-Z][a-zA-Z0-9]*)\\b");
    auto start = std::sregex_iterator(this->program.begin() + this->index, this->program.end(), form);
    auto end = std::sregex_iterator();

    if (start != end) {
        auto match = *start;
        if (match.prefix() != "")
            return false;
        std::string element = match[1].str();

        this->index += element.size();
        std::pair<int, int> pos = this->st.addIdentifier(element);
        this->pif.push_back(std::make_pair(Identifier, pos));
        return true;
    }*/
    FiniteAutomata automata("identifier.in");
    std::string word = automata.getAccepted(this->program.substr(this->index, this->program.size() - this->index));

    //Check if we found an identifier
    if (word.empty() || word == "--") return false;

    //Increment the index and store the token
    this->index += word.size();
    std::pair<int, int> pos = this->st.addIdentifier(word);
    this->pif.push_back(std::make_pair(Identifier, pos));

    return false;
}