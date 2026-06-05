#include "ConsoleManager.h"

int main() {
    ConsoleManager::initialize();
    bool running = true;
    gl_cpuCycles = 0;

    std::thread consoleThread([]() {
        ConsoleManager::getInstance()->run();
    });

    while (running) {
        running = ConsoleManager::getInstance()->isRunning();
        
        gl_cpuCycles++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    consoleThread.join();
    ConsoleManager::destroy();

    std::cout << "CPU Cycles elapsed: " << gl_cpuCycles << std::endl;
    std::cout << "Program stopped successfully.\n";

    return 0;
};