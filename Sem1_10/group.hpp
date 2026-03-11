#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Student;

class Group {
private:
    std::string groupName;
    std::vector<Student*> students;

public:
    Group();
    explicit Group(const std::string& name);
    
    void addStudent(Student* student);
    void removeStudent(int index);
    void removeStudentByName(const std::string& name);
    
    double calculateGroupAverage() const;
    void print() const;
    
    const std::vector<Student*>& getStudents() const;
    std::string getGroupName() const;
};

#endif