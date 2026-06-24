#pragma once
#include <iostream>
#include <string>

class Line {
public:
    virtual ~Line() = default;
	virtual std::string serialize() const = 0;
};

class Text : public Line {
private:
    std::string text;
public:
	std::string serialize() const override { 
		return "text:" + text; 
	}
};
 
class Checklist : public Line {
private:
    std::string task;
	bool checked;
public:
	std::string serialize() const override { 
		return "checklist:" + checked ? "1 ," : "0 ," + task; 
	}
};

class Contact : public Line {
private:
    std::string name;
    std::string email;
public:
	std::string serialize() const override { 
		return "contact:" + name + "," + email;
	}
};