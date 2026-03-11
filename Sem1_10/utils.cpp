#include "utils.hpp"
#include "student.hpp"
#include "file_header.hpp"

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
    if (studentAverages.empty()) return -1;
    
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

bool saveToFile(const std::string& filename, const std::vector<Student*>& students, int M) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Ошибка открытия файла\n";
        return false;
    }
    
    FileHeader header;
    strncpy(header.signature, "GRADES5", 8);
    header.version = 1;
    header.studentCount = students.size();
    
    file.write(reinterpret_cast<char*>(&header), sizeof(FileHeader));
    file.write(reinterpret_cast<char*>(&M), sizeof(int));
    
    for (const auto& student : students) {
        for (double grade : student->getGrades()) {
            file.write(reinterpret_cast<char*>(&grade), sizeof(double));
        }
    }
    
    file.close();
    std::cout << "Данные сохранены в файл " << filename << std::endl;
    return true;
}