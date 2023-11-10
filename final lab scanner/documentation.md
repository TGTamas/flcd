https://github.com/TGTamas/flcd

# Lexical Analyzer Documentation

## Introduction

This lexical analyzer is designed to process source code files and generate a Program Internal Form (PIF) along with a Symbol Table (ST). The analyzer supports various token types, including operators, separators, reserved words, identifiers, integers, booleans, characters, and strings.

## Components

### 1. Main Program (`main.cpp`)

The main program orchestrates the entire process of lexical analysis. It reads input files, initializes the scanner, performs lexical analysis, handles exceptions, and outputs the results to separate files.

#### Functions:

- `toString(tokenType type)`: Converts a token type to a string for printing purposes.
- `printPIF()`: Outputs the Program Internal Form to a file.
- `main()`: Reads input files, initializes the scanner, performs lexical analysis, and outputs the results.

### 2. Symbol Table (`symbol-table.cpp`)

The Symbol Table is implemented as a hash table to efficiently store and retrieve symbols (identifiers, constants, strings, and characters).

#### Classes:

- `HashTable<T>`: A generic hash table implementation.
- `SymbolTable<T>`: Represents the Symbol Table for the lexical analyzer.

#### Functions:

- `find(key)`: Searches for a key in the symbol table and returns its location.
- `getById(bucketIndex, listIndex)`: Retrieves a symbol based on its position in the symbol table.
- `insert(key)`: Inserts a new symbol into the symbol table.
- `remove(key)`: Removes a symbol from the symbol table.
- `printHashTable(out)`: Outputs the contents of the symbol table to a file.

### 3. Lexical Analyzer (`lexical-analyzer.cpp`)

The lexical analyzer processes the source code and tokenizes it, generating the Program Internal Form (PIF) and updating the Symbol Table (ST).

#### Classes:

- `Scanner`: The main class responsible for scanning the source code.

#### Functions:

- `fileToString(file)`: Converts a file to a string for processing.
- `fileToVector(file)`: Converts a file to a vector for token processing.
- `skipWhiteSpaces()`: Skips white spaces and updates the row number.
- `startsWith(b)`: Checks if the current token starts with a given string.
- `getPif()`: Retrieves the Program Internal Form.
- `getST()`: Retrieves the Symbol Table.
- `getTokens()`: Retrieves the token vector.
- `scan()`: Initiates the scanning process.
- `nextToken()`: Moves to the next token in the source code.
- `treatToken()`: Processes the current token based on its type.
- Various functions to treat specific token types (identifier, int constant, bool constant, char constant, string constant).

## Usage

1. Compile the program using a C++ compiler.
2. Run the compiled executable, providing the necessary input files.
3. View the generated output files (`p1OUT.txt`, `p1ST.txt`, `p1PIF.txt`, ..., `p4OUT.txt`, `p4ST.txt`, `p4PIF.txt`).
