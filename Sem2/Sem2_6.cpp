#include <iostream>

class VirtualThread {
private:
    int* numbers;
    int size;
    int currentIndex;

public:
    VirtualThread(int arr[], int n) : numbers(arr), size(n), currentIndex(0) {}

    bool run() {
        if (currentIndex < size) {
            int num = numbers[currentIndex];
            long long fact = 1;
            for (int i = 1; i <= num; ++i) {
                fact *= i;
            }
            std::cout << "Виртуальный поток " << (this == thread1 ? 1 : 2) << " вычисляет " << num << "! = " << fact << std::endl;
            currentIndex++;
            return true;
        }
        return false;
    }

    void setThreadId(VirtualThread* t1, VirtualThread* t2) {
        thread1 = t1;
        thread2 = t2;
    }

private:
    static VirtualThread* thread1;
    static VirtualThread* thread2;
};

VirtualThread* VirtualThread::thread1 = nullptr;
VirtualThread* VirtualThread::thread2 = nullptr;

class HyperThreadingSimulator {
private:
    VirtualThread vt1;
    VirtualThread vt2;

public:
    HyperThreadingSimulator(int arr1[], int size1, int arr2[], int size2)
        : vt1(arr1, size1), vt2(arr2, size2) {
        vt1.setThreadId(&vt1, &vt2);
        vt2.setThreadId(&vt1, &vt2);
    }

    void execute() {
        bool running1 = true;
        bool running2 = true;
        while (running1 || running2) {
            if (running1) {
                running1 = vt1.run();
            }
            if (running2) {
                running2 = vt2.run();
            }
        }
    }
};

int main() {
    int nums1[] = {5, 10};
    int nums2[] = {7, 12};

    HyperThreadingSimulator simulator(nums1, 2, nums2, 2);
    simulator.execute();

    return 0;
}