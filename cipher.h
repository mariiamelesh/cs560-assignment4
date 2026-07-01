#pragma once
#include <string>

class Cipher {
public:
	virtual std::string encrypt(const std::string& text) = 0;
	virtual std::string decrypt(const std::string& text) = 0;
	virtual ~Cipher() = default;
};

class CaesarCipher : public Cipher {
	int key_;
	public:
	CaesarCipher(int key);
	std::string encrypt(const std::string& text) override;
	std::string decrypt(const std::string& text) override;
};