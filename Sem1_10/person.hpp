#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

class Person {
protected:
    std::string name;

public:
    Person();
    explicit Person(const std::string& personName);
    virtual ~Person();
    
    virtual void print() const;
    std::string getName() const;
};

#endif