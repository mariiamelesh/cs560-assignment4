#include "text.h"
#include "state.h"
#include <sstream>

void Text::addLine(std::unique_ptr<Line> line) { 
    lines.push_back(std::move(line)); 
}

void Text::clear() { 
    lines.clear(); 
}

size_t Text::size() const { 
    return lines.size(); 
}

const Line* Text::getLine(int index) const {
    if (index >= 0 && index < (int)lines.size()) return lines[index].get();
    return nullptr;
}

void Text::printAll(const Cursor& c) const {
    for (size_t i = 0; i < lines.size(); ++i) {
        lines[i]->print((int)i == c.currentLine, c.currentIndex);
    }
}

std::string Text::serialize() const {
    std::string result;
    for (const auto& line : lines) {
        result += line->serialize() + "\n";
    }
    return result;
}

void Text::deserialize(const std::string& text) {
    clear();
    std::stringstream ss(text);
    std::string row;
    while (std::getline(ss, row)) {
        if (row.empty()) continue;
        
        if (row.rfind("text:", 0) == 0) {
            addLine(std::make_unique<Text>(row.substr(5)));
        } 
        else if (row.rfind("checklist:", 0) == 0) {
            bool checked = (row[10] == '1');
            addLine(std::make_unique<Checklist>(row.substr(12), checked));
        } 
        else if (row.rfind("contact:", 0) == 0) {
            size_t comma = row.find(',', 8);
            if (comma != std::string::npos) {
                std::string name = row.substr(8, comma - 8);
                std::string email = row.substr(comma + 1);
                addLine(std::make_unique<Contact>(name, email));
            }
        }
    }
}

std::vector<std::string> Text::getSerializedVector() const {
    std::vector<std::string> res;
    for (const auto& l : lines) res.push_back(l->serialize());
    return res;
}

void Text::fromSerializedVector(const std::vector<std::string>& vec) {
    clear();
    for (const auto& s : vec) {
        deserialize(s);
    }
}