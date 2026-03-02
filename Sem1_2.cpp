#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
 
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
    
    return 0;
}