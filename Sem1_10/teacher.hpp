#ifndef TEACHER_HPP
#define TEACHER_HPP

#include "person.hpp"
#include <string>

class Teacher : public Person {
public:
    Teacher();
    explicit Teacher(const std::string& teacherName);
    void print() const override;
};

#endif