#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>

class Task {
public:
    int value;
    int priority;
    int duration_ms;
    int steps;
    int currentStep;

    Task(int v, int p, int d, int s) : value(v), priority(p), duration_ms(d), steps(s), currentStep(0) {}

    bool isCompleted() const {
        return currentStep >= steps;
    }

    void executeStep() {
        currentStep++;
        int stepDuration = duration_ms / steps;
        std::this_thread::sleep_for(std::chrono::milliseconds(stepDuration));
    }

    int getResult() const {
        return value * value;
    }
};

class VirtualThread {
private:
    std::vector<Task> tasks;
    int id;

public:
    VirtualThread(int threadId) : id(threadId) {}

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    bool hasTasks() const {
        return !tasks.empty();
    }

    void runStep() {
        if (tasks.empty()) return;

        auto highestPriority = std::max_element(tasks.begin(), tasks.end(),
            [](const Task& a, const Task& b) {
                return a.priority < b.priority;
            });

        int oldStep = highestPriority->currentStep;
        highestPriority->executeStep();
        
        std::cout << "Виртуальный поток " << id
                  << " выполняет шаг " << highestPriority->currentStep
                  << "/" << highestPriority->steps
                  << " задачи " << highestPriority->value
                  << " с приоритетом " << highestPriority->priority << std::endl;

        if (highestPriority->isCompleted()) {
            std::cout << "Виртуальный поток " << id
                      << " завершил задачу " << highestPriority->value
                      << ": результат = " << highestPriority->getResult() << std::endl;
            tasks.erase(highestPriority);
        }
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread vt1;
    VirtualThread vt2;

public:
    HyperThreadingSimulator() : vt1(1), vt2(2) {}

    void addTaskToThread(int threadId, const Task& task) {
        if (threadId == 1) {
            vt1.addTask(task);
        } else {
            vt2.addTask(task);
        }
    }

    void execute() {
        while (vt1.hasTasks() || vt2.hasTasks()) {
            if (vt1.hasTasks()) {
                vt1.runStep();
            }
            if (vt2.hasTasks()) {
                vt2.runStep();
            }
        }
    }
};

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> valueDist(1, 50);
    std::uniform_int_distribution<int> priorityDist(1, 10);
    std::uniform_int_distribution<int> durationDist(200, 1000);
    std::uniform_int_distribution<int> stepsDist(2, 5);

    HyperThreadingSimulator simulator;

    for (int i = 0; i < 2; ++i) {
        Task t1(valueDist(gen), priorityDist(gen), durationDist(gen), stepsDist(gen));
        simulator.addTaskToThread(1, t1);

        Task t2(valueDist(gen), priorityDist(gen), durationDist(gen), stepsDist(gen));
        simulator.addTaskToThread(2, t2);
    }

    simulator.execute();

    return 0;
}