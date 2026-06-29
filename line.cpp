#include "line.h"
#include <iostream>

Text::Text(const std::string& t) : text(t) {}

void Text::print(bool hasCursor, int cursorIndex) const {
    std::cout << "text: ";
    for (size_t i = 0; i < text.length(); ++i) {
        if (hasCursor && (int)i == cursorIndex) {
            std::cout << "[" << text[i] << "]";
        } else {
            std::cout << text[i];
        }
    }
    std::cout << std::endl;
}

std::string Text::serialize() const { 
    return "text:" + text; 
}

Checklist::Checklist(const std::string& i, bool c) : task(i), checked(c) {}

void Checklist::print(bool hasCursor, int cursorIndex) const {
    std::cout << "[ " << (checked ? "x" : " ") << " ] " << task << std::endl;
}

std::string Checklist::serialize() const { 
    return "checklist:" + std::string(checked ? "1," : "0,") + task; 
}

Contact::Contact(const std::string& n, const std::string& em) : name(n), email(em) {}

void Contact::print(bool hasCursor, int cursorIndex) const {
    std::cout << "contact - " << name << ", email: " << email << std::endl;
}

std::string Contact::serialize() const { 
    return "contact:" + name + "," + email;
}