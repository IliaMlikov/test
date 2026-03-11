#include "group.hpp"
#include "student.hpp"

Group::Group() : groupName("Неизвестная группа") {}

Group::Group(const std::string& name) : groupName(name) {}

void Group::addStudent(Student* student) {
    if (student != nullptr) {
        students.push_back(student);
        std::cout << "Студент " << student->getName() << " добавлен в группу\n";
    }
}

void Group::removeStudent(int index) {
    if (index >= 0 && index < static_cast<int>(students.size())) {
        std::cout << "Студент " << students[index]->getName() << " удалён из группы\n";
        students.erase(students.begin() + index);
    } else {
        std::cout << "Неверный индекс\n";
    }
}

void Group::removeStudentByName(const std::string& name) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i]->getName() == name) {
            std::cout << "Студент " << name << " удалён из группы\n";
            students.erase(students.begin() + i);
            return;
        }
    }
    std::cout << "Студент с именем " << name << " не найден\n";
}

double Group::calculateGroupAverage() const {
    if (students.empty()) return 0.0;
    
    double sum = 0.0;
    for (const auto& student : students) {
        sum += student->calculateAverage();
    }
    return sum / students.size();
}

void Group::print() const {
    std::cout << "\n=== Группа: " << groupName << " ===\n";
    std::cout << "Количество студентов: " << students.size() << std::endl;
    std::cout << "Средний балл группы: " << std::fixed << std::setprecision(2) 
              << calculateGroupAverage() << std::endl;
    
    if (!students.empty()) {
        std::cout << "\nСписок студентов:\n";
        for (size_t i = 0; i < students.size(); i++) {
            std::cout << i + 1 << ". " << students[i]->getName() 
                      << " (№" << students[i]->getBookNumber() << ")" << std::endl;
        }
    }
}

const std::vector<Student*>& Group::getStudents() const { return students; }

std::string Group::getGroupName() const { return groupName; }