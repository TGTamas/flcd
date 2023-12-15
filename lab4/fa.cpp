#include "fa.h"
#include <iostream>

void FiniteAutomata::readFileList(std::ifstream& in, std::string version) {
    //Get the current vector, which needs to be modified
    std::vector<std::string>* workingVector;
    if (version == "states") workingVector = &this->states;
    else if (version == "finalStates") workingVector = &this->finalStates;
    else workingVector = &this->alphabet;

    std::string var;
    while (in >> var) {
        //Check for end of the list and start of the list
        if (var == "}") break;
        if (var == "{") continue;

        //Read and append the list of elements
        workingVector->push_back(var);
    }
}

void FiniteAutomata::readTransitions(std::ifstream& in) {
    std::string var;
    while (in >> var) {
        //Check for end of the list and start of the list
        if (var == "}") break;
        if (var == "{") continue;

        //Handle case of pairs
        char from = var[1];
        char value = var[3];
        char to = var[5];

        this->transitions.insert({ std::make_pair(from, value), to });
    }
}

void FiniteAutomata::readFromFile(std::ifstream& in) {
    //For all the components treat the reading
    std::string componentName;
    while (in >> componentName) {
        if (componentName == "initialState") {
            in >> this->initialState;
        }
        else if (componentName == "transitions") {
            this->readTransitions(in);
        }
        else {
            this->readFileList(in, componentName);
        }
    }
}

FiniteAutomata::FiniteAutomata(std::string fileName) {
    //Read the elements from the file
    std::ifstream in(fileName);
    this->readFromFile(in);
    in.close();
}

void FiniteAutomata::printVector(std::vector<std::string> vec) {
    std::cout << std::endl << "{";
    for (auto i : vec) {
        std::cout << i << ",";
    }
    std::cout << "}" << std::endl;
}

void FiniteAutomata::printStates() { this->printVector(this->states); }

void FiniteAutomata::printFinalStates() { this->printVector(this->finalStates); }

void FiniteAutomata::printAlphabet() { this->printVector(this->alphabet); }

void FiniteAutomata::printInitialState() {
    std::cout << std::endl << this->initialState << std::endl;
}

void FiniteAutomata::printTransitions() {
    std::cout << std::endl;
    for (const auto& elem : this->transitions)
    {
        std::cout << elem.first.first << "," << elem.first.second << "->" << elem.second << std::endl;
    }
    std::cout << std::endl;
}

bool FiniteAutomata::checkWord(std::string word) {
    //Starting at the initial state
    char state = this->initialState[0];

    //Going through the letters of the word
    for (auto i : word) {
        std::pair<char, char> currentKey = std::make_pair(state, i);
        if (this->transitions.count(currentKey) == 1) {
            state = this->transitions.at(currentKey);
        }
        else {
            return false;
        }
    }

    //Check if the state is one of the final states
    for (auto i : this->finalStates) {
        if (state == i[0]) return true;
    }

    return false;
}

std::string FiniteAutomata::getAccepted(std::string sequence) {
    //Starting at the initial state
    char state = this->initialState[0];
    std::string word;

    //Going through the letters of the word
    for (auto i : sequence) {
        std::pair<char, char> currentKey = std::make_pair(state, i);
        if (this->transitions.count(currentKey) == 1) {
            state = this->transitions.at(currentKey);
            word += i;
        }
        else break;
    }

    //Check if the state is one of the final states
    for (auto i : this->finalStates) {
        if (state == i[0]) return word;
    }

    return "--";
}