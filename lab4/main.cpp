#include <iostream>
#include <fstream>
#include "./lexical-analyzer.h"
#include "fa.h"

std::string toString(tokenType type) {
    switch (type) {
    case Operator: return "Operator";
    case Separator: return "Separator"; break;
    case ReservedWord: return "ReservedWord"; break;
    case Identifier: return "Identifier"; break;
    case Int: return "Int"; break;
    case Bool: return "Bool"; break;
    case Char: return "Char"; break;
    case String: return "String"; break;
    }
    return "None";
}

void printPIF(std::vector<std::pair<tokenType, std::pair<int, int>>>& pif, std::vector<std::string>& tokenVector, SymbolTable<std::string>& st, std::ofstream& outPIF) {
    for (int i = 0; i < pif.size(); i++) {
        std::string var;
        if (pif[i].first <= 2) var = tokenVector[pif[i].second.first];
        else if (pif[i].first == 3) var = st.getIdentifier(pif[i].second.first, pif[i].second.second);
        else if (pif[i].first <= 5) var = st.getConstant(pif[i].second.first, pif[i].second.second);
        else if (pif[i].first == 6) var = st.getCharConstant(pif[i].second.first, pif[i].second.second);
        else if (pif[i].first == 7) var = st.getStringConstant(pif[i].second.first, pif[i].second.second);


        outPIF << toString(pif[i].first) << " - " << pif[i].second.first << ", " << pif[i].second.second << " (" << var << ")" << std::endl;
        //outPIF << toString(pif[i].first) << " - " << pif[i].second.first << std::endl;
    }
}

void printMenu() {
    std::cout << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Display set of states" << std::endl;
    std::cout << "2. Display the alphabet" << std::endl;
    std::cout << "3. Display the initial state" << std::endl;
    std::cout << "4. Display set of final states" << std::endl;
    std::cout << "5. Display set of transitions" << std::endl;
    std::cout << "6. Check if word is correct" << std::endl;
    std::cout << "7. Get the substring which is accepted in a string" << std::endl;
    std::cout << "8. Run the scanner" << std::endl;
    std::cout << "9. Input automata file name" << std::endl;
}

void handleWordCheck(FiniteAutomata automata) {
    //Get the word to be checked
    std::string word;
    std::cout << "Enter the word to check: ";
    std::cin >> word;
    std::cout << std::endl;

    //Check if word is accepted and print appropiate message
    if (automata.checkWord(word)) std::cout << "Word is accepted!" << std::endl;
    else std::cout << "Invalid word!" << std::endl;
}

void handleSubstringCheck(FiniteAutomata automata) {
    //Get the sequence to be checked
    std::string sequence;
    std::cout << "Enter the sequence:" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, sequence);
    std::cout << std::endl;

    //Check if word is accepted and print appropiate message
    std::string word = automata.getAccepted(sequence);
    if (word == "--") std::cout << "Word not found!" << std::endl;
    else std::cout << word << std::endl;
}

void handleAutomataFileSwitch(FiniteAutomata& automata) {
    //Get the file name
    std::string fileName;
    std::cout << "Enter the file name: ";
    std::cin >> fileName;
    std::cout << std::endl;

    automata = FiniteAutomata(fileName);
}

void handleScannerRun() {
    //Getting all the files as arguments
    std::ifstream p1("lab1_p1.cpp");
    std::ifstream p2("lab1_p2.cpp");
    std::ifstream p3("lab1_p3.cpp");
    std::ifstream perr("lab1_p1err.in");
    std::vector<std::ifstream*> files{ &p1,&p2,&p3,&perr };

    for (int j = 0; j < files.size(); j++) {
        //Creating the scanner and the file streams
        std::ifstream tokens("token.in");
        Scanner scanner(*files[j], tokens);
        std::ofstream out("p" + std::to_string(j + 1) + "OUT.txt");
        std::ofstream outST("p" + std::to_string(j + 1) + "ST.txt");
        std::ofstream outPIF("p" + std::to_string(j + 1) + "PIF.txt");

        //Running the scanning
        try {
            scanner.scan();
        }
        catch (std::string message) {
            out << message << std::endl;

            //Getting the tables from the scanner
            SymbolTable<std::string> st = scanner.getST();
            std::vector<std::pair<tokenType, std::pair<int, int>>> pif = scanner.getPif();
            std::vector<std::string> tokenVector = scanner.getTokens();

            //Print out the pif
            printPIF(pif, tokenVector, st, outPIF);
            outPIF.close();

            //Print out the st
            st.printSymbolTable(outST);
            outST.close();
            out.close();

            return;
        }
        out << "Lexically correct!" << std::endl;
        out.close();

        //Getting the tables from the scanner
        SymbolTable<std::string> st = scanner.getST();
        std::vector<std::pair<tokenType, std::pair<int, int>>> pif = scanner.getPif();
        std::vector<std::string> tokenVector = scanner.getTokens();

        //Print out the pif
        printPIF(pif, tokenVector, st, outPIF);
        outPIF.close();

        //Print out the st
        st.printSymbolTable(outST);
        outST.close();
    }
}

int main(int argc, char* argv[]) {
    int currentChoice;
    FiniteAutomata automata("identifier.in");

    //Menu
    while (true) {
        //Print the menu and get the user input
        printMenu();
        std::cout << "> ";
        std::cin >> currentChoice;
        std::cout << std::endl;

        //Handle the different menu options
        switch (currentChoice)
        {
        case 0:
            return 0;
            break;

        case 1:
            automata.printStates();
            break;
        case 2:
            automata.printAlphabet();
            break;
        case 3:
            automata.printInitialState();
            break;
        case 4:
            automata.printFinalStates();
            break;
        case 5:
            automata.printTransitions();
            break;
        case 6:
            handleWordCheck(automata);
            break;
        case 7:
            handleSubstringCheck(automata);
            break;
        case 8:
            handleScannerRun();
            break;
        case 9:
            handleAutomataFileSwitch(automata);
            break;

        default:
            std::cout << "Choice is not supported" << std::endl;
            break;
        }
    }
}