#include <iostream>
#include <thread>
#include <chrono>

int main() {
    int N;
    std::cout << "Введите количество секунд: ";
    std::cin >> N;

    for (int i = N; i > 0; --i) {
        std::cout << "Осталось: " << i << " секунд" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Время вышло!" << std::endl;
    return 0;
}