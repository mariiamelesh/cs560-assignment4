#pragma once
#include <iostream>
#include <string>

class Line {
public:
    virtual ~Line() = default;
	virtual void print(bool hasCursor, int cursorIndex) const = 0;
	virtual std::string serialize() const = 0;
};

class Text : public Line {
private:
    std::string text;
public:
	TextLine(const std::string& t) {
		text =t;
	}

	void print(bool hasCursor, int cursorIndex) const override {
		std::cout << "Text: ";
        for (size_t i = 0; i < text.length(); ++i) {
            if (hasCursor && (int)i == cursorIndex) {
				std::cout << "[" << text[i] << "]";
			} else {
				std::cout << text[i];
			}
        }
	}
	std::string serialize() const override { 
		return "text:" + text; 
	}
};
 
class Checklist : public Line {
private:
    std::string task;
	bool checked;
public:
	Checklist(const std::string& i, bool c) {
		item = i;
		checked = c;
	}

	void print(bool hasCursor, int cursorIndex) const override {
        std::cout << "[ " << (checked ? "x" : " ") << " ] " << item << std::endl;
    }

	std::string serialize() const override { 
		return "checklist:" + checked ? "1 ," : "0 ," + task; 
	}
};

class Contact : public Line {
private:
    std::string name;
    std::string email;
public:
	Contact(const std::string& n, const std::string& em) {
		name = n;
		email = em;
	}

    void print(bool hasCursor, int cursorIndex) const override {
        std::cout << "Contact - " << name << ", E-mail: " << email << std::endl;
    }

	std::string serialize() const override { 
		return "contact:" + name + "," + email;
	}
};