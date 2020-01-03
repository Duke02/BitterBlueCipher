#include <iostream>
#include <fstream>
#include <algorithm>
#include "Cipher.h"

/// Prints the prompt and asks if the user wants to input a file or do text input.
/// \return True if user wants to input a file, False otherwise.
bool printPrompt();

/// Gets the input from a file.
/// \return The text in the file.
std::string getFileInput();

/// Gets input from the console.
/// \return The text inputted.
std::string getTextInput();

/// Gets the key to be used for the cipher.
/// \return The key for the cipher.
std::string getKey();

/// Gets how the user wants to output the ciphered message.
/// \return True if user wants to output to a file. False otherwise.
bool getModeOfOutput();

/// Outputs the given message to a file.
/// \param message The message to put into a file.
void outputToFile(const std::string &message);

/// Gets the number of times to cipher the message.
/// \return a number at least 1.
int getTimesToCipher();

/// Gets if the user wants to save the dictionary that was used to cipher the message.
/// \return True if the user wants to save the dictionary, false otherwise.
bool shouldSaveDictionary();

/// Saves the cipher object's dictionary to a file.
/// \param c the cipher object to save.
void saveDictionary(const Cipher &c);

/// Gets if the user wants to load a previously saved dictionary or use a new key.
/// \return True if use previous dictionary, False otherwise.
bool shouldLoadDictionary();

/// Loads a previous dictionary and initializes the given Cipher with it.
/// \param c The cipher to load a previous dictionary into.
void loadFromPreviousDictionary(Cipher &c);

int main() {
    bool wantsToUseFile = printPrompt();

    std::string message;

    if (wantsToUseFile) {
        message = getFileInput();
    } else {
        message = getTextInput();
    }

    if (message.empty()) {
        std::cout << "Detected empty message. Exiting program." << std::endl;
        return 0;
    }

    bool shouldLoadFromPreviousDict = shouldLoadDictionary();

    Cipher cipher;

    if (shouldLoadFromPreviousDict) {
        loadFromPreviousDictionary(cipher);
    } else {
        std::string key = getKey();
        cipher.initializeAlphabet(key);
    }
    int times = getTimesToCipher();

    std::string cipheredMessage = cipher.cipherMessage(message, times);

    std::cout << "Message: " << message << std::endl;

    bool wantsToOutputToFile = getModeOfOutput();

    if (wantsToOutputToFile) {
        outputToFile(cipheredMessage);
    } else {
        std::cout << "Ciphered Message: " << cipheredMessage << "\n";
    }

    bool wantsToSaveDictionary = shouldSaveDictionary();

    if (wantsToSaveDictionary) {
        saveDictionary(cipher);
    }

    std::cout << std::endl;

    return 0;
}

bool printPrompt() {
    std::cout << "Welcome to the Bitterblue Cipher Program, inspired by Kristin Cashore's Bitterblue.\n";
    std::cout << "Do you want the program to use a file as input or text input? F for File, T otherwise.\n";
    char c;
    std::cin >> c;
    std::cin.ignore();
    return tolower(c) == 'f';
}


std::string getFileInput() {
    std::cout << "What is the file name?\n";

    std::string filename;
    std::getline(std::cin, filename);

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cout << "Error opening file. Exiting program." << std::endl;
        return "";
    }

    std::string out;
    std::string temp;

    while (inFile >> temp) {
        out += temp + " ";
    }

    inFile.close();

    return out;
}

std::string getTextInput() {
    std::cout << "Please enter your message.\n";
    std::cout << "Press enter when you are finished.\n";
    std::string output;
    std::getline(std::cin, output);
    return output;
}

std::string getKey() {
    std::cout << "What key do you want to use?\n";
    std::string key;

    bool gotBadKey;
    do {
        std::cin >> key;
        gotBadKey = !std::all_of(key.begin(), key.end(), isalpha);

        if (gotBadKey) {
            std::cout << "Sorry we don't accept that kind of key. The key must be all alphabetical characters.\n";
        }
    } while (gotBadKey);
    std::transform(key.begin(), key.end(), key.begin(), tolower);
    return key;
}

bool getModeOfOutput() {
    std::cout << "How do you want to output the ciphered message?\n";
    std::cout << "F for file output, T for console/text output.\n";

    char c;
    std::cin >> c;
    std::cin.ignore();

    return tolower(c) == 'f';
}

void outputToFile(const std::string &message) {
    std::string filename;
    std::cout << "What is the name of the file you want to output to?\n";
    std::getline(std::cin, filename);

    std::ofstream outFile(filename);

    if (!outFile) {
        std::cout << "Error opening output file. Exiting program." << std::endl;
        return;
    }

    outFile << message;

    outFile.close();
}

int getTimesToCipher() {
    std::cout << "How many times do you want to cipher the message?\n";
    bool isBadNumber;
    int times;
    do {
        std::cin >> times;
        isBadNumber = times < 1;
        if (isBadNumber) {
            std::cout << "Sorry but the number of times to cipher the message must be at least 1.\n";
        }
    } while (isBadNumber);
    return times;
}

bool shouldSaveDictionary() {
    std::cout << "Do you want to save the dictionary that created the ciphered message?\n";
    std::cout << "Y for yes, N otherwise.\n";
    char c;
    std::cin >> c;
    std::cin.ignore();
    return tolower(c) == 'y';
}

void saveDictionary(const Cipher &c) {
    std::cout << "Input the name of the file to save the dictionary to.\n";
    std::string filename;
    std::getline(std::cin, filename);

    c.saveToFile(filename);
}

bool shouldLoadDictionary() {
    std::cout << "Do you want to load a previous dictionary or use a new key for the cipher?\n";
    std::cout << "P for previous dictionary, K for new key.\n";
    char c;
    std::cin >> c;
    std::cin.ignore();
    return tolower(c) == 'p';
}

void loadFromPreviousDictionary(Cipher &c) {
    std::cout << "Input the name of the file to load the dictionary from.\n";
    std::string filename;
    std::getline(std::cin, filename);

    c.loadFromFile(filename);
}
