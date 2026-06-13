#include "IPrint.h"

IPrint::IPrint(std::string msg, SymbolTable& symbolTable, Logger& logger) 
    : msg(std::move(msg)), symbolTable(symbolTable), logger(logger) {}

void IPrint::execute() {
    std::string log;

    auto now = std::chrono::system_clock::now();

    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm tm{};

    #ifdef _WIN32
        localtime_s(&tm, &t);
    #else
        localtime_r(&t, &tm);
    #endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%m/%d/%Y %I:%M:%S%p");

    if (symbolTable.contains(msg)) {
        log = "Value from " + msg + " = " + std::to_string(symbolTable[msg]);
        // std::cout << "Pointer: " << &symbolTable[msg] << std::endl;
    } else {
        log = msg;
    }

    logger.emplace_back(oss.str(), log);
}