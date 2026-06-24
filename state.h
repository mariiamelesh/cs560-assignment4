#pragma once
#include <vector>
#include <string>

class Cursor {
private:
    int currentLine;
    int currentIndex;
public:
    Cursor();
    
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

    Copy(const std::vector<std::string>& lines, const Cursor& c);
};

class History {
private:
    std::vector<EditorSnapshot> copies;
public:
    void addCopy(Copy c);
    bool popCopy(std::vector<std::string>& lines, Cursor& c);
    void clear();
};