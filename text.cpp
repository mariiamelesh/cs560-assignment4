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

 Line* Text::getLine(int index) {
    if (index >= 0 && index < lines.size()) {
		return lines[index].get();
	}
    return nullptr;
}


void Text::printAll(const Cursor& c) const {
    for (size_t i = 0; i < lines.size(); i++) {
        lines[i]->print(i == c.currentLine, c.currentIndex);
    }
}

std::string Text::serialize() const {
    std::string result = "";
    for (size_t i = 0; i < lines.size(); i++) {
        result += lines[i]->serialize() + "\n";
    }
    return result;
}

void Text::deserialize(const std::string& textStr) {
    std::stringstream ss(textStr);
    std::string row;
    while (std::getline(ss, row)) {
        if (row.empty()) continue;
        if (row.find("text:") == 0) {
            addLine(std::make_unique<TextLine>(row.substr(5)));
        } 
        else if (row.find("checklist:") == 0) {
            bool ch = false;
            if (row[10] == '1') {
				ch = true;
			}
            addLine(std::make_unique<Checklist>(row.substr(12), ch));
        } 
        else if (row.find("contact:") == 0) {
            size_t comma = row.find(',', 8);
            if (comma != std::string::npos) {
                std::string n = row.substr(8, comma - 8);
                std::string em = row.substr(comma + 1);
                addLine(std::make_unique<Contact>(n, em));
            }
        }
    }
}

std::vector<std::string> Text::getSerializedVector() const {
    std::vector<std::string> res;
    for (size_t i = 0; i < lines.size(); ++i) {
        res.push_back(lines[i]->serialize());
    }
    return res;
}

void Text::fromSerializedVector(const std::vector<std::string>& vec) {
    clear();
    for (size_t i = 0; i < vec.size(); ++i) {
        deserialize(vec[i]);
    }
}