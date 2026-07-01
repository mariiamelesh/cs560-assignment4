#include "cipherApi.h"
#include <cstring> 
#include <string>
#include "cipher.h"

cipher_t cipherCreateCaesar(int key) {
    return new CaesarCipher(key);
}

char* cipherEncrypt(cipher_t cipher, const char* text) {
	Cipher* objCipher = static_cast<Cipher*>(cipher);
	std::string temp = objCipher->encrypt(text);
	char* result = new char[temp.size() + 1];
    std::strcpy(result, temp.c_str());
	return result;
}

char* cipherDecrypt(cipher_t cipher, const char* text) {
	Cipher* objCipher = static_cast<Cipher*>(cipher);
	std::string temp = objCipher->decrypt(text);
	char* result = new char[temp.size() + 1];
    std::strcpy(result, temp.c_str());
	return result;
}

void cipherDestroy(cipher_t cipher) {
	delete static_cast<Cipher*>(cipher);
}

void cipherFree(char* str) {
	delete[] str;
}