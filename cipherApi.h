#pragma once

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default"))) 
#endif

extern "C" {
    typedef void* cipher_t;
    EXPORT cipher_t cipherCreateCaesar(int key);
    EXPORT char* cipherEncrypt(cipher_t cipher, const char* text);
    EXPORT char* cipherDecrypt(cipher_t cipher, const char* text);
    EXPORT void cipherDestroy(cipher_t cipher);
    EXPORT void cipherFree(char* str);

}