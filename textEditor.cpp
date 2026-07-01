#include "textEditor.h"
#include <fstream>
#include <iostream>

TextEditor::TextEditor() {
    hLib = LoadLibraryA("caesar.dll"); 
    if (hLib) {
        createCaesar = (CreateCaesar)GetProcAddress(hLib, "cipherCreateCaesar");
        cipherEncrypt = (Encrypt)GetProcAddress(hLib, "cipherEncrypt");
        cipherDecrypt = (Decrypt)GetProcAddress(hLib, "cipherDecrypt");
        cipherDestroy = (Destroy)GetProcAddress(hLib, "cipherDestroy");
        cipherFree = (Free)GetProcAddress(hLib, "cipherFree");
    } else {
        std::cout << "lib didnt load";
		return;
    }

    activeTab = 0;
    tabs.push_back(std::make_unique<Tab>());
}

TextEditor::~TextEditor() {
    if (hLib) {
        FreeLibrary(hLib);
    }
}

void TextEditor::newTab() {
    tabs.push_back(std::make_unique<Tab>());
    activeTab = tabs.size() - 1; 
}

void TextEditor::switchTab(int index) {
    if (index >= 0 && index < tabs.size()) {
        activeTab = index;
    } else {
        std::cout << "wrong tab index XD" << std::endl;
    }
}

void TextEditor::saveSystemStateUndo() {
    Copy cp(tabs[activeTab]->doc.getSerializedVector(), tabs[activeTab]->cursor, activeTab);
    historyUndo.addCopy(cp);
    historyRedo.clear(); 
}

void TextEditor::addText(const std::string& text) {
    saveSystemStateUndo();
    tabs[activeTab]->doc.addLine(std::make_unique<TextLine>(text));
}

void TextEditor::addChecklist(const std::string& task) {
    if (task == "") {
        std::cout << "task cant be empty" << std::endl;
        return;
    }
    saveSystemStateUndo();
    tabs[activeTab]->doc.addLine(std::make_unique<Checklist>(task));
}

void TextEditor::addContact(const std::string& name, const std::string& email) {
    if (name == "" || email == "") {
        std::cout << "name or email cant me empty" << std::endl;
        return;
    }
    saveSystemStateUndo();
    tabs[activeTab]->doc.addLine(std::make_unique<Contact>(name, email));
}

void TextEditor::toggleChecklist() {
    Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr == nullptr) {
		return;
	}
    Checklist* ch = dynamic_cast<Checklist*>(curr);
    if (ch != nullptr) {
        saveSystemStateUndo();
        ch->toggle();
    } else {
        std::cout << "not a checklist" << std::endl;
    }
}

void TextEditor::moveUp() { 
    tabs[activeTab]->cursor.up(); 
}
void TextEditor::moveDown() { 
    tabs[activeTab]->cursor.down(tabs[activeTab]->doc.size()); 
}
void TextEditor::moveLeft() { 
    tabs[activeTab]->cursor.left(); 
}
void TextEditor::moveRight() {
    const Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr != nullptr) {
        const TextLine* t = dynamic_cast<const TextLine*>(curr);
        int len = 0;
        if (t != nullptr) {
			len = t->getText().length();
		}
        tabs[activeTab]->cursor.right(len);
    }
}

void TextEditor::undo() {
    std::vector<std::string> prev;
    int undoTab;
    Cursor undoCursor;
    if (historyUndo.popCopy(prev, undoCursor, undoTab)) {
        Copy cur = Copy(tabs[activeTab]->doc.getSerializedVector(), tabs[activeTab]->cursor, activeTab);
        historyRedo.addCopy(cur);
        activeTab = undoTab; 
        tabs[activeTab]->cursor = undoCursor;
        tabs[activeTab]->doc.clear();
        for (size_t i = 0; i < prev.size(); ++i) {
            tabs[activeTab]->doc.deserialize(prev[i]);
        }
    } else {
        std::cout << "empty undo history" << std::endl;
    }
}

void TextEditor::redo() {
    std::vector<std::string> prev;
    int redoTab;
    Cursor redoCursor;
    if (historyRedo.popCopy(prev, redoCursor, redoTab)) {
        Copy cur = Copy(tabs[activeTab]->doc.getSerializedVector(), tabs[activeTab]->cursor, activeTab);
        historyUndo.addCopy(cur);
        activeTab = redoTab; 
        tabs[activeTab]->cursor = redoCursor;
        tabs[activeTab]->doc.clear();
        for (size_t i = 0; i < prev.size(); i++) {
            tabs[activeTab]->doc.deserialize(prev[i]);
        }
    } else {
        std::cout << "redo history empty" << std::endl;
    }
}

void TextEditor::display() const {
    std::cout << "\n	->tabs<-	\n";
    for (size_t i = 0; i < tabs.size(); ++i) {
        if (i == activeTab) {
			std::cout << "[ >" << i << "< ] ";
		} else {
			std::cout << "[ " << i << " ] ";
		}
    }
    std::cout << "\n";
    tabs[activeTab]->doc.printAll(tabs[activeTab]->cursor);
}

void TextEditor::copyText(int len) {
    const Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr == nullptr) {
		return;
	}
    const TextLine* t = dynamic_cast<const TextLine*>(curr);
    if (t != nullptr) {
        std::string temp = t->getText();
        if (tabs[activeTab]->cursor.currentIndex + len > temp.length() || len < 0) {
            std::cout << "invalid lenght" << std::endl;
            return;
        }
        clipboard = temp.substr(tabs[activeTab]->cursor.currentIndex, len);
    } else {
        std::cout << "cant copy from non text" << std::endl;
    }
}

void TextEditor::cutText(int len) {
    Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr == nullptr) {
		return;
	}
    TextLine* t = dynamic_cast<TextLine*>(curr); 
    if (t != nullptr) {
        std::string temp = t->getText();
        if (tabs[activeTab]->cursor.currentIndex + len > temp.length() || len < 0) {
            std::cout << "invalid length" << std::endl;
            return;
        }
        saveSystemStateUndo();
        clipboard = temp.substr(tabs[activeTab]->cursor.currentIndex, len);
        temp.erase(tabs[activeTab]->cursor.currentIndex, len);
        t->setText(temp);
    } else {
        std::cout << "cant cut from not text" << std::endl;
    }
}

void TextEditor::pasteText() {
    if (clipboard == "") {
        std::cout << "empty clipboard" << std::endl;
        return;
    }
    Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr == nullptr) return;
    TextLine* t = dynamic_cast<TextLine*>(curr); 
    if (t != nullptr) {
        saveSystemStateUndo();
        std::string temp = t->getText();
        temp.insert(tabs[activeTab]->cursor.currentIndex, clipboard);
        t->setText(temp);
    } else {
        std::cout << "cant paste into not text" << std::endl;
    }
}

void TextEditor::writeText(const std::string& input) {
    Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr == nullptr) return;
    TextLine* t = dynamic_cast<TextLine*>(curr); 
    if (t != nullptr) {
        saveSystemStateUndo(); 
        std::string temp = t->getText();
		temp += " ";
        temp += input;
        t->setText(temp); 
    } else {
        std::cout << "cant append to not text" << std::endl;
    }
}

void TextEditor::insertText(const std::string& input) {
    Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr == nullptr) {
		return;
	}
    TextLine* t = dynamic_cast<TextLine*>(curr); 
    if (t != nullptr) {
        saveSystemStateUndo();
        std::string temp = t->getText();
        temp.insert(tabs[activeTab]->cursor.currentIndex, input);
        t->setText(temp);
    } else {
        std::cout << "cant insert on not text lines" << std::endl;
    }
}

void TextEditor::deleteText(int len) {
    Line* curr = tabs[activeTab]->doc.getLine(tabs[activeTab]->cursor.currentLine);
    if (curr == nullptr) {
		return;
	}
    TextLine* t = dynamic_cast<TextLine*>(curr); 
    if (t != nullptr) {
        std::string temp = t->getText();
        if (tabs[activeTab]->cursor.currentIndex + len > temp.length() || len < 0) {
            std::cout << "invalid length XD" << std::endl;
            return;
        }
        saveSystemStateUndo();
        temp.erase(tabs[activeTab]->cursor.currentIndex, len);
        t->setText(temp);
    } else {
        std::cout << "cant delete on not text lines" << std::endl;
    }
}

void TextEditor::searchText(const std::string& input) const {
    if (input == "") {
		return;
	}
    for (size_t i = 0; i < tabs[activeTab]->doc.size(); ++i) {
        const Line* line = tabs[activeTab]->doc.getLine(i);
        if (line == nullptr) {
			continue;
		}
        std::string content = line->serialize();
        int position = content.find(input);
        while (position != std::string::npos) {
            std::cout << "found at: " << i << position << std::endl;
            position = content.find(input, position + 1);
        }
    }
}

void TextEditor::encryptAndSave(const std::string& filePath, int key) {

    std::string data = tabs[activeTab]->doc.serialize();
	void* cipher = createCaesar(key);
    char* encrypted = cipherEncrypt(cipher, data.c_str());
    std::string enc = encrypted;
        
    cipherFree(encrypted);
    cipherDestroy(cipher);

    std::ofstream file(filePath);
    if (file.is_open()) {
            file.write(enc.c_str(), enc.size());
        } else {
            std::cout << "invalid file" << std::endl;
        }
}

void TextEditor::loadAndDecrypt(const std::string& filePath, int key) {

    std::ifstream file(filePath, std::ios::ate);
	
    if (!file.is_open()) {
        std::cout << "file doesnt exist or broken" << std::endl;
        return;
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string temp(size, ' ');
    file.read(&temp[0], size);
    void* cipher = createCaesar(key);   
    char* decrypted = cipherDecrypt(cipher, temp.c_str());
    std::string dec = decrypted;
    cipherFree(decrypted);
    cipherDestroy(cipher);

    if (dec != "" && dec.find("text:") == std::string::npos && dec.find("checklist:") == std::string::npos && dec.find("contact:") == std::string::npos) {
		std::cout << "invalid text in file" << std::endl;
        return;
    }
	tabs[activeTab]->doc.clear();
    tabs[activeTab]->doc.deserialize(dec);
}