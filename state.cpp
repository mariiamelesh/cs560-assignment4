#pragma once
#include <vector>
#include <string>

class Cursor {
	int currentLine = 0;
    int currentIndex = 0;
public:
	void left() { 
		if (currentIndex > 0) {
			currentIndex--; 
		}
	}
    void right(int lineLen) {
		if (lineLen > 0 && currentIndex < lineLen - 1) {
			currentIndex++; 
		}
	}
    void up() { 
		if (currentLine > 0) {
			currentLine--; 
		}
	}
    void down(int totalLines) { 
		if (totalLines > 0 && currentLine < totalLines - 1) { 
			currentLine++; 
	}
};

class Copy {
public:
    std::vector<std::string> serializedLines;
    int cursorLine;
    int cursorIndex;
	Copy(const std::vector<std::string>& lines, const Cursor& c) {
		serializedLines = lines;
		cursorLine = c.currentLine;
		cursorIndex = c.currentIndex;
	}
};

class History {
    std::vector<Copy> copies;
public:
    void addCopy(Copy c) {
		if (copies.size() >= 5) {
            copies.erase(copies.begin());
        }
        copies.push_back(c);
    }

    bool popCopy(std::vector<std::string>& lines, Cursor& c) {
        if (copies.empty()) {
			return false;
		}
        Copy last = copies.back();
        copies.pop_back();
        
        lines = last.serializedLines;
        c.currentLine = last.cursorLine;
        c.currentIndex = last.cursorIndex;
        return true;
    }
    
    void clear() { 
		copies.clear(); 
	}
};