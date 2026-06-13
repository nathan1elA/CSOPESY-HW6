#include "MainConsole.h"
#include "ConsoleManager.h"

MainConsole::MainConsole() {
    commands = {
        { "initialize", [this](const auto& args) { 
            if (!args.empty()) {
                std::cerr << "Error: initialize takes no arguments." << std::endl;
                return;
            }

            MainConsole::initialize(); 
        }},

        { "screen", [this](const auto& args) { 
            if (args.empty()) {
                std::cerr << "Error: Please provide arguments for screen." << std::endl;
                return;
            }

            if (args[0] == "-s") {
                if (args.size() != 2) {
                    std::cerr << "Error: Invalid arguments for screen -s." << std::endl;
                    return;
                }

                Scheduler::getInstance()->generateSingleProcess(args[1]);
                
            } else if (args[0] == "-r") {
                if (args.size() != 2) {
                    std::cerr << "Error: Invalid arguments for screen -r." << std::endl;
                    return;
                }

                ConsoleManager::getInstance()->switchConsole(args[1]);
                
            } else if (args[0] == "-ls") {
                if (args.size() != 1) {
                    std::cerr << "Error: Invalid arguments for screen -ls." << std::endl;
                    return;
                }

                // add behavior here
            }
        }},

        { "scheduler-start", [this](const auto& args) { 
            if (!args.empty()) {
                std::cerr << "Error: scheduler-start takes no arguments." << std::endl;
                return;
            }

            std::cout << "scheduler-start command recognized. Doing something.\n"; 
        }},

        { "scheduler-stop", [this](const auto& args) { 
            if (!args.empty()) {
                std::cerr << "Error: scheduler-stop takes no arguments." << std::endl;
                return;
            }
            
            std::cout << "scheduler-stop command recognized. Doing something.\n"; 
        }},

        { "report-util", [this](const auto& args) { 
            if (!args.empty()) {
                std::cerr << "Error: report-util takes no arguments." << std::endl;
                return;
            }
            
            std::cout << "report-util command recognized. Doing something.\n";
        }},

        { "clear", [this](const auto& args) { 
            if (!args.empty()) {
                std::cerr << "Error: clear takes no arguments." << std::endl;
                return;
            }
            
            std::cout << "\033[2J\033[H"; display(); 
        }},

        { "exit", [this](const auto& args) {
            if (!args.empty()) {
                std::cerr << "Error: exit takes no arguments." << std::endl;
                return;
            }
            
            std::cout << "Exiting...\n";
            ConsoleManager::getInstance()->terminate(); 
            running = false; 
        }},
    };
}

void MainConsole::run() {
    std::string cmd;
    
    std::cout << "\033[2J\033[H";
    display();

    while(running) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, cmd);
        executeCommand(cmd);
    }
}

void MainConsole::setRunning(bool running) {
    this->running = running;
}

void MainConsole::display() {
    // ASCII Art Generator: https://patorjk.com/software/taag/
    std::cout << R"( _____  _____  ___________ _____ _______   __)" << std::endl
              << R"(/  __ \/  ___||  _  | ___ \  ___/  ___\ \ / /)" << std::endl
              << R"(| /  \/\ `--. | | | | |_/ / |__ \ `--. \ V /)" << std::endl
              << R"(| |     `--. \| | | |  __/|  __| `--. \ \ /)" << std::endl
              << R"(| \__/\/\__/ /\ \_/ / |   | |___/\__/ / | |)" << std::endl
              << R"( \____/\____/  \___/\_|   \____/\____/  \_/)" << std::endl
              << "----------------------------------------------" << std::endl
              << "Welcome to CSOPESY Emulator!                  " << std::endl
              << "                                              " << std::endl
              << "Developers:                                   " << std::endl
              << "Adiong, Nathaniel Irvin L.                    " << std::endl
              << "Ang, Clarence Ivan C.                         " << std::endl
              << "Go, Kenneth D.                                " << std::endl
              << "Trocino, Job D.                               " << std::endl
              << "                                              " << std::endl
              << "Last updated: 06-14-2026                      " << std::endl
              << "----------------------------------------------" << std::endl              
              ;
}

void MainConsole::executeCommand(const std::string& cmd) {
    if (!initializeFlag && cmd != "initialize" && cmd != "exit") {
        std::cerr << "Error: Please run 'initialize' first.\n";
        return;
    }

    std::istringstream iss(cmd);
    std::vector<std::string> tokens;
    std::string word;

    while (iss >> word) {
        tokens.push_back(word);
    }

    if (tokens.empty()) return;

    std::string cmdToken = tokens[0];

    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    auto it = commands.find(cmdToken);
    if (it != commands.end()) {
        it->second(args);
    } else {
        std::cerr << "Error: Command \'" << cmdToken << "\' not recognized." << std::endl;
    }
}

void MainConsole::initialize() {
    std::ifstream file("config.txt");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open config.txt\n";
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string key, value;

        if (ss >> key >> value) {
            if (key == "num-cpu") config.numCpu = std::stoi(value);
            if (key == "scheduler") {
                if (value == "\"fcfs\"") config.schedulerType = FCFS;
                if (value == "\"rr\"") config.schedulerType = RR;
            }
            if (key == "quantum-cycles") config.quantumCycles = std::stoi(value);
            if (key == "batch-process-freq") config.batchProcessFreq = std::stoi(value);
            if (key == "min-ins") config.minIns = std::stoi(value);
            if (key == "max-ins") config.maxIns = std::stoi(value);
            if (key == "delays-per-exec") config.delaysPerExec = std::stoi(value);
        }
    }

    initializeFlag = true;
}