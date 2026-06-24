#pragma once
#include <vector>
#include <string>

class Cursor {
public:
    int currentLine = 0;
    int currentIndex = 0;
	
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
};

class History {
   
};