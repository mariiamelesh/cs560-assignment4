#include "line.h"
#include <iostream>

TextLine::TextLine(const std::string& t) {
    text = t;
}

void TextLine::print(bool hasCursor, int cursorIndex) const {
    std::cout << "   text: "; 
    for (size_t i = 0; i < text.length(); ++i) {
        if (hasCursor && i == cursorIndex) {
            std::cout << "[" <<text[i] << "]";
        } else {
            std::cout << text[i];
        }
    }
    std::cout << std::endl;
}

std::string TextLine::serialize() const { 
    return "text:" + text; 
}

Checklist::Checklist(const std::string& i, bool c) {
    task = i;
	checked = c;
}

void Checklist::print(bool hasCursor, int cursorIndex) const {
    if (hasCursor) std::cout << "-> ";
    else std::cout << "   ";
    std::cout << "[ " << (checked ? "x" : " ") << " ] " << task << std::endl;
}

std::string Checklist::serialize() const { 
    std::string s = "0,";
    if (checked) s = "1,";
    return "checklist:" + s + task; 
}

void Checklist::toggle() {
    checked = !checked;
}

Contact::Contact(const std::string& n, const std::string& em) {
    name = n;
    email = em;
}

void Contact::print(bool hasCursor, int cursorIndex) const {
    if (hasCursor) {
		std::cout << "-> ";
	} else {
		std::cout << "   ";
	}
    std::cout << "contact: " << name << ", email: " << email << std::endl;
}

std::string Contact::serialize() const { 
    return "contact:" + name + "," + email;
}