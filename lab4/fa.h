#include <fstream>
#include <vector>
#include <string>
#include <map>

class FiniteAutomata {
private:
    void readFromFile(std::ifstream& in);
    void readTransitions(std::ifstream& in);
    void readFileList(std::ifstream& in, std::string version);

    std::vector<std::string> states;
    std::vector<std::string> finalStates;
    std::vector<std::string> alphabet;
    std::string initialState;
    std::map<std::pair<char, char>, char> transitions;

    void printVector(std::vector<std::string> vec);

public:
    FiniteAutomata(std::string fileName);
    void printStates();
    void printFinalStates();
    void printAlphabet();
    void printInitialState();
    void printTransitions();
    bool checkWord(std::string word);
    std::string getAccepted(std::string sequence);

};