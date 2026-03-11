#include "student.hpp"

Student::Student() : Person("Неизвестный"), recordBook() {}

Student::Student(const std::string& studentName, const std::string& bookNumber) 
    : Person(studentName), recordBook(bookNumber) {}

Student::Student(const std::string& studentName, const std::string& bookNumber, 
        const std::vector<double>& grades) 
    : Person(studentName), recordBook(bookNumber, grades) {}

void Student::addGrade(double grade) {
    recordBook.addGrade(grade);
}

double Student::calculateAverage() const {
    return recordBook.calculateAverage();
}

void Student::print() const {
    std::cout << "Студент: " << name << std::endl;
    recordBook.print();
}

std::string Student::getBookNumber() const { return recordBook.getBookNumber(); }

const std::vector<double>& Student::getGrades() const { return recordBook.getGrades(); }

bool Student::hasGrades() const { return recordBook.hasGrades(); }