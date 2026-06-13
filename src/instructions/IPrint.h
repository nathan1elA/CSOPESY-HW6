#pragma once

#include "Instruction.h"

class IPrint : public Instruction {
    public:
        IPrint(std::string msg, SymbolTable& symbolTable, Logger& logger);

        void execute() override;
    private:
        std::string msg;
        
        SymbolTable& symbolTable;
        Logger& logger;
};