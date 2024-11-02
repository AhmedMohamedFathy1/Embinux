#ifndef CRYPTOHANDLER_H
#define CRYPTOHANDLER_H

#include <string>
#include <openssl/evp.h>

class CryptoHandler {
public:
    CryptoHandler();

    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& encryptedData);

private:
    unsigned char key[32]; // Key for encryption

    // Function to set the default key
    void setDefaultKey();
};

#endif // CRYPTOHANDLER_H
