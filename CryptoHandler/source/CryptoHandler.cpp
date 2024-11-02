#include "CryptoHandler.hpp"
#include <openssl/rand.h>
#include <stdexcept>
#include <cstring> // For memcpy

// Constructor that initializes the key
CryptoHandler::CryptoHandler() 
{
    setDefaultKey(); // Set the default key during construction
}

void CryptoHandler::setDefaultKey() {
    // AES key (32 bytes for 256-bit AES)
    const unsigned char AES_key[32] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };
    std::memcpy(key, AES_key, sizeof(key));
}

std::string CryptoHandler::encrypt(const std::string& plaintext)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create context");

    std::string encryptedData;
    unsigned char iv[EVP_MAX_IV_LENGTH];
    if (!RAND_bytes(iv, sizeof(iv))) throw std::runtime_error("Failed to generate IV");

    encryptedData.append(reinterpret_cast<char*>(iv), sizeof(iv));

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    int outlen;
    unsigned char buffer[128];
    EVP_EncryptUpdate(ctx, buffer, &outlen, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
    encryptedData.append(reinterpret_cast<char*>(buffer), outlen);

    EVP_EncryptFinal_ex(ctx, buffer, &outlen);
    encryptedData.append(reinterpret_cast<char*>(buffer), outlen);

    EVP_CIPHER_CTX_free(ctx);
    return encryptedData;
}

std::string CryptoHandler::decrypt(const std::string& encryptedData)
{
    if (encryptedData.size() <= EVP_MAX_IV_LENGTH) 
    {
    throw std::runtime_error("Invalid data");
    }
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
         throw std::runtime_error("Failed to create context");
    }
    std::string decryptedData;
    const unsigned char* iv = reinterpret_cast<const unsigned char*>(encryptedData.data());
    const unsigned char* data = reinterpret_cast<const unsigned char*>(encryptedData.data() + EVP_MAX_IV_LENGTH);
    int dataLen = encryptedData.size() - EVP_MAX_IV_LENGTH;

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    int outlen;
    unsigned char buffer[128];
    EVP_DecryptUpdate(ctx, buffer, &outlen, data, dataLen);
    decryptedData.append(reinterpret_cast<char*>(buffer), outlen);

    EVP_DecryptFinal_ex(ctx, buffer, &outlen);
    decryptedData.append(reinterpret_cast<char*>(buffer), outlen);

    EVP_CIPHER_CTX_free(ctx);
    return decryptedData;
}
