#pragma once
#include <string>

class Line {
public:
    virtual ~Line() = default;
    virtual void print(bool hasCursor, int cursorIndex) const = 0;
    virtual std::string serialize() const = 0;
};

class TextLine : public Line {
private:
    std::string text;
public:
    TextLine(const std::string& t);
    void print(bool hasCursor, int cursorIndex) const override;
    std::string serialize() const override;
    std::string getText() const { 
		return text; 
	}
    void setText(const std::string& newText) { 
		text = newText; 
	}
};

class Checklist : public Line {
private:
    std::string task;
	bool checked;
public:
    Checklist(const std::string& t, bool checked = false);
    void print(bool hasCursor, int cursorIndex) const override;
    std::string serialize() const override;
    void toggle();
};

class Contact : public Line {
private:
    std::string name;
    std::string email;
public:
    Contact(const std::string& n, const std::string& em);
    void print(bool hasCursor, int cursorIndex) const override;
    std::string serialize() const override;
};