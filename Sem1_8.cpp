#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <cstring>

#pragma pack(push, 1)
struct FileHeader {
    char signature[8];
    int version;
    int studentCount;
};
#pragma pack(pop)

class RecordBook {
private:
    std::string bookNumber;
    std::vector<double> grades;

public:
    RecordBook() : bookNumber("000000") {}
    
    RecordBook(const std::string& number) : bookNumber(number) {}
    
    RecordBook(const std::string& number, const std::vector<double>& studentGrades) 
        : bookNumber(number), grades(studentGrades) {}
    
    void addGrade(double grade) {
        if (grade >= 0 && grade <= 5) {
            grades.push_back(grade);
        }
    }
    
    double calculateAverage() const {
        if (grades.empty()) return 0.0;
        double sum = 0.0;
        for (double grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
    
    void print() const {
        std::cout << "Номер зачётной книжки: " << bookNumber << std::endl;
        std::cout << "Оценки: ";
        for (size_t i = 0; i < grades.size(); i++) {
            std::cout << grades[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Средний балл: " << std::fixed << std::setprecision(2) 
                  << calculateAverage() << std::endl;
    }
    
    std::string getBookNumber() const { return bookNumber; }
    const std::vector<double>& getGrades() const { return grades; }
};

class Person {
protected:
    std::string name;

public:
    Person() : name("Неизвестный") {}
    
    Person(const std::string& personName) : name(personName) {}
    
    virtual ~Person() {}
    
    virtual void print() const {
        std::cout << "Имя: " << name << std::endl;
    }
    
    std::string getName() const { return name; }
};

class Student : public Person {
private:
    RecordBook recordBook;

public:
    Student() : Person("Неизвестный"), recordBook() {}
    
    Student(const std::string& studentName, const std::string& bookNumber) 
        : Person(studentName), recordBook(bookNumber) {}
    
    Student(const std::string& studentName, const std::string& bookNumber, 
            const std::vector<double>& grades) 
        : Person(studentName), recordBook(bookNumber, grades) {}
    
    void addGrade(double grade) {
        recordBook.addGrade(grade);
    }
    
    double calculateAverage() const {
        return recordBook.calculateAverage();
    }
    
    void print() const override {
        std::cout << "Студент: " << name << std::endl;
        recordBook.print();
    }
    
    std::string getBookNumber() const { return recordBook.getBookNumber(); }
    const std::vector<double>& getGrades() const { return recordBook.getGrades(); }
};

class Teacher : public Person {
public:
    Teacher() : Person("Неизвестный") {}
    
    Teacher(const std::string& teacherName) : Person(teacherName) {}
    
    void print() const override {
        std::cout << "Преподаватель: " << name << std::endl;
    }
};

double inputGrade(int studentNum, int subjectNum) {
    double grade;
    std::cout << "Студент " << studentNum + 1 << ", предмет " << subjectNum + 1 << ": ";
    std::cin >> grade;
    return grade;
}

std::vector<double> calculateStudentAverages(const std::vector<Student*>& students) {
    std::vector<double> averages;
    for (const auto& student : students) {
        averages.push_back(student->calculateAverage());
    }
    return averages;
}

std::vector<double> calculateSubjectAverages(const std::vector<Student*>& students, int M) {
    std::vector<double> averages(M, 0.0);
    
    for (int j = 0; j < M; j++) {
        double sum = 0.0;
        for (const auto& student : students) {
            sum += student->getGrades()[j];
        }
        averages[j] = sum / students.size();
    }
    
    return averages;
}

int findStudentWithMaxAverage(const std::vector<double>& studentAverages) {
    int maxIndex = 0;
    double maxAverage = studentAverages[0];
    
    for (size_t i = 1; i < studentAverages.size(); i++) {
        if (studentAverages[i] > maxAverage) {
            maxAverage = studentAverages[i];
            maxIndex = i;
        }
    }
    
    return maxIndex;
}

int main() {
    std::cout << "=== Система учёта ===\n";
    
    std::vector<Person*> people;
    
    people.push_back(new Teacher("Иванов И.И."));
    people.push_back(new Teacher("Петрова П.П."));
    people.push_back(new Teacher("Сидоров С.С."));
    
    int N, M;
    std::cout << "\nВведите количество студентов: ";
    std::cin >> N;
    std::cout << "Введите количество предметов: ";
    std::cin >> M;
    
    std::vector<Student*> students;
    
    for (int i = 0; i < N; i++) {
        std::string name;
        std::string bookNumber;
        
        std::cout << "\nВведите имя студента " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Введите номер зачётной книжки: ";
        std::cin >> bookNumber;
        
        Student* student = new Student(name, bookNumber);
        students.push_back(student);
        people.push_back(student);
        
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
    
    const std::vector<double> studentAverages = calculateStudentAverages(students);
    
    std::cout << "\n--- Средние баллы студентов ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << students[i]->getName() << " (№" << students[i]->getBookNumber() << "): " 
                  << std::fixed << std::setprecision(2) << studentAverages[i] << std::endl;
    }
    
    const std::vector<double> subjectAverages = calculateSubjectAverages(students, M);
    
    std::cout << "\n--- Средние баллы по предметам ---\n";
    for (int j = 0; j < M; j++) {
        std::cout << "Предмет " << j + 1 << ": " 
                  << std::fixed << std::setprecision(2) << subjectAverages[j] << std::endl;
    }
    
    const int bestStudentIndex = findStudentWithMaxAverage(studentAverages);
    
    std::cout << "\n--- Лучший студент ---\n";
    std::cout << students[bestStudentIndex]->getName()
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
        std::cout << place++ << ". " << students[student.first]->getName()
                  << " (№" << students[student.first]->getBookNumber() << ") - " 
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
            std::cout << "  " << students[student.first]->getName() 
                      << " (№" << students[student.first]->getBookNumber() << "): " 
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
    
    std::ofstream file(filename, std::ios::binary);
    
    FileHeader header;
    strncpy(header.signature, "GRADES5", 8);
    header.version = 1;
    header.studentCount = N;
    
    file.write(reinterpret_cast<char*>(&header), sizeof(FileHeader));
    file.write(reinterpret_cast<char*>(&M), sizeof(int));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            double grade = students[i]->getGrades()[j];
            file.write(reinterpret_cast<char*>(&grade), sizeof(double));
        }
    }
    
    file.close();
    std::cout << "Данные сохранены в файл " << filename << std::endl;
    
    for (auto person : people) {
        delete person;
    }
    
    return 0;
}