#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "person.hpp"
#include "record_book.hpp"
#include <string>
#include <vector>

class Student : public Person {
private:
    RecordBook recordBook;

public:
    Student();
    explicit Student(const std::string& studentName, const std::string& bookNumber);
    Student(const std::string& studentName, const std::string& bookNumber, 
            const std::vector<double>& grades);
    
    void addGrade(double grade);
    double calculateAverage() const;
    void print() const override;
    
    std::string getBookNumber() const;
    const std::vector<double>& getGrades() const;
    bool hasGrades() const;
};

#endif