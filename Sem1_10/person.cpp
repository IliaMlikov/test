#include "person.hpp"

Person::Person() : name("Неизвестный") {}

Person::Person(const std::string& personName) : name(personName) {}

Person::~Person() {}

void Person::print() const {
    std::cout << "Имя: " << name << std::endl;
}

std::string Person::getName() const { return name; }