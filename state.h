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
};

class History {
   
};