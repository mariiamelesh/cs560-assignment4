#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Line.h"

class Text {
	Line* lines;
public:
    void addLine(Line line);
};