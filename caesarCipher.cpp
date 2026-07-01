#include <string>
#include "cipher.h"
#include <cctype>

CaesarCipher::CaesarCipher(int key) {
	this->key_ = key;
}

std::string CaesarCipher::encrypt(const std::string& text) {
	std::string temp = text;
	for (int i = 0; temp[i] != '\0'; i++) {
		if (!std::isalpha(temp[i])) {
			continue;
		}
		char a;
		if (std::isupper(temp[i])) {
			a = 'A';
		} else {
			a = 'a';
		}
		int	shiftedPosition = temp[i] - a + key_;
		temp[i] = shiftedPosition % 26 + a;
	}
	return temp;
}

std::string CaesarCipher::decrypt(const std::string& text) {
	std::string temp = text;
	for (int i = 0; temp[i] != '\0'; i++) {
		if (!std::isalpha(temp[i])) {
			continue;
		}
		char a;
		if (std::isupper(temp[i])) {
			a = 'A';
		} else {
			a = 'a';
		}
		int	shiftedPosition = temp[i] - a + (26 - (key_ % 26));
		temp[i] = shiftedPosition % 26 + a;
	}
	return temp;
}