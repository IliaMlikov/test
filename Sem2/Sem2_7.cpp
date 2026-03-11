#include <iostream>
#include <vector>
#include <string>

class VirtualThread {
private:
    std::vector<std::string> tasks;
    size_t currentIndex;
    int id;

public:
    VirtualThread(int threadId, const std::vector<std::string>& taskList)
        : tasks(taskList), currentIndex(0), id(threadId) {}

    bool runNextTask() {
        if (currentIndex < tasks.size()) {
            std::string task = tasks[currentIndex];
            std::cout << "Виртуальный поток " << id << " начал " << task << std::endl;
            std::cout << "Виртуальный поток " << id << " закончил " << task << std::endl;
            currentIndex++;
            return true;
        }
        return false;
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread vt1;
    VirtualThread vt2;

public:
    HyperThreadingSimulator(const std::vector<std::string>& tasks1, const std::vector<std::string>& tasks2)
        : vt1(1, tasks1), vt2(2, tasks2) {}

    void execute() {
        bool running1 = true;
        bool running2 = true;

        while (running1 || running2) {
            if (running1) {
                running1 = vt1.runNextTask();
            }
            if (running2) {
                running2 = vt2.runNextTask();
            }
        }
    }
};

int main() {
    std::vector<std::string> tasks1 = {"Задача A", "Задача C"};
    std::vector<std::string> tasks2 = {"Задача B", "Задача D"};

    HyperThreadingSimulator simulator(tasks1, tasks2);
    simulator.execute();

    return 0;
}