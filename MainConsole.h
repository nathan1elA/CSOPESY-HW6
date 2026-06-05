#pragma once

#include "Console.h"
#include "globals.h"

class MainConsole : public Console {
    public:
        MainConsole();
        ~MainConsole() = default;

        void run() override;
    private:
        bool initializeFlag = false;

        void executeCommand(std::string cmd) override;
        void display();
        void initialize();
        
        bool running = false;
};