#include <iostream>
#include <fstream>
#include "./lexical-analyzer.h"

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
    }
}

int main(int argc, char* argv[]) {
    std::ifstream p1(argv[1]);
    std::ifstream p2(argv[2]);
    std::ifstream p3(argv[3]);
    std::ifstream perr(argv[4]);
    std::vector<std::ifstream*> files{ &p1,&p2,&p3,&perr };

    for (int j = 0; j < files.size(); j++) {
        std::ifstream tokens(argv[5]);
        Scanner scanner(*files[j], tokens);
        std::ofstream out("p" + std::to_string(j + 1) + "OUT.txt");
        std::ofstream outST("p" + std::to_string(j + 1) + "ST.txt");
        std::ofstream outPIF("p" + std::to_string(j + 1) + "PIF.txt");

        try {
            scanner.scan();
        }
        catch (std::string message) {
            out << message << std::endl;

            SymbolTable<std::string> st = scanner.getST();
            std::vector<std::pair<tokenType, std::pair<int, int>>> pif = scanner.getPif();
            std::vector<std::string> tokenVector = scanner.getTokens();

            printPIF(pif, tokenVector, st, outPIF);
            outPIF.close();

            st.printSymbolTable(outST);
            outST.close();
            out.close();

            return 0;
        }
        out << "Lexically correct!" << std::endl;
        out.close();

        SymbolTable<std::string> st = scanner.getST();
        std::vector<std::pair<tokenType, std::pair<int, int>>> pif = scanner.getPif();
        std::vector<std::string> tokenVector = scanner.getTokens();

        printPIF(pif, tokenVector, st, outPIF);
        outPIF.close();

        st.printSymbolTable(outST);
        outST.close();
    }

    return 0;
}