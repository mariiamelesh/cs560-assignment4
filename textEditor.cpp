#include <fstream>
#include "line.h"
#include "text.h"
#include "state.h"

class TextEditor {
    Text doc;
    Cursor cursor;
    History history;
    std::string clipboard;
	
	void saveSystemState() {
		Copy copy = Copy(doc, cursor);
        history.addCopy(copy);
    }
public:
    void addText(const std::string& text) {
        saveSystemState();
        doc.addLine(std::make_unique<Text>(text));
    }

    void addChecklist(const std::string& item, bool checked) {
        saveSystemState();
        doc.addLine(std::make_unique<Checklist>(item, checked));
    }

    void addContact(const std::string& name, const std::string& email) {
        saveSystemState();
        doc.addLine(std::make_unique<ContactLine>(name, email));
    }
};