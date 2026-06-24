#pragma once
#include <vector>
#include <memory>
#include <sstream>
#include "Line.h"

class Text {
    std::vector<std::unique_ptr<Line>> lines;
public:
    void addLine(Line line) { 
		lines.push_back(std::move(line)); 
	}
	void clear() { 
		lines.clear(); 
	}
	
	std::string serialize() const {
        std::string result;
        for (const auto& line : lines) {
            result += line->serialize() + "\n";
        }
        return result;
    }
	void deserialize(const std::string& text) {
        clear();
        std::stringstream ss(text);
        std::string row;
        while (std::getline(ss, row)) {
            if (row.empty()) {
				continue;
			}
            
            if (row.rfind("text:", 0) == 0) {
                addLine(std::make_unique<TextLine>(row.substr(5)));
            } 
            else if (row.rfind("checklist:", 0) == 0) {
                bool checked = (row[4] == '1');
                addLine(std::make_unique<ChecklistLine>(row.substr(12), checked));
            } 
            else if (row.rfind("contact:", 0) == 0) {
                size_t comma = row.find(',', 8);
                if (comma != std::string::npos) {
                    std::string name = row.substr(8, comma - 8);
                    std::string email = row.substr(comma + 1);
                    addLine(std::make_unique<ContactLine>(name, email));
                }
            }
        }
    }
}