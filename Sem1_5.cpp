#include <iostream>
#include <vector>
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
    
    int N, M;
    std::cout << "Введите количество студентов: ";
    std::cin >> N;
    std::cout << "Введите количество предметов: ";
    std::cin >> M;
    
    std::vector<std::vector<double>> grades(N, std::vector<double>(M));
    
    std::cout << "\n--- Ввод оценок ---\n";
    for (int i = 0; i < N; i++) {
        std::cout << "\nСтудент " << i + 1 << ":\n";
        for (int j = 0; j < M; j++) {
            std::cout << "Предмет " << j + 1 << ": ";
            std::cin >> grades[i][j];
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
            file.write(reinterpret_cast<char*>(&grades[i][j]), sizeof(double));
        }
    }
    
    file.close();
    std::cout << "Данные сохранены в файл " << filename << std::endl;
    
    std::ifstream infile(filename, std::ios::binary);
    
    FileHeader header2;
    infile.read(reinterpret_cast<char*>(&header2), sizeof(FileHeader));
    
    if (strncmp(header2.signature, "GRADES5", 8) == 0) {
        std::cout << "Сигнатура корректна\n";
        
        int M2;
        infile.read(reinterpret_cast<char*>(&M2), sizeof(int));
        
        std::vector<std::vector<double>> grades2(header2.studentCount, std::vector<double>(M2));
        
        for (int i = 0; i < header2.studentCount; i++) {
            for (int j = 0; j < M2; j++) {
                infile.read(reinterpret_cast<char*>(&grades2[i][j]), sizeof(double));
            }
        }
        
        std::cout << "Данные успешно прочитаны\n";
    } else {
        std::cout << "Неверная сигнатура файла\n";
    }
    
    infile.close();
    
    return 0;
}