// 2018 ReVoL Primer Template
// philmeal.h
// Милюков Александр Васильевич
// 363
// КТК
// OS-207
// 17/05/2024
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <chrono>

#define NUM_PHILOSOPHERS 5

std::mutex forks[NUM_PHILOSOPHERS];
std::mutex coutMutex;

void print(const std::string &message) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << message << std::endl;
}

void philosopher(int id, void(*eatFunction)(int)) {
    while (true) {
        // Размышления философа
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        print("Философ " + std::to_string(id) + " хочет покушать.");
        eatFunction(id);
    }
}

void eatDeadlock(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    forks[left].lock();
    print("Философ " + std::to_string(id) + " взял левую вилку.");
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // небольшая задержка для демонстрации deadlock
    forks[right].lock();
    print("Философ " + std::to_string(id) + " взял правую вилку.");
    // Философ ест
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    print("Философ " + std::to_string(id) + " положил вилки.");
    forks[right].unlock();
    forks[left].unlock();
}

void eatLifeLock(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    while (true) {
        forks[left].lock();
        print("Философ " + std::to_string(id) + " взял левую вилку.");
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // небольшая задержка для демонстрации life-lock
        if (forks[right].try_lock()) {
            print("Философ " + std::to_string(id) + " взял правую вилку.");
            // Философ ест
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            print("Философ " + std::to_string(id) + " положил вилки.");
            forks[right].unlock();
            forks[left].unlock();
            break;
        } else {
            print("Философ " + std::to_string(id) + " не смог взять правую вилку и кладет левую вилку обратно.");
            forks[left].unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000)); // ожидание перед повтором
        }
    }
}

void eatCorrect(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    std::unique_lock<std::mutex> leftLock(forks[left], std::defer_lock);
    std::unique_lock<std::mutex> rightLock(forks[right], std::defer_lock);
    std::lock(leftLock, rightLock);
    print("Философ " + std::to_string(id) + " взял обе вилки и кушает.");
    // Философ ест
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    print("Философ " + std::to_string(id) + " положил вилки.");
}

void mainf() {
    std::vector<std::thread> philosophers;
    // Выберите один из вариантов (для теста расскоментить):
    // for (int i = 0; i < NUM_PHILOSOPHERS; ++i) philosophers.emplace_back(philosopher, i, eatDeadlock);
    // for (int i = 0; i < NUM_PHILOSOPHERS; ++i) philosophers.emplace_back(philosopher, i, eatLifeLock);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) philosophers.emplace_back(philosopher, i, eatCorrect);
    for (auto &phil : philosophers) phil.join();
}

int main() {
    mainf();
    return 0;
}