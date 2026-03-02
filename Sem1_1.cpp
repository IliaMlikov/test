#include <iostream>
 
double calculateAverage(double* arr, int size) {
    if (size <= 0) return 0.0;
    
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}
 
double findMax(double* arr, int size) {
    if (size <= 0) return 0.0;
    
    double max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
 
double findMin(double* arr, int size) {
    if (size <= 0) return 0.0;
    
    double min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
 
int countAboveThreshold(double* arr, int size, double threshold) {
    if (size <= 0) return 0;
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > threshold) {
            count++;
        }
    }
    return count;
}
 
double inputGrade(int studentNumber) {
    double grade;
    bool validInput = false;
    
    do {
        std::cout << "Введите средний балл студента " << studentNumber + 1 << " (от 0 до 5): ";
        std::cin >> grade;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка\n";
            validInput = false;
        } else if (grade < 0 || grade > 5) {
            std::cout << "Ошибка\n";
            validInput = false;
        } else {
            validInput = true;
        }
    } while (!validInput);
    
    return grade;
}
 
int main() {
    int N;
    
    do {
        std::cout << "Введите количество студентов: ";
        std::cin >> N;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка\n";
            N = 0;
        } else if (N <= 0) {
            std::cout << "Ошибка\n";
        }
    } while (N <= 0);
    
    double* grades = new double[N];
    
    std::cout << "\n--- Ввод оценок ---\n";
    for (int i = 0; i < N; i++) {
        grades[i] = inputGrade(i);
    }
    
    std::cout << "\n--- Результаты ---\n";
    std::cout << "Средний балл группы: " << calculateAverage(grades, N) << std::endl;
    std::cout << "Максимальный балл: " << findMax(grades, N) << std::endl;
    std::cout << "Минимальный балл: " << findMin(grades, N) << std::endl;
    
    double threshold;
    std::cout << "\nВведите пороговое значение для подсчёта студентов: ";
    std::cin >> threshold;
    
    int aboveCount = countAboveThreshold(grades, N, threshold);
    std::cout << "Количество студентов с баллом выше " << threshold << ": " 
              << aboveCount << std::endl;
    
    delete[] grades;
    
    return 0;
}