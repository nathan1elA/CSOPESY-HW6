#pragma once

#include "globals.h"
#include "ProcessInstructions.h"

using InstructionQueue = std::queue<std::unique_ptr<Instruction>>;

class Process {
    public:
        Process(uint32_t processId, std::string name, uint8_t coreNumber);
        ~Process() = default;

        void executeInstruction();
        void displayLog();
        bool isFinished();

        uint32_t getProcessId();
        std::string getProcessName();
        uint32_t getInstructionSize();
        uint32_t getLineNumber();

    private:
        void generateInstructions();

        uint32_t processId;
        std::string name;
        uint8_t coreNumber;

        std::atomic<uint32_t> lineNumber = 1;
        uint8_t sleepCounter;
        bool isLooping = 0;

        std::unique_ptr<InstructionQueue> instructions;
        std::unique_ptr<SymbolTable> symbolTable;
        std::unique_ptr<Logger> logger;

        std::shared_mutex mtx;
};