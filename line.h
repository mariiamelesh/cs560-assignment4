#pragma once

class Line {
public:
    virtual ~Line() = default;

};

class Text : public Line {

};

class Checklist : public Line {

};

class Contact : public Line {

};