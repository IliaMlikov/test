#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

int inputPositiveInteger(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail() || value <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double inputGrade(int studentNum, int subjectNum) {
    double grade;
    while (true) {
        std::cout << "Студент " << studentNum + 1 << ", предмет " << subjectNum + 1 
                  << " (0-5): ";
        std::cin >> grade;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка\n";
        } else if (grade < 0 || grade > 5) {
            std::cout << "Ошибка\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return grade;
        }
    }
}

std::vector<double> calculateStudentAverages(const std::vector<std::vector<double>>& grades) {
    std::vector<double> averages;
    
    for (size_t i = 0; i < grades.size(); i++) {
        double sum = 0.0;
        for (size_t j = 0; j < grades[i].size(); j++) {
            sum += grades[i][j];
        }
        averages.push_back(sum / grades[i].size());
    }
    
    return averages;
}

std::vector<double> calculateSubjectAverages(const std::vector<std::vector<double>>& grades) {
    size_t numStudents = grades.size();
    size_t numSubjects = grades[0].size();
    std::vector<double> averages(numSubjects, 0.0);
    
    for (size_t j = 0; j < numSubjects; j++) {
        double sum = 0.0;
        for (size_t i = 0; i < numStudents; i++) {
            sum += grades[i][j];
        }
        averages[j] = sum / numStudents;
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
    std::cout << "=== Система учёта оценок студентов ===\n";
    int N = inputPositiveInteger("Введите количество студентов: ");
    int M = inputPositiveInteger("Введите количество предметов: ");
    
    std::vector<std::vector<double>> grades(N, std::vector<double>(M));
    
    std::cout << "\n--- Ввод оценок ---\n";
    for (int i = 0; i < N; i++) {
        std::cout << "\nСтудент " << i + 1 << ":\n";
        for (int j = 0; j < M; j++) {
            grades[i][j] = inputGrade(i, j);
        }
    }
    
    const std::vector<double> studentAverages = calculateStudentAverages(grades);
    
    std::cout << "\n--- Средние баллы студентов ---\n";
    for (size_t i = 0; i < studentAverages.size(); i++) {
        std::cout << "Студент " << i + 1 << ": " 
                  << std::fixed << std::setprecision(2) << studentAverages[i] << std::endl;
    }
    
    const std::vector<double> subjectAverages = calculateSubjectAverages(grades);
    
    std::cout << "\n--- Средние баллы по предметам ---\n";
    for (size_t j = 0; j < subjectAverages.size(); j++) {
        std::cout << "Предмет " << j + 1 << ": " 
                  << std::fixed << std::setprecision(2) << subjectAverages[j] << std::endl;
    }
    
    const int bestStudentIndex = findStudentWithMaxAverage(studentAverages);
    
    std::cout << "\n--- Лучший студент ---\n";
    std::cout << "Студент " << bestStudentIndex + 1 
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
        std::cout << place++ << ". Студент " << student.first + 1 
                  << " - " << std::fixed << std::setprecision(2) 
                  << student.second << std::endl;
    }
    
    std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";
    
    double threshold;
    std::cout << "Введите порог для удаления студентов (будут удалены студенты с баллом ниже ";
    std::cin >> threshold;
    
    auto newEnd = std::remove_if(studentList.begin(), studentList.end(), 
        [threshold](const std::pair<int, double>& student) {
            return student.second < threshold;
        });
    
    studentList.erase(newEnd, studentList.end());
    
    std::cout << "\nСтуденты после фильтрации (удалены с баллом < " << threshold << "):\n";
    if (studentList.empty()) {
        std::cout << "  Список пуст\n";
    } else {
        for (const auto& student : studentList) {
            std::cout << "  Студент " << student.first + 1 << ": " << student.second << std::endl;
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
    
    return 0;
}