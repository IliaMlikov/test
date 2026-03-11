#include "record_book.hpp"

RecordBook::RecordBook() : bookNumber("000000") {}

RecordBook::RecordBook(const std::string& number) : bookNumber(number) {}

RecordBook::RecordBook(const std::string& number, const std::vector<double>& studentGrades) 
    : bookNumber(number), grades(studentGrades) {}

void RecordBook::addGrade(double grade) {
    if (grade >= 0 && grade <= 5) {
        grades.push_back(grade);
    }
}

double RecordBook::calculateAverage() const {
    if (grades.empty()) return 0.0;
    double sum = 0.0;
    for (double grade : grades) {
        sum += grade;
    }
    return sum / grades.size();
}

void RecordBook::print() const {
    std::cout << "Номер зачётной книжки: " << bookNumber << std::endl;
    std::cout << "Оценки: ";
    for (size_t i = 0; i < grades.size(); i++) {
        std::cout << grades[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Средний балл: " << std::fixed << std::setprecision(2) 
              << calculateAverage() << std::endl;
}

std::string RecordBook::getBookNumber() const { return bookNumber; }

const std::vector<double>& RecordBook::getGrades() const { return grades; }