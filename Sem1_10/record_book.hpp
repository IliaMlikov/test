#ifndef RECORD_BOOK_HPP
#define RECORD_BOOK_HPP

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class RecordBook {
private:
    std::string bookNumber;
    std::vector<double> grades;

public:
    RecordBook();
    explicit RecordBook(const std::string& number);
    RecordBook(const std::string& number, const std::vector<double>& studentGrades);
    
    void addGrade(double grade);
    double calculateAverage() const;
    void print() const;
    
    std::string getBookNumber() const;
    const std::vector<double>& getGrades() const;
    
    inline bool hasGrades() const {
        return !grades.empty();
    }
};

#endif