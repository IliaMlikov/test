#include "teacher.hpp"

Teacher::Teacher() : Person("Неизвестный") {}

Teacher::Teacher(const std::string& teacherName) : Person(teacherName) {}

void Teacher::print() const {
    std::cout << "Преподаватель: " << name << std::endl;
}