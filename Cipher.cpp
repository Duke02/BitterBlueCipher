
#include "Cipher.h"
#include <algorithm>
#include <ostream>
#include <iostream>
#include <fstream>

Cipher::Cipher() = default;


Cipher::Cipher(const std::string &key) {
    initializeAlphabet(key);
}

std::string toLower(const std::string &s) {
    std::string output;

    for (const auto c : s) {
        output += tolower(c);
    }

    return output;
}

std::string Cipher::cipherMessage(const std::string &originalMessage) const {
    std::string casedMessage = toLower(originalMessage);

    std::string out;

    for (auto c : casedMessage) {
        if (this->cipherAlphabet.find(c) != this->cipherAlphabet.end()) {
            out += this->cipherAlphabet.at(c);
        } else {
            out += c;
        }
    }

    return out;
}

std::string removeDuplicates(const std::string &s) {
    std::string out;
    for (char c : s) {
        if (std::find(out.begin(), out.end(), c) == out.end()) {
            out += c;
        }
    }
    return out;
}

bool Cipher::isInCipherAlphabet(const char &c) const {
    for (const auto p : this->cipherAlphabet) {
        if (c == p.second) {
            return true;
        }
    }
    return false;
}

void Cipher::initializeAlphabet(const std::string &key) {
    int i;

    std::string prunedKey = removeDuplicates(key);

    for (i = 0; i < std::min(prunedKey.length(), alphabet.length()); i++) {
        this->cipherAlphabet[alphabet[i]] = prunedKey[i];
    }

    if (i >= alphabet.length()) {
        return;
    }

    // alphabetIndex is the index that is used to track the letter to add within the static
    // alphabet variable. It starts after the last letter in the key.
    auto alphabetIndex = alphabet.find(prunedKey.back()) + 1;

    while (cipherAlphabet.size() < alphabet.size()) {
        if (alphabetIndex >= alphabet.size()) {
            alphabetIndex %= alphabet.size();
        }

        if (i >= alphabet.size()) {
            i %= alphabet.size();
        }

        if (!this->isInCipherAlphabet(alphabet[alphabetIndex])) {
            cipherAlphabet[alphabet[i]] = alphabet[alphabetIndex];
            i++;
        }

        alphabetIndex++;
    }
}

std::string Cipher::cipherMessage(const std::string &originalMessage, const int &times) const {
    std::string cipheredMessage = originalMessage;
    for (int i = 0; i < times; i++) {
        cipheredMessage = cipherMessage(cipheredMessage);
    }
    return cipheredMessage;
}

void Cipher::saveToFile(const std::string &filename) const {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cout << "Error opening file " << filename << ". Cannot save dictionary.\n";
        outFile.close();
        return;
    }

    for (const auto p : this->cipherAlphabet) {
        outFile << p.first << " " << p.second << " |\n";
    }

    outFile.close();
}

void Cipher::loadFromFile(const std::string &filename) {
    std::ifstream inFile(filename);

    if (!inFile) {
        std::cout << "Error opening file " << filename << ". Cannot save dictionary.\n";
        inFile.close();
        return;
    }

    std::string line;
    std::string oldAlphabet;

    while (inFile) {
        std::getline(inFile, line);
        // This assumes that each line is in the format of
        // K V |
        // where K is the original alphabet, and V is the ciphered alphabet.
        int middleSpace = line.find_first_of(' ');

        char value = line[middleSpace + 1];
        oldAlphabet += value;
    }

    this->cipherAlphabet.clear();

    // Use the old alphabet as a key so that we can maintain backwards compatibility.
    this->initializeAlphabet(oldAlphabet);
}

