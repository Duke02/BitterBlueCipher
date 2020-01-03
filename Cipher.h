#ifndef BITTERBLUECIPHER_CIPHER_H
#define BITTERBLUECIPHER_CIPHER_H

#include <string>
#include <map>

class Cipher {
private:
    /// The alphabet to use for ciphers.
    std::map<char, char> cipherAlphabet;
    /// The alphabet of the system.
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    /// Helper function to determine if a given character is in the cipher alphabet.
    /// \param c The character to check for.
    /// \return True if the character is in the cipher alphabet.
    bool isInCipherAlphabet(const char &c) const;

public:
    Cipher();

    /// Initializes the cipher's alphabet with the given key.
    /// \param key The key to use for the alphabet.
    explicit Cipher(const std::string &key);

    /// Ciphers the given message.
    /// \param originalMessage The message to cipher.
    /// \return The ciphered message.
    std::string cipherMessage(const std::string &originalMessage) const;


    /// Ciphers the given message the given number of times.
    /// \param originalMessage The message to cipher.
    /// \param times The number of times to cipher the message.
    /// \return The final cipheredMessage.
    std::string cipherMessage(const std::string &originalMessage, const int &times) const;

    /// Initializes the alphabet with the given key.
    /// \param key The key to use for the alphabet.
    void initializeAlphabet(const std::string &key);

    /// Saves the dictionary to the file with the given name.
    /// \param filename The name of the file to save to.
    void saveToFile(const std::string &filename) const;

    /// Loads the dictionary from the file with the given name.
    /// \param filename The name of the file to load the dictionary from.
    void loadFromFile(const std::string &filename);
};


#endif //BITTERBLUECIPHER_CIPHER_H
