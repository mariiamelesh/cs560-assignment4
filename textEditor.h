#pragma once
#include <string>
#include "text.h"
#include "state.h"

class TextEditor {
private:
    TextContainer doc;
    Cursor cursor;
    History history;
    std::string clipboard; 

public:
    TextEditor();

    void addText(const std::string& text);
    void addChecklist(const std::string& task);
    void addContact(const std::string& name, const std::string& email);

};