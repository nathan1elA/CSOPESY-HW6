#include "Process.h"

Process::Process(uint32_t processId, std::string name, uint8_t coreNumber) {
    this->processId = processId;
    this->name = name;
    this->coreNumber = coreNumber;

    instructions = std::make_unique<InstructionQueue>();
    symbolTable = std::make_unique<SymbolTable>();
    logger = std::make_unique<Logger>();

    generateInstructions();
}

void Process::executeInstruction() {
    std::unique_lock lock(mtx);
    instructions->front()->execute();

    // checks whether instruction is FOR or SLEEP and is still running before removing the instruction
    if (!instructions->front()->isLooping()) {
        instructions->pop();
        lineNumber++;
    }
}

void Process::displayLog() {
    std::shared_lock lock(mtx);
    std::cout << "Logs:" << std::endl;
    for (const auto& log : *logger) {
        std::cout << "(" << std::get<0>(log) << ") Core:" << static_cast<int>(coreNumber) << " \"" << std::get<1>(log) << "\"" << std::endl;
    }
}

bool Process::isFinished() {
    std::shared_lock lock(mtx);
    return instructions->empty();
}

uint32_t Process::getProcessId() {
    return processId;
}

std::string Process::getProcessName() {
    return name;
}

uint32_t Process::getInstructionSize() {
    return instructions->size();
}

uint32_t Process::getLineNumber() {
    return lineNumber;
}

void Process::generateInstructions() {
    // temporary, replace with actual implementation later
    symbolTable->emplace("var1", 0);
    symbolTable->emplace("var2", 0);
    symbolTable->emplace("var3", 0);
    symbolTable->emplace("var4", 0);
    symbolTable->emplace("var5", 0);
    symbolTable->emplace("var6", 0);
    
    instructions->push(std::make_unique<IPrint>("Hello world from " + name + "!", *symbolTable, *logger));
    instructions->push(std::make_unique<IDeclare>(symbolTable->at("var1"), 5));
    instructions->push(std::make_unique<IDeclare>(symbolTable->at("var2"), 10));
    instructions->push(std::make_unique<IDeclare>(symbolTable->at("var3"), 2));
    instructions->push(std::make_unique<IAdd>(symbolTable->at("var4"), symbolTable->at("var1"), symbolTable->at("var2")));
    instructions->push(std::make_unique<ISubtract>(symbolTable->at("var5"), symbolTable->at("var2"), symbolTable->at("var3")));
    instructions->push(std::make_unique<IPrint>("var4", *symbolTable, *logger));
    instructions->push(std::make_unique<IPrint>("var5", *symbolTable, *logger));
    instructions->push(std::make_unique<ISleep>(10));

    std::unique_ptr<ForLoop> forLoop1 = std::make_unique<ForLoop>();
    std::unique_ptr<ForLoop> forLoop2 = std::make_unique<ForLoop>();

    forLoop1->push_back(std::make_unique<IAdd>(symbolTable->at("var6"), symbolTable->at("var6"), symbolTable->at("var1")));
    forLoop1->push_back(std::make_unique<IPrint>("var6", *symbolTable, *logger));
    forLoop2->push_back(std::make_unique<IFor>(std::move(forLoop1), 2));
    
    instructions->push(std::make_unique<IFor>(std::move(forLoop2), 3));
}

/*
    PRINT(msg)
    DECLARE(var1, 5)
    DECLARE(var2, 10)
    DECLARE(var3, 2)
    ADD(var4, var1, var2)
    SUBTRACT(var5, var2, var3)
    PRINT(var4)
    PRINT(var5)
    SLEEP(10)
    FOR([FOR([ADD(var6, var6, var1)], 2), PRINT(var6)]3)
*/