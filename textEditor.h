#pragma once
#include <string>
#include <vector>
#include <memory>
#ifdef _WIN32
#include <windows.h>
#endif
#include "text.h"
#include "state.h"

struct Tab {
    Text doc;
    Cursor cursor;
};

using CreateCaesar = void*(*)(int);
using Encrypt = char*(*)(void*, const char*);
using Decrypt = char*(*)(void*, const char*);
using Destroy = void(*)(void*);
using Free = void(*)(char*);

class TextEditor {
private:
    std::vector<std::unique_ptr<Tab>> tabs; 
    int activeTab;                          
    History historyUndo;
    History historyRedo;
    std::string clipboard; 

    HINSTANCE hLib;
    CreateCaesar createCaesar;
    Encrypt cipherEncrypt;
    Decrypt cipherDecrypt;
    Destroy cipherDestroy;
    Free cipherFree;

    void saveSystemStateUndo();
public:
    TextEditor();
    ~TextEditor(); 

    void newTab();
    void switchTab(int index);
    void addText(const std::string& text);
    void addChecklist(const std::string& task);
    void addContact(const std::string& name, const std::string& email);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void undo();
    void redo();
    void toggleChecklist();
    void display() const;
    void copyText(int len);
    void cutText(int len);
    void pasteText();
    void searchText(const std::string& query) const;
    void deleteText(int len);
    void insertText(const std::string& input);
    void writeText(const std::string& input);
    
    void encryptAndSave(const std::string& filePath, int key);
    void loadAndDecrypt(const std::string& filePath, int key);
};