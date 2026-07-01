#include "state.h"

void Cursor::left() { 
    if (currentIndex > 0) currentIndex--; 
}
void Cursor::right(int lineLen) { 
    if (lineLen > 0 && currentIndex < lineLen - 1) currentIndex++; 
}
void Cursor::up() { 
    if (currentLine > 0) currentLine--; 
}
void Cursor::down(int totalLines) { 
    if (totalLines > 0 && currentLine < totalLines - 1) currentLine++; 
}

Copy::Copy(const std::vector<std::string>& lines, const Cursor& c, int tIndex) {
    serializedLines = lines;
    cursorLine = c.currentLine;
    cursorIndex = c.currentIndex;
    tabIndex = tIndex; 
}

void History::addCopy(Copy c) {
    if (copies.size() >= 5) {
        copies.erase(copies.begin());
    }
    copies.push_back(c);
}

bool History::popCopy(std::vector<std::string>& lines, Cursor& c, int& tIndex) {
    if (copies.empty()) return false;
    Copy last = copies.back();
    copies.pop_back();
    lines = last.serializedLines;
    c.currentLine = last.cursorLine;
    c.currentIndex = last.cursorIndex;
    tIndex = last.tabIndex; 
    return true;
}

void History::clear() { 
    copies.clear(); 
}