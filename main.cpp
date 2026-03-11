#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

#include "person.hpp"
#include "student.hpp"
#include "teacher.hpp"
#include "group.hpp"
#include "utils.hpp"
#include "file_header.hpp"

int main() {
    std::cout << "=== Система учёта ===\n";
    
    std::vector<Person*> people;
    
    std::cout << "\n--- Добавление преподавателей ---\n";
    people.push_back(new Teacher("Иванов И.И."));
    people.push_back(new Teacher("Петрова П.П."));
    people.push_back(new Teacher("Сидоров С.С."));
    
    int N, M;
    std::cout << "\nВведите количество студентов: ";
    std::cin >> N;
    std::cout << "Введите количество предметов: ";
    std::cin >> M;
    
    std::string groupName;
    std::cout << "Введите название группы: ";
    std::cin >> groupName;
    
    Group group(groupName);
    std::vector<Student*> allStudents;
    
    for (int i = 0; i < N; i++) {
        std::string name;
        std::string bookNumber;
        
        std::cout << "\nВведите имя студента " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Введите номер зачётной книжки: ";
        std::cin >> bookNumber;
        
        Student* student = new Student(name, bookNumber);
        allStudents.push_back(student);
        people.push_back(student);
        group.addStudent(student);
        
        std::cout << "Ввод оценок для " << name << ":\n";
        for (int j = 0; j < M; j++) {
            double grade = inputGrade(i, j);
            student->addGrade(grade);
        }
    }
    
    std::cout << "\n=== ВСЕ ЛЮДИ ===\n";
    for (const auto& person : people) {
        person->print();
        std::cout << std::endl;
    }
    
    group.print();
    std::cout << std::endl;
    
    std::vector<double> studentAverages = calculateStudentAverages(allStudents);
    
    std::cout << "\n--- Средние баллы студентов ---\n";
    for (size_t i = 0; i < allStudents.size(); i++) {
        std::cout << allStudents[i]->getName() << " (№" << allStudents[i]->getBookNumber() << "): " 
                  << std::fixed << std::setprecision(2) << studentAverages[i] << std::endl;
        
        if (allStudents[i]->hasGrades()) {
            std::cout << "  (есть оценки)\n";
        }
    }
    
    std::vector<double> subjectAverages = calculateSubjectAverages(allStudents, M);
    
    std::cout << "\n--- Средние баллы по предметам ---\n";
    for (int j = 0; j < M; j++) {
        std::cout << "Предмет " << j + 1 << ": " 
                  << std::fixed << std::setprecision(2) << subjectAverages[j] << std::endl;
    }
    
    int bestStudentIndex = findStudentWithMaxAverage(studentAverages);
    
    std::cout << "\n--- Лучший студент ---\n";
    std::cout << allStudents[bestStudentIndex]->getName()
              << " имеет максимальный средний балл: " 
              << std::fixed << std::setprecision(2) 
              << studentAverages[bestStudentIndex] << std::endl;
    
    std::vector<std::pair<int, double>> studentList;
    
    for (size_t i = 0; i < studentAverages.size(); i++) {
        studentList.push_back({static_cast<int>(i), studentAverages[i]});
    }
    
    std::cout << "\n=== СОРТИРОВКА СТУДЕНТОВ ПО СРЕДНЕМУ БАЛЛУ ===\n";
    
    std::sort(studentList.begin(), studentList.end(), 
        [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            } else {
                return a.first < b.first;
            }
        });
    
    std::cout << "\nОтсортированный список:\n";
    int place = 1;
    for (const auto& student : studentList) {
        std::cout << place++ << ". " << allStudents[student.first]->getName()
                  << " (№" << allStudents[student.first]->getBookNumber() << ") - " 
                  << std::fixed << std::setprecision(2) 
                  << student.second << std::endl;
    }
    
    std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";
    
    double threshold;
    std::cout << "Введите порог для удаления студентов: ";
    std::cin >> threshold;
    
    auto newEnd = std::remove_if(studentList.begin(), studentList.end(), 
        [threshold](const std::pair<int, double>& student) {
            return student.second < threshold;
        });
    
    studentList.erase(newEnd, studentList.end());
    
    std::cout << "\nСтуденты после фильтрации:\n";
    if (studentList.empty()) {
        std::cout << "  Список пуст\n";
    } else {
        for (const auto& student : studentList) {
            std::cout << "  " << allStudents[student.first]->getName() 
                      << " (№" << allStudents[student.first]->getBookNumber() << "): " 
                      << student.second << std::endl;
        }
    }
    
    int excellentCount = 0;
    int lowCount = 0;
    
    for (const auto& student : studentList) {
        if (student.second >= 4.5) {
            excellentCount++;
        }
        if (student.second < 3.0) {
            lowCount++;
        }
    }
    
    std::cout << "\n--- Статистика ---\n";
    std::cout << "Количество отличников (балл >= 4.5): " << excellentCount << std::endl;
    std::cout << "Количество студентов, близких к отчислению (балл < 3.0): " << lowCount << std::endl;
    
    std::cout << "\n=== РАБОТА С ФАЙЛОМ ===\n";
    
    std::cout << "Размер структуры FileHeader: " << sizeof(FileHeader) << " байт\n";
    
    std::string filename;
    std::cout << "Введите имя файла для сохранения: ";
    std::cin >> filename;
    
    saveToFile(filename, allStudents, M);
    
    std::cout << "\n=== ДЕМОНСТРАЦИЯ АГРЕГАЦИИ ===\n";
    std::cout << "Хотите удалить студента? (y/n): ";
    char action;
    std::cin >> action;
    
    if (action == 'y' || action == 'Y') {
        group.print();
        
        std::cout << "Введите имя студента для удаления: ";
        std::string name;
        std::cin >> name;
        
        group.removeStudentByName(name);
        
        std::cout << "\n=== ГРУППА ПОСЛЕ УДАЛЕНИЯ ===\n";
        group.print();
    }
    
    for (auto person : people) {
        delete person;
    }
    
    return 0;
}