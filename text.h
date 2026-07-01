#pragma once
#include <vector>
#include <memory>
#include <string>
#include "line.h"

class Text {
private:
    std::vector<std::unique_ptr<Line>> lines;
public:
    void addLine(std::unique_ptr<Line> line);
    void clear();
    size_t size() const;
    Line* getLine(int index);
    void printAll(const class Cursor& c) const;
    std::string serialize() const;
    void deserialize(const std::string& text);
    std::vector<std::string> getSerializedVector() const;
    void fromSerializedVector(const std::vector<std::string>& vec);
};