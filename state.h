#pragma once
#include <vector>
#include <string>

class Cursor {
public:
    int currentLine = 0;
    int currentIndex = 0;
    void up();
    void down(int totalLines);
    void left();
    void right(int lineLength);
};

class Copy {
public:
    std::vector<std::string> serializedLines;
    int cursorLine;
    int cursorIndex;
    int tabIndex;
    Copy(const std::vector<std::string>& lines, const Cursor& c, int tIndex);
};

class History {
private:
    std::vector<Copy> copies;
public:
    void addCopy(Copy c);
    bool popCopy(std::vector<std::string>& lines, Cursor& c, int& tIndex);
    void clear();
};