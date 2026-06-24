#include <fstream>
#include "line.h"
#include "text.h"
#include "state.h"
class TextEditor {
    Text doc;
    Cursor cursor;
    History history;
    std::string clipboard;
};