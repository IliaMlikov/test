#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

class TaskTimer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    long long getDuration() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }

    void measureSorting(std::vector<int>& vec) {
        start();
        std::sort(vec.begin(), vec.end());
        stop();
        std::cout << "Время выполнения сортировки: " << getDuration() << " миллисекунд" << std::endl;
    }
};

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100000);

    TaskTimer timer;

    std::vector<int> vec1(100000);
    for (int& num : vec1) {
        num = dist(gen);
    }
    timer.measureSorting(vec1);

    std::vector<int> vec2(100000);
    for (int& num : vec2) {
        num = dist(gen);
    }
    timer.measureSorting(vec2);

    return 0;
}