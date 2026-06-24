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
}