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
}